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

#include <SDL_mixer.h>

#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

SDLMixer::SDLMixer(int flags) {
	if ((Mix_Init(flags) & flags) != flags)
		throw Exception("Mix_Init");
}

SDLMixer::~SDLMixer() {
	// see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC10
	while (Mix_Init(0))
		Mix_Quit();
}

int SDLMixer::InitMore(int flags) {
	int ret;
	if (((ret = Mix_Init(flags)) & flags) != flags)
		throw Exception("Mix_Init");
	return ret;
}

int SDLMixer::GetInitFlags() {
	return Mix_Init(0);
}

}
