/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2014-2016 Dmitry Marakasov <amdmi3@amdmi3.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL2PP_STREAMRWOPS_HH
#define SDL2PP_STREAMRWOPS_HH

#include <SDL2pp/RWops.hh>

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <type_traits>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief RWops adaptor for STL streams
///
/// \ingroup io
///
/// \headerfile SDL2pp/StreamRWops.hh
///
/// This class extends functionality of %RWops concept onto STL
/// streams. With ContainerRWops, you may read from / write to
/// STL streams with %SDL functions.
///
/// This template supports both input and output streams, but not
/// at the same time, as separate input and output pointers of
/// streams are not compatible with %RWops.
///
////////////////////////////////////////////////////////////
template <class S>
class StreamRWops : public CustomRWops {
	// since STL streams have different pointers for reading and writing,
	// supporting both at the same time is impossible
	static_assert(!(std::is_base_of<std::istream, S>::value && std::is_base_of<std::ostream, S>::value), "StreamRWops does not support reading and writing at the same time");

protected:
	S& stream_; ///< Reference to stream

private:
	template <class SS>
	typename std::enable_if<std::is_base_of<std::istream, SS>::value && !std::is_base_of<std::ostream, SS>::value, void>::type SeekHelper(typename SS::off_type off, std::ios_base::seekdir dir) {
		stream_.seekg(off, dir);
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::istream, SS>::value && std::is_base_of<std::ostream, SS>::value, void>::type SeekHelper(typename SS::off_type off, std::ios_base::seekdir dir) {
		stream_.seekp(off, dir);
	}

	template <class SS>
	typename std::enable_if<std::is_base_of<std::istream, SS>::value && !std::is_base_of<std::ostream, SS>::value, typename SS::off_type>::type TellHelper() {
		return stream_.tellg();
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::istream, SS>::value && std::is_base_of<std::ostream, SS>::value, typename SS::off_type>::type TellHelper() {
		return stream_.tellp();
	}

	template <class SS>
	typename std::enable_if<std::is_base_of<std::istream, SS>::value, size_t>::type ReadHelper(void* ptr, size_t size, size_t maxnum) {
		stream_.read(static_cast<char*>(ptr), size * maxnum);

		// http://en.cppreference.com/w/cpp/io/streamsize:
		// "Except in the constructors of std::strstreambuf,
		// negative values of std::streamsize are never used"
		size_t nread = static_cast<size_t>(stream_.gcount());

		// eof is OK
		if (stream_.rdstate() == (std::ios_base::eofbit | std::ios_base::failbit))
			stream_.clear();

		if (nread != size * maxnum) {
			// short read
			char* pos = static_cast<char*>(ptr);
			pos += nread;

			size_t count = nread % size;

			// put partially read object back into the stream
			while (count != 0) {
				stream_.putback(*--pos);
				--count;
			}
		}

		return nread / size;
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::istream, SS>::value, size_t>::type ReadHelper(void*, size_t, size_t) {
		return 0;
	}

	template <class SS>
	typename std::enable_if<std::is_base_of<std::ostream, SS>::value, size_t>::type WriteHelper(const void* ptr, size_t size, size_t num) {
		stream_.write(static_cast<const char*>(ptr), size * num);
		// XXX: there seem to be no reliable way to tell how much
		// was actually written
		if (stream_.rdstate() & std::ios_base::badbit)
			return 0;
		return num;
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::ostream, SS>::value, size_t>::type WriteHelper(const void*, size_t, size_t) {
		return 0;
	}

	template <class SS>
	typename std::enable_if<std::is_base_of<std::ostream, SS>::value, int>::type CloseHelper() {
		stream_.flush();
		return (stream_.rdstate() & std::ios_base::badbit) ? -1 : 0;
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::ostream, SS>::value, int>::type CloseHelper() {
		return 0;
	}

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct StreamRWops for specified stream
	///
	/// \param[in] stream Stream to use
	///
	////////////////////////////////////////////////////////////
	StreamRWops(S& stream) : stream_(stream) {
	}

	////////////////////////////////////////////////////////////
	/// \brief Get the size of the data stream
	///
	/// \returns Size of the data stream on success, -1 if unknown
	///
	/// \see SDL2pp::RWops::Size
	/// \see http://wiki.libsdl.org/SDL_RWsize
	///
	////////////////////////////////////////////////////////////
	virtual Sint64 Size() override {
		Sint64 old_pos = TellHelper<S>();
		if (old_pos == -1) // not seekable?
			return -1;
		SeekHelper<S>(0, std::ios_base::end);
		Sint64 size = TellHelper<S>();
		SeekHelper<S>(old_pos, std::ios_base::beg);
		assert(TellHelper<S>() == old_pos); // make sure we're back to where we were
		return size;
	}

	////////////////////////////////////////////////////////////
	/// \brief Seek within the stream
	///
	/// \param[in] offset Offset in bytes, relative to whence location; can
	///                   be negative
	/// \param[in] whence Any of RW_SEEK_SET, RW_SEEK_CUR, RW_SEEK_END
	///
	/// \returns Final offset in the stream after the seek or -1 on error
	///
	/// \see SDL2pp::RWops::Seek
	/// \see http://wiki.libsdl.org/SDL_RWseek
	///
	////////////////////////////////////////////////////////////
	virtual Sint64 Seek(Sint64 offset, int whence) override {
		switch (whence) {
		case RW_SEEK_SET:
			SeekHelper<S>(offset, std::ios_base::beg);
			break;
		case RW_SEEK_CUR:
			SeekHelper<S>(offset, std::ios_base::cur);
			break;
		case RW_SEEK_END:
			SeekHelper<S>(offset, std::ios_base::end);
			break;
		default:
			throw std::logic_error("Unexpected whence value for StreamRWops::Seek");
		}
		return TellHelper<S>();
	}

	////////////////////////////////////////////////////////////
	/// \brief Read from a stream
	///
	/// \param[in] ptr Pointer to a buffer to read data into
	/// \param[in] size Size of each object to read, in bytes
	/// \param[in] maxnum Maximum number of objects to be read
	///
	/// \returns Number of objects read, or 0 at error or end of file
	///
	/// \see SDL2pp::RWops::Read
	/// \see http://wiki.libsdl.org/SDL_RWread
	///
	////////////////////////////////////////////////////////////
	virtual size_t Read(void* ptr, size_t size, size_t maxnum) override {
		return ReadHelper<S>(ptr, size, maxnum);
	}

	////////////////////////////////////////////////////////////
	/// \brief Write to a stream
	///
	/// \param[in] ptr Pointer to a buffer containing data to write
	/// \param[in] size Size of each object to write, in bytes
	/// \param[in] num Number of objects to be write
	///
	/// \returns Number of objects written
	///
	/// \see SDL2pp::RWops::Write
	/// \see http://wiki.libsdl.org/SDL_RWwrite
	///
	////////////////////////////////////////////////////////////
	virtual size_t Write(const void* ptr, size_t size, size_t num) override {
		return WriteHelper<S>(ptr, size, num);
	}

	////////////////////////////////////////////////////////////
	/// \brief Close stream
	///
	/// \returns 0 on success or a negative error code on failure
	///
	/// \see SDL2pp::RWops::Close
	/// \see http://wiki.libsdl.org/SDL_RWclose
	///
	////////////////////////////////////////////////////////////
	virtual int Close() override {
		return CloseHelper<S>();
	}
};

}

#endif
