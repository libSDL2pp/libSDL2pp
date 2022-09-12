/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2013-2016 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_EXCEPTION_HH
#define SDL2PP_EXCEPTION_HH

#include <string>
#include <stdexcept>

#include <SDL2pp/Export.hh>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief %Exception object representing SDL2 error
///
/// \ingroup general
///
/// \headerfile SDL2pp/Exception.hh
///
/// Internally, libSDL2pp checks return value of each SDL2
/// function it calls which may fail. If the function fails,
/// SDL2pp::Exception is thrown, and SDL2 error which explains
/// cause of function failure is stored in the exception and
/// may be extracted later.
///
/// what() usually contains a name of SDL2 function which failed,
/// e.g. "SDL_Init() failed"
///
/// Note: this Exception object is used to report errors from
/// SDL2 satellite libraries (SDL_image, SDL_mixer, SDL_ttf)
/// as well. Though they use their own error handling functions
/// (IMG_GetError, Mix_GetError, TTF_GetError), those are (currently)
/// just macros pointing to SDL_GetError. We currently rely on that.
/// If that changes, we'll need a hierarchy of specific exceptions.
///
/// Usage example:
/// \code
/// {
///     try {
///         SDL2pp::SDL sdl(SDL_INIT_VIDEO);
///     } catch (SDL2pp::Exception& e) {
///         std::cerr << "Fatal error:"
///                   << e.what()         // "SDL_Init failed"
///                   << ", SDL error: "
///                   << e.GetSDLError()  // "x11 not available"
///                   << std::endl;
///     }
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Exception : public std::runtime_error {
private:
	std::string sdl_function_; ///< SDL function which caused an error
	std::string sdl_error_;    ///< SDL error string

private:
	static std::string make_what(const char* sdl_function, const char* sdl_error);

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct exception, storing result of SDL_GetError()
	///
	/// \param[in] function Name of SDL function which generated an error
	///
	////////////////////////////////////////////////////////////
	explicit Exception(const char* function);

	////////////////////////////////////////////////////////////
	/// \brief Copy constructor
	///
	////////////////////////////////////////////////////////////
	Exception(const Exception&) = default;

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~Exception() noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Get name of SDL function which caused an error
	///
	/// \returns Name of function which caused an error
	///
	////////////////////////////////////////////////////////////
	std::string GetSDLFunction() const;

	////////////////////////////////////////////////////////////
	/// \brief Get SDL2 error text
	///
	/// \returns Stored result of SDL_GetError()
	///
	/// \see http://wiki.libsdl.org/SDL_GetError
	///
	////////////////////////////////////////////////////////////
	std::string GetSDLError() const;
};

}

#endif
