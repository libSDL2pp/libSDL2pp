#include <atomic>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "testing.h"

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

	{
		EXPECT_TRUE(device.GetStatus(), SDL_AUDIO_PAUSED);
		EXPECT_TRUE(callback_requests == 0);

		long saved_reqs1 = callback_requests;

		device.Pause(false);
		EXPECT_TRUE(device.GetStatus(), SDL_AUDIO_PLAYING);

		SDL_Delay(1000);
		EXPECT_TRUE(callback_requests > saved_reqs1);

		device.Pause(true);
		EXPECT_TRUE(device.GetStatus(), SDL_AUDIO_PLAYING);

		long saved_reqs2 = callback_requests;

		SDL_Delay(1000);
		EXPECT_TRUE(callback_requests == saved_reqs2);

		device.Pause(false);

		long saved_reqs3;
		{
			AudioDevice::LockHandle lock = device.Lock();
			saved_reqs3 = callback_requests;

			SDL_Delay(1000);

			EXPECT_TRUE(callback_requests == saved_reqs3);
		}

		SDL_Delay(1000);

		EXPECT_TRUE(callback_requests > saved_reqs3);
	}
END_TEST()
