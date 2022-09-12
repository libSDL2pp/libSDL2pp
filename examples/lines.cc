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

using namespace SDL2pp;

int main(int, char*[]) try {
	SDL sdl(SDL_INIT_VIDEO);
	Window window("libSDL2pp demo: sprites", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

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

		// Rect corner test
		// This may show diagonal lines:
		// - bright ones indicate that pixels are overdrawn
		// - dark ones indicate that some corner pixels are missing
		// Unfortunately, on most implementations some of
		// these problems exist
		render.SetDrawColor(255, 255, 255, 32);
		for (int i = 0; i < 50; i++)
			render.DrawRect(100+i, 100+i, 200-i, 200-i);

		render.Present();

		// Frame limiter
		SDL_Delay(1);
	}

	return 0;
} catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
