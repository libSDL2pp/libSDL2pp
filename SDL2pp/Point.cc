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

namespace SDL2pp {

Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(const SDL_Point& point) {
	x = point.x;
	y = point.y;
}

Point::Point(int nx, int ny) {
	x = nx;
	y = ny;
}

Optional<Point> Point::Null() {
	return NullOpt;
}

bool Point::operator==(const Point& other) const {
	return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
	return !(*this == other);
}

SDL_Point* Point::Get() {
	return this;
}

const SDL_Point* Point::Get() const {
	return this;
}

bool Point::IsNull() const {
	return false;
}

int Point::GetX() const {
	return x;
}

void Point::SetX(int nx) {
	x = nx;
}

int Point::GetY() const {
	return y;
}

void Point::SetY(int ny) {
	y = ny;
}

Point Point::operator+(const Point& other) const {
	return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point& other) const {
	return Point(x - other.x, y - other.y);
}

Point Point::operator/(int value) const {
	return Point(x / value, y / value);
}

Point Point::operator*(int value) const {
	return Point(x * value, y * value);
}

Point& Point::operator+=(const Point& other) {
	x += other.x;
	y += other.y;

	return *this;
}

Point& Point::operator-=(const Point& other) {
	x -= other.x;
	y -= other.y;

	return *this;
}

Point& Point::operator/=(int value) {
	x /= value;
	y /= value;

	return *this;
}

Point& Point::operator*=(int value) {
	x *= value;
	y *= value;

	return *this;
}

}
