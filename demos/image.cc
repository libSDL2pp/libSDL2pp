/*
  libSDL2pp - C++ wrapper for libSDL2
  Copyright (C) 2013-2014 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2/SDL.h>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

int Run() {
	SDL sdl(SDL_INIT_VIDEO);
	Window window("libSDL2pp demo: loading", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprite texture
	Texture sprite(render, TESTDATA_DIR "/test.png");
	sprite.SetBlendMode(SDL_BLENDMODE_BLEND);

	render.SetDrawBlendMode(SDL_BLENDMODE_BLEND);

	while (1) {
		// Process input
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)))
				return 0;

		// Clear screen
		render.SetDrawColor(255, 255, 255);
		render.Clear();

		// Simple copy
		float angle = SDL_GetTicks() / 5000.0 * 2.0 * M_PI;
		render.Copy(sprite, Rect::Null(), Rect(320 - 64, 240 - 64, 128, 128), angle / M_PI * 180.0);
		render.Copy(sprite, Rect::Null(), Rect(320 - 32 + sin(angle) * 40, 240 - 32 + cos(angle) * 40, 64, 64));
		render.Copy(sprite, Rect::Null(), Rect(320 - 32 - sin(angle) * 40, 240 - 32 - cos(angle) * 40, 64, 64));

		render.Present();

		// Frame limiter
		SDL_Delay(1);
	}

	return 0;
}

int main() {
	try {
		return Run();
	} catch (Exception& e) {
		std::cerr << "Error: " << e.what() << " (" << e.GetSDLError() << ")" << std::endl;
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return -1;
}
