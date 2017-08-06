#include <SDL_main.h>

#include <SDL2pp/Private/EventHandler.hh>

using namespace SDL2pp::Private;

void EventHandlerFunction(SDL_Event);

struct EventHandlerFunctor {
	void operator()(SDL_Event);
};

struct EventHandler {
	void HandleEvent(SDL_Event);
};

struct InvalidEventHandler {
	void handleEvent(SDL_Event);
};

int main(int, char*[]) {
	auto lambda = [](SDL_Event) { };

	// Test IsEventHandlerFunctor
	static_assert(
		IsEventHandlerFunctor<decltype(EventHandlerFunction), SDL_Event>::value,
		"IsEventHandlerFunctor<> should accept functions like void(SDL_Event)"
	);
	static_assert(
		IsEventHandlerFunctor<decltype(lambda), SDL_Event>::value,
		"IsEventHandlerFunctor<> should accept functions like void(SDL_Event)"
	);
	static_assert(
		IsEventHandlerFunctor<EventHandlerFunctor, SDL_Event>::value,
		"IsEventHandlerFunctor<> shouldn accept a class with operator(SDL_Event)"
	);
	
	// Test IsEventHandlerObject
	static_assert(
		IsEventHandlerObject<EventHandler, SDL_Event>::value,
		"IsEventHandlerObject<> should accept a class with HandleEvent(SDL_Event)"
	);
	static_assert(
		!IsEventHandlerObject<InvalidEventHandler, SDL_Event>::value,
		"IsEventHandlerObject<> shouldn't accept a class without a valid signature"
	);
	
	// Test IsEventHandler
	static_assert(
		IsEventHandler<decltype(EventHandlerFunction), SDL_Event>::value,
		"IsEventHandler<> should accept functions like void(SDL_Event)"
	);
	static_assert(
		IsEventHandler<decltype(lambda), SDL_Event>::value,
		"IsEventHandler<> should accept functions like void(SDL_Event)"
	);
	static_assert(
		IsEventHandler<EventHandlerFunctor, SDL_Event>::value,
		"IsEventHandler<> should accept a class with operator(SDL_Event)"
	);
	static_assert(
		IsEventHandler<EventHandler, SDL_Event>::value,
		"IsEventHandler<> should accept a class with HandleEvent(SDL_Event)"
	);
	static_assert(
		!IsEventHandler<InvalidEventHandler, SDL_Event>::value,
		"IsEventHandler<> shouldn't accept a class without a valid signature"
	);
}
