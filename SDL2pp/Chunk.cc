/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2pp/Chunk.hh>
#include <SDL2pp/RWops.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Chunk::Chunk(Mix_Chunk* chunk) : chunk_(chunk) {
	assert(chunk);
}

Chunk::Chunk(const std::string& file) {
	if ((chunk_ = Mix_LoadWAV(file.c_str())) == nullptr)
		throw Exception("Mix_LoadWAV");
}

Chunk::Chunk(RWops& rwops) {
	if ((chunk_ = Mix_LoadWAV_RW(rwops.Get(), 0)) == nullptr)
		throw Exception("Mix_LoadWAV_RW");
}

Chunk::~Chunk() {
	if (chunk_ != nullptr)
		Mix_FreeChunk(chunk_);
}

Chunk::Chunk(Chunk&& other) noexcept : chunk_(other.chunk_) {
	other.chunk_ = nullptr;
}

Chunk& Chunk::operator=(Chunk&& other) noexcept {
	if (&other == this)
		return *this;
	if (chunk_ != nullptr)
		Mix_FreeChunk(chunk_);
	chunk_ = other.chunk_;
	other.chunk_ = nullptr;
	return *this;
}

Mix_Chunk* Chunk::Get() const {
	return chunk_;
}

int Chunk::SetVolume(int volume) {
	return Mix_VolumeChunk(chunk_, volume);
}

int Chunk::GetVolume() const {
	return Mix_VolumeChunk(chunk_, -1);
}

}
