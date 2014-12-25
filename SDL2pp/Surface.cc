/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
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

#include <SDL2/SDL_surface.h>

#include <SDL2pp/Surface.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Surface::Surface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
	if ((surface_ = SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask)) == nullptr)
		throw Exception("SDL_CreateRGBSurface failed");
}

Surface::Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
	if ((surface_ = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask)) == nullptr)
		throw Exception("SDL_CreateRGBSurfaceFrom failed");
}

Surface::~Surface() {
	if (surface_ != nullptr)
		SDL_FreeSurface(surface_);
}

Surface::Surface(Surface&& other) noexcept : surface_(other.surface_) {
	other.surface_ = nullptr;
}

Surface& Surface::operator=(Surface&& other) noexcept {
	if (&other == this)
		return *this;
	if (surface_ != nullptr)
		SDL_FreeSurface(surface_);
	surface_ = other.surface_;
	other.surface_ = nullptr;
	return *this;
}

SDL_Surface* Surface::Get() const {
	return surface_;
}

}
