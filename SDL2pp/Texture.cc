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

#include <utility>
#include <algorithm>
#include <cassert>

#include <SDL2pp/Config.hh>

#include <SDL_render.h>
#ifdef SDL2PP_WITH_IMAGE
#	include <SDL_image.h>
#endif

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Config.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Surface.hh>
#ifdef SDL2PP_WITH_IMAGE
#	include <SDL2pp/RWops.hh>
#endif

namespace SDL2pp {

Texture::Texture(SDL_Texture* texture) : texture_(texture) {
	assert(texture);
}

Texture::Texture(Renderer& renderer, Uint32 format, int access, int w, int h) {
	if ((texture_ = SDL_CreateTexture(renderer.Get(), format, access, w, h)) == nullptr)
		throw Exception("SDL_CreateTexture");
}

#ifdef SDL2PP_WITH_IMAGE
Texture::Texture(Renderer& renderer, RWops& rwops) {
	if ((texture_ = IMG_LoadTexture_RW(renderer.Get(), rwops.Get(), 0)) == nullptr)
		throw Exception("IMG_LoadTexture_RW");
}

Texture::Texture(Renderer& renderer, const std::string& path) {
	if ((texture_ = IMG_LoadTexture(renderer.Get(), path.c_str())) == nullptr)
		throw Exception("IMG_LoadTexture");
}
#endif

Texture::Texture(Renderer& renderer, const Surface& surface) {
	if ((texture_ = SDL_CreateTextureFromSurface(renderer.Get(), surface.Get())) == nullptr)
		throw Exception("SDL_CreateTextureFromSurface");
}

Texture::~Texture() {
	if (texture_ != nullptr)
		SDL_DestroyTexture(texture_);
}

Texture::Texture(Texture&& other) noexcept : texture_(other.texture_) {
	other.texture_ = nullptr;
}

Texture& Texture::operator=(Texture&& other) noexcept {
	if (&other == this)
		return *this;
	if (texture_ != nullptr)
		SDL_DestroyTexture(texture_);
	texture_ = other.texture_;
	other.texture_ = nullptr;
	return *this;
}

SDL_Texture* Texture::Get() const {
	return texture_;
}

Texture& Texture::Update(const Optional<Rect>& rect, const void* pixels, int pitch) {
	if (SDL_UpdateTexture(texture_, rect ? &*rect : nullptr, pixels, pitch) != 0)
		throw Exception("SDL_UpdateTexture");
	return *this;
}

Texture& Texture::Update(const Optional<Rect>& rect, Surface& surface) {
	Rect real_rect = rect ? *rect : Rect(0, 0, GetWidth(), GetHeight());

	real_rect.w = std::min(real_rect.w, surface.GetWidth());
	real_rect.h = std::min(real_rect.h, surface.GetHeight());

	if (GetFormat() == surface.GetFormat()) {
		Surface::LockHandle lock = surface.Lock();

		return Update(real_rect, lock.GetPixels(), lock.GetPitch());
	} else {
		Surface converted = surface.Convert(GetFormat());
		Surface::LockHandle lock = converted.Lock();

		return Update(real_rect, lock.GetPixels(), lock.GetPitch());
	}
}

Texture& Texture::Update(const Optional<Rect>& rect, Surface&& surface) {
	Rect real_rect = rect ? *rect : Rect(0, 0, GetWidth(), GetHeight());

	real_rect.w = std::min(real_rect.w, surface.GetWidth());
	real_rect.h = std::min(real_rect.h, surface.GetHeight());

	if (GetFormat() == surface.GetFormat()) {
		Surface::LockHandle lock = surface.Lock();

		return Update(real_rect, lock.GetPixels(), lock.GetPitch());
	} else {
		Surface converted = surface.Convert(GetFormat());
		Surface::LockHandle lock = converted.Lock();

		return Update(real_rect, lock.GetPixels(), lock.GetPitch());
	}
}

Texture& Texture::UpdateYUV(const Optional<Rect>& rect, const Uint8* yplane, int ypitch, const Uint8* uplane, int upitch, const Uint8* vplane, int vpitch) {
	if (SDL_UpdateYUVTexture(texture_, rect ? &*rect : nullptr, yplane, ypitch, uplane, upitch, vplane, vpitch) != 0)
		throw Exception("SDL_UpdateYUVTexture");
	return *this;
}

Texture& Texture::SetBlendMode(SDL_BlendMode blendMode) {
	if (SDL_SetTextureBlendMode(texture_, blendMode) != 0)
		throw Exception("SDL_SetTextureBlendMode");
	return *this;
}

Texture& Texture::SetAlphaMod(Uint8 alpha) {
	if (SDL_SetTextureAlphaMod(texture_, alpha) != 0)
		throw Exception("SDL_SetTextureAlphaMod");
	return *this;
}

Texture& Texture::SetColorMod(Uint8 r, Uint8 g, Uint8 b) {
	if (SDL_SetTextureColorMod(texture_, r, g, b) != 0)
		throw Exception("SDL_SetTextureColorMod");
	return *this;
}

Texture& Texture::SetColorAndAlphaMod(const Color& color) {
	return SetColorMod(color.r, color.g, color.b).SetAlphaMod(color.a);
}

Texture::LockHandle Texture::Lock(const Optional<Rect>& rect) {
	return LockHandle(this, rect);
}

Uint32 Texture::GetFormat() const {
	Uint32 format;
	if (SDL_QueryTexture(texture_, &format, nullptr, nullptr, nullptr) != 0)
		throw Exception("SDL_QueryTexture");
	return format;
}

int Texture::GetAccess() const {
	int access;
	if (SDL_QueryTexture(texture_, nullptr, &access, nullptr, nullptr) != 0)
		throw Exception("SDL_QueryTexture");
	return access;
}

int Texture::GetWidth() const {
	int w;
	if (SDL_QueryTexture(texture_, nullptr, nullptr, &w, nullptr) != 0)
		throw Exception("SDL_QueryTexture");
	return w;
}

int Texture::GetHeight() const {
	int h;
	if (SDL_QueryTexture(texture_, nullptr, nullptr, nullptr, &h) != 0)
		throw Exception("SDL_QueryTexture");
	return h;
}

Point Texture::GetSize() const {
	int w, h;
	if (SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h) != 0)
		throw Exception("SDL_QueryTexture");
	return Point(w, h);
}

Uint8 Texture::GetAlphaMod() const {
	Uint8 alpha;
	if (SDL_GetTextureAlphaMod(texture_, &alpha) != 0)
		throw Exception("SDL_GetTextureAlphaMod");
	return alpha;
}

SDL_BlendMode Texture::GetBlendMode() const {
	SDL_BlendMode mode;
	if (SDL_GetTextureBlendMode(texture_, &mode) != 0)
		throw Exception("SDL_GetTextureBlendMode");
	return mode;
}

void Texture::GetColorMod(Uint8& r, Uint8& g, Uint8& b) const {
	if (SDL_GetTextureColorMod(texture_, &r, &g, &b) != 0)
		throw Exception("SDL_GetTextureColorMod");
}

Color Texture::GetColorAndAlphaMod() const {
	Color color;
	GetColorMod(color.r, color.g, color.b);
	color.a = GetAlphaMod();
	return color;
}

}
