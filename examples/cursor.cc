/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Cursor.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Optional.hh>

using namespace SDL2pp;

Uint8 cursor_data[8] = { 0x38, 0x28, 0xEE, 0x82, 0xEE, 0x28, 0x38, 0x00 };
Uint8 cursor_mask[8] = { 0x38, 0x38, 0xFE, 0xFE, 0xFE, 0x38, 0x38, 0x00 };

Cursor GenCursor(int mode) {
	switch (mode % 4) {
	default:
		return Cursor::CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	case 1:
		return Cursor::CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	case 2:
		return Cursor::CreateCursor(cursor_data, cursor_mask, 8, 8, 3, 3);
	case 3:
		{
			Surface surf(TESTDATA_DIR "/test.png");
			return Cursor::CreateColorCursor(surf, surf.GetWidth() / 2, surf.GetHeight() / 2);
		}
	}
}

int Run() {
	SDL sdl(SDL_INIT_VIDEO);
	Window window("libSDL2pp demo: cursors", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	Renderer render(window, -1, SDL_RENDERER_ACCELERATED);

	int cursormode = 0;
	Optional<Cursor> cur;

	while (1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q))) {
				return 0;
			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
				cur = GenCursor(++cursormode);
				cur->Set();
			}
		}

		// Clear screen
		render.SetDrawColor(0, 32, 32);
		render.Clear();

		render.Present();

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
