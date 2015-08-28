/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
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

#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Mixer::Mixer(int frequency, Uint16 format, int channels, int chunksize) : open_(true) {
	if (Mix_OpenAudio(frequency, format, channels, chunksize) != 0)
		throw Exception("Mix_OpenAudio");
}

Mixer::~Mixer() {
	if (open_)
		Mix_CloseAudio();
}

Mixer::Mixer(Mixer&& other) noexcept : open_(other.open_) {
	other.open_ = false;
}

Mixer& Mixer::operator=(Mixer&& other) noexcept {
	if (&other == this)
		return *this;
	if (open_)
		Mix_CloseAudio();
	open_ = other.open_;
	other.open_ = false;
	return *this;
}

}
