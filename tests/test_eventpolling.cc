#include <SDL.h>

#include <SDL2pp/SDL.hh>
#include <SDL2pp/EventPolling.hh>

#include "testing.h"

using namespace SDL2pp;
using namespace SDL2pp::Event;

BEGIN_TEST(int, char*[])
	SDL sdl{SDL_INIT_EVENTS};

	// Empty event poll
	SDL_Event event;
	while (SDL_PollEvent(&event));

	// Poll a single event
	{
		event.type = SDL_KEYUP;
		SDL_PushEvent(&event);
		
		EXPECT_TRUE(PollEvent());
		EXPECT_TRUE(!PollEvent()); // Verify no additional events
	}

	// Poll multiple events single event
	{
		event.type = SDL_KEYUP;
		constexpr auto amountOfEvents = 5;
		for (auto n = 0; n < amountOfEvents; n++)
			SDL_PushEvent(&event);
		
		EXPECT_EQUAL(PollAllEvents(), amountOfEvents);
		EXPECT_TRUE(!PollEvent()); // Verify no additional events
	}

	// Poll with an event handler
	{
		struct EventHandler {
			int eventsHandled = 0;
			int keyboardEventsHandled = 0;
			bool quitEventHandled = false;
			
			void HandleEvent(SDL_Event) {
				eventsHandled++;
			}
			
			void HandleEvent(SDL_KeyboardEvent) {
				keyboardEventsHandled++;
			}
			
			void HandleEvent(SDL_QuitEvent) {
				quitEventHandled = true;
			}
		};
		
		event.type = SDL_KEYUP;
		SDL_PushEvent(&event);
		
		event.type = SDL_KEYDOWN;
		SDL_PushEvent(&event);
		
		event.type = SDL_QUIT;
		SDL_PushEvent(&event);
		
		auto eventHandler = EventHandler{};
		
		EXPECT_EQUAL(PollAllEvents(eventHandler), 3);
		EXPECT_TRUE(!PollEvent()); // Verify no additional events
		
		EXPECT_EQUAL(eventHandler.eventsHandled, 3);
		EXPECT_EQUAL(eventHandler.keyboardEventsHandled, 2);
		EXPECT_EQUAL(eventHandler.quitEventHandled, true);
	}
END_TEST()
