#include <atomic>
#include <algorithm>
#include <vector>

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "testing.h"
#include "movetest.hh"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	SDL sdl(SDL_INIT_AUDIO);

	static constexpr int samplerate = 48000;

	AudioSpec spec(samplerate, AUDIO_S16SYS, 1, 4096);

	std::atomic_long callback_requests(0);

	AudioDevice device(NullOpt, 0, spec, [&callback_requests](Uint8* stream, int len) {
				std::fill(stream, stream + len, 0);
				++callback_requests;
			});

	MOVE_TEST(AudioDevice, device, Get, 0)

	{
		// Default state
		EXPECT_EQUAL(device.GetStatus(), SDL_AUDIO_PAUSED);
		EXPECT_TRUE(callback_requests == 0);

		long saved_reqs = callback_requests;

		// Unpause
		device.Pause(false);
		EXPECT_EQUAL(device.GetStatus(), SDL_AUDIO_PLAYING);

		SDL_Delay(1000);
		EXPECT_TRUE(callback_requests > saved_reqs);

		// Pause
		device.Pause(true);
		EXPECT_EQUAL(device.GetStatus(), SDL_AUDIO_PAUSED);

		saved_reqs = callback_requests;

		SDL_Delay(1000);
		EXPECT_TRUE(callback_requests == saved_reqs);

		device.Pause(false);

		{
			// Lock
			AudioDevice::LockHandle lock = device.Lock();
			saved_reqs = callback_requests;

			SDL_Delay(1000);

			EXPECT_TRUE(callback_requests == saved_reqs);

			{
				// Recursive lock
				AudioDevice::LockHandle lock1(lock);

				AudioDevice::LockHandle lock2, lock4;

				lock2 = lock1;

				AudioDevice::LockHandle lock3(std::move(lock1));

				lock4 = std::move(lock2);

				SDL_Delay(1000);
			}

			EXPECT_TRUE(callback_requests == saved_reqs);
		}

		// Unlocked
		SDL_Delay(1000);
		EXPECT_TRUE(callback_requests > saved_reqs);

		// Change callback
		device.ChangeCallback([&callback_requests](Uint8* stream, int len) {
				std::fill(stream, stream + len, 0);
				--callback_requests;
			});

		saved_reqs = callback_requests;

		SDL_Delay(1000);
		EXPECT_TRUE(callback_requests < saved_reqs);
	}


#if SDL_VERSION_ATLEAST(2, 0, 4)
	{
		// Queue won't work for callbacked device
		EXPECT_EXCEPTION(device.QueueAudio(0, 0), Exception);

		AudioDevice device2 = AudioDevice(NullOpt, 0, spec);

		static constexpr size_t buflen = 1024 * 1024;

		std::vector<char> zeroes(buflen);
		device2.QueueAudio(zeroes.data(), buflen);

		// Not sure if safe to check for equality; may it
		// already suck in some data?
		EXPECT_EQUAL(device2.GetQueuedAudioSize(), buflen);

		device2.Pause(false);

		// This will suck in some data
		SDL_Delay(1000);
		EXPECT_TRUE(device2.GetQueuedAudioSize() < buflen);

		device2.ClearQueuedAudio();
		EXPECT_EQUAL(device2.GetQueuedAudioSize(), (Uint32)0);
	}
#endif
END_TEST()
