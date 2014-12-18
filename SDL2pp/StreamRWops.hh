/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
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

#ifndef SDL2PP_STREAMRWOPS_HH
#define SDL2PP_STREAMRWOPS_HH

#include <SDL2pp/RWops.hh>

#include <stdexcept>
#include <iostream>

namespace SDL2pp {

template<typename S>
class StreamRWops : public CustomRWops {
protected:
	S& stream_;

public:
	StreamRWops(const S& stream) : stream_(stream) {
	}

	StreamRWops(const StreamRWops<S>&) = default;
	StreamRWops& operator=(const StreamRWops<S>&) = delete;
	StreamRWops(StreamRWops<S>&&) noexcept = default;
	StreamRWops& operator=(StreamRWops<S>&&) = delete;

	virtual Sint64 Seek(Sint64 offset, int whence) override {
		switch (whence) {
		case RW_SEEK_SET:
			stream_.seekg(offset, std::ios_base::beg);
			break;
		case RW_SEEK_CUR:
			stream_.seekg(offset, std::ios_base::cur);
			break;
		case RW_SEEK_END:
			stream_.seekg(offset, std::ios_base::end);
			break;
		default:
			throw Exception("Unexpected whence value for StreamRWops::Seek");
		}
		return stream_.tellg();
	}

	virtual size_t Read(void* ptr, size_t size, size_t maxnum) override {
		stream_.read(ptr, size * maxnum);
		size_t nread = stream_.gcount();

		if (nread != size * maxnum) {
			// short read
			unsigned char* pos = static_cast<unsigned char*>(ptr);
			pos += nread + 1;

			int count = nread % size;

			// put partially read object back into the stream
			while (--count >= 0)
				stream_.putback(*--pos);

			stream_.seekg(-count, std::ios_base::cur);
		}
		return nread / size;
	}

	virtual size_t Write(const void* ptr, size_t size, size_t maxnum) override {
		stream_.write(ptr, size * maxnum);
		// XXX: there seem to be no reliable way to tell how much
		// was actually written
		if (stream_.restate() & std::ios_base::badbit)
			return 0;
		return maxnum;
	}

	virtual int Close() override {
		stream_.flush();
		return stream_.restate() & std::ios_base::badbit;
	}
};

}

#endif
