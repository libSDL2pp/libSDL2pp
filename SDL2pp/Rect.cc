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

#include <algorithm>

#include <SDL2pp/Point.hh>

#include <SDL2pp/Rect.hh>

namespace SDL2pp {

Rect Rect::GetUnion(const Rect& rect) const {
	return Rect::FromCorners(
			std::min(x, rect.x),
			std::min(y, rect.y),
			std::max(GetX2(), rect.GetX2()),
			std::max(GetY2(), rect.GetY2())
		);
}

Rect& Rect::Union(const Rect& rect) {
	int nx = std::min(x, rect.x);
	int ny = std::min(y, rect.y);
	int nx2 = std::max(GetX2(), rect.GetX2());
	int ny2 = std::max(GetY2(), rect.GetY2());
	x = nx;
	y = ny;
	SetX2(nx2);
	SetY2(ny2);
	return *this;
}

Rect Rect::GetExtension(unsigned int amount) const {
	Rect r = *this;
	r.Extend(amount);
	return r;
}

Rect Rect::GetExtension(unsigned int hamount, unsigned int vamount) const {
	Rect r = *this;
	r.Extend(hamount, vamount);
	return r;
}

Rect& Rect::Extend(unsigned int amount) {
	return Extend(amount, amount);
}

Rect& Rect::Extend(unsigned int hamount, unsigned int vamount) {
	x -= hamount;
	y -= vamount;
	w += hamount * 2;
	h += vamount * 2;
	return *this;
}

Optional<Rect> Rect::GetIntersection(const Rect& rect) const {
	if (!Intersects(rect))
		return NullOpt;

	return Rect::FromCorners(
			std::max(x, rect.x),
			std::max(y, rect.y),
			std::min(GetX2(), rect.GetX2()),
			std::min(GetY2(), rect.GetY2())
		);
}

bool Rect::IntersectLine(int& x1, int& y1, int& x2, int& y2) const {
	return SDL_IntersectRectAndLine(this, &x1, &y1, &x2, &y2) == SDL_TRUE;
}

bool Rect::IntersectLine(Point& p1, Point& p2) const {
	return SDL_IntersectRectAndLine(this, &p1.x, &p1.y, &p2.x, &p2.y) == SDL_TRUE;
}

}

std::ostream& operator<<(std::ostream& stream, const SDL2pp::Rect& rect) {
	stream << "[x:" << rect.x << ",y:" << rect.y << ",w:" << rect.w << ",h:" << rect.h << "]";
	return stream;
}

bool operator<(const SDL2pp::Rect& a, const SDL2pp::Rect& b) {
	if (a.x == b.x) {
		if (a.y == b.y) {
			if (a.w == b.w)
				return a.h < b.h;
			return a.w < b.w;
		}
		return a.y < b.y;
	}
	return a.x < b.x;
}
