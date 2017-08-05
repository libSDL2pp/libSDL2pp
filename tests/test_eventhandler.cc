#include <SDL_main.h>

#include <SDL2pp/Private/EventHandler.hh>

using namespace SDL2pp::Private;

void EventHandlerFunction(const SDL_Event &);

struct EventHandlerOperator {
	void operator()(SDL_Event);
};

struct EventHandler {
	void HandleEvent(const SDL_Event &);
};

struct InvalidEventHandler {
	void HandleEvent(SDL_Event);
};

int main(int, char*[]) {
	auto lambda = [](const SDL_Event &) { };

	// Test IsEventHandlerFunctor
	static_assert(
		IsEventHandlerFunctor<decltype(EventHandlerFunction), SDL_Event>::value,
		"IsEventHandlerFunctor<> should accept functions like void(const SDL_Event &)"
	);
	static_assert(
		IsEventHandlerFunctor<decltype(lambda), SDL_Event>::value,
		"IsEventHandlerFunctor<> should accept functions like void(const SDL_Event &)"
	);
	static_assert(
		!IsEventHandlerFunctor<EventHandlerOperator, SDL_Event>::value,
		"IsEventHandlerFunctor<> shouldn't accept a class with operator(const SDL_Event &)"
	);
	
	// Test IsEventHandlerObject
	static_assert(
		IsEventHandlerObject<EventHandler, SDL_Event>::value,
		"IsEventHandlerObject<> should accept a class with HandleEvent(const SDL_Event &)"
	);
	static_assert(
		!IsEventHandlerObject<InvalidEventHandler, SDL_Event>::value,
		"IsEventHandlerObject<> shouldn't accept a class with a different HandleEvent() signature"
	);
	
	// Test IsEventHandler
	static_assert(
		IsEventHandler<decltype(EventHandlerFunction), SDL_Event>::value,
		"IsEventHandler<> should accept functions like void(const SDL_Event &)"
	);
	static_assert(
		IsEventHandler<decltype(lambda), SDL_Event>::value,
		"IsEventHandler<> should accept functions like void(const SDL_Event &)"
	);
	static_assert(
		IsEventHandler<EventHandler, SDL_Event>::value,
		"IsEventHandler<> should accept a class with HandleEvent(const SDL_Event &)"
	);
	static_assert(
		!IsEventHandler<EventHandlerOperator, SDL_Event>::value,
		"IsEventHandler<> shouldn't accept a class with operator(const SDL_Event &)"
	);
	static_assert(
		!IsEventHandler<InvalidEventHandler, SDL_Event>::value,
		"IsEventHandler<> shouldn't accept a class with a different HandleEvent() signature"
	);
}
