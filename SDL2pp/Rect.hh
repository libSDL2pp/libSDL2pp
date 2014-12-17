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

#ifndef SDL2PP_RECT_HH
#define SDL2PP_RECT_HH

#include <SDL2/SDL_rect.h>

struct SDL_Rect;

namespace SDL2pp {

class Point;

class Rect {
private:
	SDL_Rect rect_;
	bool valid_;

private:
	Rect();

public:
	Rect(int x, int y, int w, int h);
	virtual ~Rect();

	static Rect Null();

	static Rect FromCenter(int cx, int cy, int w, int h);

	Rect(const Rect&) noexcept = default;
	Rect(Rect&&) noexcept = default;
	Rect& operator=(const Rect&) noexcept = default;
	Rect& operator=(Rect&&) noexcept = default;

	bool operator==(const Rect& other) const;
	bool operator!=(const Rect& other) const;

	SDL_Rect* Get();
	const SDL_Rect* Get() const;

	bool IsNull() const;

	int GetX() const;
	void SetX(int x);

	int GetY() const;
	void SetY(int y);

	int GetW() const;
	void SetW(int w);

	int GetH() const;
	void SetH(int h);

	int GetX2() const;
	void SetX2(int x2);

	int GetY2() const;
	void SetY2(int y2);

	bool Contains(const Point& point) const;
};

}

#endif
