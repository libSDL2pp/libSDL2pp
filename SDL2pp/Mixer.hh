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

#ifndef SDL2PP_MIXER_HH
#define SDL2PP_MIXER_HH

#include <string>

#include <SDL2/SDL_mixer.h>

namespace SDL2pp {

class RWops;

////////////////////////////////////////////////////////////
/// \brief SDL_mixer's audio mixer
///
/// \ingroup mixer
///
/// \headerfile SDL2pp/Mixer.hh
///
/// This class represents open SDL_mixer audio device. Object
/// of this class must be constructed before creating any
/// SDL2pp:Chunk's.
///
////////////////////////////////////////////////////////////
class Mixer {
private:
	bool open_;

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct a mixer and open an audio device
	///
	/// \param[in] frequency Output sampling frequency in samples
	///                      per second (Hz). You might use
	///                      MIX_DEFAULT_FREQUENCY(22050) since that
	///                      is a good value for most games
	/// \param[in] format Output sample format
	/// \param[in] channels Number of sound channels in output. Set
	///                     to 2 for stereo, 1 for mono. This has
	///                     nothing to do with mixing channels
	/// \param[in] chunksize Bytes used per output sample
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC11
	///
	////////////////////////////////////////////////////////////
	Mixer(int frequency, Uint16 format, int channels, int chunksize);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.html#SEC12
	///
	////////////////////////////////////////////////////////////
	~Mixer();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Mixer object to move data from
	///
	////////////////////////////////////////////////////////////
	Mixer(Mixer&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::Mixer object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Mixer& operator=(Mixer&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Mixer(const Mixer& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Mixer& operator=(const Mixer& other) = delete;
};

}

#endif
