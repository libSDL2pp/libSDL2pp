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

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

#define RGBA(r, g, b, a) r, g, b, a
unsigned char pixels[4 * 4 * 4] = {
	RGBA(0xff, 0x00, 0x00, 0xff), RGBA(0xff, 0x80, 0x00, 0xff), RGBA(0xff, 0xff, 0x00, 0xff), RGBA(0x80, 0xff, 0x00, 0xff),
	RGBA(0xff, 0x00, 0x80, 0xff), RGBA(0xff, 0xff, 0xff, 0xff), RGBA(0x00, 0x00, 0x00, 0x00), RGBA(0x00, 0xff, 0x00, 0xff),
	RGBA(0xff, 0x00, 0xff, 0xff), RGBA(0x00, 0x00, 0x00, 0x00), RGBA(0x00, 0x00, 0x00, 0xff), RGBA(0x00, 0xff, 0x80, 0xff),
	RGBA(0x80, 0x00, 0xff, 0xff), RGBA(0x00, 0x00, 0xff, 0xff), RGBA(0x00, 0x80, 0xff, 0xff), RGBA(0x00, 0xff, 0xff, 0xff),
};

int main() {
	SDL sdl(SDL_INIT_VIDEO);
	Window window("libSDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
	Texture sprite(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 4, 4);

	sprite.Update(Rect::Null(), pixels, 4 * 4);
	sprite.SetBlendMode(SDL_BLENDMODE_BLEND);

	render.SetDrawBlendMode(SDL_BLENDMODE_BLEND);

	while (1) {
		// Process events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return 0;
		}

		// Render
		render.SetDrawColor(0, 0, 0);
		render.Clear();

		// Render lines
		render.SetDrawColor(255, 0, 0);
		render.DrawLine(10, 10, 630, 10);
		render.SetDrawColor(0, 255, 0);
		render.DrawLine(630, 10, 630, 470);
		render.SetDrawColor(0, 0, 255);
		render.DrawLine(630, 470, 10, 470);
		render.SetDrawColor(255, 255, 255);
		render.DrawLine(10, 470, 10, 10);

		render.SetDrawColor(255, 255, 255, 127);
		render.FillRect(0, 0, 20, 20);
		render.SetDrawColor(255, 255, 255);
		render.DrawRect(0, 0, 20, 20);

		// Pixel-perfectness test
		render.SetDrawColor(192, 192, 192);
		render.DrawLine(6, 2, 6, 10);
		render.DrawLine(2, 6, 10, 6);

		render.SetDrawColor(255, 255, 255);
		render.DrawRect(5, 5, 7, 7);
		render.DrawRect(3, 3, 9, 9);

		// Render 4 smaller squares
		sprite.SetAlphaMod(0xff);
		render.Copy(sprite, Rect::Null(), Rect(80, 0, 240, 240), SDL_GetTicks() / 5000.0 * 360.0, Point::Null(), SDL_FLIP_NONE);
		render.Copy(sprite, Rect::Null(), Rect(80, 360, 240, 240), -1.0 * SDL_GetTicks() / 5000.0 * 360.0, Point::Null(), SDL_FLIP_NONE);
		render.Copy(sprite, Rect::Null(), Rect(400, 0, 240, 240), -1.0 * SDL_GetTicks() / 5000.0 * 360.0, Point::Null(), SDL_FLIP_NONE);
		render.Copy(sprite, Rect::Null(), Rect(400, 360, 240, 240), SDL_GetTicks() / 5000.0 * 360.0, Point::Null(), SDL_FLIP_NONE);

		// Render transparent bigger square
		sprite.SetAlphaMod(0x80);
		render.Copy(sprite, Rect::Null(), Rect(80, 0, 480, 480), SDL_GetTicks() / 10000.0 * 360.0, Point::Null(), SDL_FLIP_NONE);

		render.Present();

		// Frame limiter
		SDL_Delay(1);
	}

	return 0;
}
