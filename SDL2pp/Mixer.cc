/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2015-2016 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Music.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Mixer::Mixer(int frequency, Uint16 format, int channels, int chunksize) : open_(true) {
	if (Mix_OpenAudio(frequency, format, channels, chunksize) != 0)
		throw Exception("Mix_OpenAudio");
}

Mixer::~Mixer() {
	if (open_)
		Mix_CloseAudio();
}

Mixer::Mixer(Mixer&& other) noexcept : open_(other.open_), current_music_hook_(std::move(other.current_music_hook_)) {
	other.open_ = false;
}

Mixer& Mixer::operator=(Mixer&& other) noexcept {
	if (&other == this)
		return *this;
	if (open_)
		Mix_CloseAudio();
	open_ = other.open_;
	current_music_hook_ = std::move(other.current_music_hook_);
	other.open_ = false;
	return *this;
}

int Mixer::AllocateChannels(int numchans) {
	return Mix_AllocateChannels(numchans);
}

int Mixer::GetNumChannels() const {
	return Mix_AllocateChannels(-1);
}

int Mixer::SetVolume(int channel, int volume) {
	return Mix_Volume(channel, volume);
}

int Mixer::GetVolume(int channel) const {
	return Mix_Volume(channel, -1);
}

int Mixer::PlayChannel(int channel, const Chunk& chunk, int loops) {
	int chan;
	if ((chan = Mix_PlayChannel(channel, chunk.Get(), loops)) == -1)
		throw Exception("Mix_PlayChannel");
	return chan;
}

int Mixer::PlayChannel(int channel, const Chunk& chunk, int loops, int ticks) {
	int chan;
	if ((chan = Mix_PlayChannelTimed(channel, chunk.Get(), loops, ticks)) == -1)
		throw Exception("Mix_PlayChannelTimed");
	return chan;
}

int Mixer::FadeInChannel(int channel, const Chunk& chunk, int loops, int ms) {
	int chan;
	if ((chan = Mix_FadeInChannel(channel, chunk.Get(), loops, ms)) == -1)
		throw Exception("Mix_FadeInChannel");
	return chan;
}

int Mixer::FadeInChannel(int channel, const Chunk& chunk, int loops, int ms, int ticks) {
	int chan;
	if ((chan = Mix_FadeInChannelTimed(channel, chunk.Get(), loops, ms, ticks)) == -1)
		throw Exception("Mix_FadeInChannelTimed");
	return chan;
}

void Mixer::PauseChannel(int channel) {
	Mix_Pause(channel);
}

void Mixer::ResumeChannel(int channel) {
	Mix_Resume(channel);
}

void Mixer::HaltChannel(int channel) {
	Mix_HaltChannel(channel);
}

int Mixer::ExpireChannel(int channel, int ticks) {
	return Mix_ExpireChannel(channel, ticks);
}

int Mixer::FadeOutChannel(int channel, int ms) {
	return Mix_FadeOutChannel(channel, ms);
}

void Mixer::SetChannelFinishedHandler(ChannelFinishedHandler channel_finished) {
	Mix_ChannelFinished(channel_finished);
}

void Mixer::RemoveChannelFinishedHandler() {
	Mix_ChannelFinished(nullptr);
}

int Mixer::IsChannelPlaying(int channel) const {
	return Mix_Playing(channel);
}

int Mixer::IsChannelPaused(int channel) const {
	return Mix_Paused(channel);
}

Mix_Fading Mixer::GetChannelFading(int which) const {
	return Mix_FadingChannel(which);
}

int Mixer::ReserveChannels(int num) {
	return Mix_ReserveChannels(num);
}

void Mixer::GroupChannel(int which, int tag) {
	if (Mix_GroupChannel(which, tag) != 1)
		throw Exception("Mix_GroupChannel");
}

void Mixer::GroupChannels(int from, int to, int tag) {
	if (Mix_GroupChannels(from, to, tag) != to - from + 1)
		throw Exception("Mix_GroupChannels");
}

int Mixer::GetGroupNumChannels(int tag) const {
	return Mix_GroupCount(tag);
}

int Mixer::GetGroupAvailableChannel(int tag) const {
	return Mix_GroupAvailable(tag);
}

int Mixer::GetGroupOldestChannel(int tag) const {
	return Mix_GroupOldest(tag);
}

int Mixer::GetGroupNewestChannel(int tag) const {
	return Mix_GroupNewer(tag);
}

int Mixer::FadeOutGroup(int tag, int ms) {
	return Mix_FadeOutGroup(tag, ms);
}

void Mixer::HaltGroup(int tag) {
	Mix_HaltGroup(tag);
}

void Mixer::PlayMusic(const Music& music, int loops) {
	if (Mix_PlayMusic(music.Get(), loops) == -1)
		throw Exception("Mix_PlayMusic");
}

void Mixer::FadeInMusic(const Music& music, int loops, int ms) {
	if (Mix_FadeInMusic(music.Get(), loops, ms) == -1)
		throw Exception("Mix_FadeInMusic");
}

int Mixer::SetMusicVolume(int volume) {
	return Mix_VolumeMusic(volume);
}

int Mixer::GetMusicVolume() const {
	return Mix_VolumeMusic(-1);
}

void Mixer::PauseMusic() {
	Mix_PauseMusic();
}

void Mixer::ResumeMusic() {
	Mix_ResumeMusic();
}

void Mixer::RewindMusic() {
	Mix_RewindMusic();
}

void Mixer::SetMusicPosition(double position) {
	if (Mix_SetMusicPosition(position) == -1)
		throw Exception("Mix_SetMusicPosition");
}

void Mixer::HaltMusic() {
	Mix_HaltMusic();
}

bool Mixer::FadeOutMusic(int ms) {
	return Mix_FadeOutMusic(ms) > 0;
}

bool Mixer::IsMusicPlaying() const {
	return Mix_PlayingMusic() > 0;
}

bool Mixer::IsMusicPaused() const {
	return Mix_PausedMusic() > 0;
}

Mix_Fading Mixer::GetMusicFading() const {
	return Mix_FadingMusic();
}

void Mixer::SetMusicFinishedHandler(MusicFinishedHandler music_finished) {
	Mix_HookMusicFinished(music_finished);
}

void Mixer::RemoveMusicFinishedHandler() {
	Mix_HookMusicFinished(nullptr);
}

void Mixer::SetMusicHook(MusicHook&& hook) {
	if (!hook) {
		Mix_HookMusic(nullptr, nullptr);
		current_music_hook_.reset(nullptr);
		return;
	}

	current_music_hook_.reset(new MusicHook(std::move(hook)));

	Mix_HookMusic([](void *udata, Uint8 *stream, int len) {
		static_cast<std::function<void(Uint8 *stream, int len)>*>(udata)->operator()(stream, len);
	}, current_music_hook_.get());
}

void Mixer::SetPanning(int channel, Uint8 left, Uint8 right) {
	if (Mix_SetPanning(channel, left, right) == 0)
		throw Exception("Mix_SetPanning");
}

void Mixer::UnsetPanning(int channel) {
	if (Mix_SetPanning(channel, 255, 255) == 0)
		throw Exception("Mix_SetPanning");
}

void Mixer::SetDistance(int channel, Uint8 distance) {
	if (Mix_SetDistance(channel, distance) == 0)
		throw Exception("Mix_SetDistance");
}

void Mixer::UnsetDistance(int channel) {
	if (Mix_SetDistance(channel, 0) == 0)
		throw Exception("Mix_SetDistance");
}

void Mixer::SetPosition(int channel, Sint16 angle, Uint8 distance) {
	if (Mix_SetPosition(channel, angle, distance) == 0)
		throw Exception("Mix_SetPosition");
}

void Mixer::UnsetPosition(int channel) {
	if (Mix_SetPosition(channel, 0, 0) == 0)
		throw Exception("Mix_SetPosition");
}

void Mixer::SetReverseStereo(int channel) {
	if (Mix_SetReverseStereo(channel, 1) == 0)
		throw Exception("Mix_SetReverseStereo");
}

void Mixer::UnsetReverseStereo(int channel) {
	if (Mix_SetReverseStereo(channel, 0) == 0)
		throw Exception("Mix_SetReverseStereo");
}

}
