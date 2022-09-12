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

#ifndef SDL2PP_SDLMIXER_HH
#define SDL2PP_SDLMIXER_HH

#include <SDL2pp/Export.hh>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief Helper class taking care of SDL_mixer library initialization
///        and deinitialization
///
/// \ingroup mixer
///
/// \headerfile SDL2pp/SDLMixer.hh
///
/// Usage example:
/// \code
/// int main() {
///     SDL2pp::SDL sdl(SDL_INIT_VIDEO);
///     SDL2pp::SDLMixer mixer(MIX_INIT_OGG);
///
///     // SDL_mixer library is automatically deinitialized before exit
///     return 0;
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT SDLMixer {
public:
	////////////////////////////////////////////////////////////
	/// \brief Initializes SDL_mixer library
	///
	/// \param[in] flags Flags to pass to Mix_Init()
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC9
	///
	////////////////////////////////////////////////////////////
	explicit SDLMixer(int flags = 0);

	////////////////////////////////////////////////////////////
	/// \brief Destructor, deinitializes SDL_mixer library
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC10
	///
	////////////////////////////////////////////////////////////
	virtual ~SDLMixer();

	////////////////////////////////////////////////////////////
	/// \brief Try to init more SDL_mixer formats
	///
	/// \param[in] flags Flags to pass to Mix_Init()
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC9
	///
	////////////////////////////////////////////////////////////
	int InitMore(int flags);

	////////////////////////////////////////////////////////////
	/// \brief Get mask of initialized SDL_mixer formats
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC9
	///
	////////////////////////////////////////////////////////////
	int GetInitFlags();

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	SDLMixer(const SDLMixer& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	SDLMixer& operator=(const SDLMixer& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted move constructor
	///
	/// This class is not movable
	///
	////////////////////////////////////////////////////////////
	SDLMixer(SDLMixer&& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted move assignment operator
	///
	/// This class is not movable
	///
	////////////////////////////////////////////////////////////
	SDLMixer& operator=(SDLMixer&& other) = delete;
};

}

#endif
