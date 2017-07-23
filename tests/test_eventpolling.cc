#include <SDL_main.h>

#include <SDL2pp/EventPolling.hh>
#include <SDL2pp/Exception.hh>

#include "testing.h"

#include <vector>

using namespace SDL2pp;
using namespace SDL2pp::Event;
using namespace std;

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

namespace StaticEventHandler {
	vector<SDL_Event> events;

	inline void EventHandler(const SDL_Event& event) {
		events.push_back(event);
	}
}

struct CallableEventHandler {
	vector<SDL_Event> events;

	void operator()(const SDL_Event& event) {
		events.push_back(event);
	}
};

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


	// With function as an event handler
	{
		StaticEventHandler::events.clear();
		
		const SDL_Event expected = PushUserEvent(15);
		
		EXPECT_TRUE(PollEvent(StaticEventHandler::EventHandler) == true);
		EXPECT_TRUE(StaticEventHandler::events.size() == 1);
		
		const SDL_Event result = StaticEventHandler::events[0];
		EXPECT_TRUE(result.type == expected.type);
		EXPECT_TRUE(result.user.code == expected.user.code);
		
		// Verify no further events
		EXPECT_TRUE(PollEvent(StaticEventHandler::EventHandler) == false);
		EXPECT_TRUE(StaticEventHandler::events.size() == 1);
	}
	
	// With lambda as an event handler
	{
		vector<SDL_Event> events;
		const SDL_Event expectedEvent = PushUserEvent(22);
		
		EXPECT_TRUE(PollEvent([&events](const SDL_Event& event) {
			events.push_back(event);
		}) == true);
		EXPECT_TRUE(events.size() == 1);
		
		const SDL_Event result = events[0];
		EXPECT_TRUE(result.type == expectedEvent.type);
		EXPECT_TRUE(result.user.code == expectedEvent.user.code);
		
		// Verify no further events
		EXPECT_TRUE(PollEvent([&events](const SDL_Event& event) {
			events.push_back(event);
		}) == false);
		EXPECT_TRUE(events.size() == 1);
	}
	
	// With callable object
	{
		CallableEventHandler eventHandler;
		
		const SDL_Event expectedEvent = PushUserEvent(45);
		
		EXPECT_TRUE(PollEvent(std::ref(eventHandler)) == true);
		EXPECT_TRUE(eventHandler.events.size() == 1);
		
		const SDL_Event result = eventHandler.events[0];
		EXPECT_TRUE(result.type == expectedEvent.type);
		EXPECT_TRUE(result.user.code == expectedEvent.user.code);
		
		// Verify no further events
		EXPECT_TRUE(PollEvent(eventHandler) == false);
		EXPECT_TRUE(eventHandler.events.size() == 1);
	}

	// With no callback and no polled events
	{
		EXPECT_TRUE(PollAllEvents() == 0);
	}
	
	// With no callback and several polled events
	{
		constexpr int totalEvents = 5;
		for (int n = 0; n < totalEvents; ++n) {
			PushUserEvent();
		}
		
		EXPECT_TRUE(PollAllEvents() == totalEvents);
		// Verify no further events
		EXPECT_TRUE(PollEvent() == false);
	}
	
	// With function as an event handler
	{
		StaticEventHandler::events.clear();
		
		vector<SDL_Event> expectedEvents;
		for (const auto eventCode : { 15, 32, 99, 85 }) {
			expectedEvents.push_back(PushUserEvent(eventCode));
		}
		int totalExpectedEvents = static_cast<int>(expectedEvents.size());
		
		EXPECT_TRUE(PollAllEvents(StaticEventHandler::EventHandler) == totalExpectedEvents);
		EXPECT_TRUE(StaticEventHandler::events.size() == expectedEvents.size());
		
		for (int n = 0; n < totalExpectedEvents; n++) {
			const SDL_Event result = StaticEventHandler::events[n];
			const SDL_Event expected = expectedEvents[n];
			
			EXPECT_TRUE(result.type == expected.type);
			EXPECT_TRUE(result.user.code == expected.user.code);
		}
		
		// Verify no further events
		EXPECT_TRUE(PollEvent(StaticEventHandler::EventHandler) == false);
		EXPECT_TRUE(StaticEventHandler::events.size() == expectedEvents.size());
	}
	
	// With lambda as an event handler
	{
		vector<SDL_Event> handledEvents;
		vector<SDL_Event> expectedEvents;
		for (const auto eventCode : { 37, 88, 42, 63, 23, 19 }) {
			expectedEvents.push_back(PushUserEvent(eventCode));
		}
		int totalExpectedEvents = static_cast<int>(expectedEvents.size());
		
		EXPECT_TRUE(PollAllEvents([&handledEvents](const SDL_Event& event) {
			handledEvents.push_back(event);
		}) == totalExpectedEvents);
		EXPECT_TRUE(handledEvents.size() == expectedEvents.size());
		
		for (int n = 0; n < totalExpectedEvents; n++) {
			const SDL_Event result = handledEvents[n];
			const SDL_Event expected = expectedEvents[n];
			
			EXPECT_TRUE(result.type == expected.type);
			EXPECT_TRUE(result.user.code == expected.user.code);
		}
		
		// Verify no further events
		EXPECT_TRUE(PollEvent([&handledEvents](const SDL_Event& event) {
			handledEvents.push_back(event);
		}) == false);
		EXPECT_TRUE(handledEvents.size() == expectedEvents.size());
	}
	
	// With callable object as an event handler
	{
		CallableEventHandler eventHandler;
		
		vector<SDL_Event> expectedEvents;
		for (const auto eventCode : { 11, 98, 62, 35, 71 }) {
			expectedEvents.push_back(PushUserEvent(eventCode));
		}
		int totalExpectedEvents = static_cast<int>(expectedEvents.size());
		
		EXPECT_TRUE(PollAllEvents(std::ref(eventHandler)) == totalExpectedEvents);
		EXPECT_TRUE(eventHandler.events.size() == expectedEvents.size());
		
		for (int n = 0; n < totalExpectedEvents; n++) {
			const SDL_Event result = eventHandler.events[n];
			const SDL_Event expected = expectedEvents[n];
			
			EXPECT_TRUE(result.type == expected.type);
			EXPECT_TRUE(result.user.code == expected.user.code);
		}
		
		// Verify no further events
		EXPECT_TRUE(PollEvent(eventHandler) == false);
		EXPECT_TRUE(eventHandler.events.size() == expectedEvents.size());
	}
END_TEST()
