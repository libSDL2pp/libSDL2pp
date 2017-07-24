#include <SDL_main.h>

#include <SDL2pp/Surface.hh>

#include "testing.h"
#include "movetest.hh"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	Surface crate(TESTDATA_DIR "/crate.png");

	MOVE_TEST(Surface, crate, Get, nullptr);

	{
		EXPECT_EQUAL(crate.GetWidth(), 32);
		EXPECT_EQUAL(crate.GetHeight(), 32);
		EXPECT_EQUAL(crate.GetSize(), Point(32, 32));
	}

#if SDL_VERSION_ATLEAST(2, 0, 5)
	{
		// Test create surface from pixel format
		Surface surface(0, 600, 300, 24, SDL_PIXELFORMAT_RGBA32);
		
		EXPECT_EQUAL(surface.GetWidth(), 600);
		EXPECT_EQUAL(surface.GetHeight(), 300);
		EXPECT_EQUAL(surface.GetFormat(), SDL_PIXELFORMAT_RGBA32);
	}
#endif
END_TEST()
