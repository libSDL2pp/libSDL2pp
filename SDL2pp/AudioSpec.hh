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

#ifndef SDL2PP_AUDIOSPEC_HH
#define SDL2PP_AUDIOSPEC_HH

#include <SDL_audio.h>

#include <SDL2pp/Export.hh>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief Audio format specification
///
/// \ingroup audio
///
/// \headerfile SDL2pp/AudioSpec.hh
///
/// This class extends SDL_AudioSpec - a structure that describes
/// audio format. It may be used to describe format of loaded
/// SDL2pp::Wav audio fragments and to specify desired or actual
/// audio output format of SDL2pp::AudioDevice
///
/// \see http://wiki.libsdl.org/SDL_AudioSpec
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT AudioSpec : public SDL_AudioSpec {
public:
	////////////////////////////////////////////////////////////
	/// \brief Create empty (invalid) audio format specification
	///
	/// This is needed for cases where e.g. SDL_LoadWAV() fills
	/// existing SDL_AudioSpec structure with values.
	///
	////////////////////////////////////////////////////////////
	AudioSpec();

	////////////////////////////////////////////////////////////
	/// \brief Create audio format specification with given properties
	///
	/// \param[in] freq Sampling frequency in samples/second
	/// \param[in] format Sample format, see http://wiki.libsdl.org/SDL_AudioSpec#Remarks
	/// \param[in] channels Number of separate audio channels
	/// \param[in] samples Audio buffer size in samples (power of 2)
	///
	/// \see http://wiki.libsdl.org/SDL_AudioSpec#Remarks
	///
	////////////////////////////////////////////////////////////
	AudioSpec(int freq, SDL_AudioFormat format, Uint8 channels, Uint16 samples);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	~AudioSpec();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::AudioSpec object to move data from
	///
	////////////////////////////////////////////////////////////
	AudioSpec(AudioSpec&& other);

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::AudioSpec object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	AudioSpec& operator=(AudioSpec&& other);

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	AudioSpec(const AudioSpec& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	AudioSpec& operator=(const AudioSpec& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to managed SDL_AudioSpec structure
	///
	/// \returns Pointer to managed SDL_AudioSpec structure
	///
	////////////////////////////////////////////////////////////
	const SDL_AudioSpec* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Merges audio format changes from another SDL2pp::AudioSpec
	///
	/// \param[in] obtained SDL2pp::AudioSpec to merge data from
	///
	////////////////////////////////////////////////////////////
	void MergeChanges(const SDL_AudioSpec& obtained);

	////////////////////////////////////////////////////////////
	/// \brief Checks if format of another SDL2pp::AudioSpec is the same
	///
	/// \param[in] other SDL2pp::AudioSpec to compare to
	///
	////////////////////////////////////////////////////////////
	bool IsSameFormat(const AudioSpec& other) const;
};

}

#endif
