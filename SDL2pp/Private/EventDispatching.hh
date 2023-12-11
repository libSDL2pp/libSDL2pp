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

#ifndef SDL2PP_PRIVATE_EVENTDISPATCHING_HH
#define SDL2PP_PRIVATE_EVENTDISPATCHING_HH

#include <SDL2pp/Private/EventTypeFilters.hh>

namespace SDL2pp {
/*
 * This is code not to be used directly by users of SDL2pp.
 */
namespace Private {
	/*
	 * Templated function to dynamically dispatch an event of type EventType to an event handler functor of type EventHandlerType.
	 *
	 * This will be only called if 'eventHandler(event)' can be called
	 */
	template <typename EventHandlerType, typename EventType>
	auto DispatchEventHandlerFunctor(const EventType &event, EventHandlerType&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandlerType, EventType>::value>::type
	{
		eventHandler(event);
	}
	
	/*
	 * Templated function to do nothing when trying to dispatch an event of type EventType to an invalid event handler functor of type EventHandlerType.
	 */
	template <typename EventHandlerType, typename EventType>
	auto DispatchEventHandlerFunctor(const EventType &, EventHandlerType&&) -> typename std::enable_if<!IsEventHandlerFunctor<EventHandlerType, EventType>::value>::type
	{
		// no-op
	}
	
	/*
	 * Templated function to dynamically dispatch an event of type EventType to an event handler object of type EventHandlerType.
	 *
	 * This will be only called if 'eventHandler.HandleEvent(event)' can be called
	 */
	template <typename EventHandlerType, typename EventType>
	auto DispatchEventHandlerObject(const EventType &event, EventHandlerType&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandlerType, EventType>::value>::type
	{
		eventHandler.HandleEvent(event);
	}
	
	
	/*
	 * Templated function to do nothing when trying to dispatch an event of type EventType to an invalid event handler object of type EventHandlerType.
	 */
	template <typename EventHandlerType, typename EventType>
	auto DispatchEventHandlerObject(const EventType &, EventHandlerType&&) -> typename std::enable_if<!IsEventHandlerObject<EventHandlerType, EventType>::value>::type
	{
		// no-op
	}

	/*
	 * Templated class to dispatch an event to a given event handler:
	 *
	 * ValidEventHandler is a boolean to detect if the event was actially valid for any of the event types
	 * EventHandlerType is the type of the event handler
	 * EvenTypes is a tuple containing a list of valid event types
	 *
	 * Basically, this class would be roughly the equivalent of the following pseudocode:
	 *
	 * DispatchEvent(SDL_Event event, EventHandlerType eventHandler, EventTypes eventTypes) {
	 *     auto validEventHandler = false;
	 *
	 *     for (auto eventType : eventTypes) {
	 *         validEventHandler |= IsValidEventHandler(EventHandler, eventType);
	 *         if (ShouldHandleEvent(event)) {
	 *             DispatchEventToFunctor(event, eventHandler);
	 *             DispatchEventToObject(event, eventHandler);
	 *         }
	 *     }
	 *
	 *     if (!validEventHandler) throw;
	 * }
	 */
	template <bool ValidEventHandler, typename EventHandlerType, typename... EventTypes>
	struct EventDispatcher;
	
	/*
	 * Instatiation of the class to dispatch an event to a given event handler, expansion to a given type:
	 *
	 * The head of the tuple is "peeled" and used to dispatch the event to the event handler.
	 * The tail then is passed to another expansion of EventDispatcher along with the calculated value of IsEventHandler
	 *
	 */
	template <bool ValidEventHandler, typename EventHandlerType, typename EventType, typename... EventTypes>
	struct EventDispatcher<ValidEventHandler, EventHandlerType, std::tuple<EventType, EventTypes...>> {
		static constexpr bool IsValidEventHandler = ValidEventHandler || IsEventHandler<EventHandlerType, EventType>::value;
		
		using Filter = EventTypeFilter<EventType>;
		
		static void DispatchEvent(const SDL_Event &event, EventHandlerType&& eventHandler) {
			if (Filter::ShouldHandleEvent(event)) {
				DispatchEventHandlerFunctor(Filter::GetEventByType(event), std::forward<EventHandlerType>(eventHandler));
				DispatchEventHandlerObject(Filter::GetEventByType(event), std::forward<EventHandlerType>(eventHandler));
				
			}
			
			EventDispatcher<IsValidEventHandler, EventHandlerType, std::tuple<EventTypes...>>::DispatchEvent(event, std::forward<EventHandlerType>(eventHandler));
		}
	};
	
	/*
	 * Instantiation of the class to dispatch an event to a given event handler, final expansion:
	 *
	 * The tuple of valid event types is empty and the value of the ValidEventHandler boolean
	 * is placed in the IsValidEventHandler variable, finally when an event gets dispatched
	 * an static_assert happens to verify if the event handler actually handled any events.
	 */
	template <bool ValidEventHandler, typename EventHandlerType>
	struct EventDispatcher<ValidEventHandler, EventHandlerType, std::tuple<>> {
		static constexpr auto IsValidEventHandler = ValidEventHandler;
		
		static void DispatchEvent(const SDL_Event &, EventHandlerType&&) {
			static_assert(IsValidEventHandler, "One of the given event handlers is not a valid one");
		}
	};

	/*
	 * Templated class expand a list of event handlers so they can be dispatched.
	 */
	template <typename... EventHandlerTypes>
	void DispatchEvent(const SDL_Event &, EventHandlerTypes&&...);

	/*
	 * Instantiation of the class to expand a list of event handlers so they can be dispatched.
	 *
	 * This "peels" the first event handler from the arguments, dispatchs it and then expands the tail of the list.
	 */
	template <typename EventHandlerType, typename... EventHandlerTypes>
	void DispatchEvent(const SDL_Event &event, EventHandlerType&& eventHandler, EventHandlerTypes&&... eventHandlers) {
		EventDispatcher<false, EventHandlerType, ValidEventTypes>::DispatchEvent(event, std::forward<EventHandlerType>(eventHandler));
		DispatchEvent(event, eventHandlers...);
	}

	/*
	 * Instantiation of the class to expand a list of event handlers, when the list is empty.
	 */
	template <>
	void DispatchEvent(const SDL_Event &) {
		// no-op
	}
}
}

#endif
