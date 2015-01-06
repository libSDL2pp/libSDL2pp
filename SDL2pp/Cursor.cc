/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2pp/Cursor.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Cursor::Cursor(SDL_Cursor* cursor) : cursor_(cursor) {
}

Cursor Cursor::CreateSystemCursor(SDL_SystemCursor id) {
	SDL_Cursor* cursor = SDL_CreateSystemCursor(id);
	if (cursor == nullptr)
		throw Exception("SDL_CreateSystemCursor failed");
	return Cursor(cursor);
}

Cursor Cursor::CreateCursor(const Uint8* data, const Uint8* mask, int w, int h, int hot_x, int hot_y) {
	SDL_Cursor* cursor = SDL_CreateCursor(data, mask, w, h, hot_x, hot_y);
	if (cursor == nullptr)
		throw Exception("SDL_CreateCursor failed");
	return Cursor(cursor);
}

Cursor Cursor::CreateColorCursor(const Surface& surface, int hot_x, int hot_y) {
	SDL_Cursor* cursor = SDL_CreateColorCursor(surface.Get(), hot_x, hot_y);
	if (cursor == nullptr)
		throw Exception("SDL_CreateColorCursor failed");
	return Cursor(cursor);
}

Cursor::~Cursor() {
	if (cursor_ != nullptr)
		SDL_FreeCursor(cursor_);
}

Cursor::Cursor(Cursor&& other) noexcept : cursor_(other.cursor_) {
	other.cursor_ = nullptr;
}

Cursor& Cursor::operator=(Cursor&& other) noexcept {
	if (&other == this)
		return *this;
	if (cursor_ != nullptr)
		SDL_FreeCursor(cursor_);
	cursor_ = other.cursor_;
	other.cursor_ = nullptr;
	return *this;
}

SDL_Cursor* Cursor::Get() const {
	return cursor_;
}

void Cursor::Set() {
	SDL_SetCursor(cursor_);
}

}
