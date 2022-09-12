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
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLImage.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>

using namespace SDL2pp;

static const float pi = 3.14159265358979323846f;

static int Run() {
	SDL sdl(SDL_INIT_VIDEO);
	SDLImage image(IMG_INIT_PNG); // optional
	Window window("libSDL2pp demo: fill", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprite texture; sprite1 and sprite2 are actually the same
	// however first one is loaded directly into texture, and second
	// one is loaded through an intermediary surface
	Surface surf(TESTDATA_DIR "/crate.png");

	Texture sprite(render, TESTDATA_DIR "/crate.png");

	while (1) {
		// Process input
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)))
				return 0;

		// Clear screen
		render.SetDrawColor(255, 255, 255);
		render.Clear();

		// Fill
		float dx = std::sin(SDL_GetTicks() / 5000.0f * pi) * 32.0f;
		float dy = std::cos(SDL_GetTicks() / 10000.0f * pi) * 32.0f;

		render.FillCopy(sprite, NullOpt, Rect(32, 32, window.GetWidth() - 64, window.GetHeight() - 64), SDL2pp::Point((int)dx, (int)dy), SDL_FLIP_HORIZONTAL);

		render.Present();

		// Frame limiter
		SDL_Delay(1);
	}

	return 0;
}

int main(int, char*[]) {
	try {
		return Run();
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return -1;
}
