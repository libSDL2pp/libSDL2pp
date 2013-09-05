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

#include <SDL2/SDL.h>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Point.hh>

namespace SDL2pp {

Renderer::Renderer(Window& window, int index, Uint32 flags) {
	if ((renderer_ = SDL_CreateRenderer(window.Get(), index, flags)) == nullptr)
		throw Exception("SDL_CreateRenderer failed");
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer_);
}

SDL_Renderer* Renderer::Get() const {
	return renderer_;
}

void Renderer::SetLogicalSize(int w, int h) {
	if (SDL_RenderSetLogicalSize(renderer_, w, h) != 0)
		throw Exception("SDL_RenderSetLogicalSize failed");
}

void Renderer::Present() {
	SDL_RenderPresent(renderer_);
}

void Renderer::Clear() {
	if (SDL_RenderClear(renderer_) != 0)
		throw Exception("SDL_RenderClear failed");
}

void Renderer::Copy(Texture& texture, const Rect& srcrect, const Rect& dstrect) {
	if (SDL_RenderCopy(renderer_, texture.Get(), srcrect.Get(), dstrect.Get()) != 0)
		throw Exception("SDL_RenderCopy failed");
}

void Renderer::Copy(Texture& texture, const Rect& srcrect, const Rect& dstrect, double angle, const Point& center, SDL_RendererFlip flip) {
	if (SDL_RenderCopyEx(renderer_, texture.Get(), srcrect.Get(), dstrect.Get(), angle, center.Get(), flip) != 0)
		throw Exception("SDL_RenderCopyEx failed");
}

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (SDL_SetRenderDrawColor(renderer_, r, g, b, a) != 0)
		throw Exception("SDL_SetRenderDrawColor failed");
}

void Renderer::SetTarget(Texture& texture) {
	if (SDL_SetRenderTarget(renderer_, texture.Get()) != 0)
		throw Exception("SDL_SetRenderTarget failed");
}

}
