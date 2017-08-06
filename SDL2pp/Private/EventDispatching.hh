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
#include <SDL_version.h>

namespace SDL2pp {
namespace Private
{
	template <typename EventHandler, typename EventType>
	void DispatchEventToObject(const EventType &event, EventHandler&& eventHandler) {
		eventHandler.HandleEvent(event);
	}

	template <typename EventHandler, typename EventType>
	void DispatchEventToFunctor(const EventType &event, EventHandler&& eventHandler) {
		eventHandler(event);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_Event>::value>::type
	{
		DispatchEventToObject(event, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_Event>::value>::type
	{
		DispatchEventToFunctor(event, eventHandler);
	}
	
#if SDL_VERSION_ATLEAST(2, 0, 5)
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_AudioDeviceEvent>::value>::type
	{
		if (event.type == SDL_AUDIODEVICEADDED || event.type == SDL_AUDIODEVICEREMOVED)
			DispatchEventToObject(event.type, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_AudioDeviceEvent>::value>::type
	{
		if (event.type == SDL_AUDIODEVICEADDED || event.type == SDL_AUDIODEVICEREMOVED)
			DispatchEventToFunctor(event.type, eventHandler);
	}
#endif
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_ControllerAxisEvent>::value>::type
	{
		if (event.type == SDL_CONTROLLERAXISMOTION)
			DispatchEventToObject(event.caxis, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_ControllerAxisEvent>::value>::type
	{
		if (event.type == SDL_CONTROLLERAXISMOTION)
			DispatchEventToFunctor(event.caxis, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_ControllerButtonEvent>::value>::type
	{
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONDOWN)
			DispatchEventToObject(event.cbutton, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_ControllerButtonEvent>::value>::type
	{
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONDOWN)
			DispatchEventToFunctor(event.cbutton, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_ControllerDeviceEvent>::value>::type
	{
		if (event.type == SDL_CONTROLLERDEVICEADDED || event.type == SDL_CONTROLLERDEVICEREMOVED || event.type == SDL_CONTROLLERDEVICEREMAPPED)
			DispatchEventToObject(event.cdevice, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_ControllerDeviceEvent>::value>::type
	{
		if (event.type == SDL_CONTROLLERDEVICEADDED || event.type == SDL_CONTROLLERDEVICEREMOVED || event.type == SDL_CONTROLLERDEVICEREMAPPED)
			DispatchEventToFunctor(event.cdevice, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_DollarGestureEvent>::value>::type
	{
		if (event.type == SDL_DOLLARGESTURE || event.type == SDL_DOLLARRECORD)
			DispatchEventToObject(event.dgesture, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_DollarGestureEvent>::value>::type
	{
		if (event.type == SDL_DOLLARGESTURE || event.type == SDL_DOLLARRECORD)
			DispatchEventToFunctor(event.dgesture, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_DropEvent>::value>::type
	{
		if (event.type == SDL_DROPFILE || event.type == SDL_DROPTEXT
#if SDL_VERSION_ATLEAST(2, 0, 5)
			|| event.type == SDL_DROPBEGIN || event.type == SDL_DROPCOMPLETE
#endif
		)
			DispatchEventToObject(event.drop, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_DropEvent>::value>::type
	{
		if (event.type == SDL_DROPFILE || event.type == SDL_DROPTEXT
#if SDL_VERSION_ATLEAST(2, 0, 5)
			|| event.type == SDL_DROPBEGIN || event.type == SDL_DROPCOMPLETE
#endif
		)
			DispatchEventToObject(event.drop, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_JoyAxisEvent>::value>::type
	{
		if (event.type == SDL_JOYAXISMOTION)
			DispatchEventToObject(event.jaxis, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_JoyAxisEvent>::value>::type
	{
		if (event.type == SDL_JOYAXISMOTION)
			DispatchEventToFunctor(event.jaxis, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_JoyBallEvent>::value>::type
	{
		if (event.type == SDL_JOYBALLMOTION)
			DispatchEventToObject(event.jball, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_JoyBallEvent>::value>::type
	{
		if (event.type == SDL_JOYBALLMOTION)
			DispatchEventToFunctor(event.jball, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_JoyButtonEvent>::value>::type
	{
		if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP)
			DispatchEventToObject(event.jbutton, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_JoyButtonEvent>::value>::type
	{
		if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP)
			DispatchEventToFunctor(event.jbutton, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_JoyDeviceEvent>::value>::type
	{
		if (event.type == SDL_JOYDEVICEADDED || event.type == SDL_JOYDEVICEREMOVED)
			DispatchEventToObject(event.jdevice, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_JoyDeviceEvent>::value>::type
	{
		if (event.type == SDL_JOYDEVICEADDED || event.type == SDL_JOYDEVICEREMOVED)
			DispatchEventToFunctor(event.jdevice, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_JoyHatEvent>::value>::type
	{
		if (event.type == SDL_JOYHATMOTION)
			DispatchEventToObject(event.jhat, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_JoyHatEvent>::value>::type
	{
		if (event.type == SDL_JOYHATMOTION)
			DispatchEventToFunctor(event.jhat, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_KeyboardEvent>::value>::type
	{
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			DispatchEventToObject(event.key, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_KeyboardEvent>::value>::type
	{
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
			DispatchEventToFunctor(event.key, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_MouseButtonEvent>::value>::type
	{
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			DispatchEventToObject(event.button, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_MouseButtonEvent>::value>::type
	{
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			DispatchEventToFunctor(event.button, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_MouseMotionEvent>::value>::type
	{
		if (event.type == SDL_MOUSEMOTION)
			DispatchEventToObject(event.motion, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_MouseMotionEvent>::value>::type
	{
		if (event.type == SDL_MOUSEMOTION)
			DispatchEventToFunctor(event.motion, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_MouseWheelEvent>::value>::type
	{
		if (event.type == SDL_MOUSEWHEEL)
			DispatchEventToObject(event.wheel, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_MouseWheelEvent>::value>::type
	{
		if (event.type == SDL_MOUSEWHEEL)
			DispatchEventToFunctor(event.wheel, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_MultiGestureEvent>::value>::type
	{
		if (event.type == SDL_MULTIGESTURE)
			DispatchEventToObject(event.mgesture, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_MultiGestureEvent>::value>::type
	{
		if (event.type == SDL_MULTIGESTURE)
			DispatchEventToFunctor(event.mgesture, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_QuitEvent>::value>::type
	{
		if (event.type == SDL_QUIT)
			DispatchEventToObject(event.quit, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_QuitEvent>::value>::type
	{
		if (event.type == SDL_QUIT)
			DispatchEventToFunctor(event.quit, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_SysWMEvent>::value>::type
	{
		if (event.type == SDL_SYSWMEVENT)
			DispatchEventToObject(event.syswm, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_SysWMEvent>::value>::type
	{
		if (event.type == SDL_SYSWMEVENT)
			DispatchEventToFunctor(event.syswm, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_TextEditingEvent>::value>::type
	{
		if (event.type == SDL_TEXTEDITING)
			DispatchEventToObject(event.edit, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_TextEditingEvent>::value>::type
	{
		if (event.type == SDL_TEXTEDITING)
			DispatchEventToFunctor(event.edit, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_TextInputEvent>::value>::type
	{
		if (event.type == SDL_TEXTINPUT)
			DispatchEventToObject(event.text, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_TextInputEvent>::value>::type
	{
		if (event.type == SDL_TEXTINPUT)
			DispatchEventToFunctor(event.text, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_TouchFingerEvent>::value>::type
	{
		if (event.type == SDL_FINGERMOTION || event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP)
			DispatchEventToObject(event.tfinger, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_TouchFingerEvent>::value>::type
	{
		if (event.type == SDL_FINGERMOTION || event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP)
			DispatchEventToFunctor(event.tfinger, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_UserEvent>::value>::type
	{
		if (event.type == SDL_USEREVENT)
			DispatchEventToObject(event.user, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_UserEvent>::value>::type
	{
		if (event.type == SDL_USEREVENT)
			DispatchEventToFunctor(event.user, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerObject<EventHandler, SDL_WindowEvent>::value>::type
	{
		if (event.type == SDL_WINDOWEVENT)
		DispatchEventToObject(event.window, eventHandler);
	}
	
	template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &event, EventHandler&& eventHandler) -> typename std::enable_if<IsEventHandlerFunctor<EventHandler, SDL_WindowEvent>::value>::type
	{
		if (event.type == SDL_WINDOWEVENT)
			DispatchEventToFunctor(event.window, eventHandler);
	}

	// TODO: Find an easy way to make IsEventHandler<EventHandler, ANY_EVENT>
	/*template <typename EventHandler>
	auto DispatchSpecificEvent(const SDL_Event &, EventHandler&&) -> typename std::enable_if<!IsEventHandler<EventHandler, SDL_Event>::value>::type
	{
		static_assert(IsEventHandler<EventHandler, SDL_Event>::value, "Event handler is not a valid functor or object");
	}*/

	template <typename... EventHandlers>
	void DispatchEvent(const SDL_Event &, EventHandlers&&...);
	
	template <typename EventHandler, typename... EventHandlers>
	void DispatchEvent(const SDL_Event &event, EventHandler&& eventHandler, EventHandlers&&... eventHandlers) {
		DispatchSpecificEvent(event, eventHandler);
		DispatchEvent(event, eventHandlers...);
	}
	
	template <>
	void DispatchEvent(const SDL_Event &) {
		// no-op
	}
}
}

#endif
