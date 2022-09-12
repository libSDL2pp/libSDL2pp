 /*
 libSDL2pp - C++ bindings/wrapper for SDL2
 Copyright (C) 2017 Vraiment <jemc44@gmail.com>

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

#ifndef SDL2PP_COLOR_HH
#define SDL2PP_COLOR_HH

#include <ostream>

#include <SDL_pixels.h>

#include <SDL2pp/Export.hh>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief RGB color with Alpha
///
/// \ingroup graphics
///
/// \headerfile SDL2pp/Color.hh
///
/// This class is public-derived from SDL_Color structure,
/// may generally used as it if passed via pointer or
/// reference. It also supports direct access to r, g, b
/// and a members.
///
/// \see http://wiki.libsdl.org/SDL_Color
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Color : public SDL_Color {
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Color(0, 0, 0, 0)
	///
	////////////////////////////////////////////////////////////
	constexpr Color() : SDL_Color{0, 0, 0, 0} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct a color from existing SDL_Color
	///
	/// \param[in] color Existing SDL_Color
	///
	////////////////////////////////////////////////////////////
	constexpr Color(const SDL_Color& color) : SDL_Color{color.r, color.g, color.b, color.a} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the color from given RGB, alpha is opaque
	///
	/// \param[in] r Red component in the range 0-255
	/// \param[in] g Green component in the range 0-255
	/// \param[in] b Blue component in the range 0-255
	///
	////////////////////////////////////////////////////////////
	constexpr Color(Uint8 r, Uint8 g, Uint8 b) : SDL_Color{r, g, b, SDL_ALPHA_OPAQUE} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Construct the color from given RGB and alpha values
	///
	/// \param[in] r Red component in the range 0-255
	/// \param[in] g Green component in the range 0-255
	/// \param[in] b Blue component in the range 0-255
	/// \param[in] a Alpha component in the range 0-255
	///
	////////////////////////////////////////////////////////////
	constexpr Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : SDL_Color{r, g, b, a} {
	}

	////////////////////////////////////////////////////////////
	/// \brief Copy constructor
	///
	////////////////////////////////////////////////////////////
	Color(const Color&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	////////////////////////////////////////////////////////////
	Color(Color&&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Assignment operator
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Color& operator=(const Color&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Color& operator=(Color&&) noexcept = default;

	////////////////////////////////////////////////////////////
	/// \brief Get the red component from the color
	///
	/// \returns The red component from the color
	///
	////////////////////////////////////////////////////////////
	constexpr Uint8 GetRed() const {
		return r;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set the red component from the color
	///
	/// \param[in] nr New red component value
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Color& SetRed(int nr) {
		r = nr;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get the green component from the color
	///
	/// \returns The green component from the color
	///
	////////////////////////////////////////////////////////////
	constexpr Uint8 GetGreen() const {
		return g;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set the green component from the color
	///
	/// \param[in] ng New green component value
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Color& SetGreen(int ng) {
		g = ng;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get the blue component from the color
	///
	/// \returns The blue component from the color
	///
	////////////////////////////////////////////////////////////
	constexpr Uint8 GetBlue() const {
		return b;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set the blue component from the color
	///
	/// \param[in] nb New blue component value
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Color& SetBlue(int nb) {
		b = nb;
		return *this;
	}

	////////////////////////////////////////////////////////////
	/// \brief Get the alpha component from the color
	///
	/// \returns The alpha component from the color
	///
	////////////////////////////////////////////////////////////
	constexpr Uint8 GetAlpha() const {
		return a;
	}

	////////////////////////////////////////////////////////////
	/// \brief Set the alpha component from the color
	///
	/// \param[in] na New alpha component value
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Color& SetAlpha(int na) {
		a = na;
		return *this;
	}
};

}

////////////////////////////////////////////////////////////
/// \brief Equality operator for SDL2pp::Color
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if two rectangles are identical
///
////////////////////////////////////////////////////////////
constexpr bool operator==(const SDL2pp::Color& a, const SDL2pp::Color& b) {
	return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

////////////////////////////////////////////////////////////
/// \brief Inequality operator for SDL2pp::Color
///
/// \param[in] a First argument for comparison
/// \param[in] b Second argument for comparison
///
/// \returns True if two rectangles are not identical
///
////////////////////////////////////////////////////////////
constexpr bool operator!=(const SDL2pp::Color& a, const SDL2pp::Color& b) {
	return !(a == b);
}

////////////////////////////////////////////////////////////
/// \brief Stream output operator overload for SDL2pp::Color
///
/// \param[in] stream Stream to output to
/// \param[in] color Color to output
///
/// \returns stream
///
////////////////////////////////////////////////////////////
SDL2PP_EXPORT std::ostream& operator<<(std::ostream& stream, const SDL2pp::Color& color);

namespace std {

////////////////////////////////////////////////////////////
/// \brief std::hash specialization for SDL2pp::Color
///
////////////////////////////////////////////////////////////
template<>
struct hash<SDL2pp::Color> {
	////////////////////////////////////////////////////////////
	/// \brief Hash function for SDL2pp::Color
	///
	/// \param[in] c Input Color
	///
	/// \returns Hash value
	///
	////////////////////////////////////////////////////////////
	size_t operator()(const SDL2pp::Color& c) const {
		size_t seed = std::hash<int>()(c.r);
		seed ^= std::hash<int>()(c.g) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		seed ^= std::hash<int>()(c.b) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		seed ^= std::hash<int>()(c.a) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	}
};

}

#endif
