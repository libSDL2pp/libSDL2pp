/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2017 Vraiment <jemc44@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL2PP_PRIVATE_EVENTHANDLER_HH
#define SDL2PP_PRIVATE_EVENTHANDLER_HH

#include <SDL2pp/Private/Utility.hh>

#include <functional>
#include <tuple>
#include <type_traits>

#include <SDL_events.h>

namespace SDL2pp {
/*
 * This is code not to be used directly by users of SDL2pp.
 */
namespace Private {
	/*
	 * Tuple containing all the valid events that can be handled.
	 */
	using ValidEventTypes = std::tuple<
		SDL_Event,
		SDL_AudioDeviceEvent,
		SDL_ControllerAxisEvent,
		SDL_ControllerButtonEvent,
		SDL_ControllerDeviceEvent,
		SDL_DollarGestureEvent,
		SDL_DropEvent,
		SDL_JoyAxisEvent,
		SDL_JoyBallEvent,
		SDL_JoyButtonEvent,
		SDL_JoyDeviceEvent,
		SDL_JoyHatEvent,
		SDL_KeyboardEvent,
		SDL_MouseButtonEvent,
		SDL_MouseMotionEvent,
		SDL_MouseWheelEvent,
		SDL_MultiGestureEvent,
		SDL_QuitEvent,
		SDL_SysWMEvent,
		SDL_TextEditingEvent,
		SDL_TextInputEvent,
		SDL_TouchFingerEvent,
		SDL_UserEvent,
		SDL_WindowEvent
	>;
	
	/*
	 * Templated class to identify a class that is not an event handler functor.
	 */
	template <typename, typename, typename = void>
	struct IsEventHandlerFunctor : std::false_type { };

	/*
	 * Templated class to identify a class that is an event handler functor, the
	 * way this is done is by verifying if the functor is assignable to the
	 * expected signature.
	 */
	template <typename EventHandlerType, typename EventType>
	struct IsEventHandlerFunctor<
		EventHandlerType,
		EventType,
		typename std::enable_if<
			std::is_convertible<EventHandlerType, std::function<void(EventType)>>::value
		>::type
	> : std::true_type { };
	
	/*
	 * Templated class to identify a class that is not an event handler object.
	 */
	template <typename, typename, typename = void>
	struct IsEventHandlerObject : std::false_type { };
	
	/*
	 * Templated class to identify a class that is an event handler object, the
	 * way this is done is by verifying that an instance of EventHandlerType has
	 * the "HandleEvent" member function which received a "EventType" and
	 * returns void.
	 */
	template <typename EventHandlerType, typename EventType>
	struct IsEventHandlerObject<
		EventHandlerType,
		EventType,
		typename std::enable_if<
			std::is_same<
				decltype(std::declval<EventHandlerType>().HandleEvent(std::declval<EventType>())),
				void
			>::value
		>::type
	> : std::true_type { };
	
	/*
	 * Templated class to identify a class that is not an event handler.
	 */
	template <typename, typename, typename = void>
	struct IsEventHandler : std::false_type { };

	/*
	 * Templated class to identify a type that is an event handler, the type
	 * EventHandlerType is considered to be an event handler if is either an
	 * event handler object or an event handler functor for the given event
	 * type. Also the event type must be a valid SDL event type.
	 *
	 * In other words, any of the following code can be executed:
	 * {
	 *     EventType event;
	 *     EventHandlerType eventHandler;
	 *     eventHandler(event);
	 *     // or
	 *     eventHandler.HandleEvent(event);
	 * }
	 */
	template <typename EventHandlerType, typename EventType>
	struct IsEventHandler<
		EventHandlerType,
		EventType,
		typename std::enable_if<
			And<
				Or<
					IsEventHandlerObject<EventHandlerType, EventType>,
					IsEventHandlerFunctor<EventHandlerType, EventType>
				>,
				TupleHasType<EventType, ValidEventTypes>
			>::value
		>::type
	> : std::true_type { };
}
}

#endif
