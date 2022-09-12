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

#include <iostream>

#include <SDL.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

using namespace SDL2pp;

#define RGBA(r, g, b, a) r, g, b, a
static const unsigned char pixels[4 * 4 * 4] = {
	RGBA(0xff, 0x00, 0x00, 0xff), RGBA(0xff, 0x80, 0x00, 0xff), RGBA(0xff, 0xff, 0x00, 0xff), RGBA(0x80, 0xff, 0x00, 0xff),
	RGBA(0xff, 0x00, 0x80, 0xff), RGBA(0xff, 0xff, 0xff, 0xff), RGBA(0x00, 0x00, 0x00, 0x00), RGBA(0x00, 0xff, 0x00, 0xff),
	RGBA(0xff, 0x00, 0xff, 0xff), RGBA(0x00, 0x00, 0x00, 0x00), RGBA(0x00, 0x00, 0x00, 0xff), RGBA(0x00, 0xff, 0x80, 0xff),
	RGBA(0x80, 0x00, 0xff, 0xff), RGBA(0x00, 0x00, 0xff, 0xff), RGBA(0x00, 0x80, 0xff, 0xff), RGBA(0x00, 0xff, 0xff, 0xff),
};

enum {
	MY_SPRITE_SIZE = 4,
	MY_SCREEN_WIDTH = 640,
	MY_SCREEN_HEIGHT = 480,
	MY_RENDERTARGET_SIZE = 512,
};

int main(int, char*[]) try {
	SDL sdl(SDL_INIT_VIDEO);
	Window window("libSDL2pp demo: sprites", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MY_SCREEN_WIDTH, MY_SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	render.SetDrawBlendMode(SDL_BLENDMODE_BLEND);

	// Necessary checks according to SDL docs
	SDL_RendererInfo ri;
	render.GetInfo(ri);

	if (!(ri.flags & SDL_RENDERER_TARGETTEXTURE)) {
		std::cerr << "Sorry, your renderer doesn't support texture targets" << std::endl;
		return 1;
	}

	// Sprite data
	Texture sprite(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, MY_SPRITE_SIZE, MY_SPRITE_SIZE);

	sprite.Update(NullOpt, pixels, MY_SPRITE_SIZE * MY_SPRITE_SIZE);
	sprite.SetBlendMode(SDL_BLENDMODE_BLEND);

	// Two render target textures
	Texture target1(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, MY_RENDERTARGET_SIZE, MY_RENDERTARGET_SIZE);
	target1.SetBlendMode(SDL_BLENDMODE_BLEND);

	Texture target2(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, MY_RENDERTARGET_SIZE, MY_RENDERTARGET_SIZE);
	target2.SetBlendMode(SDL_BLENDMODE_BLEND);

	while (1) {
		// Process input
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)))
				return 0;

		// Note we fill with transparent color, not black
		render.SetDrawColor(0, 0, 0, 0);

		// Fill base texture with sprite texture
		render.SetTarget(target1);
		render.Clear();
		render.Copy(sprite);

		// Repeat several cycles of flip-flop tiling
		for (int i = 0; i < 4; i++) {
			render.SetTarget(target2);
			render.Clear();
			render.Copy(target1, NullOpt, Rect(0, 0, MY_RENDERTARGET_SIZE / 2, MY_RENDERTARGET_SIZE / 2), SDL_GetTicks() / 10000.0 * 360.0);
			render.Copy(target1, NullOpt, Rect(MY_RENDERTARGET_SIZE / 2, 0, MY_RENDERTARGET_SIZE / 2, MY_RENDERTARGET_SIZE / 2), SDL_GetTicks() / 10000.0 * 360.0);
			render.Copy(target1, NullOpt, Rect(0, MY_RENDERTARGET_SIZE / 2, MY_RENDERTARGET_SIZE / 2, MY_RENDERTARGET_SIZE / 2), SDL_GetTicks() / 10000.0 * 360.0);
			render.Copy(target1, NullOpt, Rect(MY_RENDERTARGET_SIZE / 2, MY_RENDERTARGET_SIZE / 2, MY_RENDERTARGET_SIZE / 2, MY_RENDERTARGET_SIZE / 2), SDL_GetTicks() / 10000.0 * 360.0);

			// Swap textures to copy recursively
			std::swap(target1, target2);
		}

		// Draw result to screen
		render.SetTarget();
		render.Clear();

		render.Copy(target1, NullOpt, Rect((MY_SCREEN_WIDTH - MY_SCREEN_HEIGHT) / 2, 0, MY_SCREEN_HEIGHT, MY_SCREEN_HEIGHT), SDL_GetTicks() / 10000.0 * 360.0);

		render.Present();

		// Frame limiter
		SDL_Delay(1);
	}

	return 0;
} catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
