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

#ifndef SDL2PP_WAV_HH
#define SDL2PP_WAV_HH

#include <string>

#include <SDL2pp/AudioSpec.hh>
#include <SDL2pp/Export.hh>

namespace SDL2pp {

class RWops;

////////////////////////////////////////////////////////////
/// \brief %Chunk of audio data read from a .WAV file
///
/// \ingroup audio
///
/// \headerfile SDL2pp/Wav.hh
///
/// SDL2pp::Wav is a wrapper around basic SDL2 audio fragment
/// handling functionality, basically SDL_LoadWAV() and related
/// functions.
///
/// The class holds raw audio data which is loaded from a disk
/// file or from an arbitrary source with SDL2pp::RWops and
/// may be used in audio playback.
///
/// See audio_wav demo for an example.
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Wav {
private:
	Uint8* audio_buffer_; ///< Raw audio data
	Uint32 audio_length_; ///< Raw audio data length in bytes

	AudioSpec spec_;      ///< Description of audio data format

public:
	////////////////////////////////////////////////////////////
	/// \brief Load audio from file on disk
	///
	/// \param[in] file Path to the wav file
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_LoadWAV
	///
	////////////////////////////////////////////////////////////
	explicit Wav(const std::string& file);

	////////////////////////////////////////////////////////////
	/// \brief Load audio using RWops
	///
	/// \param[in] rwops SDL2pp::RWops used to access wav data
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_LoadWAV_RW
	///
	////////////////////////////////////////////////////////////
	explicit Wav(RWops& rwops);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	~Wav();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Wav object to move data from
	///
	////////////////////////////////////////////////////////////
	Wav(Wav&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::Wav object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Wav& operator=(Wav&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Wav(const Wav& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Wav& operator=(const Wav& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get length of audio data
	///
	/// \returns Length of audio data in bytes
	///
	////////////////////////////////////////////////////////////
	Uint32 GetLength() const;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to raw audio data
	///
	/// \returns Pointer to raw audio data
	///
	////////////////////////////////////////////////////////////
	Uint8* GetBuffer();

	////////////////////////////////////////////////////////////
	/// \brief Get constant pointer to raw audio data
	///
	/// \returns Constant pointer to raw audio data
	///
	////////////////////////////////////////////////////////////
	const Uint8* GetBuffer() const;

	////////////////////////////////////////////////////////////
	/// \brief Get descriptor of audio format
	///
	/// \returns SDL2pp::AudioSpec describing format of audio data
	///
	////////////////////////////////////////////////////////////
	const AudioSpec& GetSpec() const;
};

}

#endif
