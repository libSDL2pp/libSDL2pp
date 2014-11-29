/*
  libSDL2pp - C++ wrapper for libSDL2
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

#ifndef SDL2PP_AUDIO_HH
#define SDL2PP_AUDIO_HH

#include <functional>
#include <string>

#include <SDL2/SDL_audio.h>

#include <SDL2pp/Config.hh>

namespace SDL2pp {

class AudioSpec : public SDL_AudioSpec {
public:
	typedef std::function<void(Uint8* stream, int len)> AudioCallback;

private:
	AudioCallback callback_;

private:
	static void SDLCallback(void *userdata, Uint8* stream, int len);

public:
	AudioSpec();
	AudioSpec(int freq, SDL_AudioFormat format, Uint8 channels, Uint16 samples, AudioCallback&& callback = AudioCallback());
	~AudioSpec();

	AudioSpec(AudioSpec&& other);
	AudioSpec& operator=(AudioSpec&& other);
	AudioSpec(const AudioSpec& other) = delete;
	AudioSpec& operator=(const AudioSpec& other) = delete;

	void ChangeCallback(AudioCallback&& callback); // should be called with audio device using this spec locked!

	void MergeChanges(const SDL_AudioSpec& obtained);
	const SDL_AudioSpec* Get() const;
};

class AudioDevice {
private:
	SDL_AudioDeviceID device_id_;

public:
	class LockHandle {
		friend class AudioDevice;
	private:
		AudioDevice* device_;

	private:
		LockHandle(AudioDevice* device);

	public:
		~LockHandle();

		LockHandle(LockHandle&& other) noexcept;
		LockHandle& operator=(LockHandle&& other) noexcept;

		LockHandle(const LockHandle& other) = delete;
		LockHandle& operator=(const LockHandle& other) = delete;
	};

public:
	AudioDevice(const std::string& device, bool iscapture, const AudioSpec& spec);
	AudioDevice(const std::string& device, bool iscapture, AudioSpec& spec, int allowed_changes);
	virtual ~AudioDevice();

	AudioDevice(const AudioDevice& other) = delete;
	AudioDevice(AudioDevice&& other) noexcept;
	AudioDevice& operator=(const AudioDevice& other) = delete;
	AudioDevice& operator=(AudioDevice&& other) noexcept;

	SDL_AudioDeviceID Get() const;

	void Pause(bool pause_on);
	SDL_AudioStatus GetStatus() const;

	LockHandle Lock();

#ifdef SDL2PP_NEW_2_0_4
	void QueueAudio(const void* data, Uint32 len);
	void ClearQueuedAudio();
	Uint32 GetQueuedAudioSize() const;
#endif
};

}

#endif
