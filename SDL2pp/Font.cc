/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2014 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2/SDL_ttf.h>

#include <SDL2pp/Font.hh>
#include <SDL2pp/RWops.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Font::Font(const std::string& file, int ptsize, long index) {
	if ((font_ = TTF_OpenFontIndex(file.c_str(), ptsize, index)) == nullptr)
		throw Exception("TTF_OpenFontIndex failed");
}

Font::Font(RWops& rwops, int ptsize, long index) {
	if ((font_ = TTF_OpenFontIndexRW(rwops.Get(), 0, ptsize, index)) == nullptr)
		throw Exception("TTF_OpenFontIndexRW failed");
}

Font::~Font() {
	if (font_ != nullptr)
		TTF_CloseFont(font_);
}

Font::Font(Font&& other) noexcept : font_(other.font_) {
	other.font_ = nullptr;
}

Font& Font::operator=(Font&& other) noexcept {
	if (&other == this)
		return *this;
	if (font_ != nullptr)
		TTF_CloseFont(font_);
	font_ = other.font_;
	other.font_ = nullptr;
	return *this;
}

TTF_Font* Font::Get() const {
	return font_;
}

Surface Font::RenderText_Solid(const std::string& text, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderText_Solid failed");
	return Surface(surface);
}

Surface Font::RenderText_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg) {
	SDL_Surface* surface = TTF_RenderText_Shaded(font_, text.c_str(), fg, bg);
	if (surface == nullptr)
		throw Exception("TTF_RenderText_Shaded failed");
	return Surface(surface);
}

Surface Font::RenderText_Blended(const std::string& text, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderText_Blended(font_, text.c_str(), fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderText_Blended failed");
	return Surface(surface);
}

}
