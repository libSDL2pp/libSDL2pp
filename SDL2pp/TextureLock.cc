/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2013-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL_render.h>

#include <SDL2pp/Exception.hh>
#include <SDL2pp/Rect.hh>

#include <SDL2pp/Texture.hh>

namespace SDL2pp {

Texture::LockHandle::LockHandle() : texture_(nullptr), pixels_(nullptr), pitch_(0) {
}

Texture::LockHandle::LockHandle(Texture* texture, const Optional<Rect>& rect) : texture_(texture) {
	if (SDL_LockTexture(texture_->Get(), rect ? &*rect : nullptr, &pixels_, &pitch_) != 0)
		throw Exception("SDL_LockTexture");
}

Texture::LockHandle::LockHandle(Texture::LockHandle&& other) noexcept : texture_(other.texture_), pixels_(other.pixels_), pitch_(other.pitch_) {
	other.texture_ = nullptr;
	other.pixels_ = nullptr;
	other.pitch_ = 0;
}

Texture::LockHandle& Texture::LockHandle::operator=(Texture::LockHandle&& other) noexcept {
	if (&other == this)
		return *this;

	if (texture_ != nullptr)
		SDL_UnlockTexture(texture_->Get());

	texture_ = other.texture_;
	pixels_ = other.pixels_;
	pitch_ = other.pitch_;

	other.texture_ = nullptr;
	other.pixels_ = nullptr;
	other.pitch_ = 0;

	return *this;
}

Texture::LockHandle::~LockHandle() {
	if (texture_ != nullptr)
		SDL_UnlockTexture(texture_->Get());
}

void* Texture::LockHandle::GetPixels() const {
	return pixels_;
}

int Texture::LockHandle::GetPitch() const {
	return pitch_;
}

}
