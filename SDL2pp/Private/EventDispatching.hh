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

#include <SDL2pp/Private/EventHandler.hh>

#include <type_traits>

#include <SDL_events.h>

namespace SDL2pp {
namespace Private
{
	template <typename EventHandler>
	auto DispatchEvent(const SDL_Event &event, EventHandler&& eventHandler) -> std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_Event>::value>
	{
		eventHandler(event);
	}
	
	template <typename EventHandler>
	auto DispatchEvent(const SDL_Event &event, EventHandler&& eventHandler) -> std::enable_if<IsEventHandlerObject<EventHandler, SDL_Event>::value>
	{
		eventHandler.HandleEvent(event);
	}
	
	template <typename EventHandler>
	auto DispatchEvent(const SDL_Event&, EventHandler&&) -> std::enable_if<!IsEventHandler<EventHandler, SDL_Event>::value>
	{
		static_assert(!IsEventHandler<EventHandler, SDL_Event>::value, "One of the given values is not a valid event handler");
	}

	template <typename... EventHandlers>
	void DispatchEvent(const SDL_Event & event, EventHandlers&&... eventHandlers) {
		DispatchEvent(event, eventHandlers...);
	}
	
	template <typename EventHandler, typename... EventHandlers>
	void DispatchEvent(const SDL_Event &event, EventHandler&& eventHandler, EventHandlers&&... eventHandlers) {
		DispatchEvent(event, eventHandler);
		DispatchEvent(event, eventHandlers...);
	}
	
	template <>
	void DispatchEvent(const SDL_Event &) {
		// no-op
	}
}
}

#endif
