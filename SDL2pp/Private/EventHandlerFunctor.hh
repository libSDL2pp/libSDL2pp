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

#ifndef SDL2PP_PRIVATE_EVENTHANDLERFUNCTOR_HH
#define SDL2PP_PRIVATE_EVENTHANDLERFUNCTOR_HH

#include <functional>
#include <type_traits>

namespace SDL2pp {
/*
 * This is code not to be used directly by users of SDL2pp.
 */
namespace Private {
	/*
	 * Helper alias to help identify a functor object with the correct signature
	 * to be used as an event handler.
	 */
	template <typename EventType>
	using EventHandlerFunctorSignature = std::function<void(const EventType &)>;

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
		std::is_convertible<EventHandlerType, EventHandlerFunctorSignature<EventType>>
	> : std::true_type { };
}
}

#endif
