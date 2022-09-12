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

int main(int, char*[]) try {
	SDL sdl(SDL_INIT_VIDEO);
	Window window("libSDL2pp demo: sprites", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprite texture
	Texture sprite(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 4, 4);
	sprite.Update(NullOpt, pixels, 4 * 4);
	sprite.SetBlendMode(SDL_BLENDMODE_BLEND);

	render.SetDrawBlendMode(SDL_BLENDMODE_BLEND);

	while (1) {
		// Process input
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)))
				return 0;

		// Clear screen
		render.SetDrawColor(0, 32, 32);
		render.Clear();

		// Simple copy
		render.Copy(sprite, NullOpt, Rect(80, 0, 240, 240));

		// Copy with modulation
		render.Copy(sprite, NullOpt, Rect(400, 0, 120, 120));
		sprite.SetAlphaMod(92);
		render.Copy(sprite, NullOpt, Rect(400 + 120, 0, 120, 120));
		sprite.SetColorMod(255, 0, 0);
		render.Copy(sprite, NullOpt, Rect(400, 0 + 120, 120, 120));
		sprite.SetAlphaMod();
		render.Copy(sprite, NullOpt, Rect(400 + 120, 0 + 120, 120, 120));
		sprite.SetColorMod();

		// Copy with rotation
		render.Copy(sprite, NullOpt, Rect(80, 240, 240, 240), -1.0 * SDL_GetTicks() / 5000.0 * 360.0, NullOpt, SDL_FLIP_NONE);

		// Rotation around another point
		render.Copy(sprite, NullOpt, Rect(520, 360, 120, 120), -1.0 * SDL_GetTicks() / 5000.0 * 360.0, Point(0, 0), SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

		render.Present();

		// Frame limiter
		SDL_Delay(1);
	}

	return 0;
} catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
