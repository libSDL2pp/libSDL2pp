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

#include <SDL_surface.h>

#include <SDL2pp/Exception.hh>

#include <SDL2pp/Surface.hh>

namespace SDL2pp {

Surface::LockHandle::LockHandle() : surface_(nullptr) {
}

Surface::LockHandle::LockHandle(Surface* surface) : surface_(surface) {
	if (SDL_MUSTLOCK(surface_->Get())) {
		if (SDL_LockSurface(surface_->Get()))
			throw Exception("SDL_LockSurface");
	}
}

Surface::LockHandle::LockHandle(Surface::LockHandle&& other) noexcept : surface_(other.surface_) {
	other.surface_ = nullptr;
}

Surface::LockHandle& Surface::LockHandle::operator=(Surface::LockHandle&& other) noexcept {
	if (&other == this)
		return *this;

	if (surface_ != nullptr) {
		if (SDL_MUSTLOCK(surface_->Get()))
			SDL_UnlockSurface(surface_->Get());
	}

	surface_ = other.surface_;

	other.surface_ = nullptr;

	return *this;
}

Surface::LockHandle::~LockHandle() {
	if (surface_ != nullptr) {
		if (SDL_MUSTLOCK(surface_->Get()))
			SDL_UnlockSurface(surface_->Get());
	}
}

void* Surface::LockHandle::GetPixels() const {
	return surface_->Get()->pixels;
}

int Surface::LockHandle::GetPitch() const {
	return surface_->Get()->pitch;
}

const SDL_PixelFormat& Surface::LockHandle::GetFormat() const {
	return *surface_->Get()->format;
}

}
