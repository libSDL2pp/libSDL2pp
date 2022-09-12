/*
  libSDL2pp - C++ bindings/wrapper for SDL2
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

#include <SDL2pp/AudioDevice.hh>

namespace SDL2pp {

AudioDevice::LockHandle::LockHandle() : device_(nullptr) {
}

AudioDevice::LockHandle::LockHandle(AudioDevice* device) : device_(device) {
	SDL_LockAudioDevice(device_->device_id_);
}

AudioDevice::LockHandle::~LockHandle() {
	if (device_ != nullptr)
		SDL_UnlockAudioDevice(device_->device_id_);
}

AudioDevice::LockHandle::LockHandle(AudioDevice::LockHandle&& other) noexcept : device_(other.device_) {
	other.device_ = nullptr;
}

AudioDevice::LockHandle& AudioDevice::LockHandle::operator=(AudioDevice::LockHandle&& other) noexcept {
	if (&other == this)
		return *this;

	if (device_ != nullptr)
		SDL_UnlockAudioDevice(device_->device_id_);

	device_ = other.device_;

	other.device_ = nullptr;

	return *this;
}

AudioDevice::LockHandle::LockHandle(const AudioDevice::LockHandle& other) : device_(other.device_) {
	SDL_LockAudioDevice(device_->device_id_);
}

AudioDevice::LockHandle& AudioDevice::LockHandle::operator=(const AudioDevice::LockHandle& other) {
	if (&other == this)
		return *this;

	if (device_ != nullptr)
		SDL_UnlockAudioDevice(device_->device_id_);

	device_ = other.device_;
	SDL_LockAudioDevice(device_->device_id_);

	return *this;
}

}
