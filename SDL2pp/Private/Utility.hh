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

#ifndef SDL2PP_PRIVATE_UTILITY_HH
#define SDL2PP_PRIVATE_UTILITY_HH

#if __cplusplus > 201703L
// No need to include utility, until C++17 there
// is no definition for std::disjuntion before
#include <utility>
#endif

#include <tuple>
#include <type_traits>

namespace SDL2pp {
/*
 * This is code not to be used directly by users of SDL2pp.
 */
namespace Private {
/*
 * Templated class to perform an "OR" operation on any amount of types.
 *
 * Usage is as follows:
 *     template <typename T,
 *               typename = typename Or<HasFeatureOne<T>, HasFeatureTwo<T>>
 *     void UseFeatureOneOrFeatureTwo(T t) {
 *         // The code will be only compiled if either
 *         // HasFeatureOne<T> or HasFeatureTwo<T> are type_true
 *     }
 */
#if __cplusplus >= 201703L
	// Use the standard definitions if they are available
	template <typename T, typename... Tx>
	using Or = typename std::disjunction<T, Tx...>::type;
#else
	template <typename...>
	struct OrOperation : std::false_type { };
	
	template <typename T>
	struct OrOperation<T> : T { };
	
	template <typename T, typename... Tx>
	struct OrOperation<T, Tx...> : std::conditional<bool(T::value), T, OrOperation<Tx...>> { };
	
	template <typename T, typename... Tx>
	using Or = typename OrOperation<T, Tx...>::type;
#endif

/*
 * Templated class to perform an "AND" operation on any amount of types.
 *
 * Usage is as follows:
 *     template <typename T,
 *               typename = typename And<HasFeatureOne<T>, HasFeatureTwo<T>>
 *     void UseFeatureOneAndFeatureTwo(T t) {
 *         // The code will be only compiled if both
 *         // HasFeatureOne<T> and HasFeatureTwo<T> are type_true
 *     }
 */
#if __cplusplus >= 201703L
	// Use the standard definitions if they are available
	template <typename T, typename... Tx>
	using And = typename std::conjunction<T, Tx...>::type;
#else
	template <typename...>
	struct AndOperation : std::true_type { };
	
	template <typename T>
	struct AndOperation<T> : T { };
	
	template <typename T, typename... Tx>
	struct AndOperation<T, Tx...> : std::conditional<bool(T::value), AndOperation<Tx...>, T> { };
	
	template <typename T, typename... Tx>
	using And = typename AndOperation<T, Tx...>::type;
#endif

/*
 * Templated class to an specific type in a tuple, returns std::true_type if the
 * tuple contains T, std::false_type otherwise.
 */
template <typename T, typename Tuple>
struct TupleHasTypeOperation;

template <typename T>
struct TupleHasTypeOperation<T, std::tuple<>> : std::false_type { };

template <typename T, typename U, typename... Tx>
struct TupleHasTypeOperation<T, std::tuple<U, Tx...>> : TupleHasTypeOperation<T, std::tuple<Tx...>> { };

template <typename T, typename... Tx>
struct TupleHasTypeOperation<T, std::tuple<T, Tx...>> : std::true_type { };

template <typename T, typename... Tx>
using TupleHasType = typename TupleHasTypeOperation<T, Tx...>::type;
}
}

#endif
