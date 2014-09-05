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

#include <cassert>

#include <SDL2pp/RWops.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Sint64 RWops::StdSeekFuncWrapper(SDL_RWops* context, Sint64 offset, int whence) {
	assert(context != nullptr);
	SDL_RWops* sdl_rwops = reinterpret_cast<SDL_RWops*>(context->hidden.unknown.data1);
	assert(sdl_rwops != nullptr);
	return sdl_rwops->seek(sdl_rwops, offset, whence);
}

size_t RWops::StdReadFuncWrapper(SDL_RWops* context, void *ptr, size_t size, size_t maxnum) {
	assert(context != nullptr);
	SDL_RWops* sdl_rwops = reinterpret_cast<SDL_RWops*>(context->hidden.unknown.data1);
	assert(sdl_rwops != nullptr);
	return sdl_rwops->read(sdl_rwops, ptr, size, maxnum);
}

size_t RWops::StdWriteFuncWrapper(SDL_RWops* context, const void *ptr, size_t size, size_t maxnum) {
	assert(context != nullptr);
	SDL_RWops* sdl_rwops = reinterpret_cast<SDL_RWops*>(context->hidden.unknown.data1);
	assert(sdl_rwops != nullptr);
	return sdl_rwops->write(sdl_rwops, ptr, size, maxnum);
}

int RWops::StdCloseFuncWrapper(SDL_RWops* context) {
	assert(context != nullptr);
	SDL_RWops* sdl_rwops = reinterpret_cast<SDL_RWops*>(context->hidden.unknown.data1);
	RWops* rwops = reinterpret_cast<RWops*>(context->hidden.unknown.data2);
	assert(sdl_rwops != nullptr);
	assert(rwops != nullptr);

	// this automatically frees sdl_rwops
	int ret = sdl_rwops->close(sdl_rwops);

	SDL_FreeRW(rwops->rwops_);
	rwops->rwops_ = nullptr;

	return ret;
}

Sint64 RWops::CustomSeekFuncWrapper(SDL_RWops* context, Sint64 offset, int whence) {
	assert(context != nullptr);
	CustomRWops* custom_rwops = reinterpret_cast<CustomRWops*>(context->hidden.unknown.data1);
	assert(custom_rwops != nullptr);
	return custom_rwops->Seek(offset, whence);
}

size_t RWops::CustomReadFuncWrapper(SDL_RWops* context, void *ptr, size_t size, size_t maxnum) {
	assert(context != nullptr);
	CustomRWops* custom_rwops = reinterpret_cast<CustomRWops*>(context->hidden.unknown.data1);
	assert(custom_rwops != nullptr);
	return custom_rwops->Read(ptr, size, maxnum);
}

size_t RWops::CustomWriteFuncWrapper(SDL_RWops* context, const void *ptr, size_t size, size_t maxnum) {
	assert(context != nullptr);
	CustomRWops* custom_rwops = reinterpret_cast<CustomRWops*>(context->hidden.unknown.data1);
	assert(custom_rwops != nullptr);
	return custom_rwops->Write(ptr, size, maxnum);
}

int RWops::CustomCloseFuncWrapper(SDL_RWops* context) {
	assert(context != nullptr);
	CustomRWops* custom_rwops = reinterpret_cast<CustomRWops*>(context->hidden.unknown.data1);
	RWops* rwops = reinterpret_cast<RWops*>(context->hidden.unknown.data2);
	assert(custom_rwops != nullptr);
	assert(rwops != nullptr);

	int ret = custom_rwops->Close();

	delete custom_rwops;

	SDL_FreeRW(rwops->rwops_);
	rwops->rwops_ = nullptr;

	return ret;
}

RWops RWops::CheckedCreateStandardRWops(SDL_RWops* sdl_rwops, const char* errmsg) {
	if (sdl_rwops == nullptr)
		throw Exception(errmsg);

	try {
		return RWops(sdl_rwops);
	} catch (...) {
		SDL_FreeRW(sdl_rwops);
		throw;
	}
}

RWops RWops::FromFP(FILE* file, bool autoclose) {
	return CheckedCreateStandardRWops(SDL_RWFromFP(file, autoclose ? SDL_TRUE : SDL_FALSE), "SDL_RWFromFP failed");
}

RWops RWops::FromConstMem(const void* mem, int size) {
	return CheckedCreateStandardRWops(SDL_RWFromConstMem(mem, size), "SDL_RWFromConstMem failed");
}

RWops RWops::FromMem(void* mem, int size) {
	return CheckedCreateStandardRWops(SDL_RWFromMem(mem, size), "SDL_RWFromMem failed");
}

RWops RWops::FromFile(const std::string& file, const std::string& mode) {
	return CheckedCreateStandardRWops(SDL_RWFromFile(file.c_str(), mode.c_str()), "SDL_RWFromFile failed");
}

RWops::RWops(SDL_RWops* rwops) {
	rwops_ = SDL_AllocRW();
	if (rwops_ == nullptr)
		throw Exception("SDL_AllocRW failed");

	rwops_->seek = StdSeekFuncWrapper;
	rwops_->read = StdReadFuncWrapper;
	rwops_->write = StdWriteFuncWrapper;
	rwops_->close = StdCloseFuncWrapper;
	rwops_->type = 0x57525370; // "pSRW" for libSDLp[p] [S]tandard [RW]ops
	rwops_->hidden.unknown.data1 = static_cast<void*>(rwops);
	rwops_->hidden.unknown.data2 = static_cast<void*>(this);
}

RWops::RWops(RWops&& other) noexcept : rwops_(other.rwops_) {
	other.rwops_ = nullptr;
	rwops_->hidden.unknown.data2 = static_cast<void*>(this);
}

RWops& RWops::operator=(RWops&& other) noexcept {
	rwops_ = other.rwops_;
	rwops_->hidden.unknown.data2 = static_cast<void*>(this);
	other.rwops_ = nullptr;
	return *this;
}

RWops::~RWops() {
	if (rwops_ != nullptr)
		Close();
}

SDL_RWops* RWops::Get() const {
	return rwops_;
}

int RWops::Close() {
	return SDL_RWclose(rwops_);
}

size_t RWops::Read(void* ptr, size_t size, size_t maxnum) {
	return SDL_RWread(rwops_, ptr, size, maxnum);
}

Sint64 RWops::Seek(Sint64 offset, int whence) {
	return SDL_RWseek(rwops_, offset, whence);
}

size_t RWops::Write(const void* ptr, size_t size, size_t num) {
	return SDL_RWwrite(rwops_, ptr, size, num);
}

Sint64 RWops::Tell() {
	return SDL_RWtell(rwops_);
}

Sint64 RWops::Size() {
	Sint64 old_pos = Tell();
	Sint64 size = Seek(0, SEEK_END);
	Sint64 back_pos = Seek(old_pos, SEEK_SET);
	assert(back_pos == old_pos);
	return size;
}

}
