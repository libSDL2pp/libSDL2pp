/*
  libSDL2pp - C++ wrapper for libSDL2
  Copyright (C) 2014 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_EXTRARWOPS_HH
#define SDL2PP_EXTRARWOPS_HH

#include <SDL2pp/RWops.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

template<typename C>
class ContainerRWops : public CustomRWops {
protected:
	C& container_;
	size_t position_;

public:
	ContainerRWops(C& container) : container_(container), position_(0) {
	}

	ContainerRWops(const ContainerRWops<C>&) = default;
	ContainerRWops& operator=(const ContainerRWops<C>&) = delete;
	ContainerRWops(ContainerRWops<C>&&) noexcept = default;
	ContainerRWops& operator=(ContainerRWops<C>&&) = delete;

	virtual Sint64 Seek(Sint64 offset, int whence) override {
		switch (whence) {
		case RW_SEEK_SET:
			position_ = offset;
			break;
		case RW_SEEK_CUR:
			position_ = position_ + offset;
			break;
		case RW_SEEK_END:
			position_ = container_.size() + offset;
			break;
		default:
			throw Exception("Unexpected whence value for WritableMemRWops::Seek");
		}
		return position_;
	}

	virtual size_t Read(void* ptr, size_t size, size_t maxnum) override {
		if (position_ + size > container_.size())
			return 0;

		int toread = std::min((container_.size() - position_), maxnum * size);

		std::copy(container_.begin() + position_, container_.begin() + position_ + toread, reinterpret_cast<unsigned char*>(ptr));

		position_ += toread;

		return toread / size;
	}

	virtual size_t Write(const void* ptr, size_t size, size_t maxnum) override {
		if (position_ + size * maxnum > container_.size())
			container_.resize(position_ + size * maxnum);

		std::copy(reinterpret_cast<const unsigned char*>(ptr), reinterpret_cast<const unsigned char*>(ptr) + size * maxnum, container_.begin() + position_);

		position_ += size * maxnum;

		return maxnum;
	}

	virtual int Close() override {
		return 0;
	}
};

template<typename C>
class ConstContainerRWops : public CustomRWops {
protected:
	const C& container_;
	size_t position_;

public:
	ConstContainerRWops(const C& container) : container_(container), position_(0) {
	}

	ConstContainerRWops(const ConstContainerRWops<C>&) = default;
	ConstContainerRWops& operator=(const ConstContainerRWops<C>&) = delete;
	ConstContainerRWops(ConstContainerRWops<C>&&) noexcept = default;
	ConstContainerRWops& operator=(ConstContainerRWops<C>&&) = delete;

	virtual Sint64 Seek(Sint64 offset, int whence) override {
		switch (whence) {
		case RW_SEEK_SET:
			position_ = offset;
			break;
		case RW_SEEK_CUR:
			position_ = position_ + offset;
			break;
		case RW_SEEK_END:
			position_ = container_.size() + offset;
			break;
		default:
			throw Exception("Unexpected whence value for WritableMemRWops::Seek");
		}
		return position_;
	}

	virtual size_t Read(void* ptr, size_t size, size_t maxnum) override {
		if (position_ + size > container_.size())
			return 0;

		int toread = std::min((container_.size() - position_), maxnum * size);

		std::copy(container_.begin() + position_, container_.begin() + position_ + toread, reinterpret_cast<unsigned char*>(ptr));

		position_ += toread;

		return toread / size;
	}

	virtual size_t Write(const void*, size_t, size_t) override {
		SDL_SetError("Can't write to read-only container");
		return 0;
	}

	virtual int Close() override {
		return 0;
	}
};

}

#endif
