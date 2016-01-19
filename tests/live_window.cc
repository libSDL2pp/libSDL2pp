#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "testing.h"

using namespace SDL2pp;

static void ProcessEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
	}
}

BEGIN_TEST(int, char*[])
	SDL sdl(SDL_INIT_VIDEO);
	Window window("libSDL2pp test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, 0);

	ProcessEvents();

	{
		// Size
		EXPECT_EQUAL(window.GetSize(), Point(320, 240));
		EXPECT_EQUAL(window.GetWidth(), 320);
		EXPECT_EQUAL(window.GetHeight(), 240);

		window.SetSize(400, 300);

		EXPECT_EQUAL(window.GetSize(), Point(400, 300));
		EXPECT_EQUAL(window.GetWidth(), 400);
		EXPECT_EQUAL(window.GetHeight(), 300);
	}

	{
		// Title
		EXPECT_EQUAL(window.GetTitle(), "libSDL2pp test");

		window.SetTitle("libSDL2pp window test");

		EXPECT_EQUAL(window.GetTitle(), "libSDL2pp window test");
	}

	{
		// Drawable size
		EXPECT_EQUAL(window.GetDrawableSize(), Point(window.GetDrawableWidth(), window.GetDrawableHeight()));

		// Drawable may be larget than window size, see SDL docs
		// Should we compare with multiplies of window size?
		EXPECT_TRUE(window.GetDrawableWidth() >= window.GetWidth());
		EXPECT_TRUE(window.GetDrawableHeight() >= window.GetHeight());
		EXPECT_TRUE(window.GetDrawableWidth() > window.GetDrawableHeight());
	}

	{
		// Position
		Point old_pos = window.GetPosition();

		window.SetPosition(old_pos + Point(2, 1));

		EXPECT_EQUAL(window.GetPosition(), old_pos + Point(2, 1));

		window.SetPosition(old_pos.x + 4, old_pos.y + 2);

		EXPECT_EQUAL(window.GetPosition(), old_pos + Point(4, 2));
	}

END_TEST()
