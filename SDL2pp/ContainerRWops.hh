/*
  libSDL2pp - C++ bindings/wrapper for SDL2
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

#ifndef SDL2PP_CONTAINERRWOPS_HH
#define SDL2PP_CONTAINERRWOPS_HH

#include <SDL2pp/RWops.hh>

#include <type_traits>
#include <stdexcept>
#include <algorithm>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief RWops adaptor for random access STL containers
///
/// \ingroup io
///
/// \headerfile SDL2pp/ContainerRWops.hh
///
/// This class extends functionality of %RWops concept onto random
/// access STL containers such as std::vector. With ContainerRWops,
/// you may read from / write to a container with %SDL functions as
/// if it were a plain file.
///
/// Note that this template supports both const and mutable containers.
/// Writes to const containers always return 0, writes to mutable
/// containers extend them as needed.
///
////////////////////////////////////////////////////////////
template <class C>
class ContainerRWops : public CustomRWops {
protected:
	C& container_;    ///< Reference to container
	size_t position_; ///< Virtual file pointer position

private:
	template <class CC>
	typename std::enable_if<!std::is_const<CC>::value, size_t>::type WriteHelper(const void* ptr, size_t size, size_t num) {
		if (position_ + size * num > container_.size())
			container_.resize(position_ + size * num);

		std::copy(reinterpret_cast<const unsigned char*>(ptr), reinterpret_cast<const unsigned char*>(ptr) + size * num, container_.begin() + position_);

		position_ += size * num;

		return num;
	}

	template <class CC>
	typename std::enable_if<std::is_const<CC>::value, size_t>::type WriteHelper(const void*, size_t, size_t) {
		SDL_SetError("Can't write to read-only container");
		return 0;
	}

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct ContainerRWops for specified container
	///
	/// \param[in] container Container to use
	///
	////////////////////////////////////////////////////////////
	ContainerRWops(C& container) : container_(container), position_(0) {
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
		return static_cast<Sint64>(container_.size());
	}

	////////////////////////////////////////////////////////////
	/// \brief Seek within the container
	///
	/// \param[in] offset Offset in bytes, relative to whence location; can
	///                   be negative
	/// \param[in] whence Any of RW_SEEK_SET, RW_SEEK_CUR, RW_SEEK_END
	///
	/// \returns Final offset in the container after the seek or -1 on error
	///
	/// \see SDL2pp::RWops::Seek
	/// \see http://wiki.libsdl.org/SDL_RWseek
	///
	////////////////////////////////////////////////////////////
	virtual Sint64 Seek(Sint64 offset, int whence) override {
		switch (whence) {
		case RW_SEEK_SET:
			position_ = static_cast<size_t>(offset);
			break;
		case RW_SEEK_CUR:
			position_ = static_cast<size_t>(position_ + offset);
			break;
		case RW_SEEK_END:
			position_ = static_cast<size_t>(container_.size() + offset);
			break;
		default:
			throw std::logic_error("Unexpected whence value for ContainerRWops::Seek");
		}
		return position_;
	}

	////////////////////////////////////////////////////////////
	/// \brief Read from a container
	///
	/// \param[in] ptr Pointer to a buffer to read data into
	/// \param[in] size Size of each object to read, in bytes
	/// \param[in] maxnum Maximum number of objects to be read
	///
	/// \returns Number of objects read, or 0 at end of file
	///
	/// \see SDL2pp::RWops::Read
	/// \see http://wiki.libsdl.org/SDL_RWread
	///
	////////////////////////////////////////////////////////////
	virtual size_t Read(void* ptr, size_t size, size_t maxnum) override {
		if (position_ + size > container_.size())
			return 0;

		size_t toread = std::min((container_.size() - position_), maxnum * size);

		std::copy(container_.begin() + position_, container_.begin() + position_ + toread, reinterpret_cast<unsigned char*>(ptr));

		position_ += toread;

		return toread / size;
	}

	////////////////////////////////////////////////////////////
	/// \brief Write to container
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
		return WriteHelper<C>(ptr, size, num);
	}

	////////////////////////////////////////////////////////////
	/// \brief Close data source
	///
	/// \returns Always returns 0
	///
	/// This function is a no-op: there's nothing to be done
	/// to "close" the container
	///
	/// \see SDL2pp::RWops::Close
	/// \see http://wiki.libsdl.org/SDL_RWclose
	///
	////////////////////////////////////////////////////////////
	virtual int Close() override {
		return 0;
	}
};

}

#endif
