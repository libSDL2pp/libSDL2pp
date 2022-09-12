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
#include <vector>

#include <SDL_stdinc.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

using namespace SDL2pp;

int main(int, char*[]) try {
	SDL sdl(SDL_INIT_VIDEO);
	SDLTTF ttf;
	Window window("libSDL2pp demo: font", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED);

	Font font(TESTDATA_DIR "/Vera.ttf", 30);

	std::vector<Texture> textures;

	textures.emplace_back(render,
			font.RenderText_Solid("Hello, world! (solid mode)", SDL_Color{255, 255, 255, 255})
		);
	textures.emplace_back(render,
			font.RenderText_Shaded("Hello, world! (shaded mode)", SDL_Color{255, 255, 255, 255}, SDL_Color{127, 127, 127, 255})
		);
	textures.emplace_back(render,
			font.RenderText_Blended("Hello, world! (blended mode)", SDL_Color{255, 255, 255, 255})
		);

	font.SetOutline(1);

	textures.emplace_back(render,
			font.RenderText_Blended("Hello, world! (blended + outline)", SDL_Color{255, 255, 255, 255})
		);

	font.SetOutline(0);

	textures.emplace_back(render,
			font.RenderUTF8_Blended(u8"Hello, world! «¼½¾» (UTF-8 support)", SDL_Color{255, 255, 255, 255})
		);
	textures.emplace_back(render,
			font.RenderUNICODE_Blended(u"Hello, world! «¼½¾» (UTF-16 support)", SDL_Color{255, 255, 255, 255})
		);

	while (1) {
		// Process input
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)))
				return 0;

		// Clear screen
		render.SetDrawColor(0, 63, 63);
		render.Clear();

		// Render all strings
		int h = 0;
		for (auto& texture: textures) {
			render.Copy(texture, NullOpt, Rect(0, h, texture.GetWidth(), texture.GetHeight()));
			h += texture.GetHeight();
		}

		render.Present();

		// Frame limiter
		SDL_Delay(1);
	}

	return 0;
} catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
}
