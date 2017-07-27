#include <SDL.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/EventWait.hh>

#include "testing.h"

using namespace SDL2pp;
using namespace SDL2pp::Event;

BEGIN_TEST(int, char*[])
	const SDL sdl(SDL_INIT_EVENTS);

	// Test wait event with no timeout
	{
		SDL_Event expected;
		expected.type = SDL_USEREVENT;
		expected.user.code = 99;
		SDL_PushEvent(&expected);
		
		auto result = WaitEvent();
		EXPECT_TRUE(result.type == expected.type);
		EXPECT_TRUE(result.user.code == expected.user.code);
	}

	// Test wait event with timeout and with event
	{
		SDL_Event expected;
		expected.type = SDL_USEREVENT;
		expected.user.code = 32;
		SDL_PushEvent(&expected);
		
		auto result = WaitEvent(10);
		EXPECT_TRUE(!(result == NullOpt));
		EXPECT_TRUE(result->type == expected.type);
		EXPECT_TRUE(result->user.code == expected.user.code);
	}

	// Test wait event with timeout and no event
	{
		auto result = WaitEvent(10);
		EXPECT_TRUE(result == NullOpt);
	}
END_TEST()
