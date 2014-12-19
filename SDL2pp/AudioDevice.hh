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
	class LockHandle {
		friend class AudioDevice;
	private:
		AudioDevice* device_;

	private:
		LockHandle(AudioDevice* device);

	public:
		LockHandle();
		~LockHandle();

		LockHandle(LockHandle&& other) noexcept;
		LockHandle& operator=(LockHandle&& other) noexcept;

		LockHandle(const LockHandle& other);
		LockHandle& operator=(const LockHandle& other);
	};

	typedef std::function<void(Uint8* stream, int len)> AudioCallback;

private:
	SDL_AudioDeviceID device_id_;
	AudioCallback callback_;

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

	LockHandle Lock();

#ifdef SDL2PP_WITH_2_0_4
	void QueueAudio(const void* data, Uint32 len);
	void ClearQueuedAudio();
	Uint32 GetQueuedAudioSize() const;
#endif
};

}

#endif
