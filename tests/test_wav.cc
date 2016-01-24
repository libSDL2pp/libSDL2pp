#include <SDL2/SDL_main.h>

#include <SDL2pp/Wav.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	Wav wav(TESTDATA_DIR "/test.wav");

	{
		EXPECT_EQUAL(wav.GetLength(), (Uint32)121044);
		EXPECT_TRUE(wav.GetBuffer() != nullptr);
		EXPECT_TRUE((const Uint8*)wav.GetBuffer() == (Uint8*)wav.GetBuffer());

		const AudioSpec& spec = wav.GetSpec();

		EXPECT_EQUAL(spec.Get()->freq, 44100);
		EXPECT_EQUAL((int)spec.Get()->channels, 2);
	}

	{
		// Move tests
		Uint8* buf = wav.GetBuffer();

		Wav wav1(std::move(wav));
		EXPECT_TRUE(wav1.GetBuffer() == buf);
		EXPECT_TRUE(wav.GetBuffer() == nullptr);

		std::swap(wav, wav1);
		EXPECT_TRUE(wav.GetBuffer() == buf);
		EXPECT_TRUE(wav1.GetBuffer() == nullptr);

		wav = std::move(wav); // self-move
		EXPECT_TRUE(wav.GetBuffer() == buf);
	}
END_TEST()
