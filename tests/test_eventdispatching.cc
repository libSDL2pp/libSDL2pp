#include <SDL_main.h>

#include <SDL2pp/Private/EventDispatching.hh>

#include "testing.h"

using namespace SDL2pp::Private;

static auto globalResult = Sint32{0};

inline void handler(SDL_Event event)
{
	globalResult = event.user.code;
}

BEGIN_TEST(int, char*[])

SDL_Event event;
event.type = SDL_USEREVENT;
event.user.code = 31;

DispatchEvent(event);

auto result = Sint32{0};
DispatchEvent(event, [&result](SDL_Event event) {
	result = event.user.code;
});
EXPECT_EQUAL(event.user.code, result);

DispatchEvent(event, handler);
EXPECT_EQUAL(event.user.code, globalResult);

struct EventHandlerFunctor {
	Sint32 result;

	void operator()(SDL_Event event) {
		result = event.user.code;
	}
};

auto eventHandlerFunctor = EventHandlerFunctor{};
DispatchEvent(event, eventHandlerFunctor);
EXPECT_EQUAL(event.user.code, eventHandlerFunctor.result);

struct EventHandlerObject {
	Sint32 result;

	void HandleEvent(SDL_Event event) {
		result = event.user.code;
	}
};

auto eventHandlerObject = EventHandlerObject{};
DispatchEvent(event, eventHandlerObject);
EXPECT_EQUAL(event.user.code, eventHandlerObject.result);

struct SpecificEventHandler {
	Sint32 result;
	
	void HandleEvent(SDL_UserEvent event) {
		result = event.code;
	}
};

auto specificEventHandler = SpecificEventHandler{};
DispatchEvent(event, specificEventHandler);
EXPECT_EQUAL(event.user.code, specificEventHandler.result);

END_TEST()
