/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2015-2017 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_MUSIC_HH
#define SDL2PP_MUSIC_HH

#include <string>

#include <SDL_mixer.h>

#include <SDL2pp/Export.hh>

namespace SDL2pp {

class RWops;

////////////////////////////////////////////////////////////
/// \brief %Music data
///
/// \ingroup mixer
///
/// \headerfile SDL2pp/Music.hh
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Music {
private:
	Mix_Music* music_;    ///< Managed Mix_Music object

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct from existing Mix_Music pointer
	///
	/// \param[in] music Existing Mix_Music to manage
	///
	////////////////////////////////////////////////////////////
	explicit Music(Mix_Music* music);

	////////////////////////////////////////////////////////////
	/// \brief Load music file
	///
	/// \param[in] file Name of music file to use
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC55
	///
	////////////////////////////////////////////////////////////
	explicit Music(const std::string& file);

	////////////////////////////////////////////////////////////
	/// \brief Load music using RWops
	///
	/// This uses undocumented SDL_Mixer function. Comment
	/// in SDL_mixer.h suggests it's only indended to work with
	/// Ogg and MikMod.
	///
	/// \param[in] rwops SDL2pp::RWops used to access music data
	///
	/// \throws SDL2pp::Exception
	///
	////////////////////////////////////////////////////////////
	explicit Music(RWops& rwops);

	////////////////////////////////////////////////////////////
	/// \brief Load music using RWops
	///
	/// This uses undocumented SDL_Mixer function.
	///
	/// \param[in] rwops SDL2pp::RWops used to access music data
	/// \param[in] type Music type to load
	///
	/// \throws SDL2pp::Exception
	///
	////////////////////////////////////////////////////////////
	Music(RWops& rwops, Mix_MusicType type);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC56
	///
	////////////////////////////////////////////////////////////
	~Music();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Music object to move data from
	///
	////////////////////////////////////////////////////////////
	Music(Music&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::Music object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Music& operator=(Music&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Music(const Music& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Music& operator=(const Music& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to managed Mix_Music
	///
	/// \returns Pointer to managed Mix_Music
	///
	////////////////////////////////////////////////////////////
	Mix_Music* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the music encoding type
	///
	/// \returns The type of music
	///
	////////////////////////////////////////////////////////////
	Mix_MusicType GetType() const;
};

}

#endif
