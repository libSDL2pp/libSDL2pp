/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
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

#ifndef SDL2PP_WINDOW_HH
#define SDL2PP_WINDOW_HH

#include <string>

#include <SDL2/SDL_stdinc.h>

#include <SDL2pp/Point.hh>

struct SDL_Window;

namespace SDL2pp {

class Window {
private:
	SDL_Window* window_;

public:
	Window(const std::string& title, int x, int y, int w, int h, Uint32 flags);
	virtual ~Window();

	Window(const Window& other) = delete;
	Window(Window&& other) noexcept;
	Window& operator=(const Window& other) = delete;
	Window& operator=(Window&& other) noexcept;

	Point GetSize() const;
	int GetWidth() const;
	int GetHeight() const;

	void SetTitle(const std::string& title);

	SDL_Window* Get() const;
};

}

#endif
