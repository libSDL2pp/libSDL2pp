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

#include <SDL2pp/Exception.hh>

#include <SDL2pp/Audio.hh>

namespace SDL2pp {

AudioDevice::AudioDevice(const std::string& device, bool iscapture, const AudioSpec& spec) {
	SDL_AudioSpec obtained;

	if ((device_id_ = SDL_OpenAudioDevice(device.empty() ? nullptr : device.c_str(), iscapture ? 1 : 0, &spec, &obtained, 0)) == 0)
		throw Exception("SDL_OpenAudioDevice failed");
}

AudioDevice::AudioDevice(const std::string& device, bool iscapture, AudioSpec& spec, int allowed_changes) {
	SDL_AudioSpec obtained;

	if ((device_id_ = SDL_OpenAudioDevice(device.empty() ? nullptr : device.c_str(), iscapture ? 1 : 0, &spec, &obtained, allowed_changes)) == 0)
		throw Exception("SDL_OpenAudioDevice failed");

	spec.MergeChanges(obtained);
}

AudioDevice::~AudioDevice() {
	if (device_id_ != 0)
		SDL_CloseAudioDevice(device_id_);
}

AudioDevice::AudioDevice(AudioDevice&& other) noexcept : device_id_(other.device_id_) {
	other.device_id_ = 0;
}

AudioDevice& AudioDevice::operator=(AudioDevice&& other) noexcept {
	if (device_id_)
		SDL_CloseAudioDevice(device_id_);

	device_id_ = other.device_id_;
	other.device_id_ = 0;

	return *this;
}

SDL_AudioDeviceID AudioDevice::Get() const {
	return device_id_;
}

void AudioDevice::Pause(bool pause_on) {
	SDL_PauseAudioDevice(device_id_, pause_on ? 1 : 0);
}

SDL_AudioStatus AudioDevice::GetStatus() const {
	return SDL_GetAudioDeviceStatus(device_id_);
}

AudioDevice::LockHandle AudioDevice::Lock() {
	return LockHandle(this);
}

#ifdef SDL2PP_NEW_2_0_4
void AudioDevice::QueueAudio(const void* data, Uint32 len) {
	if (SDL_QueueAudio(device_id_, data, len) == 0)
		throw Exception("SDL_QueueAudio failed");
}

void AudioDevice::ClearQueuedAudio() {
	SDL_ClearQueuedAudio(device_id_);
}

Uint32 GetQueuedAudioSize() const {
	return SDL_GetQueuedAudioSize(device_id_);
}
#endif

}
