/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2014 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_FONT_HH
#define SDL2PP_FONT_HH

#include <string>

#include <SDL2/SDL_ttf.h>

//#include <SDL2pp/Config.hh>
//#include <SDL2pp/Optional.hh>
//#include <SDL2pp/Rect.hh>

//struct SDL_PixelFormat;

namespace SDL2pp {

class RWops;

////////////////////////////////////////////////////////////
/// \brief Loaded font
///
/// \ingroup ttf
///
/// \headerfile SDL2pp/Font.hh
///
/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC56
///
////////////////////////////////////////////////////////////
class Font {
private:
	TTF_Font* font_; ///< Contained SDL_Font structure

public:
	////////////////////////////////////////////////////////////
	/// \brief Loads font from .ttf or .fon file
	///
	/// \param file Pointer File name to load font from
	/// \param ptsize Point size (based on 72DPI) to load font as. This basically translates to pixel height
	/// \param index Choose a font face from a file containing multiple font faces. The first face is always index 0
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC14
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC16
	///
	////////////////////////////////////////////////////////////
	Font(const std::string& file, int ptsize = 0, long index = 0);

	////////////////////////////////////////////////////////////
	/// \brief Loads font with RWops
	///
	/// \param RWops RWops to load font from
	/// \param ptsize Point size (based on 72DPI) to load font as. This basically translates to pixel height
	/// \param index Choose a font face from a file containing multiple font faces. The first face is always index 0
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC15
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC17
	///
	////////////////////////////////////////////////////////////
	Font(RWops& rwops, int ptsize = 0, long index = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC18
    ///
    ////////////////////////////////////////////////////////////
	virtual ~Font();

    ////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param other SDL2pp::Font object to move data from
	///
	////////////////////////////////////////////////////////////
	Font(Font&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment
	///
	/// \param other SDL2pp::Font object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Font& operator=(Font&& other) noexcept;

	// Deleted copy constructor and assignment
	Font(const Font&) = delete;
	Font& operator=(const Font&) = delete;

    ////////////////////////////////////////////////////////////
	/// \brief Get pointer to contained SDL_Font structure
	///
	/// \returns Pointer to contained SDL_Font structure
	///
	////////////////////////////////////////////////////////////
	TTF_Font* Get() const;
};

}

#endif
