#include <vector>

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/RWops.hh>

#include "testing.h"
#include "movetest.hh"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	SDL sdl(SDL_INIT_AUDIO);
	SDLMixer mixerlib(MIX_INIT_OGG);

	{
		// Init
		EXPECT_EQUAL(mixerlib.GetInitFlags(), MIX_INIT_OGG, "Mix_Init(0) doesn't return mask of init'd loaders", NON_FATAL);

		EXPECT_TRUE(mixerlib.InitMore(MIX_INIT_FLAC) & MIX_INIT_FLAC);

		EXPECT_EQUAL(mixerlib.GetInitFlags(), MIX_INIT_OGG | MIX_INIT_FLAC, "Mix_Init(0) doesn't return mask of init'd loaders", NON_FATAL);
	}

	Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

	Chunk sound(TESTDATA_DIR "/test.ogg");
	Music music(TESTDATA_DIR "/test.ogg");

	// RWops methods
	{
		auto rwops = RWops::FromFile(TESTDATA_DIR "/test.ogg");
		Chunk chunk_by_rw(rwops);

		EXPECT_TRUE(chunk_by_rw.Get() != nullptr);

		rwops.Seek(0, RW_SEEK_SET);
		Music music_by_rw1(rwops);

		EXPECT_TRUE(music_by_rw1.Get() != nullptr);
		EXPECT_EQUAL(music_by_rw1.GetType(), MUS_OGG);

		rwops.Seek(0, RW_SEEK_SET);
		Music music_by_rw2(rwops, MUS_OGG);

		EXPECT_TRUE(music_by_rw2.Get() != nullptr);
		EXPECT_EQUAL(music_by_rw2.GetType(), MUS_OGG);

		// bad format
		rwops.Seek(0, RW_SEEK_SET);
		EXPECT_EXCEPTION(Music(rwops, MUS_WAV), Exception);
	}

	MOVE_TEST(Chunk, sound, Get, nullptr);
	MOVE_TEST(Music, music, Get, nullptr);

	constexpr int delay = 500;

	// Chunk methods
	{
		int prevvol = sound.GetVolume();
		EXPECT_EQUAL(sound.SetVolume(MIX_MAX_VOLUME/2), prevvol);
		EXPECT_EQUAL(sound.GetVolume(), MIX_MAX_VOLUME/2);
	}

	// Music methods
	EXPECT_EQUAL(music.GetType(), MUS_OGG);

	// Mixer: channels
	EXPECT_TRUE(mixer.GetNumChannels() > 0);
	EXPECT_EQUAL(mixer.AllocateChannels(10), 10);
	EXPECT_EQUAL(mixer.GetNumChannels(), 10);

	// Mixer: volume
	{
		int prevvol = mixer.GetVolume(0);
		EXPECT_EQUAL(mixer.SetVolume(0, MIX_MAX_VOLUME/2), prevvol);
		EXPECT_EQUAL(mixer.GetVolume(0), MIX_MAX_VOLUME/2);
	}

	// Mixer: sound finished handler
	// Since we can't pass a closure to SetChannelFinishedHandler,
	// we have to use static var
	static int finchan = -1;
	mixer.SetChannelFinishedHandler([](int chan){ finchan = chan; });

	// Mixer: idle channel status
	EXPECT_EQUAL(mixer.IsChannelPlaying(0), 0);
	EXPECT_EQUAL(mixer.IsChannelPaused(0), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(0), MIX_NO_FADING);

	// Mixer: basic playing, operations and status examination
	int chan = mixer.PlayChannel(-1, sound);
	EXPECT_TRUE(chan >= 0);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);

	mixer.PauseChannel(chan);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 1);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);
	EXPECT_EQUAL(finchan, -1);

	mixer.ResumeChannel(chan);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);
	EXPECT_EQUAL(finchan, -1);

	mixer.ExpireChannel(chan, delay);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);
	EXPECT_EQUAL(finchan, -1);

	SDL_Delay(delay * 2);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 0);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);
	EXPECT_EQUAL(finchan, chan);

	mixer.RemoveChannelFinishedHandler();

	// Mixer: timed play
	chan = mixer.PlayChannel(-1, sound, -1, delay);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);

	SDL_Delay(delay * 2);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 0);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);

	// Mixer: fading
	chan = mixer.FadeInChannel(-1, sound, -1, delay);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_FADING_IN);

	SDL_Delay(delay * 2);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);

	EXPECT_EQUAL(mixer.FadeOutChannel(chan, 500), 1);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_FADING_OUT);

	SDL_Delay(delay * 2);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 0);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);

	// Mixer: timed fading, halt
	chan = mixer.FadeInChannel(-1, sound, -1, delay, delay * 4);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_FADING_IN);

	SDL_Delay(delay * 2);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 1);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);

	mixer.HaltChannel(-1);

	EXPECT_EQUAL(mixer.IsChannelPlaying(chan), 0);
	EXPECT_EQUAL(mixer.IsChannelPaused(chan), 0);
	EXPECT_EQUAL(mixer.GetChannelFading(chan), MIX_NO_FADING);

	// Mixer: music volume
	{
		int prevvol = mixer.GetMusicVolume();
		EXPECT_EQUAL(mixer.SetMusicVolume(MIX_MAX_VOLUME/2), prevvol);
		EXPECT_EQUAL(mixer.GetMusicVolume(), MIX_MAX_VOLUME/2);
	}

	// Mixer: music finished handler
	static bool finmusic = false;
	mixer.SetMusicFinishedHandler([](){ finmusic = true; });

	// Mixer: music

	EXPECT_EQUAL(mixer.IsMusicPlaying(), false);

	mixer.PlayMusic(music, -1);

	EXPECT_EQUAL(mixer.IsMusicPlaying(), true);
	EXPECT_EQUAL(mixer.IsMusicPaused(), false);
	EXPECT_EQUAL(mixer.GetMusicFading(), MIX_NO_FADING);
	EXPECT_EQUAL(finmusic, false);

	mixer.PauseMusic();

	EXPECT_EQUAL(mixer.IsMusicPlaying(), true);
	EXPECT_EQUAL(mixer.IsMusicPaused(), true);
	EXPECT_EQUAL(mixer.GetMusicFading(), MIX_NO_FADING);
	EXPECT_EQUAL(finmusic, false);

	mixer.ResumeMusic();

	EXPECT_EQUAL(mixer.IsMusicPlaying(), true);
	EXPECT_EQUAL(mixer.IsMusicPaused(), false);
	EXPECT_EQUAL(mixer.GetMusicFading(), MIX_NO_FADING);
	EXPECT_EQUAL(finmusic, false);

	EXPECT_EQUAL(mixer.FadeOutMusic(delay), true);

	EXPECT_EQUAL(mixer.IsMusicPlaying(), true);
	EXPECT_EQUAL(mixer.IsMusicPaused(), false);
	EXPECT_EQUAL(mixer.GetMusicFading(), MIX_FADING_OUT);
	EXPECT_EQUAL(finmusic, false);

	SDL_Delay(delay * 2);

	EXPECT_EQUAL(mixer.IsMusicPlaying(), false);
	EXPECT_EQUAL(mixer.IsMusicPaused(), false);
	EXPECT_EQUAL(mixer.GetMusicFading(), MIX_NO_FADING);
	EXPECT_EQUAL(finmusic, true);

	mixer.RemoveMusicFinishedHandler();

	// Mixer: music fadein, rewind, halt
	mixer.FadeInMusic(music, -1, delay);

	EXPECT_EQUAL(mixer.IsMusicPlaying(), true);
	EXPECT_EQUAL(mixer.IsMusicPaused(), false);
	EXPECT_EQUAL(mixer.GetMusicFading(), MIX_FADING_IN);

	SDL_Delay(delay * 2);

	EXPECT_EQUAL(mixer.IsMusicPlaying(), true);
	EXPECT_EQUAL(mixer.IsMusicPaused(), false);
	EXPECT_EQUAL(mixer.GetMusicFading(), MIX_NO_FADING);

	mixer.RewindMusic();

	mixer.SetMusicPosition(0.0);

	mixer.HaltMusic();

	EXPECT_EQUAL(mixer.IsMusicPlaying(), false);
	EXPECT_EQUAL(mixer.IsMusicPaused(), false);
	EXPECT_EQUAL(mixer.GetMusicFading(), MIX_NO_FADING);
END_TEST()
