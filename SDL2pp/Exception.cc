/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2013-2016 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL.h>

#include <SDL2pp/Exception.hh>

namespace SDL2pp {

std::string Exception::make_what(const char* function, const char* sdl_error) {
	std::string tmp(function);
	tmp += " failed: ";
	tmp += sdl_error;
	return tmp;
}

Exception::Exception(const char* function)
	: std::runtime_error(make_what(function, SDL_GetError())),
	  sdl_function_(function),
	  sdl_error_(SDL_GetError()) {
}

Exception::~Exception() noexcept {
}

std::string Exception::GetSDLFunction() const {
	return sdl_function_;
}

std::string Exception::GetSDLError() const {
	return sdl_error_;
}

} // namespace SDL2pp
