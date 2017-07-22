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

#include <SDL_events.h>

#include <SDL2pp/Export.hh>

namespace SDL2pp {
	namespace Event {
		////////////////////////////////////////////////////////////
		/// \brief Polls a single event
		///
		/// This function tries to poll a single event from the event
		/// queue using SDL_PollEvent(). If an event was polled it
		/// returns true, if not it returns false.
		///
		/// \ingroup events
		///
		/// \headerfile SDL2pp/EventPolling.hh
		///
		/// \returns True if an event was polled, false otherwise
		///
		/// \see https://wiki.libsdl.org/SDL_PollEvent
		///
		////////////////////////////////////////////////////////////
		SDL2PP_EXPORT bool PollEvent();
		
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
		/// \ingroup events
		///
		/// \headerfile SDL2pp/EventPolling.hh
		///
		/// \param[in] eventHandler Object that can be used as eventHandler(event)
		///                         where event is an instance of SDL_Event
		///
		/// \returns True if an event was polled, false otherwise
		///
		/// \see https://wiki.libsdl.org/SDL_Event
		/// \see https://wiki.libsdl.org/SDL_PollEvent
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		bool PollEvent(T&& eventHandler) {
			SDL_Event event;
			if (!SDL_PollEvent(&event)) {
				return false;
			}
			
			eventHandler(event);
			
			return true;
		}
		
		////////////////////////////////////////////////////////////
		/// \brief Polls all the events from the event queue
		///
		/// This function calls SDL_PollEvent() until the event queue is empty.
		/// Returns the amount of events that were polled from the queue.
		///
		/// \ingroup events
		///
		/// \headerfile SDL2pp/EventPolling.hh
		///
		/// \returns The amount of polled events (can be zero)
		///
		/// \see https://wiki.libsdl.org/SDL_PollEvent
		///
		////////////////////////////////////////////////////////////
		SDL2PP_EXPORT int PollAllEvents();
		
		////////////////////////////////////////////////////////////
		/// \brief Polls and handles all the events from the event queue
		///
		/// This function calls SDL_PollEvent() until the event queue is empty.
		/// Then for each event that was polled the event handler is called
		/// using the polled event as an argument. This function returns the
		/// amount of events that were polled.
		///
		/// \ingroup events
		///
		/// \headerfile SDL2pp/EventPolling.hh
		///
		/// \param[in] eventHandler Object that can be used as eventHandler(event)
		///                         where event is an instance of SDL_Event
		///
		/// \returns The amount of polled events (can be zero)
		///
		/// \see https://wiki.libsdl.org/SDL_Event
		/// \see https://wiki.libsdl.org/SDL_PollEvent
		///
		////////////////////////////////////////////////////////////
		template <typename T>
		int PollAllEvents(T&& eventHandler) {
			int result;
			for (result = 0; PollEvent(eventHandler); result++);
			return result;
		}
	}
}

#endif
