/*
  libSDL2pp - C++ wrapper for libSDL2
  Copyright (C) 2014 Rian Hunter <rian@alum.mit.edu>

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

#ifndef SDL2PP_EVENT_HH
#define SDL2PP_EVENT_HH

#include <SDL2pp/Optional.hh>

#include <SDL2/SDL_events.h>

namespace SDL2pp {

class Event {
private:
	SDL_Event event_;

private:
	Event();

public:
	virtual ~Event();

	static Util::Optional<Event> Poll();

	Uint32 GetType() const;
	const SDL_Event & GetEvent() const;
};

}

#endif
