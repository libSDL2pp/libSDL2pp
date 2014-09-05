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

#ifndef SDL2PP_RWOPS_HH
#define SDL2PP_RWOPS_HH

#include <string>

#include <SDL2/SDL_rwops.h>
#include <SDL2pp/Exception.hh>

/*
 * This looks quite complicated, but it's needed to both retain
 * compatibility with C SDL and make it possible to write pure C++
 * RWops classes, doing both safely.
 *
 * This class supports either standard SDL_RWops (e.g. created with
 * SDL_RWFrom* famuly of functions or SDL_AllocRW) or custom C++-style
 * rwops derived from CustomRWops class
 *
 * Either may be used via C++ interface (Read/Write/Seek/Tell/Close
 * functions) or via C SDL interface (SDL_RWread/SDL_RWwrite/...)
 * functions on SDL_RWops obtained with Get() method.
 */

namespace SDL2pp {

class CustomRWops {
public:
	virtual ~CustomRWops() {}

	virtual Sint64 Seek(Sint64 offset, int whence) = 0;
	virtual size_t Read(void* ptr, size_t size, size_t maxnum) = 0;
	virtual size_t Write(const void* ptr, size_t size, size_t maxnum) = 0;
	virtual int Close() = 0;
};

class RWops {
protected:
	SDL_RWops* rwops_;

private:
	static Sint64 StdSeekFuncWrapper(SDL_RWops* context, Sint64 offset, int whence);
	static size_t StdReadFuncWrapper(SDL_RWops* context, void *ptr, size_t size, size_t maxnum);
	static size_t StdWriteFuncWrapper(SDL_RWops* context, const void *ptr, size_t size, size_t maxnum);
	static int StdCloseFuncWrapper(SDL_RWops* context);

	static Sint64 CustomSeekFuncWrapper(SDL_RWops* context, Sint64 offset, int whence);
	static size_t CustomReadFuncWrapper(SDL_RWops* context, void *ptr, size_t size, size_t maxnum);
	static size_t CustomWriteFuncWrapper(SDL_RWops* context, const void *ptr, size_t size, size_t maxnum);
	static int CustomCloseFuncWrapper(SDL_RWops* context);

	static RWops CheckedCreateStandardRWops(SDL_RWops* sdl_rwops, const char* errmsg);

public:
	static RWops FromFP(FILE* file, bool autoclose);
	static RWops FromConstMem(const void* mem, int size);
	static RWops FromMem(void* mem, int size);
	static RWops FromFile(const std::string& file, const std::string& mode = "rb");

	RWops(SDL_RWops* rwops);

	RWops(const RWops&) = delete;
	RWops& operator=(const RWops&) = delete;
	RWops(RWops&& other) noexcept;
	RWops& operator=(RWops&& other) noexcept;

	template<class C>
	RWops(C&& custom_rwops) {
		rwops_ = SDL_AllocRW();
		if (rwops_ == nullptr)
			throw Exception("SDL_AllocRW failed");

		rwops_->seek = CustomSeekFuncWrapper;
		rwops_->read = CustomReadFuncWrapper;
		rwops_->write = CustomWriteFuncWrapper;
		rwops_->close = CustomCloseFuncWrapper;
		rwops_->type = 0x57524370; // "pCRW" for libSDLp[p] [C]ustom [RW]ops
		try {
			rwops_->hidden.unknown.data1 = static_cast<void*>(new C(custom_rwops));
		} catch (...) {
			SDL_FreeRW(rwops_);
			throw;
		}
		rwops_->hidden.unknown.data2 = static_cast<void*>(this);
	}

	~RWops();

	SDL_RWops* Get() const;

	int Close();
	size_t Read(void* ptr, size_t size, size_t maxnum);
	Sint64 Seek(Sint64 offset, int whence);
	size_t Write(const void* ptr, size_t size, size_t num);
	Sint64 Tell();
	Sint64 Size();
};

}

#endif
