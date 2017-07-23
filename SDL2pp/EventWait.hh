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

#ifndef SDL2PP_EVENTWAIT_HH
#define SDL2PP_EVENTWAIT_HH

#include <SDL_events.h>

#include <SDL2pp/Optional.hh>

namespace SDL2pp {
	namespace Event {
		////////////////////////////////////////////////////////////
		/// \brief Waits indefinitely for an event
		///
		/// This function waits for the next available event. This
		/// function WILL STOP the program execution until an event
		/// is available.
		///
		/// \ingroup events
		///
		/// \headerfile SDL2pp/EventWait.hh
		///
		/// \returns The event that was available
		///
		/// \throws SDL2pp::Exception
		///
		/// \see https://wiki.libsdl.org/SDL_WaitEvent
		///
		////////////////////////////////////////////////////////////
		SDL_Event WaitEvent();
		
		////////////////////////////////////////////////////////////
		/// \brief Waits a given amount of time for an event
		///
		/// This function waits for the next available event for
		/// specified amount of time. This function WILL STOP the
		/// program execution until the given amount of time runs out
		/// or an event is available.
		///
		/// \ingroup events
		///
		/// \headerfile SDL2pp/EventWait.hh
		///
		/// \param[in] timeout The amount of time to wait for an event
		///
		/// \returns The last event that was available
		///
		/// \throws SDL2pp::Exception
		///
		/// \see https://wiki.libsdl.org/SDL_WaitEvent
		///
		////////////////////////////////////////////////////////////
		Optional<SDL_Event> WaitEvent(int timeout);
	}
}

#endif
