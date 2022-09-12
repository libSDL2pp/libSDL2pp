/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2014-2016 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_AUDIODEVICE_HH
#define SDL2PP_AUDIODEVICE_HH

#include <functional>
#include <string>

#include <SDL_audio.h>
#include <SDL_version.h>

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Config.hh>
#include <SDL2pp/Export.hh>

namespace SDL2pp {

class AudioSpec;

////////////////////////////////////////////////////////////
/// \brief Audio device
///
/// \ingroup audio
///
/// \headerfile SDL2pp/AudioDevice.hh
///
/// This class provides access to basic %SDL (not SDL_mixer!)
/// audio functionality.
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT AudioDevice {
public:
	////////////////////////////////////////////////////////////
	/// \brief SDL2pp::AudioDevice lock
	///
	/// \ingroup audio
	///
	/// \headerfile SDL2pp/AudioDevice.hh
	///
	/// Audio devices may be locked, which means that audio
	/// callback will not be called in a locked state, allowing
	/// to change data it accesses in a thread-safe way.
	///
	/// This class represents the lock and controls its lifetime
	/// as the lock is released as soon as LockHandle is destroyed.
	///
	/// Usage example:
	/// \code
	/// {
	///     // Some audio data is loaded
	///     SDL2pp::Wav audiodata;
	///
	///     // Audio device is created, its callback accesses our audio data
	///     SDL2pp::AudioDevice dev(..., [&audiodata](){...});
	///
	///     dev.Pause(false); // playback starts, the callback is called periodically
	///
	///     {
	///         SDL2pp::AudioDevice::LockHandle lock = dev.Lock();
	///         // Now audiodata may be safely modified, no callback will be called to access it
	///     }
	///     // At this point lock is released, playback continues
	/// }
	/// \endcode
	///
	////////////////////////////////////////////////////////////
	class SDL2PP_EXPORT LockHandle {
		friend class AudioDevice;
	private:
		AudioDevice* device_; ///< SDL2pp::AudioDevice the lock belongs to

	private:
		////////////////////////////////////////////////////////////
		/// \brief Create lock for specific SDL2pp::AudioDevice
		///
		/// \param[in] device Pointer to audio device to lock
		///
		/// This operation locks a device, which remains locked
		/// until LockHandle is destroyed
		///
		/// Recursive locking is allowed
		///
		/// \see http://wiki.libsdl.org/SDL_LockAudioDevice
		///
		////////////////////////////////////////////////////////////
		explicit LockHandle(AudioDevice* device);

	public:
		////////////////////////////////////////////////////////////
		/// \brief Create no-op lock
		///
		/// This may be initialized with real lock later via move
		/// assignment
		///
		////////////////////////////////////////////////////////////
		LockHandle();

		////////////////////////////////////////////////////////////
		/// \brief Destructor
		///
		/// Releases the lock
		///
		/// \see http://wiki.libsdl.org/SDL_UnlockAudioDevice
		///
		////////////////////////////////////////////////////////////
		~LockHandle();

		////////////////////////////////////////////////////////////
		/// \brief Move constructor
		///
		/// \param[in] other SDL2pp::AudioDevice::LockHandle to move data from
		///
		////////////////////////////////////////////////////////////
		LockHandle(LockHandle&& other) noexcept;

		////////////////////////////////////////////////////////////
		/// \brief Move assignment operator
		///
		/// \param[in] other SDL2pp::AudioDevice::LockHandle to move data from
		///
		/// \returns Reference to self
		///
		////////////////////////////////////////////////////////////
		LockHandle& operator=(LockHandle&& other) noexcept;

		////////////////////////////////////////////////////////////
		/// \brief Copy constructor
		///
		/// \param[in] other SDL2pp::AudioDevice::LockHandle to copy data from
		///
		////////////////////////////////////////////////////////////
		LockHandle(const LockHandle& other);

		////////////////////////////////////////////////////////////
		/// \brief Assignment operator
		///
		/// \param[in] other SDL2pp::AudioDevice::LockHandle to copy data from
		///
		/// \returns Reference to self
		///
		////////////////////////////////////////////////////////////
		LockHandle& operator=(const LockHandle& other);
	};

	typedef std::function<void(Uint8* stream, int len)> AudioCallback; ///< Function type for audio callback

private:
	SDL_AudioDeviceID device_id_; ///< SDL2 device id
	AudioCallback callback_;      ///< Callback used to feed audio data to the device

private:
	////////////////////////////////////////////////////////////
	/// \brief Static wrapper for audio callback
	///
	/// This only extracts this from userdata and
	/// runs real this->callback_
	///
	////////////////////////////////////////////////////////////
	static void SDLCallback(void *userdata, Uint8* stream, int len);

public:
	////////////////////////////////////////////////////////////
	/// \brief Open audio device with specified output format
	///
	/// \param[in] device Name of the device to open
	/// \param[in] iscapture Non-zero to open device for recording
	///                      (SDL2 doesn't support this yet)
	/// \param[in] spec Audio output format
	/// \param[in] callback Callback which will feed audio to the device
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_OpenAudioDevice
	///
	////////////////////////////////////////////////////////////
	AudioDevice(const Optional<std::string>& device, bool iscapture, const AudioSpec& spec, AudioCallback&& callback = AudioCallback());

	////////////////////////////////////////////////////////////
	/// \brief Open audio device with desired output format
	///
	/// \param[in] device Name of the device to open
	/// \param[in] iscapture Non-zero to open device for recording
	///                      (SDL2 doesn't support this yet)
	/// \param[in] allowed_changes Flag mask specifying which audio
	///                            format properties may change
	/// \param[in,out] spec Desired audio output format (may be changed)
	/// \param[in] callback Callback which will feed audio to the device
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_OpenAudioDevice
	///
	////////////////////////////////////////////////////////////
	AudioDevice(const Optional<std::string>& device, bool iscapture, AudioSpec& spec, int allowed_changes, AudioCallback&& callback = AudioCallback());

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~AudioDevice();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::AudioDevice to move data from
	///
	////////////////////////////////////////////////////////////
	AudioDevice(AudioDevice&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::AudioDevice to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	AudioDevice& operator=(AudioDevice&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	AudioDevice(const AudioDevice&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	AudioDevice& operator=(const AudioDevice&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get managed audio device ID
	///
	/// \returns Managed audio device ID
	///
	////////////////////////////////////////////////////////////
	SDL_AudioDeviceID Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Pause or unpause audio playback
	///
	/// \param[in] pause_on Whether audio should be paused
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_PauseAudioDevice
	///
	////////////////////////////////////////////////////////////
	AudioDevice& Pause(bool pause_on);

	////////////////////////////////////////////////////////////
	/// \brief Get playback status
	///
	/// \returns Playback status (SDL_AUDIO_STOPPED, SDL_AUDIO_PLAYING, SDL_AUDIO_PAUSED)
	///
	/// \see http://wiki.libsdl.org/SDL_GetAudioDeviceStatus
	///
	////////////////////////////////////////////////////////////
	SDL_AudioStatus GetStatus() const;

	////////////////////////////////////////////////////////////
	/// \brief Replace audio callback
	///
	/// \param[in] callback New audio callback
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	AudioDevice& ChangeCallback(AudioCallback&& callback);

	////////////////////////////////////////////////////////////
	/// \brief Lock audio device to prevent it from calling audio callback
	///
	/// \returns Lock handle used to control lock lifetime
	///
	/// The device remains locked for the lifetime of returned LockHandle
	///
	/// Recursive locking is allowed
	///
	/// \see http://wiki.libsdl.org/SDL_LockAudioDevice
	///
	////////////////////////////////////////////////////////////
	LockHandle Lock();

#if SDL_VERSION_ATLEAST(2, 0, 4)
	////////////////////////////////////////////////////////////
	/// \brief Queue more audio for a non-callback device
	///
	/// \param[in] data Data to queue for later playback
	/// \param[in] len Data length in bytes (not samples!)
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_QueueAudio
	///
	////////////////////////////////////////////////////////////
	AudioDevice& QueueAudio(const void* data, Uint32 len);

	////////////////////////////////////////////////////////////
	/// \brief Drop queued audio
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_ClearQueuedAudio
	///
	////////////////////////////////////////////////////////////
	AudioDevice& ClearQueuedAudio();

	////////////////////////////////////////////////////////////
	/// \brief Get number of bytes of still-queued audio
	///
	/// \returns Number of bytes (not samples!) of still-queued audio
	///
	/// \see http://wiki.libsdl.org/SDL_GetQueuedAudioSize
	///
	////////////////////////////////////////////////////////////
	Uint32 GetQueuedAudioSize() const;
#endif
};

}

#endif
