/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2013-2016 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <cmath>
#include <iostream>

#include <SDL.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/Mixer.hh>

using namespace SDL2pp;

int main(int, char*[]) try {
	SDL sdl(SDL_INIT_AUDIO);
	Mixer mixer(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 1, 4096);

	// XXX: this should be constexpr and not captured in lambda
	// below, but that fails on microsoft crapiler
	float frequency = 2093.00f; // C7 tone
	int64_t nsample = 0;

	// Set custom music hook which generates a sine wave
	mixer.SetMusicHook([&nsample, frequency](Uint8* stream, int len) {
				// fill provided buffer with sine wave
				for (Uint8* ptr = stream; ptr < stream + len; ptr += 2)
					*(Uint16*)ptr = (Uint16)(32766.0f * sin(nsample++ / (float)MIX_DEFAULT_FREQUENCY * frequency));
			}
		);

	// Play for 1 second, after which everything is stopped and closed
	SDL_Delay(1000);

	return 0;
} catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
