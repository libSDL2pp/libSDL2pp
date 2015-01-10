/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2014-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <stdexcept>
#include <iostream>
#include <type_traits>

namespace SDL2pp {

template <class S>
class StreamRWops : public CustomRWops {
	// since STL streams have different pointers for reading and writing,
	// supporting both at the same time is impossible
	static_assert(!(std::is_base_of<std::istream, S>::value && std::is_base_of<std::ostream, S>::value), "StreamRWops does not support reading and writing at the same time");

protected:
	S& stream_;

private:
	template <class SS>
	typename std::enable_if<std::is_base_of<std::istream, SS>::value && !std::is_base_of<std::ostream, SS>::value, void>::type SeekHelper(off_t off, std::ios_base::seekdir dir) {
		stream_.seekg(off, dir);
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::istream, SS>::value && std::is_base_of<std::ostream, SS>::value, void>::type SeekHelper(off_t off, std::ios_base::seekdir dir) {
		stream_.seekp(off, dir);
	}

	template <class SS>
	typename std::enable_if<std::is_base_of<std::istream, SS>::value && !std::is_base_of<std::ostream, SS>::value, off_t>::type TellHelper() {
		return stream_.tellg();
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::istream, SS>::value && std::is_base_of<std::ostream, SS>::value, off_t>::type TellHelper() {
		return stream_.tellp();
	}

	template <class SS>
	typename std::enable_if<std::is_base_of<std::istream, SS>::value, size_t>::type ReadHelper(void* ptr, size_t size, size_t maxnum) {
		stream_.read(static_cast<char*>(ptr), size * maxnum);
		size_t nread = stream_.gcount();

		// eof is OK
		if (stream_.rdstate() == (std::ios_base::eofbit | std::ios_base::failbit))
			stream_.clear();

		if (nread != size * maxnum) {
			// short read
			char* pos = static_cast<char*>(ptr);
			pos += nread;

			int count = nread % size;

			// put partially read object back into the stream
			while (--count >= 0)
				stream_.putback(*--pos);
		}

		return nread / size;
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::istream, SS>::value, size_t>::type ReadHelper(void*, size_t, size_t) {
		return 0;
	}

	template <class SS>
	typename std::enable_if<std::is_base_of<std::ostream, SS>::value, size_t>::type WriteHelper(const void* ptr, size_t size, size_t maxnum) {
		stream_.write(static_cast<const char*>(ptr), size * maxnum);
		// XXX: there seem to be no reliable way to tell how much
		// was actually written
		if (stream_.rdstate() & std::ios_base::badbit)
			return 0;
		return maxnum;
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::ostream, SS>::value, size_t>::type WriteHelper(const void*, size_t, size_t) {
		return 0;
	}

	template <class SS>
	typename std::enable_if<std::is_base_of<std::ostream, SS>::value, int>::type CloseHelper() {
		stream_.flush();
		return stream_.rdstate() & std::ios_base::badbit;
	}

	template <class SS>
	typename std::enable_if<!std::is_base_of<std::ostream, SS>::value, int>::type CloseHelper() {
		return 0;
	}

public:
	StreamRWops(S& stream) : stream_(stream) {
	}

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

	virtual size_t Read(void* ptr, size_t size, size_t maxnum) override {
		return ReadHelper<S>(ptr, size, maxnum);
	}

	virtual size_t Write(const void* ptr, size_t size, size_t maxnum) override {
		return WriteHelper<S>(ptr, size, maxnum);
	}

	virtual int Close() override {
		return CloseHelper<S>();
	}
};

}

#endif
