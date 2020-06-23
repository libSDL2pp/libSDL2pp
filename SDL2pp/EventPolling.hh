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

#ifndef SDL2PP_EVENTPOLLING_HH
#define SDL2PP_EVENTPOLLING_HH

#include <SDL2pp/Private/EventDispatching.hh>

namespace SDL2pp {
namespace Event {
	////////////////////////////////////////////////////////////
	/// \brief Polls and handles a single event
	///
	/// This function tries to poll a single event from the event
	/// queue using SDL_PollEvent(). If an event was polled the
	/// event handler is called using the retrieved SDL_Event as an
	/// argument then this function returns true. If no event was
	/// retrieved the event handler is not called and this function
	/// returns false.
	///
	/// This function accepts the following as event handlers:
	///     - Functors (lambdas, free functions, callable objects)
	///     - Objects (Objects that have a HandleEvent(EventType) function)
	///
	/// \ingroup events
	///
	/// \headerfile SDL2pp/EventPolling.hh
	///
	/// \param[in] eventHandlers A list of event handlers that will handle the event
	///
	/// \returns True if an event was polled, false otherwise
	///
	/// \see https://wiki.libsdl.org/SDL_PollEvent
	/// \see https://wiki.libsdl.org/CategoryEvents#Structures
	///
	////////////////////////////////////////////////////////////
	template <typename... EventHandlers>
	bool PollEvent(EventHandlers&&... eventHandlers) {
		SDL_Event event;
		if (!SDL_PollEvent(&event)) {
			return false;
		}
		
		Private::DispatchEvent(event, eventHandlers...);
		
		return true;
	}
	
	////////////////////////////////////////////////////////////
	/// \brief Polls and handles all the events from the event queue
	///
	/// This function calls SDL_PollEvent() until the event queue is empty.
	/// Then for each event that was polled the event handler is called
	/// using the polled event as an argument. This function returns the
	/// amount of events that were polled.
	///
	/// This function accepts the following as event handlers:
	///     - Functors (lambdas, free functions, callable objects)
	///     - Objects (Objects that have a HandleEvent(EventType) function)
	///
	/// \ingroup events
	///
	/// \headerfile SDL2pp/EventPolling.hh
	///
	/// \param[in] eventHandlers A list of event handlers that will handle the polled event
	///
	/// \returns The amount of polled events (can be zero)
	///
	/// \see https://wiki.libsdl.org/SDL_PollEvent
	/// \see https://wiki.libsdl.org/CategoryEvents#Structures
	///
	////////////////////////////////////////////////////////////
	template <typename... EventHandlers>
	int PollAllEvents(EventHandlers&&... eventHandlers) {
		int result;
		
		for (result = 0; PollEvent(eventHandlers...); result++);
		
		return result;
	}
}
}

#endif
