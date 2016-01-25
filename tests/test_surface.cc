#include <SDL2/SDL_main.h>

#include <SDL2pp/Surface.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	Surface crate(TESTDATA_DIR "/crate.png");

	{
		EXPECT_EQUAL(crate.GetWidth(), 32);
		EXPECT_EQUAL(crate.GetHeight(), 32);
		EXPECT_EQUAL(crate.GetSize(), Point(32, 32));
	}
END_TEST()
