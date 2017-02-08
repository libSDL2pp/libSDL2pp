#include <SDL_main.h>

#include <SDL2pp/Wav.hh>

#include "testing.h"
#include "movetest.hh"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	Wav wav(TESTDATA_DIR "/test.wav");

	MOVE_TEST(Wav, wav, GetBuffer, nullptr);

	{
		// Wav tests
		EXPECT_EQUAL(wav.GetLength(), (Uint32)121044);
		EXPECT_TRUE(wav.GetBuffer() != nullptr);
		EXPECT_TRUE(wav.GetBuffer() == const_cast<const Wav&>(wav).GetBuffer());

		const AudioSpec& spec = wav.GetSpec();

		EXPECT_EQUAL(spec.Get()->freq, 44100);
		EXPECT_EQUAL((int)spec.Get()->channels, 2);
	}

	{
		const AudioSpec& spec = wav.GetSpec();

		// Audiospec tests
		AudioSpec spec2(spec.Get()->freq, spec.Get()->format, spec.Get()->channels, spec.Get()->samples);

		EXPECT_TRUE(spec.IsSameFormat(spec2));
	}
END_TEST()
