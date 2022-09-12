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

#include <SDL2pp/Exception.hh>
#include <SDL2pp/AudioSpec.hh>

#include <SDL2pp/AudioDevice.hh>

namespace SDL2pp {

void AudioDevice::SDLCallback(void *userdata, Uint8* stream, int len) {
	AudioDevice* audiodevice = static_cast<AudioDevice*>(userdata);
	audiodevice->callback_(stream, len);
}

AudioDevice::AudioDevice(const Optional<std::string>& device, bool iscapture, const AudioSpec& spec, AudioDevice::AudioCallback&& callback) {
	SDL_AudioSpec spec_with_callback = *spec.Get();
	if (callback) {
		spec_with_callback.callback = SDLCallback;
		spec_with_callback.userdata = static_cast<void*>(this);
	}
	SDL_AudioSpec obtained;

	if ((device_id_ = SDL_OpenAudioDevice(device ? device->c_str() : nullptr, iscapture ? 1 : 0, &spec_with_callback, &obtained, 0)) == 0)
		throw Exception("SDL_OpenAudioDevice");

	callback_ = std::move(callback);
}

AudioDevice::AudioDevice(const Optional<std::string>& device, bool iscapture, AudioSpec& spec, int allowed_changes, AudioDevice::AudioCallback&& callback) {
	SDL_AudioSpec spec_with_callback = *spec.Get();
	if (callback) {
		spec_with_callback.callback = SDLCallback;
		spec_with_callback.userdata = static_cast<void*>(this);
	}
	SDL_AudioSpec obtained;

	if ((device_id_ = SDL_OpenAudioDevice(device ? device->c_str() : nullptr, iscapture ? 1 : 0, &spec_with_callback, &obtained, allowed_changes)) == 0)
		throw Exception("SDL_OpenAudioDevice");

	spec.MergeChanges(obtained);

	callback_ = std::move(callback);
}

AudioDevice::~AudioDevice() {
	if (device_id_ != 0)
		SDL_CloseAudioDevice(device_id_);
}

AudioDevice::AudioDevice(AudioDevice&& other) noexcept : device_id_(other.device_id_), callback_(std::move(other.callback_)) {
	other.device_id_ = 0;
}

AudioDevice& AudioDevice::operator=(AudioDevice&& other) noexcept {
	if (&other == this)
		return *this;

	if (device_id_)
		SDL_CloseAudioDevice(device_id_);

	device_id_ = other.device_id_;
	callback_ = std::move(other.callback_);
	other.device_id_ = 0;

	return *this;
}

SDL_AudioDeviceID AudioDevice::Get() const {
	return device_id_;
}

AudioDevice& AudioDevice::Pause(bool pause_on) {
	SDL_PauseAudioDevice(device_id_, pause_on ? 1 : 0);
	return *this;
}

SDL_AudioStatus AudioDevice::GetStatus() const {
	return SDL_GetAudioDeviceStatus(device_id_);
}

AudioDevice& AudioDevice::ChangeCallback(AudioDevice::AudioCallback&& callback) {
	// make sure callback is not called while it's being replaced
	LockHandle lock = Lock();

	callback_ = std::move(callback);

	return *this;
}

AudioDevice::LockHandle AudioDevice::Lock() {
	return LockHandle(this);
}

#if SDL_VERSION_ATLEAST(2, 0, 4)
AudioDevice& AudioDevice::QueueAudio(const void* data, Uint32 len) {
	if (SDL_QueueAudio(device_id_, data, len) != 0)
		throw Exception("SDL_QueueAudio");
	return *this;
}

AudioDevice& AudioDevice::ClearQueuedAudio() {
	SDL_ClearQueuedAudio(device_id_);
	return *this;
}

Uint32 AudioDevice::GetQueuedAudioSize() const {
	return SDL_GetQueuedAudioSize(device_id_);
}
#endif

}
