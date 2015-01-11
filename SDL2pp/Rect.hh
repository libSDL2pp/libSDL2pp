/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
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

#ifndef SDL2PP_RECT_HH
#define SDL2PP_RECT_HH

#include <SDL2/SDL_rect.h>

#include <SDL2pp/Config.hh>
#include <SDL2pp/Optional.hh> // for deprecated functionality

struct SDL_Rect;

namespace SDL2pp {

class Point;

////////////////////////////////////////////////////////////
/// \brief 2D rectangle
///
/// \ingroup geometry
///
/// \headerfile SDL2pp/Rect.hh
///
/// This class is public-derived from SDL_Rect structure,
/// may generally used as it if passed via pointer or
/// reference. It also supports direct access to x, y, w
/// and h members.
///
/// \see http://wiki.libsdl.org/SDL_Rect
///
////////////////////////////////////////////////////////////
class Rect : public SDL_Rect {
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Rect(0, 0, 0, 0)
	///
	////////////////////////////////////////////////////////////
	Rect();

	////////////////////////////////////////////////////////////
	/// \brief Construct a rect from existing SDL_Rect
	///
	/// \param rect Existing SDL_Rect
	///
	////////////////////////////////////////////////////////////
	Rect(const SDL_Rect& rect);

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given corner coordinates, and size
	///
	/// \param corner Coordinates of the top left rectangle corner
	/// \param size Dimensions of the rectangle
	///
	////////////////////////////////////////////////////////////
	Rect(const Point& corner, const Point& size);

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given corner coordinates, width and height
	///
	/// \param x X coordinate of the top left rectangle corner
	/// \param y Y coordinate of the top left rectangle corner
	/// \param w Width of the rectangle
	/// \param h Height of the rectangle
	///
	////////////////////////////////////////////////////////////
	Rect(int x, int y, int w, int h);

	SDL2PP_DEPRECATED static Optional<Rect> Null();

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given center coordinates, width and height
	///
	/// \param cx X coordinate of the rectangle center
	/// \param cy Y coordinate of the rectangle center
	/// \param w Width of the rectangle
	/// \param h Height of the rectangle
	///
	////////////////////////////////////////////////////////////
	static Rect FromCenter(int cx, int cy, int w, int h);

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given center coordinates and size
	///
	/// \param center Coordinates of the rectangle center
	/// \param size Dimensions of the rectangle
	///
	////////////////////////////////////////////////////////////
	static Rect FromCenter(const Point& center, const Point& size);

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given corners coordinates
	///
	/// \param x1 X coordinate of the top left rectangle corner
	/// \param y1 Y coordinate of the top left rectangle corner
	/// \param x2 X coordinate of the bottom right rectangle corner
	/// \param y2 Y coordinate of the bottom right rectangle corner
	///
	////////////////////////////////////////////////////////////
	static Rect FromCorners(int x1, int y1, int x2, int y2);

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given centers coordinates
	///
	/// \param p1 Coordinates of the top left rectangle corner
	/// \param p2 Coordinates of the bottom right rectangle corner
	///
	////////////////////////////////////////////////////////////
	static Rect FromCorners(const Point& p1, const Point& p2);

	////////////////////////////////////////////////////////////
	/// \brief Copy constructor
	///
	////////////////////////////////////////////////////////////
	Rect(const Rect&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	////////////////////////////////////////////////////////////
	Rect(Rect&&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Assignment operator
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& operator=(const Rect&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& operator=(Rect&&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Equality operator
	///
	/// \param other Rect to compare to
	///
	/// \returns True if two rectangles are identical
	///
	////////////////////////////////////////////////////////////
	bool operator==(const Rect& other) const;

	////////////////////////////////////////////////////////////
	/// \brief Inequality operator
	///
	/// \param other Rect to compare to
	///
	/// \returns True if two rectangles are not identical
	///
	////////////////////////////////////////////////////////////
	bool operator!=(const Rect& other) const;

	SDL2PP_DEPRECATED SDL_Rect* Get();
	SDL2PP_DEPRECATED const SDL_Rect* Get() const;

	SDL2PP_DEPRECATED bool IsNull() const;

	////////////////////////////////////////////////////////////
	/// \brief Get X coordinate of the rect corner
	///
	/// \returns X coordinate of the rect corner
	///
	////////////////////////////////////////////////////////////
	int GetX() const;

	////////////////////////////////////////////////////////////
	/// \brief Set X coordinate of the rect corner
	///
	/// \param nx New X coordinate value
	///
	////////////////////////////////////////////////////////////
	void SetX(int nx);

	////////////////////////////////////////////////////////////
	/// \brief Get Y coordinate of the rect corner
	///
	/// \returns Y coordinate of the rect corner
	///
	////////////////////////////////////////////////////////////
	int GetY() const;

	////////////////////////////////////////////////////////////
	/// \brief Set Y coordinate of the rect corner
	///
	/// \param ny New Y coordinate value
	///
	////////////////////////////////////////////////////////////
	void SetY(int ny);

	////////////////////////////////////////////////////////////
	/// \brief Get width of the rect
	///
	/// \returns Width of the rect
	///
	////////////////////////////////////////////////////////////
	int GetW() const;

	////////////////////////////////////////////////////////////
	/// \brief Set width of the rect
	///
	/// \param nw New width of the rect
	///
	////////////////////////////////////////////////////////////
	void SetW(int nw);

	////////////////////////////////////////////////////////////
	/// \brief Get height of the rect
	///
	/// \returns Height of the rect
	///
	////////////////////////////////////////////////////////////
	int GetH() const;

	////////////////////////////////////////////////////////////
	/// \brief Set height of the rect
	///
	/// \param nh New height of the rect
	///
	////////////////////////////////////////////////////////////
	void SetH(int nh);

	////////////////////////////////////////////////////////////
	/// \brief Get X coordinate of the rect second corner
	///
	/// \returns X coordinate of the rect second corner
	///
	////////////////////////////////////////////////////////////
	int GetX2() const;

	////////////////////////////////////////////////////////////
	/// \brief Set X coordinate of the rect second corner
	///
	/// \param x2 New X coordinate value
	///
	////////////////////////////////////////////////////////////
	void SetX2(int x2);

	////////////////////////////////////////////////////////////
	/// \brief Get Y coordinate of the rect second corner
	///
	/// \returns Y coordinate of the rect second corner
	///
	/// This modifies rectangle width internally
	///
	////////////////////////////////////////////////////////////
	int GetY2() const;

	////////////////////////////////////////////////////////////
	/// \brief Set Y coordinate of the rect second corner
	///
	/// \param y2 New Y coordinate value
	///
	/// This modifies rectangle height internally
	///
	////////////////////////////////////////////////////////////
	void SetY2(int y2);

	////////////////////////////////////////////////////////////
	/// \brief Check whether the rect contains given point
	///
	/// \param x X coordinate of a point
	/// \param y Y coordinate of a point
	///
	/// \returns True if the point is contained in the rect
	///
	////////////////////////////////////////////////////////////
	bool Contains(int x, int y) const;

	////////////////////////////////////////////////////////////
	/// \brief Check whether the rect contains given point
	///
	/// \param point Point to check
	///
	/// \returns True if the point is contained in the rect
	///
	////////////////////////////////////////////////////////////
	bool Contains(const Point& point) const;

	////////////////////////////////////////////////////////////
	/// \brief Check whether the rect contains another rect
	///
	/// \param rect Rect to check
	///
	/// \returns True if the checked rect is contained in this rect
	///
	////////////////////////////////////////////////////////////
	bool Contains(const Rect& rect) const;

	////////////////////////////////////////////////////////////
	/// \brief Check whether the rect intersects another rect
	///
	/// \param rect Rect to check
	///
	/// \returns True if rectangles intersect
	///
	////////////////////////////////////////////////////////////
	bool Intersects(const Rect& rect) const;

	////////////////////////////////////////////////////////////
	/// \brief Calculate union with another rect
	///
	/// \param rect Rect to union with
	///
	/// \returns Rect representing union of two rectangles
	///
	////////////////////////////////////////////////////////////
	Rect GetUnion(const Rect& rect) const;

	////////////////////////////////////////////////////////////
	/// \brief Calculate intersection with another rect
	///
	/// \param rect Rect to intersect with
	///
	/// \returns Rect representing intersection area or NullOpt if there was no intersection
	///
	////////////////////////////////////////////////////////////
	Optional<Rect> GetIntersection(const Rect& rect) const;

	////////////////////////////////////////////////////////////
	/// \brief Get rectangle moved by a given offset
	///
	/// \param offset Point specifying an offset
	///
	/// \returns Moved rectangle
	///
	////////////////////////////////////////////////////////////
	Rect operator+(const Point& offset) const;

	////////////////////////////////////////////////////////////
	/// \brief Get rectangle moved by an opposite of given offset
	///
	/// \param offset Point specifying an offset
	///
	/// \returns Moved rectangle
	///
	////////////////////////////////////////////////////////////
	Rect operator-(const Point& offset) const;

	////////////////////////////////////////////////////////////
	/// \brief Move by then given offset
	///
	/// \param offset Point specifying an offset
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& operator+=(const Point& offset);

	////////////////////////////////////////////////////////////
	/// \brief Move by an opposite of the given offset
	///
	/// \param offset Point specifying an offset
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& operator-=(const Point& offset);
};

}

#endif
