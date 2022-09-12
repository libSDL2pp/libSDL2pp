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

#ifndef SDL2PP_POINT_HH
#define SDL2PP_POINT_HH

#include <iostream>
#include <functional>

#include <SDL_rect.h>

#include <SDL2pp/Export.hh>

namespace SDL2pp {

class Rect;

////////////////////////////////////////////////////////////
/// \brief 2D point
///
/// \ingroup geometry
///
/// \headerfile SDL2pp/Point.hh
///
/// This class is public-derived from SDL_Point structure,
/// may generally used as it if passed via pointer or
/// reference. It also supports direct access to x and y
/// members.
///
/// \see http://wiki.libsdl.org/SDL_Point
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Point : public SDL_Point {
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Point(0, 0)
	///
	////////////////////////////////////////////////////////////
	constexpr Point() : SDL_Point{0, 0} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct a point from existing SDL_Point
	///
	/// \param[in] point Existing SDL_Point
	///
	////////////////////////////////////////////////////////////
	constexpr Point(const SDL_Point& point) : SDL_Point{point.x, point.y} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the point from given coordinates
	///
	/// \param[in] x X coordinate
	/// \param[in] y Y coordinate
	///
	////////////////////////////////////////////////////////////
	constexpr Point(int x, int y) : SDL_Point{x, y} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Copy constructor
	///
	////////////////////////////////////////////////////////////
	Point(const Point&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	////////////////////////////////////////////////////////////
	Point(Point&&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Assignment operator
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator=(const Point&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator=(Point&&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Get X coordinate of the point
	///
	/// \returns X coordinate of the point
	///
	////////////////////////////////////////////////////////////
	constexpr int GetX() const {
		return x;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set X coordinate of the point
	///
	/// \param[in] nx New X coordinate value
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& SetX(int nx) {
		x = nx;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get Y coordinate of the point
	///
	/// \returns Y coordinate of the point
	///
	////////////////////////////////////////////////////////////
	constexpr int GetY() const {
		return y;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set Y coordinate of the point
	///
	/// \param[in] ny New Y coordinate value
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& SetY(int ny) {
		y = ny;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise negation
	///
	/// \returns New Point representing memberwise negation
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator-() const {
		return Point(-x, -y);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise addition with another point
	///
	/// \param[in] other Point to add
	///
	/// \returns New Point representing memberwise addition with another point
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator+(const Point& other) const {
		return Point(x + other.x, y + other.y);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise subtraction with another point
	///
	/// \param[in] other Point to subtract
	///
	/// \returns New Point representing memberwise subtraction of another point
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator-(const Point& other) const {
		return Point(x - other.x, y - other.y);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise division by an integer
	///
	/// \param[in] value Divisor
	///
	/// \returns New Point representing memberwise division of
	///          point by an integer
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator/(int value) const {
		return Point(x / value, y / value);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise division by another point
	///
	/// \param[in] other Divisor
	///
	/// \returns New Point representing memberwise division of
	///          point by another point
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator/(const Point& other) const {
		return Point(x / other.x, y / other.y);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise remainder from division
	///        by an integer
	///
	/// \param[in] value Divisor
	///
	/// \returns New Point representing memberwise remainder
	///          from division by an integer
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator%(int value) const {
		return Point(x % value, y % value);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise remainder from division
	///        by another point
	///
	/// \param[in] other Divisor
	///
	/// \returns New Point representing memberwise remainder
	///          from division by another point
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator%(const Point& other) const {
		return Point(x % other.x, y % other.y);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise multiplication by an
	///        integer
	///
	/// \param[in] value Multiplier
	///
	/// \returns New Point representing memberwise multiplication
	///          of point by an integer
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator*(int value) const {
		return Point(x * value, y * value);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get point's memberwise multiplication by anoter
	///        point
	///
	/// \param[in] other Multiplier
	///
	/// \returns New Point representing memberwise multiplication
	///          of point by another point
	///
	////////////////////////////////////////////////////////////
	constexpr Point operator*(const Point& other) const {
		return Point(x * other.x, y * other.y);
	}

	////////////////////////////////////////////////////////////
	/// \brief Memberwise add another point
	///
	/// \param[in] other Point to add to the current one
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator+=(const Point& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Memberwise subtract another point
	///
	/// \param[in] other Point to subtract from the current one
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator-=(const Point& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Memberwise divide by an integer
	///
	/// \param[in] value Divisor
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator/=(int value) {
		x /= value;
		y /= value;
		return *this;
	}

	///////////////////////////////////////////////////////////
	/// nbrief Memberwise divide by another point
	///
	/// \param[in] other Divisor
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator/=(const Point& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Memberwise remainder from division by an integer
	///
	/// \param[in] value Divisor
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator%=(int value) {
		x %= value;
		y %= value;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Memberwise remainder from division by another
	///        point
	///
	/// \param[in] other Divisor
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator%=(const Point& other) {
		x %= other.x;
		y %= other.y;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Memberwise multiply by an integer
	///
	/// \param[in] value Multiplier
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator*=(int value) {
		x *= value;
		y *= value;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Memberwise multiply by another point
	///
	/// \param[in] other Multiplier
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator*=(const Point& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get a point with coordinates modified so it fits
	///        into a given rect
	///
	/// \param[in] rect Rectangle to clamp with
	///
	/// \returns Clamped point
	///
	////////////////////////////////////////////////////////////
	Point GetClamped(const Rect& rect) const;

	////////////////////////////////////////////////////////////
	/// \brief Clamp point coordinates to make it fit into a
	///        given rect
	///
	/// \param[in] rect Rectangle to clamp with
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& Clamp(const Rect& rect);

	////////////////////////////////////////////////////////////
	/// \brief Get a point wrapped within a specified rect
	///
	/// \param[in] rect Rectangle to wrap with
	///
	/// \returns Wrapped point
	///
	////////////////////////////////////////////////////////////
	Point GetWrapped(const Rect& rect) const;

	////////////////////////////////////////////////////////////
	/// \brief Wrap point coordinates within a spedified rect
	///
	/// \param[in] rect Rectangle to wrap with
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& Wrap(const Rect& rect);
};

}

////////////////////////////////////////////////////////////
/// \brief Equality operator for SDL2pp::Point
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if two points are identical
///
////////////////////////////////////////////////////////////
constexpr bool operator==(const SDL2pp::Point&a, const SDL2pp::Point& b) {
	return a.x == b.x && a.y == b.y;
}

////////////////////////////////////////////////////////////
/// \brief Inequality operator for SDL2pp::Point
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if two points are not identical
///
////////////////////////////////////////////////////////////
constexpr bool operator!=(const SDL2pp::Point& a, const SDL2pp::Point& b) {
	return !(a == b);
}

////////////////////////////////////////////////////////////
/// \brief Less-than operator for SDL2pp::Point
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if a < b
///
////////////////////////////////////////////////////////////
SDL2PP_EXPORT bool operator<(const SDL2pp::Point& a, const SDL2pp::Point& b);

////////////////////////////////////////////////////////////
/// \brief Stream output operator overload for SDL2pp::Point
///
/// \param[in] stream Stream to output to
/// \param[in] point Point to output
///
/// \returns stream
///
////////////////////////////////////////////////////////////
SDL2PP_EXPORT std::ostream& operator<<(std::ostream& stream, const SDL2pp::Point& point);

namespace std {

////////////////////////////////////////////////////////////
/// \brief std::hash specialization for SDL2pp::Rect
///
////////////////////////////////////////////////////////////
template<>
struct hash<SDL2pp::Point> {
	////////////////////////////////////////////////////////////
	/// \brief Hash function for SDL2pp::Point
	///
	/// \param[in] p Input Point
	///
	/// \returns Hash value
	///
	////////////////////////////////////////////////////////////
	size_t operator()(const SDL2pp::Point& p) const {
		size_t seed = std::hash<int>()(p.x);
		seed ^= std::hash<int>()(p.y) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	}
};

}

#endif
