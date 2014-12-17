/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2013-2014 Dmitry Marakasov <amdmi3@amdmi3.ru>

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
#include <stdexcept>

#include <SDL2/SDL.h>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

int Run() {
	SDL sdl(SDL_INIT_AUDIO);

	Wav wav(TESTDATA_DIR "/test.wav");

	// Setup audio device, and provide callback which plays looped wave sound
	Uint8* wav_pos = wav.GetBuffer();
	AudioSpec spec(wav.GetSpec(), [&wav, &wav_pos](Uint8* stream, int len) {
				// Fill provided buffer with wave contents
				Uint8* stream_pos = stream;
				Uint8* stream_end = stream + len;

				while (stream_pos < stream_end) {
					Uint8* wav_end = wav.GetBuffer() + wav.GetLength();

					int copylen = std::min(wav_end - wav_pos, stream_end - stream_pos);

					std::copy(wav_pos, wav_pos + copylen, stream_pos);
					stream_pos += copylen;
					wav_pos += copylen;
					if (wav_pos >= wav_end)
						wav_pos = wav.GetBuffer();
				}
			}
		);

	// Open audio device
	AudioDevice dev("", 0, spec);

	// Ensure SDL has set up format conversion for us
	if (!spec.IsSameFormat(wav.GetSpec()))
		throw std::runtime_error("WAV format is not the same as output format");

	// Sound plays after this call
	dev.Pause(false);

	// Play for 5 seconds, after which everything is stopped and closed
	SDL_Delay(5000);

	return 0;
}

int main() {
	try {
		return Run();
	} catch (Exception& e) {
		std::cerr << "Error: " << e.what() << " (" << e.GetSDLError() << ")" << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return -1;
}
