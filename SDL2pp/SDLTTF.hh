/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2014-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_SDLTTF_HH
#define SDL2PP_SDLTTF_HH

#include <SDL2pp/Export.hh>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief Helper class taking care of SDL_ttf library initialization
///        and deinitialization
///
/// \ingroup ttf
///
/// \headerfile SDL2pp/SDLTTF.hh
///
/// To use SDL_ttf functions, SDL_ttf library must be initialized first.
/// This initialization and automatic deinitialization is handled by
/// this class. You may only use SDL_ttf (Font class) functionality
/// as long as SDLTTF object lives. SDL itself must not be initialized
/// to use TTF.
///
/// Usage example:
/// \code
/// int main() {
///     SDL2pp::SDLTTF ttf;
///
///     // ...use SDL_ttf functions...
///
///     // SDL_ttf library is automatically deinitialized before exit
///     return 0;
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT SDLTTF {
public:
	////////////////////////////////////////////////////////////
	/// \brief Initializes SDL_ttf library
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC8
	///
	////////////////////////////////////////////////////////////
	SDLTTF();

	////////////////////////////////////////////////////////////
	/// \brief Destructor, deinitializes SDL_ttf library
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC10
	///
	////////////////////////////////////////////////////////////
	virtual ~SDLTTF();

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	SDLTTF(const SDLTTF& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	SDLTTF& operator=(const SDLTTF& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted move constructor
	///
	/// This class is not movable
	///
	////////////////////////////////////////////////////////////
	SDLTTF(SDLTTF&& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted move assignment operator
	///
	/// This class is not movable
	///
	////////////////////////////////////////////////////////////
	SDLTTF& operator=(SDLTTF&& other) = delete;
};

}

#endif
