/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_CURSOR_HH
#define SDL2PP_CURSOR_HH

#include <SDL2/SDL_mouse.h>

namespace SDL2pp {

class Surface;

////////////////////////////////////////////////////////////
/// \brief Mouse pointer image
///
/// \ingroup windows
///
/// \headerfile SDL2pp/Cursor.hh
///
////////////////////////////////////////////////////////////
class Cursor {
private:
	SDL_Cursor* cursor_; ///< Contained SDL_Cursor structure

public:
    ////////////////////////////////////////////////////////////
	/// \brief Construct from existing SDL_Cursor structure
	///
	/// \param texture Existing SDL_Cursor to manage
	///
	////////////////////////////////////////////////////////////
	Cursor(SDL_Cursor* cursor);

	////////////////////////////////////////////////////////////
	/// \brief Create system cursor
	///
	/// \param id System cursor enum value
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_CreateSystemCursor
	///
	////////////////////////////////////////////////////////////
	static Cursor CreateSystemCursor(SDL_SystemCursor id);

	////////////////////////////////////////////////////////////
	/// \brief Create a cursor using the specified bitmap data and mask (in MSB format)
	///
	/// \param data Color value for each pixel of the cursor
	/// \param mask Mask value for each pixel of the cursor
	/// \param w Width of the cursor
	/// \param h Height of the cursor
	/// \param hot_x X-axis location of the upper left corner of the cursor relative to the actual mouse position
	/// \param hot_x Y-axis location of the upper left corner of the cursor relative to the actual mouse position
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_CreateCursor
	///
	////////////////////////////////////////////////////////////
	static Cursor CreateCursor(const Uint8* data, const Uint8* mask, int w, int h, int hot_x, int hot_y);

	////////////////////////////////////////////////////////////
	/// \brief Create a cursor using the specified bitmap data and mask (in MSB format)
	///
	/// \param surface SDL2pp::Surface representing the cursor image
	/// \param hot_x X position of the cursor hot spot
	/// \param hot_y Y position of the cursor hot spot
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_CreateColorCursor
	///
	////////////////////////////////////////////////////////////
	static Cursor CreateColorCursor(const Surface& surface, int hot_x, int hot_y);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see http://wiki.libsdl.org/SDL_FreeCursor
	///
	////////////////////////////////////////////////////////////
	virtual ~Cursor();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param other SDL2pp::Cursor object to move data from
	///
	////////////////////////////////////////////////////////////
	Cursor(Cursor&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment
	///
	/// \param other SDL2pp::Cursor object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Cursor& operator=(Cursor&& other) noexcept;

	// Deleted copy constructor and assignment
	Cursor(const Cursor& other) = delete;
	Cursor& operator=(const Cursor& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to contained SDL_Cursor structure
	///
	/// \returns Pointer to contained SDL_Cursor structure
	///
	////////////////////////////////////////////////////////////
	SDL_Cursor* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the active cursor
	///
	/// \see http://wiki.libsdl.org/SDL_SetCursor
	///
	////////////////////////////////////////////////////////////
	void Set();
};

}

#endif
