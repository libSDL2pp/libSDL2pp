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

#include <iostream>

#include <SDL.h>
#include <SDL_mixer.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh>

using namespace SDL2pp;

int main(int, char*[]) try {
	SDL sdl(SDL_INIT_AUDIO);
	Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

	Chunk sound(TESTDATA_DIR "/test.ogg");

	// Panning
	std::cerr << "Panning: left" << std::endl;
	mixer.SetPanning(MIX_CHANNEL_POST, 255, 0);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	std::cerr << "Panning: right" << std::endl;
	mixer.SetPanning(MIX_CHANNEL_POST, 0, 255);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	mixer.UnsetPanning(MIX_CHANNEL_POST);

	// Distance
	std::cerr << "Distance: somewhat far" << std::endl;
	mixer.SetDistance(MIX_CHANNEL_POST, 128);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	std::cerr << "Distance: further" << std::endl;
	mixer.SetDistance(MIX_CHANNEL_POST, 192);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	std::cerr << "Distance: even further" << std::endl;
	mixer.SetDistance(MIX_CHANNEL_POST, 224);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	mixer.UnsetDistance(MIX_CHANNEL_POST);

	// Position
	std::cerr << "Position: closest left" << std::endl;
	mixer.SetPosition(MIX_CHANNEL_POST, 270, 0);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	std::cerr << "Position: somewhat far front" << std::endl;
	mixer.SetPosition(MIX_CHANNEL_POST, 0, 128);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	std::cerr << "Position: further right" << std::endl;
	mixer.SetPosition(MIX_CHANNEL_POST, 90, 192);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	std::cerr << "Position: even further back" << std::endl;
	mixer.SetPosition(MIX_CHANNEL_POST, 180, 224);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	mixer.UnsetPosition(MIX_CHANNEL_POST);

	// Position
	std::cerr << "Reverse stereo" << std::endl;

	mixer.SetReverseStereo(MIX_CHANNEL_POST);
	mixer.PlayChannel(-1, sound);
	SDL_Delay(2000);
	mixer.HaltChannel(-1);

	mixer.UnsetReverseStereo(MIX_CHANNEL_POST);

	return 0;
} catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
