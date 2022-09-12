/*
  libSDL2pp - C++ bindings/wrapper for SDL2
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

#ifndef SDL2PP_CHUNK_HH
#define SDL2PP_CHUNK_HH

#include <string>

#include <SDL_mixer.h>

#include <SDL2pp/Export.hh>

namespace SDL2pp {

class RWops;

////////////////////////////////////////////////////////////
/// \brief Fragment of audio data
///
/// \ingroup mixer
///
/// \headerfile SDL2pp/Chunk.hh
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Chunk {
private:
	Mix_Chunk* chunk_;    ///< Managed Mix_Chunk object

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct from existing Mix_Chunk structure
	///
	/// \param[in] chunk Existing Mix_Chunk to manage
	///
	////////////////////////////////////////////////////////////
	explicit Chunk(Mix_Chunk* chunk);

	////////////////////////////////////////////////////////////
	/// \brief Load file for use as a sample
	///
	/// \param[in] file File name to load sample from
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC19
	///
	////////////////////////////////////////////////////////////
	explicit Chunk(const std::string& file);

	////////////////////////////////////////////////////////////
	/// \brief Load sample using RWops
	///
	/// \param[in] rwops SDL2pp::RWops used to access sample data
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC20
	///
	////////////////////////////////////////////////////////////
	explicit Chunk(RWops& rwops);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC24
	///
	/// \note Despite what Mix_FreeChunk() documentation (and even
	///       comment in function implementation) says, right after
	///       the named comment there's a code which stops playback
	///       of any channel which plays the chunk being freed.
	///       Thus, it is safe to destroy Chunk before destroying
	///       Mixer, even if it still plays the chunk.
	///
	////////////////////////////////////////////////////////////
	~Chunk();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Chunk object to move data from
	///
	////////////////////////////////////////////////////////////
	Chunk(Chunk&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::Chunk object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Chunk& operator=(Chunk&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Chunk(const Chunk& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Chunk& operator=(const Chunk& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to managed Mix_Chunk structure
	///
	/// \returns Pointer to managed Mix_Chunk structure
	///
	////////////////////////////////////////////////////////////
	Mix_Chunk* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Set volume of a chunk
	///
	/// \param[in] volume The volume to use from 0 to MIX_MAX_VOLUME(128)
	///
	/// \returns Previous volume setting
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC23
	///
	////////////////////////////////////////////////////////////
	int SetVolume(int volume);

	////////////////////////////////////////////////////////////
	/// \brief Get volume of a chunk
	///
	/// \returns Current volume setting
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC23
	///
	////////////////////////////////////////////////////////////
	int GetVolume() const;
};

}

#endif
