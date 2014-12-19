/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2014 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2/SDL_audio.h>

#include <SDL2pp/Config.hh>

namespace SDL2pp {

class AudioSpec;

class AudioDevice {
public:
	////////////////////////////////////////////////////////////
	/// \brief SDL2pp::AudioDevice lock
	/// \ingroup audio
	///
	/// \details
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
	class LockHandle {
		friend class AudioDevice;
	private:
		AudioDevice* device_; ///< SDL2pp::AudioDevice the lock belongs to

	private:
		////////////////////////////////////////////////////////////
		/// \brief Create lock for specific SDL2pp::AudioDevice
		///
		/// \param device Pointer to audio device to lock
		///
		/// \see http://wiki.libsdl.org/SDL_LockAudioDevice
		///
		/// This operation locks a device, which remains locked
		/// until LockHandle is destroyed
		///
		/// Recursive locking is allowed
		///
		////////////////////////////////////////////////////////////
		LockHandle(AudioDevice* device);

	public:
		////////////////////////////////////////////////////////////
		/// \brief Create no-op lock
		///
		/// \details
		/// This may be initialized with real lock later with move
		/// assignment operator
		///
		////////////////////////////////////////////////////////////
		LockHandle();

		////////////////////////////////////////////////////////////
		/// \brief Destructor
		///
		/// \details
		/// Releases the lock
		///
		////////////////////////////////////////////////////////////
		~LockHandle();

		////////////////////////////////////////////////////////////
		/// \brief Move constructor
		///
		/// \param other SDL2pp::AudioDevice::LockHandle to move data from
		///
		////////////////////////////////////////////////////////////
		LockHandle(LockHandle&& other) noexcept;

		////////////////////////////////////////////////////////////
		/// \brief Move assignment operator
		///
		/// \param other SDL2pp::AudioDevice::LockHandle to move data from
		///
		////////////////////////////////////////////////////////////
		LockHandle& operator=(LockHandle&& other) noexcept;

		// Deleted copy constructor and assignment
		LockHandle(const LockHandle& other) = delete;
		LockHandle& operator=(const LockHandle& other) = delete;
	};

	typedef std::function<void(Uint8* stream, int len)> AudioCallback;

private:
	SDL_AudioDeviceID device_id_; ///< SDL2 device id
	AudioCallback callback_;      ///< Callback used to feed audio data to the device

private:
	static void SDLCallback(void *userdata, Uint8* stream, int len);

public:
	AudioDevice(const std::string& device, bool iscapture, const AudioSpec& spec, AudioCallback&& callback = AudioCallback());
	AudioDevice(const std::string& device, bool iscapture, AudioSpec& spec, int allowed_changes, AudioCallback&& callback = AudioCallback());
	virtual ~AudioDevice();

	AudioDevice(const AudioDevice& other) = delete;
	AudioDevice(AudioDevice&& other) noexcept;
	AudioDevice& operator=(const AudioDevice& other) = delete;
	AudioDevice& operator=(AudioDevice&& other) noexcept;

	SDL_AudioDeviceID Get() const;

	void Pause(bool pause_on);
	SDL_AudioStatus GetStatus() const;

	void ChangeCallback(AudioCallback&& callback);

	////////////////////////////////////////////////////////////
	/// \brief Lock audio device to prevent it from calling audio callback
	///
	/// \returns Lock handle used to control lock lifetime
	///
	/// \details
	/// The device remains locked for the lifetime of returned LockHandle
	///
	/// Recursive locking is allowed
	//
	/// \see http://wiki.libsdl.org/SDL_LockAudioDevice
	///
	////////////////////////////////////////////////////////////
	LockHandle Lock();

#ifdef SDL2PP_WITH_2_0_4
	void QueueAudio(const void* data, Uint32 len);
	void ClearQueuedAudio();
	Uint32 GetQueuedAudioSize() const;
#endif
};

}

#endif
