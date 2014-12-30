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

#include <algorithm>

#include <SDL2pp/Point.hh>

#include <SDL2pp/Rect.hh>

namespace SDL2pp {

Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(const SDL_Rect& rect) {
	x = rect.x;
	y = rect.y;
	w = rect.w;
	h = rect.h;
}

Rect::Rect(const Point& corner, const Point& size) {
	x = corner.x;
	y = corner.y;
	w = size.x;
	h = size.y;
}

Rect::Rect(int nx, int ny, int nw, int nh) {
	x = nx;
	y = ny;
	w = nw;
	h = nh;
}

Optional<Rect> Rect::Null() {
	return NullOpt;
}

bool Rect::operator==(const Rect& other) const {
	return x == other.x && y == other.y &&
	       w == other.w && h == other.h;
}

bool Rect::operator!=(const Rect& other) const {
	return !(*this == other);
}

SDL_Rect* Rect::Get() {
	return this;
}

const SDL_Rect* Rect::Get() const {
	return this;
}

Rect Rect::FromCenter(int cx, int cy, int w, int h) {
	return Rect(cx - w/2, cy - h/2, w, h);
}

Rect Rect::FromCenter(const Point& center, const Point& size) {
	return Rect(center - size / 2, size);
}

Rect Rect::FromCorners(int x1, int y1, int x2, int y2) {
	return Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

Rect Rect::FromCorners(const Point& p1, const Point& p2) {
	return Rect(p1, p2 - p1 + Point(1, 1));
}

bool Rect::IsNull() const {
	return false;
}

int Rect::GetX() const {
	return x;
}

void Rect::SetX(int nx) {
	x = nx;
}

int Rect::GetY() const {
	return y;
}

void Rect::SetY(int ny) {
	y = ny;
}

int Rect::GetW() const {
	return w;
}

void Rect::SetW(int nw) {
	w = nw;
}

int Rect::GetH() const {
	return h;
}

void Rect::SetH(int nh) {
	h = nh;
}

int Rect::GetX2() const {
	return x + w - 1;
}

void Rect::SetX2(int x2) {
	w = x2 - x + 1;
}

int Rect::GetY2() const {
	return y + h - 1;
}

void Rect::SetY2(int y2) {
	h = y2 - y + 1;
}

bool Rect::Contains(const Point& point) const {
	return point.x >= x && point.y >= y && point.x <= GetX2() && point.y <= GetY2();
}

bool Rect::Contains(const Rect& rect) const {
	return rect.x >= x && rect.y >= y && rect.GetX2() <= GetX2() && rect.GetY2() <= GetY2();
}

bool Rect::Intersects(const Rect& rect) const {
	return !(rect.GetX2() < x || rect.GetY2() < y || rect.x > GetX2() || rect.y > GetY2());
}

Rect Rect::GetUnion(const Rect& rect) const {
	return Rect::FromCorners(
			std::min(x, rect.x),
			std::min(y, rect.y),
			std::max(GetX2(), rect.GetX2()),
			std::max(GetY2(), rect.GetY2())
		);
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

Rect Rect::operator+(const Point& offset) const {
	return Rect(x + offset.x, y + offset.y, w, h);
}

Rect& Rect::operator+=(const Point& offset) {
	x += offset.x;
	y += offset.y;

	return *this;
}

Rect Rect::operator-(const Point& offset) const {
	return Rect(x - offset.x, y - offset.y, w, h);
}

Rect& Rect::operator-=(const Point& offset) {
	x -= offset.x;
	y -= offset.y;

	return *this;
}

}
