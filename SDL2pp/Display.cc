/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2017 Vraiment <jemc44@gmail.com>

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

#include <SDL2pp/Display.hh>

#include <SDL2pp/Exception.hh>

#include <SDL_video.h>

using std::string;

namespace SDL2pp {
Rect GetDisplayBounds(int displayIndex) {
	Rect result;
	if (SDL_GetDisplayBounds(displayIndex, &result) < 0) {
		throw Exception("SDL_GetDisplayBounds");
	}
 	
	return result;
}

string GetDisplayName(int displayIndex) {
	const char* name = SDL_GetDisplayName(displayIndex);
	if (name == nullptr) {
		throw Exception("SDL_GetDisplayName");
	}
	
	return string{name};
}

#if SDL_VERSION_ATLEAST(2, 0, 4)
DPI GetDisplayDPI(int displayIndex) {
	float diagonal = 0, horizontal = 0, vertical = 0;
	if (SDL_GetDisplayDPI(displayIndex, &diagonal, &horizontal, &vertical) < 0) {
		throw Exception("SDL_GetDisplayDPI");
	}
	
	return DPI{diagonal, horizontal, vertical};
}
#endif

#if SDL_VERSION_ATLEAST(2, 0, 5)
Rect GetDisplayUsableBounds(int displayIndex) {
	Rect result;
	if (SDL_GetDisplayUsableBounds(displayIndex, &result) < 0) {
		throw Exception("SDL_GetDisplayUsableBounds");
	}
	
	return result;
}
#endif
}
