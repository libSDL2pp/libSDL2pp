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

#ifndef SDL2PP_POINT_HH
#define SDL2PP_POINT_HH

#include <SDL2/SDL_rect.h>

#include <SDL2pp/Config.hh>
#include <SDL2pp/Optional.hh> // for deprecated functionality

namespace SDL2pp {

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
class Point : public SDL_Point {
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Point(0, 0)
	///
	////////////////////////////////////////////////////////////
	Point();

	////////////////////////////////////////////////////////////
	/// \brief Construct the point from given coordinates
	///
	/// \param nx X coordinate
	/// \param ny Y coordinate
	///
	////////////////////////////////////////////////////////////
	Point(int nx, int ny);

	SDL2PP_DEPRECATED static Optional<Point> Null();

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
	/// \brief Equality operator
	///
	/// \param other Point to compare to
	///
	/// \returns True if two points are identical
	///
	////////////////////////////////////////////////////////////
	bool operator==(const Point& other) const;

	////////////////////////////////////////////////////////////
	/// \brief Inequality operator
	///
	/// \param other Point to compare to
	///
	/// \returns True if two points are not identical
	///
	////////////////////////////////////////////////////////////
	bool operator!=(const Point& other) const;

	SDL2PP_DEPRECATED SDL_Point* Get();
	SDL2PP_DEPRECATED const SDL_Point* Get() const;

	SDL2PP_DEPRECATED bool IsNull() const;

	////////////////////////////////////////////////////////////
	/// \brief Get X coordinate of the point
	///
	/// \returns X coordinate of the point
	///
	////////////////////////////////////////////////////////////
	int GetX() const;

	////////////////////////////////////////////////////////////
	/// \brief Set X coordinate of the point
	///
	/// \param nx New X coordinate value
	///
	////////////////////////////////////////////////////////////
	void SetX(int nx);

	////////////////////////////////////////////////////////////
	/// \brief Get Y coordinate of the point
	///
	/// \returns Y coordinate of the point
	///
	////////////////////////////////////////////////////////////
	int GetY() const;

	////////////////////////////////////////////////////////////
	/// \brief Set Y coordinate of the point
	///
	/// \param ny New Y coordinate value
	///
	////////////////////////////////////////////////////////////
	void SetY(int ny);

	////////////////////////////////////////////////////////////
	/// \brief Get sum of two points
	///
	/// \param other Point to add
	///
	/// \returns New Point representing memberwise addition of two points
	///
	////////////////////////////////////////////////////////////
	Point operator+(const Point& other) const;

	////////////////////////////////////////////////////////////
	/// \brief Get subtraction of two points
	///
	/// \param other Point to subtract
	///
	/// \returns New Point representing memberwise subtraction of two points
	///
	////////////////////////////////////////////////////////////
	Point operator-(const Point& other) const;

	////////////////////////////////////////////////////////////
	/// \brief Add another point
	///
	/// \param other Point to add to the current one
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator+=(const Point& other);

	////////////////////////////////////////////////////////////
	/// \brief Substact another point
	///
	/// \param other Point to subtract from the current one
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Point& operator-=(const Point& other);
};

}

#endif
