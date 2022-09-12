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

#ifndef SDL2PP_RECT_HH
#define SDL2PP_RECT_HH

#include <functional>

#include <SDL_rect.h>

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Export.hh>

namespace SDL2pp {

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
class SDL2PP_EXPORT Rect : public SDL_Rect {
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Rect(0, 0, 0, 0)
	///
	////////////////////////////////////////////////////////////
	constexpr Rect() : SDL_Rect{0, 0, 0, 0} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct a rect from existing SDL_Rect
	///
	/// \param[in] rect Existing SDL_Rect
	///
	////////////////////////////////////////////////////////////
	constexpr Rect(const SDL_Rect& rect) : SDL_Rect{rect.x, rect.y, rect.w, rect.h} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given corner coordinates, and size
	///
	/// \param[in] corner Coordinates of the top left rectangle corner
	/// \param[in] size Dimensions of the rectangle
	///
	////////////////////////////////////////////////////////////
	constexpr Rect(const Point& corner, const Point& size) : SDL_Rect{corner.x, corner.y, size.x, size.y} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given corner coordinates, width and height
	///
	/// \param[in] x X coordinate of the top left rectangle corner
	/// \param[in] y Y coordinate of the top left rectangle corner
	/// \param[in] w Width of the rectangle
	/// \param[in] h Height of the rectangle
	///
	////////////////////////////////////////////////////////////
	constexpr Rect(int x, int y, int w, int h) : SDL_Rect{x, y, w, h} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given center coordinates, width and height
	///
	/// \param[in] cx X coordinate of the rectangle center
	/// \param[in] cy Y coordinate of the rectangle center
	/// \param[in] w Width of the rectangle
	/// \param[in] h Height of the rectangle
	///
	////////////////////////////////////////////////////////////
	static constexpr Rect FromCenter(int cx, int cy, int w, int h) {
		return Rect(cx - w/2, cy - h/2, w, h);
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given center coordinates and size
	///
	/// \param[in] center Coordinates of the rectangle center
	/// \param[in] size Dimensions of the rectangle
	///
	////////////////////////////////////////////////////////////
	static constexpr Rect FromCenter(const Point& center, const Point& size) {
		return Rect(center - size / 2, size);
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given corners coordinates
	///
	/// \param[in] x1 X coordinate of the top left rectangle corner
	/// \param[in] y1 Y coordinate of the top left rectangle corner
	/// \param[in] x2 X coordinate of the bottom right rectangle corner
	/// \param[in] y2 Y coordinate of the bottom right rectangle corner
	///
	////////////////////////////////////////////////////////////
	static constexpr Rect FromCorners(int x1, int y1, int x2, int y2) {
		return Rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the rect from given centers coordinates
	///
	/// \param[in] p1 Coordinates of the top left rectangle corner
	/// \param[in] p2 Coordinates of the bottom right rectangle corner
	///
	////////////////////////////////////////////////////////////
	static constexpr Rect FromCorners(const Point& p1, const Point& p2) {
		return Rect(p1, p2 - p1 + Point(1, 1));
	}

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
	/// \brief Get X coordinate of the rect corner
	///
	/// \returns X coordinate of the rect corner
	///
	////////////////////////////////////////////////////////////
	constexpr int GetX() const {
		return x;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set X coordinate of the rect corner
	///
	/// \param[in] nx New X coordinate value
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& SetX(int nx) {
		x = nx;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get Y coordinate of the rect corner
	///
	/// \returns Y coordinate of the rect corner
	///
	////////////////////////////////////////////////////////////
	constexpr int GetY() const {
		return y;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set Y coordinate of the rect corner
	///
	/// \param[in] ny New Y coordinate value
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& SetY(int ny) {
		y = ny;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get width of the rect
	///
	/// \returns Width of the rect
	///
	////////////////////////////////////////////////////////////
	constexpr int GetW() const {
		return w;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set width of the rect
	///
	/// \param[in] nw New width of the rect
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& SetW(int nw) {
		w = nw;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get height of the rect
	///
	/// \returns Height of the rect
	///
	////////////////////////////////////////////////////////////
	constexpr int GetH() const {
		return h;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set height of the rect
	///
	/// \param[in] nh New height of the rect
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& SetH(int nh) {
		h = nh;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get X coordinate of the rect second corner
	///
	/// \returns X coordinate of the rect second corner
	///
	////////////////////////////////////////////////////////////
	constexpr int GetX2() const {
		return x + w - 1;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set X coordinate of the rect second corner
	///
	/// \param[in] x2 New X coordinate value
	///
	/// This modifies rectangle width internally
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& SetX2(int x2) {
		w = x2 - x + 1;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get Y coordinate of the rect second corner
	///
	/// \returns Y coordinate of the rect second corner
	///
	////////////////////////////////////////////////////////////
	constexpr int GetY2() const {
		return y + h - 1;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set Y coordinate of the rect second corner
	///
	/// \param[in] y2 New Y coordinate value
	///
	/// This modifies rectangle height internally
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& SetY2(int y2) {
		h = y2 - y + 1;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get top left corner of the rect
	///
	/// \returns Top left corner of the rect
	///
	////////////////////////////////////////////////////////////
	constexpr Point GetTopLeft() const {
		return Point(x, y);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get top right corner of the rect
	///
	/// \returns Top right corner of the rect
	///
	////////////////////////////////////////////////////////////
	constexpr Point GetTopRight() const {
		return Point(GetX2(), y);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get bottom left corner of the rect
	///
	/// \returns bottom left corner of the rect
	///
	////////////////////////////////////////////////////////////
	constexpr Point GetBottomLeft() const {
		return Point(x, GetY2());
	}

	////////////////////////////////////////////////////////////
	/// \brief Get bottom right corner of the rect
	///
	/// \returns Bottom right corner of the rect
	///
	////////////////////////////////////////////////////////////
	constexpr Point GetBottomRight() const {
		return Point(GetX2(), GetY2());
	}

	////////////////////////////////////////////////////////////
	/// \brief Get size of the rect
	///
	/// \returns Size of the rect
	///
	////////////////////////////////////////////////////////////
	constexpr Point GetSize() const {
		return Point(w, h);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get centroid of the rect
	///
	/// \returns Centroid of the rect
	///
	////////////////////////////////////////////////////////////
	constexpr Point GetCentroid() const {
		return Point(x + w/2, y + h/2);
	}

	////////////////////////////////////////////////////////////
	/// \brief Check whether the rect contains given point
	///
	/// \param[in] px X coordinate of a point
	/// \param[in] py Y coordinate of a point
	///
	/// \returns True if the point is contained in the rect
	///
	////////////////////////////////////////////////////////////
	constexpr bool Contains(int px, int py) const {
		return px >= x && py >= y && px <= GetX2() && py <= GetY2();
	}

	////////////////////////////////////////////////////////////
	/// \brief Check whether the rect contains given point
	///
	/// \param[in] point Point to check
	///
	/// \returns True if the point is contained in the rect
	///
	////////////////////////////////////////////////////////////
	constexpr bool Contains(const Point& point) const {
		return point.x >= x && point.y >= y && point.x <= GetX2() && point.y <= GetY2();
	}

	////////////////////////////////////////////////////////////
	/// \brief Check whether the rect contains another rect
	///
	/// \param[in] rect Rect to check
	///
	/// \returns True if the checked rect is contained in this rect
	///
	////////////////////////////////////////////////////////////
	constexpr bool Contains(const Rect& rect) const {
		return rect.x >= x && rect.y >= y && rect.GetX2() <= GetX2() && rect.GetY2() <= GetY2();
	}

	////////////////////////////////////////////////////////////
	/// \brief Check whether the rect intersects another rect
	///
	/// \param[in] rect Rect to check
	///
	/// \returns True if rectangles intersect
	///
	////////////////////////////////////////////////////////////
	constexpr bool Intersects(const Rect& rect) const {
		return !(rect.GetX2() < x || rect.GetY2() < y || rect.x > GetX2() || rect.y > GetY2());
	}

	////////////////////////////////////////////////////////////
	/// \brief Calculate union with another rect
	///
	/// \param[in] rect Rect to union with
	///
	/// \returns Rect representing union of two rectangles
	///
	////////////////////////////////////////////////////////////
	Rect GetUnion(const Rect& rect) const;

	////////////////////////////////////////////////////////////
	/// \brief Union rect with another rect
	///
	/// \param[in] rect Rect to union with
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& Union(const Rect& rect);

	////////////////////////////////////////////////////////////
	/// \brief Get a rect extended by specified amount of pixels
	///
	/// \param[in] amount Number of pixels to extend by
	///
	/// \returns Extended rect
	///
	////////////////////////////////////////////////////////////
	Rect GetExtension(unsigned int amount) const;

	////////////////////////////////////////////////////////////
	/// \brief Get a rect extended by specified amount of pixels
	///
	/// \param[in] hamount Number of pixels to extend by
	///                    in horizontal direction
	/// \param[in] vamount Number of pixels to extend by
	///                    in vertical direction
	///
	/// \returns Extended rect
	///
	////////////////////////////////////////////////////////////
	Rect GetExtension(unsigned int hamount, unsigned int vamount) const;

	////////////////////////////////////////////////////////////
	/// \brief Extend a rect by specified amount of pixels
	///
	/// \param[in] amount Number of pixels to extend by
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& Extend(unsigned int amount);

	////////////////////////////////////////////////////////////
	/// \brief Extend a rect by specified amount of pixels
	///
	/// \param[in] hamount Number of pixels to extend by
	///                    in horizontal direction
	/// \param[in] vamount Number of pixels to extend by
	///                    in vertical direction
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& Extend(unsigned int hamount, unsigned int vamount);

	////////////////////////////////////////////////////////////
	/// \brief Calculate intersection with another rect
	///
	/// \param[in] rect Rect to intersect with
	///
	/// \returns Rect representing intersection area or NullOpt if there was no intersection
	///
	////////////////////////////////////////////////////////////
	Optional<Rect> GetIntersection(const Rect& rect) const;

	////////////////////////////////////////////////////////////
	/// \brief Calculate the intersection of a rectangle and line segment
	///
	/// \param[in,out] x1 Starting X-coordinate of the line
	/// \param[in,out] y1 Starting Y-coordinate of the line
	/// \param[in,out] x2 Ending X-coordinate of the line
	/// \param[in,out] y2 Ending Y-coordinate of the line
	///
	/// \returns True if there is an intersection, false otherwise
	///
	/// This function is used to clip a line segment to a
	/// rectangle. A line segment contained entirely within the
	/// rectangle or that does not intersect will remain unchanged.
	/// A line segment that crosses the rectangle at either or both
	/// ends will be clipped to the boundary of the rectangle and
	/// the new coordinates saved in x1, y1, x2, and/or y2 as
	/// necessary.
	///
	////////////////////////////////////////////////////////////
	bool IntersectLine(int& x1, int& y1, int& x2, int& y2) const;

	////////////////////////////////////////////////////////////
	/// \brief Calculate the intersection of a rectangle and line segment
	///
	/// \param[in,out] p1 Starting coordinates of the line
	/// \param[in,out] p2 Ending coordinates of the line
	///
	/// \returns True if there is an intersection, false otherwise
	///
	/// This function is used to clip a line segment to a
	/// rectangle. A line segment contained entirely within the
	/// rectangle or that does not intersect will remain unchanged.
	/// A line segment that crosses the rectangle at either or both
	/// ends will be clipped to the boundary of the rectangle and
	/// the new coordinates saved in p1 and/or p2 as necessary.
	///
	////////////////////////////////////////////////////////////
	bool IntersectLine(Point& p1, Point& p2) const;

	////////////////////////////////////////////////////////////
	/// \brief Get rectangle moved by a given offset
	///
	/// \param[in] offset Point specifying an offset
	///
	/// \returns Moved rectangle
	///
	////////////////////////////////////////////////////////////
	constexpr Rect operator+(const Point& offset) const {
		return Rect(x + offset.x, y + offset.y, w, h);
	}

	////////////////////////////////////////////////////////////
	/// \brief Get rectangle moved by an opposite of given offset
	///
	/// \param[in] offset Point specifying an offset
	///
	/// \returns Moved rectangle
	///
	////////////////////////////////////////////////////////////
	constexpr Rect operator-(const Point& offset) const {
		return Rect(x - offset.x, y - offset.y, w, h);
	}

	////////////////////////////////////////////////////////////
	/// \brief Move by then given offset
	///
	/// \param[in] offset Point specifying an offset
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& operator+=(const Point& offset) {
		x += offset.x;
		y += offset.y;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Move by an opposite of the given offset
	///
	/// \param[in] offset Point specifying an offset
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Rect& operator-=(const Point& offset) {
		x -= offset.x;
		y -= offset.y;
		return *this;
	}
};

}

////////////////////////////////////////////////////////////
/// \brief Equality operator for SDL2pp::Rect
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if two rectangles are identical
///
////////////////////////////////////////////////////////////
constexpr bool operator==(const SDL2pp::Rect& a, const SDL2pp::Rect& b) {
	return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
}

////////////////////////////////////////////////////////////
/// \brief Inequality operator for SDL2pp::Rect
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if two rectangles are not identical
///
////////////////////////////////////////////////////////////
constexpr bool operator!=(const SDL2pp::Rect& a, const SDL2pp::Rect& b) {
	return !(a == b);
}

////////////////////////////////////////////////////////////
/// \brief Less-than operator for SDL2pp::Rect
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if a < b
///
////////////////////////////////////////////////////////////
SDL2PP_EXPORT bool operator<(const SDL2pp::Rect& a, const SDL2pp::Rect& b);

////////////////////////////////////////////////////////////
/// \brief Stream output operator overload for SDL2pp::Rect
///
/// \param[in] stream Stream to output to
/// \param[in] rect Rect to output
///
/// \returns stream
///
////////////////////////////////////////////////////////////
SDL2PP_EXPORT std::ostream& operator<<(std::ostream& stream, const SDL2pp::Rect& rect);

namespace std {

////////////////////////////////////////////////////////////
/// \brief std::hash specialization for SDL2pp::Rect
///
////////////////////////////////////////////////////////////
template<>
struct hash<SDL2pp::Rect> {
	////////////////////////////////////////////////////////////
	/// \brief Hash function for SDL2pp::Rect
	///
	/// \param[in] r Input Rect
	///
	/// \returns Hash value
	///
	////////////////////////////////////////////////////////////
	size_t operator()(const SDL2pp::Rect& r) const {
		size_t seed = std::hash<int>()(r.x);
		seed ^= std::hash<int>()(r.y) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		seed ^= std::hash<int>()(r.w) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		seed ^= std::hash<int>()(r.h) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	}
};

}

#endif
