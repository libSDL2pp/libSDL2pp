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

#include <SDL2pp/Exception.hh>
#include <SDL2pp/RWops.hh>

#include <SDL2pp/Wav.hh>

namespace SDL2pp {

Wav::Wav(const std::string& file) {
	if (SDL_LoadWAV(file.c_str(), &spec_, &audio_buffer_, &audio_length_) == nullptr)
		throw Exception("SDL_LoadWAV");
}

Wav::Wav(RWops& rwops) {
	if (SDL_LoadWAV_RW(rwops.Get(), 0, &spec_, &audio_buffer_, &audio_length_) == nullptr)
		throw Exception("SDL_LoadWAV_RW");
}

Wav::~Wav() {
	if (audio_buffer_ != nullptr)
		SDL_FreeWAV(audio_buffer_);
}

Wav::Wav(Wav&& other) noexcept : audio_buffer_(other.audio_buffer_), audio_length_(other.audio_length_), spec_(std::move(other.spec_)) {
	other.audio_buffer_ = nullptr;
	other.audio_length_ = 0;
}

Wav& Wav::operator=(Wav&& other) noexcept {
	if (&other == this)
		return *this;

	if (audio_buffer_ != nullptr)
		SDL_FreeWAV(audio_buffer_);

	spec_ = std::move(other.spec_);
	audio_buffer_ = other.audio_buffer_;
	audio_length_ = other.audio_length_;

	other.audio_buffer_ = nullptr;
	other.audio_length_ = 0;

	return *this;
}

Uint32 Wav::GetLength() const {
	return audio_length_;
}

Uint8* Wav::GetBuffer() {
	return audio_buffer_;
}

const Uint8* Wav::GetBuffer() const {
	return audio_buffer_;
}

const AudioSpec& Wav::GetSpec() const {
	return spec_;
}

}
