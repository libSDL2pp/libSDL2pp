/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2014-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_OPTIONAL_HH
#define SDL2PP_OPTIONAL_HH

#include <SDL2pp/Config.hh>

////////////////////////////////////////////////////////////
/// \class SDL2pp::Optional
///
/// \brief %Optional value container
///
/// \ingroup general
///
/// \headerfile SDL2pp/Optional.hh
///
/// This class contains an optional value, i.e. a value that
/// semantically may not be present.
///
/// \see http://en.cppreference.com/w/cpp/experimental/optional
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \class SDL2pp::BadOptionalAccess
///
/// \brief %Exception thrown on accessing a SDL2pp::Optional object with uninitialized state
///
/// \ingroup general
///
/// \headerfile SDL2pp/Optional.hh
///
/// \see http://en.cppreference.com/w/cpp/utility/bad_optional_access
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \var SDL2pp::NullOpt
///
/// \brief Null value for SDL2pp::Optional
///
/// \ingroup general
///
/// \headerfile SDL2pp/Optional.hh
///
/// \see http://en.cppreference.com/w/cpp/experimental/optional
///
////////////////////////////////////////////////////////////

#include <optional>

namespace SDL2pp {

template<typename T>
using Optional = std::optional<T>;

using BadOptionalAccess = std::bad_optional_access;

constexpr std::nullopt_t NullOpt = std::nullopt;

}

#endif
