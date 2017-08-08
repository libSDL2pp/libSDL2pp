#include <SDL_main.h>

#include <SDL2pp/Private/EventDispatching.hh>

#include "testing.h"

using namespace SDL2pp::Private;

namespace TestFreeFunctions {
	static auto globalResult = Sint32{0};

	inline void handler(SDL_Event event) {
		globalResult = event.user.code;
	}
}

BEGIN_TEST(int, char*[])
	// These test require a major rework, commenting everything in the mean time
	SDL_Event event;
	event.type = SDL_QUIT;
	event.user.code = 31;

	// Test dispatching with no event handler
	DispatchEvent(event);

	// Test dispatching with lambda as event handler
	{
		auto result = Sint32{0};
		DispatchEvent(event, [&result](SDL_Event event) {
			result = event.user.code;
		});
		EXPECT_EQUAL(event.user.code, result);
	}

	// Test dispatching with function as event handler
	{
		DispatchEvent(event, TestFreeFunctions::handler);
		EXPECT_EQUAL(event.user.code, TestFreeFunctions::globalResult);
	}

	// Test dispatching with a functor as event handler
	{
		struct EventHandlerFunctor {
			Sint32 result;

			void operator()(SDL_Event event) {
				result = event.user.code;
			}
		};

		auto eventHandlerFunctor = EventHandlerFunctor{};
		DispatchEvent(event, eventHandlerFunctor);
		EXPECT_EQUAL(event.user.code, eventHandlerFunctor.result);
	}

	// Test dispatching with an object as event handler
	{
		struct EventHandlerObject {
			Sint32 result;

			void HandleEvent(SDL_Event event) {
				result = event.user.code;
			}
		};

		auto eventHandlerObject = EventHandlerObject{};
		DispatchEvent(event, eventHandlerObject);
		EXPECT_EQUAL(event.user.code, eventHandlerObject.result);
	}

	// Test several event handlers
	{
		struct EventHandlerFunctor {
			bool executed = false;
			
			void operator()(SDL_QuitEvent) {
				executed = true;
			}
		};
		auto eventHandlerFunctor1 = EventHandlerFunctor{};
		auto eventHandlerFunctor2 = EventHandlerFunctor{};
		
		struct EventHandlerObject {
			bool executed = false;
			
			void HandleEvent(SDL_QuitEvent) {
				executed = true;
			}
		};
		auto eventHandlerObject = EventHandlerObject{};
	
		auto lambdaExecuted = false;
		auto lambda = [&lambdaExecuted](SDL_QuitEvent) { lambdaExecuted = true; };
		
		DispatchEvent(event, eventHandlerFunctor1, eventHandlerFunctor2, eventHandlerObject, lambda);
		EXPECT_TRUE(eventHandlerFunctor1.executed);
		EXPECT_TRUE(eventHandlerFunctor2.executed);
		EXPECT_TRUE(eventHandlerObject.executed);
		EXPECT_TRUE(lambdaExecuted);
	}

	// Test event handler with several event types
	{
		struct EventHandler {
			bool quitEventExecuted = false;
			bool keyboardEventExecuted = false;
			
			void HandleEvent(SDL_QuitEvent) {
				quitEventExecuted = true;
			}
			
			void HandleEvent(SDL_KeyboardEvent) {
				keyboardEventExecuted = true;
			}
		};
		
		auto eventHandler = EventHandler{};
		DispatchEvent(event, eventHandler);
		
		EXPECT_TRUE(eventHandler.quitEventExecuted);
		EXPECT_TRUE(!eventHandler.keyboardEventExecuted);
		
		eventHandler.quitEventExecuted = false;
		
		event.type = SDL_KEYUP;
		
		DispatchEvent(event, eventHandler);
		
		EXPECT_TRUE(!eventHandler.quitEventExecuted);
		EXPECT_TRUE(eventHandler.keyboardEventExecuted);
	}
END_TEST()
