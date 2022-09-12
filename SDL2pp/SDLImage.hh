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

#ifndef SDL2PP_SDLIMAGE_HH
#define SDL2PP_SDLIMAGE_HH

#include <SDL2pp/Export.hh>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief Helper class taking care of SDL_image library initialization
///        and deinitialization
///
/// \ingroup image
///
/// \headerfile SDL2pp/SDLImage.hh
///
/// Though it's possible to use SDL_image without initializing it,
/// library provides initialization/deinitialization functions to
/// be able to preload libraries for specific file format support
/// (png, jpeg or tiff) beforehand. In SDL2pp, this is handled by
/// this class.
///
/// Usage example:
/// \code
/// int main() {
///     SDL2pp::SDL sdl(SDL_INIT_VIDEO);
///     SDL2pp::SDLImage image(IMG_INIT_PNG);
///
///     // use SDL_image functions
///     SDL2pp::Texture t("/path/to/file.png");
///
///     // SDL_image library is automatically deinitialized before exit
///     return 0;
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT SDLImage {
public:
	////////////////////////////////////////////////////////////
	/// \brief Initializes SDL_image library
	///
	/// \param[in] flags Flags to pass to IMG_Init()
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC8
	///
	////////////////////////////////////////////////////////////
	explicit SDLImage(int flags = 0);

	////////////////////////////////////////////////////////////
	/// \brief Destructor, deinitializes SDL_image library
	///
	/// \see https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC9
	///
	////////////////////////////////////////////////////////////
	virtual ~SDLImage();

	////////////////////////////////////////////////////////////
	/// \brief Try to init more SDL_image formats
	///
	/// \param[in] flags Flags to pass to IMG_Init()
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC8
	///
	////////////////////////////////////////////////////////////
	int InitMore(int flags);

	////////////////////////////////////////////////////////////
	/// \brief Get mask of initialized SDL_image formats
	///
	/// \see https://www.libsdl.org/projects/SDL_image/docs/SDL_image.html#SEC8
	///
	////////////////////////////////////////////////////////////
	int GetInitFlags();

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	SDLImage(const SDLImage& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	SDLImage& operator=(const SDLImage& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted move constructor
	///
	/// This class is not movable
	///
	////////////////////////////////////////////////////////////
	SDLImage(SDLImage&& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted move assignment operator
	///
	/// This class is not movable
	///
	////////////////////////////////////////////////////////////
	SDLImage& operator=(SDLImage&& other) = delete;
};

}

#endif
