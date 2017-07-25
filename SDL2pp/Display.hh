/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
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

#ifndef SDL2PP_DISPLAY_HH
#define SDL2PP_DISPLAY_HH

#include <SDL2pp/Export.hh>

#include <SDL_version.h>

#include <SDL2pp/Rect.hh>
#include <string>

namespace SDL2pp {
	////////////////////////////////////////////////////////////
	/// \brief Gets the name of a given display
	///
	/// \ingroup graphics
	///
	/// \headerfile SDL2pp/Display.hh
	///
	/// \param[in] displayIndex The display to retrieve its name
	///
	/// \returns A string with the name of the given display
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://wiki.libsdl.org/SDL_GetDisplayName
	///
	////////////////////////////////////////////////////////////
	SDL2PP_EXPORT std::string GetDisplayName(int displayIndex);
	
#if SDL_VERSION_ATLEAST(2, 0, 4)
	////////////////////////////////////////////////////////////
	/// \brief Read-only struct to store DPI information of a display
	///
	/// \ingroup graphics
	///
	/// \headerfile SDL2pp/Display.hh
	///
	////////////////////////////////////////////////////////////
	struct SDL2PP_EXPORT DPI {
		////////////////////////////////////////////////////////////
		/// \brief The diagonal DPI of the display
		///
		////////////////////////////////////////////////////////////
		const float Diagonal;
		
		////////////////////////////////////////////////////////////
		/// \brief The horizontal DPI of the display
		///
		////////////////////////////////////////////////////////////
		const float Horizontal;
		
		////////////////////////////////////////////////////////////
		/// \brief The vertical DPI of the display
		///
		////////////////////////////////////////////////////////////
		const float Vertical;
	};
	
	////////////////////////////////////////////////////////////
	/// \brief Gets the dots/pixels per inch of a given display
	///
	/// \ingroup graphics
	///
	/// \headerfile SDL2pp/Display.hh
	///
	/// \param[in] displayIndex The display to retrieve the DPI
	///
	/// \returns A DPI object with the dpi values for the given display
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://wiki.libsdl.org/SDL_GetDisplayDPI
	///
	////////////////////////////////////////////////////////////
	SDL2PP_EXPORT DPI GetDisplayDPI(int displayIndex);
#endif

#if SDL_VERSION_ATLEAST(2, 0, 5)
	////////////////////////////////////////////////////////////
	/// \brief Gets the usable desktop area of a given display
	///
	/// This function retrieves an rectangle with the usable area
	/// of the given display, with the initial display being
	/// located at (0,0). This function does takes into account
	/// space that is not usable, like OS X's menu bar, removing it
	/// and returning the actual usable area.
	///
	/// \ingroup graphics
	///
	/// \headerfile SDL2pp/Display.hh
	///
	/// \param[in] displayIndex The display to retrieve the usable area
	///
	/// \returns A rectangle with the usable area of the given display
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://wiki.libsdl.org/SDL_GetDisplayUsableBounds
	///
	////////////////////////////////////////////////////////////
	SDL2PP_EXPORT Rect GetDisplayUsableBounds(int displayIndex);
#endif
}

#endif
