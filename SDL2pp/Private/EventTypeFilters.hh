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

#ifndef SDL2PP_PRIVATE_EVENTHANDLERBYTYPE_HH
#define SDL2PP_PRIVATE_EVENTHANDLERBYTYPE_HH

#include <SDL2pp/Private/EventHandler.hh>

#include <SDL_version.h>

namespace SDL2pp {
/*
 * This is code not to be used directly by users of SDL2pp.
 */
namespace Private {
	/*
	 * Templated struct that is used to:
	 *     - Verify an event is of the given type
	 *     - Get the specific event for that given type
	 */
	template <typename EventType>
	struct EventTypeFilter {
		// Should return true if the given event is of the type EventType
		static bool ShouldHandleEvent(const SDL_Event &);
		
		// Should return the member of SDL_Event that is of the given EventType
		static const EventType &GetEventByType(const SDL_Event &event);
	};
	
	// SDL_Event is defined without a macro because the arguments are not used
	// this shutdowns "unnused variables" warnings on some compilers
	template <>
	struct EventTypeFilter<SDL_Event> {
		static bool ShouldHandleEvent(const SDL_Event &) {
			return true;
		}
		
		static const SDL_Event &GetEventByType(const SDL_Event &event) {
			return event;
		}
	};
	
// I use a macro here to make things less verbose
#define SDL2PP_DEFINE_EVENT_MAPPING(eventType, condition, eventObject) template<>\
	struct EventTypeFilter<eventType> {\
		static bool ShouldHandleEvent(const SDL_Event &event) {\
			return condition;\
		}\
		\
		static const eventType &GetEventByType(const SDL_Event &event) {\
			return eventObject;\
		}\
	}
	
#if SDL_VERSION_ATLEAST(2, 0, 4)
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_AudioDeviceEvent, event.type == SDL_AUDIODEVICEADDED || event.type == SDL_AUDIODEVICEREMOVED, event.adevice);
#endif
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_ControllerAxisEvent, event.type == SDL_CONTROLLERAXISMOTION, event.caxis);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_ControllerButtonEvent, event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP, event.cbutton);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_ControllerDeviceEvent, event.type == SDL_CONTROLLERDEVICEADDED || event.type == SDL_CONTROLLERDEVICEREMOVED || event.type == SDL_CONTROLLERDEVICEREMAPPED, event.cdevice);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_DollarGestureEvent, event.type == SDL_DOLLARGESTURE || event.type == SDL_DOLLARRECORD, event.dgesture);
#if SDL_VERSION_ATLEAST(2, 0, 5)
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_DropEvent, event.type == SDL_DROPFILE || event.type == SDL_DROPTEXT || event.type == SDL_DROPBEGIN || event.type == SDL_DROPCOMPLETE, event.drop);
#else
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_DropEvent, event.type == SDL_DROPFILE || event.type == SDL_DROPTEXT, event.drop);
#endif
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_JoyAxisEvent, event.type == SDL_JOYAXISMOTION, event.jaxis);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_JoyBallEvent, event.type == SDL_JOYBALLMOTION, event.jball);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_JoyButtonEvent, event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP, event.jbutton);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_JoyDeviceEvent, event.type == SDL_JOYDEVICEADDED || event.type == SDL_JOYDEVICEREMOVED, event.jdevice);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_JoyHatEvent, event.type == SDL_JOYHATMOTION, event.jhat);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_KeyboardEvent, event.type == SDL_KEYDOWN || event.type == SDL_KEYUP, event.key);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_MouseButtonEvent, event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP, event.button);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_MouseMotionEvent, event.type == SDL_MOUSEMOTION, event.motion);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_MouseWheelEvent, event.type == SDL_MOUSEWHEEL, event.wheel);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_MultiGestureEvent, event.type == SDL_MULTIGESTURE, event.mgesture);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_QuitEvent, event.type == SDL_QUIT, event.quit);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_SysWMEvent, event.type == SDL_SYSWMEVENT, event.syswm);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_TextEditingEvent, event.type == SDL_TEXTEDITING, event.edit);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_TextInputEvent, event.type == SDL_TEXTINPUT, event.text);
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_TouchFingerEvent, event.type == SDL_FINGERMOTION || event.type == SDL_FINGERDOWN || event.type == SDL_FINGERUP, event.tfinger);
	//SDL2PP_DEFINE_EVENT_MAPPING(SDL_UserEvent, event.type == SDL_USEREVENT, event.user); <- This won't work
	SDL2PP_DEFINE_EVENT_MAPPING(SDL_WindowEvent, event.type == SDL_WINDOWEVENT, event.window);
	
#undef SDL2PP_DEFINE_EVENT_MAPPING
}
}

#endif
