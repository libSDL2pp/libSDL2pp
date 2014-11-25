/*
  libSDL2pp - C++ wrapper for libSDL2
  Copyright (C) 2013 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2pp/Config.hh>

#include <SDL2/SDL_render.h>
#ifdef SDL2PP_WITH_IMAGE
#	include <SDL2/SDL_image.h>
#endif

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Config.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Rect.hh>
#ifdef SDL2PP_WITH_IMAGE
#	include <SDL2pp/RWops.hh>
#endif

namespace SDL2pp {

Texture::Texture(Renderer& renderer, Uint32 format, int access, int w, int h) {
	if ((texture_ = SDL_CreateTexture(renderer.Get(), format, access, w, h)) == nullptr)
		throw Exception("SDL_CreateTexture failed");
}

#ifdef SDL2PP_WITH_IMAGE
Texture::Texture(Renderer& renderer, RWops& rwops) {
	texture_ = IMG_LoadTexture_RW(renderer.Get(), rwops.Get(), 0);
}

Texture::Texture(Renderer& renderer, const std::string& path) {
	RWops rwops = RWops::FromFile(path);
	texture_ = IMG_LoadTexture_RW(renderer.Get(), rwops.Get(), 0);
}
#endif

Texture::~Texture() {
	if (texture_ != nullptr)
		SDL_DestroyTexture(texture_);
}

Texture::Texture(Texture&& other) noexcept : texture_(other.texture_) {
	other.texture_ = nullptr;
}

Texture& Texture::operator=(Texture&& other) noexcept {
	texture_ = other.texture_;
	other.texture_ = nullptr;
	return *this;
}

SDL_Texture* Texture::Get() const {
	return texture_;
}

void Texture::Update(const Rect& rect, const void* pixels, int pitch) {
	if (SDL_UpdateTexture(texture_, rect.Get(), pixels, pitch) != 0)
		throw Exception("SDL_UpdateTexture failed");
}

void Texture::SetBlendMode(SDL_BlendMode blendMode) {
	if (SDL_SetTextureBlendMode(texture_, blendMode) != 0)
		throw Exception("SDL_SetTextureBlendMode failed");
}

void Texture::SetAlphaMod(Uint8 alpha) {
	if (SDL_SetTextureAlphaMod(texture_, alpha) != 0)
		throw Exception("SDL_SetTextureAlphaMod failed");
}

void Texture::SetColorMod(Uint8 r, Uint8 g, Uint8 b) {
	if (SDL_SetTextureColorMod(texture_, r, g, b) != 0)
		throw Exception("SDL_SetTextureColorMod failed");
}

Texture::LockHandle Texture::Lock(const Rect& rect) {
	return LockHandle(this, rect);
}

Uint32 Texture::GetFormat() const {
	Uint32 format;
	if (SDL_QueryTexture(texture_, &format, nullptr, nullptr, nullptr) != 0)
		throw Exception("SDL_QueryTexture failed");
	return format;
}

int Texture::GetAccess() const {
	int access;
	if (SDL_QueryTexture(texture_, nullptr, &access, nullptr, nullptr) != 0)
		throw Exception("SDL_QueryTexture failed");
	return access;
}

int Texture::GetWidth() const {
	int w;
	if (SDL_QueryTexture(texture_, nullptr, nullptr, &w, nullptr) != 0)
		throw Exception("SDL_QueryTexture failed");
	return w;
}

int Texture::GetHeight() const {
	int h;
	if (SDL_QueryTexture(texture_, nullptr, nullptr, nullptr, &h) != 0)
		throw Exception("SDL_QueryTexture failed");
	return h;
}

}
