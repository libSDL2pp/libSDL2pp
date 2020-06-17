#include <ios>

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "testing.h"
#include "movetest.hh"

using namespace SDL2pp;

static void EventSleep(Uint32 ms) {
	Uint32 now = SDL_GetTicks();
	Uint32 deadline = now + ms;

	SDL_Event event;
	while ((now = SDL_GetTicks()) < deadline)
		SDL_WaitEventTimeout(&event, deadline - now);
}

BEGIN_TEST(int, char*[])
	SDL sdl(SDL_INIT_VIDEO);
	Window window("libSDL2pp test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_RESIZABLE);

	MOVE_TEST(Window, window, Get, nullptr);

	EventSleep(1000); // Process events for newborn window

	{
		// Size
		EXPECT_EQUAL(window.GetSize(), Point(320, 240), "May fail on some WMs", NON_FATAL);
		EXPECT_EQUAL(window.GetWidth(), 320, "May fail on some WMs", NON_FATAL);
		EXPECT_EQUAL(window.GetHeight(), 240, "May fail on some WMs", NON_FATAL);

		window.SetSize(400, 300);
		EXPECT_EQUAL(window.GetSize(), Point(400, 300));
		EXPECT_EQUAL(window.GetWidth(), 400);
		EXPECT_EQUAL(window.GetHeight(), 300);
		EventSleep(1000);

		window.SetSize(Point(500, 400));
		EXPECT_EQUAL(window.GetWidth(), 500);
		EXPECT_EQUAL(window.GetHeight(), 400);
		EventSleep(1000);
	}

	{
		// Title
		EXPECT_EQUAL(window.GetTitle(), "libSDL2pp test");

		window.SetTitle("libSDL2pp window test");
		EXPECT_EQUAL(window.GetTitle(), "libSDL2pp window test");
		EventSleep(1000);
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
		EventSleep(1000);

		window.SetPosition(old_pos.x + 4, old_pos.y + 2);
		EXPECT_EQUAL(window.GetPosition(), old_pos + Point(4, 2));
		EventSleep(1000);
	}

	{
		// Min/max size
		window.SetMinimumSize(16, 16);
		window.SetMaximumSize(1600, 1600);

		EXPECT_EQUAL(window.GetMinimumSize(), Point(16, 16));
		EXPECT_EQUAL(window.GetMaximumSize(), Point(1600, 1600));

		window.SetMinimumSize(Point(32, 32));
		window.SetMaximumSize(Point(3200, 3200));

		EXPECT_EQUAL(window.GetMinimumSize(), Point(32, 32));
		EXPECT_EQUAL(window.GetMaximumSize(), Point(3200, 3200));
	}

	{
		// Grab
		EXPECT_TRUE(!window.GetGrab());
		window.SetGrab(true);
		EXPECT_TRUE(window.GetGrab());
		EventSleep(1000);

		window.SetGrab(false);
		EXPECT_TRUE(!window.GetGrab());
		EventSleep(1000);
	}

	{
		// Brightness
		EXPECT_EQUAL(window.GetBrightness(), 1.0f);

		window.SetBrightness(1.2f);
		EXPECT_EQUAL(window.GetBrightness(), 1.2f);
		EventSleep(1000);

		window.SetBrightness(1.0f);
		EXPECT_EQUAL(window.GetBrightness(), 1.0f);
		EventSleep(1000);
	}

	{
		// Flags
		std::cerr << "Window flags: " << std::hex << "0x" << window.GetFlags() << std::dec << std::endl;

		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_SHOWN, SDL_WINDOW_SHOWN);
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_RESIZABLE, SDL_WINDOW_RESIZABLE);

		window.Hide();
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_SHOWN, 0U);
		EventSleep(1000);

		window.Show();
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_SHOWN, SDL_WINDOW_SHOWN);
		EventSleep(1000);

		window.Maximize();
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_MAXIMIZED, SDL_WINDOW_MAXIMIZED);
		EventSleep(1000);

		window.Restore();
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_MAXIMIZED, 0U);
		EventSleep(1000);

		window.Minimize();
		EventSleep(1000); // Minimization may take some time, e.g. on Ubuntu due to animations
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_MINIMIZED, SDL_WINDOW_MINIMIZED, "May fail on some WMs", NON_FATAL);
		EventSleep(1000);

		window.Restore();
		EventSleep(1000); // Restore from minimized state may take some time, e.g. on Ubuntu due to animations
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_MINIMIZED, 0U);
		EventSleep(1000);

		// May hang until window is moved (SDL bug?)
//		window.SetBordered(false);
//		EXPECT_TRUE(window.GetFlags() & SDL_WINDOW_BORDERLESS);
//		EventSleep(1000);

//		window.SetBordered(true);
//		EXPECT_TRUE(!(window.GetFlags() & SDL_WINDOW_BORDERLESS));
//		EventSleep(1000);

		window.Raise();
		EventSleep(1000);
	}

	{
		// Display index & mode

		// XXX: may throw
		int displayindex = 0;
		EXPECT_NO_EXCEPTION(displayindex = window.GetDisplayIndex());
		std::cerr << "Display index: " << displayindex << std::endl;

		SDL_DisplayMode mode;
		EXPECT_NO_EXCEPTION(window.GetDisplayMode(mode));

		std::cerr << "Display mode:" << std::endl;
		std::cerr << "  Format: 0x" << std::hex << mode.format << std::dec << std::endl;
		std::cerr << "  Width: " << mode.w << std::endl;
		std::cerr << "  Height: " << mode.h << std::endl;
		std::cerr << "  Refresh rate: " << mode.refresh_rate << std::endl;
	}

	{
		// Fullscreen
		window.SetFullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP);
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_FULLSCREEN_DESKTOP);
		EventSleep(1000);

		window.SetFullscreen(0);
		EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_FULLSCREEN_DESKTOP, 0U);
		EventSleep(1000);
	}

#if SDL_VERSION_ATLEAST(2, 0, 5)
	{
		// Opacity
		bool has_opacity = true;
		try {
			window.SetOpacity(0.5f);
		} catch (...) {
			has_opacity = false;
			std::cerr << "Setting window opacity is not supported on this platform" << std::endl;
		}

		if (has_opacity) {
			EXPECT_TRUE(window.GetOpacity() > 0.49f);
			EXPECT_TRUE(window.GetOpacity() < 0.51f);
			EventSleep(1000);

			window.SetOpacity();
			EXPECT_TRUE(window.GetOpacity() > 0.99f);
			EventSleep(1000);
		}
	}

    {
        // Resizable
        Uint32 flags = window.GetFlags();

        if (flags & SDL_WINDOW_RESIZABLE) {
			window.SetResizable(false);
			EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_RESIZABLE, 0U);
            EventSleep(1000);

			window.SetResizable(true);
			EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_RESIZABLE, SDL_WINDOW_RESIZABLE);
            EventSleep(1000);
        } else {
			window.SetResizable(true);
			EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_RESIZABLE, SDL_WINDOW_RESIZABLE);
            EventSleep(1000);

			window.SetResizable(false);
			EXPECT_EQUAL(window.GetFlags() & SDL_WINDOW_RESIZABLE, 0U);
            EventSleep(1000);
        }
    }
#endif

END_TEST()
