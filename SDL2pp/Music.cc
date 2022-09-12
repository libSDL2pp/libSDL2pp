/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2015-2017 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2pp/Exception.hh>
#include <SDL2pp/Music.hh>
#include <SDL2pp/RWops.hh>

namespace SDL2pp {

Music::Music(Mix_Music* music) : music_(music) {
	assert(music);
}

Music::Music(const std::string& file) {
	if ((music_ = Mix_LoadMUS(file.c_str())) == nullptr)
		throw Exception("Mix_LoadMUS");
}

Music::Music(RWops& rwops) {
	if ((music_ = Mix_LoadMUS_RW(rwops.Get(), 0)) == nullptr)
		throw Exception("Mix_LoadMUS_RW");
}

Music::Music(RWops& rwops, Mix_MusicType type) {
	if ((music_ = Mix_LoadMUSType_RW(rwops.Get(), type, 0)) == nullptr)
		throw Exception("Mix_LoadMUSType_RW");
}

Music::~Music() {
	if (music_ != nullptr)
		Mix_FreeMusic(music_);
}

Music::Music(Music&& other) noexcept : music_(other.music_) {
	other.music_ = nullptr;
}

Music& Music::operator=(Music&& other) noexcept {
	if (&other == this)
		return *this;
	if (music_ != nullptr)
		Mix_FreeMusic(music_);
	music_ = other.music_;
	other.music_ = nullptr;
	return *this;
}

Mix_Music* Music::Get() const {
	return music_;
}

Mix_MusicType Music::GetType() const {
	return Mix_GetMusicType(music_);
}

}
