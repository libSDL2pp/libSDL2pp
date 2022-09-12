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

#include <cmath>
#include <iostream>

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

int main(int, char*[]) try {
	SDL sdl(SDL_INIT_VIDEO);
	SDLImage image(IMG_INIT_PNG); // optional
	Window window("libSDL2pp demo: loading", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprite texture; sprite1 and sprite2 are actually the same
	// however first one is loaded directly into texture, and second
	// one is loaded through an intermediary surface
	Surface surf(TESTDATA_DIR "/test.png");

	Texture sprite1(render, TESTDATA_DIR "/test.png");
	Texture sprite2(render, surf);

	sprite1.SetBlendMode(SDL_BLENDMODE_BLEND);
	sprite2.SetBlendMode(SDL_BLENDMODE_BLEND);

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
		float angle = SDL_GetTicks() / 5000.0f * 2.0f * pi;
		render.Copy(sprite1, NullOpt, Rect(320 - 64, 240 - 64, 128, 128), angle / pi * 180.0f);
		render.Copy(sprite1, NullOpt, Rect(320 - 32 + (int)(std::sin(angle) * 40.0f), 240 - 32 + (int)(std::cos(angle) * 40.0f), 64, 64));
		render.Copy(sprite2, NullOpt, Rect(320 - 32 - (int)(std::sin(angle) * 40.0f), 240 - 32 - (int)(std::cos(angle) * 40.0f), 64, 64));

		render.Present();

		// Frame limiter
		SDL_Delay(1);
	}

	return 0;
} catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
