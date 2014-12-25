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

#include <cassert>

#include <SDL2pp/Point.hh>

#include <SDL2pp/Rect.hh>

namespace SDL2pp {

Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
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
	return !(point.x < x || point.y < y || point.x > GetX2() || point.y > GetY2());
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
