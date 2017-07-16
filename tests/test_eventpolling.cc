#include <SDL_main.h>

#include <SDL2pp/EventPolling.hh>
#include <SDL2pp/Exception.hh>

#include "testing.h"

using namespace SDL2pp;

inline SDL_Event PushUserEvent(Sint32 userCode = 0, void *data1 = nullptr, void *data2 = nullptr) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = userCode;
	event.user.data1 = data1;
	event.user.data2 = data2;
	
	if (SDL_PushEvent(&event) < 0) {
		throw Exception("SDL_PushEvent");
	}
	
	return event;
}

BEGIN_TEST(int, char*[])
	// With no callback and no polled event
	{
		EXPECT_TRUE(PollEvent() == false);
	}
	
	// With no callback and a polled event
	{
		PushUserEvent();
		
		EXPECT_TRUE(PollEvent() == true);
		EXPECT_TRUE(PollEvent() == false);
	}
END_TEST()
