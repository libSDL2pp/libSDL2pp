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

#ifndef SDL2PP_SDL_HH
#define SDL2PP_SDL_HH

#include <SDL_stdinc.h>

#include <SDL2pp/Export.hh>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief Helper class taking care of SDL library initialization
///        and deinitialization
///
/// \ingroup general
///
/// \headerfile SDL2pp/SDL.hh
///
/// Before using any SDL2 functions, the library must be initialized.
/// Likewise, it should be deinitialized before application exits.
/// SDL2pp::SDL object takes care of this in a RAII way
/// by initializing the library in constructor and deinitializing
/// in destructor, with an ability to init/quit specific subsystems
/// in between
///
/// Usage example:
/// \code
/// int main() {
///     SDL2pp::SDL sdl(SDL_INIT_VIDEO);
///
///     // ...use SDL functions...
///
///     // SDL library is automatically deinitialized before exit
///     return 0;
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT SDL {
public:
	////////////////////////////////////////////////////////////
	/// \brief Initializes SDL2 library
	///
	/// \param[in] flags Flags to pass to SDL_Init()
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_Init
	///
	////////////////////////////////////////////////////////////
	SDL(Uint32 flags);

	////////////////////////////////////////////////////////////
	/// \brief Destructor, deinitializes SDL2 library
	///
	/// \see http://wiki.libsdl.org/SDL_Quit
	///
	////////////////////////////////////////////////////////////
	virtual ~SDL();

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	SDL(const SDL& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	SDL& operator=(const SDL& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted move constructor
	///
	/// This class is not movable
	///
	////////////////////////////////////////////////////////////
	SDL(SDL&& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted move assignment operator
	///
	/// This class is not movable
	///
	////////////////////////////////////////////////////////////
	SDL& operator=(SDL&& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Checks which SDL2 subsystems were initialized
	///
	/// \param[in] flags 0 to return mask of initialized subsystems
	///                  or any combination of flags to return initialization
	///                  status of the specified subsystems
	///
	/// \returns Mask of initialized subsystems or the initialization
	///          status of the specified subsystems
	///
	/// \see http://wiki.libsdl.org/SDL_WasInit
	///
	////////////////////////////////////////////////////////////
	Uint32 WasInit(Uint32 flags);

	////////////////////////////////////////////////////////////
	/// \brief Initializes additional SDL2 subsystems
	///
	/// \param[in] flags Set of flags which determines which subsystems
	///                  to initialize
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_InitSubSystem
	///
	////////////////////////////////////////////////////////////
	void InitSubSystem(Uint32 flags);

	////////////////////////////////////////////////////////////
	/// \brief Deinitializes specific SDL2 subsystems
	///
	/// \param[in] flags Set of flags which determines which subsystems
	///                  to deinitialize
	///
	/// \see http://wiki.libsdl.org/SDL_QuitSubSystem
	///
	////////////////////////////////////////////////////////////
	void QuitSubSystem(Uint32 flags);
};

}

#endif
