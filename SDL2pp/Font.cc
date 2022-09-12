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

#include <cassert>
#include <vector>

#include <SDL_ttf.h>

#include <SDL2pp/Font.hh>
#include <SDL2pp/RWops.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Font::Font(TTF_Font* font) : font_(font) {
	assert(font);
}

Font::Font(const std::string& file, int ptsize, long index) {
	if ((font_ = TTF_OpenFontIndex(file.c_str(), ptsize, index)) == nullptr)
		throw Exception("TTF_OpenFontIndex");
}

Font::Font(RWops& rwops, int ptsize, long index) {
	if ((font_ = TTF_OpenFontIndexRW(rwops.Get(), 0, ptsize, index)) == nullptr)
		throw Exception("TTF_OpenFontIndexRW");
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

int Font::GetStyle() const {
	return TTF_GetFontStyle(font_);
}

Font& Font::SetStyle(int style) {
	TTF_SetFontStyle(font_, style);
	return *this;
}

int Font::GetOutline() const {
	return TTF_GetFontOutline(font_);
}

Font& Font::SetOutline(int outline) {
	TTF_SetFontOutline(font_, outline);
	return *this;
}

int Font::GetHinting() const {
	return TTF_GetFontHinting(font_);
}

Font& Font::SetHinting(int hinting) {
	TTF_SetFontHinting(font_, hinting);
	return *this;
}

bool Font::GetKerning() const {
	return TTF_GetFontKerning(font_) > 0;
}

Font& Font::SetKerning(bool allowed) {
	TTF_SetFontKerning(font_, allowed);
	return *this;
}

int Font::GetHeight() const {
	return TTF_FontHeight(font_);
}

int Font::GetAscent() const {
	return TTF_FontAscent(font_);
}

int Font::GetDescent() const {
	return TTF_FontDescent(font_);
}

int Font::GetLineSkip() const {
	return TTF_FontLineSkip(font_);
}

long Font::GetNumFaces() const {
	return TTF_FontFaces(font_);
}

bool Font::IsFixedWidth() const {
	return TTF_FontFaceIsFixedWidth(font_) > 0;
}

Optional<std::string> Font::GetFamilyName() const {
	const char* str = TTF_FontFaceFamilyName(font_);
	if (str == nullptr)
		return NullOpt;
	return std::string(str);
}

Optional<std::string> Font::GetStyleName() const {
	const char* str = TTF_FontFaceStyleName(font_);
	if (str == nullptr)
		return NullOpt;
	return std::string(str);
}

int Font::IsGlyphProvided(Uint16 ch) const {
	return TTF_GlyphIsProvided(font_, ch);
}

void Font::GetGlyphMetrics(Uint16 ch, int& minx, int& maxx, int& miny, int& maxy, int& advance) const {
	if (TTF_GlyphMetrics(font_, ch, &minx, &maxx, &miny, &maxy, &advance) != 0)
		throw Exception("TTF_GlyphMetrics");
}

Rect Font::GetGlyphRect(Uint16 ch) const {
	int minx, maxx, miny, maxy;
	if (TTF_GlyphMetrics(font_, ch, &minx, &maxx, &miny, &maxy, nullptr) != 0)
		throw Exception("TTF_GlyphMetrics");
	return Rect(minx, miny, maxx - minx, maxy - miny);
}

int Font::GetGlyphAdvance(Uint16 ch) const {
	int advance;
	if (TTF_GlyphMetrics(font_, ch, nullptr, nullptr, nullptr, nullptr, &advance) != 0)
		throw Exception("TTF_GlyphMetrics");
	return advance;
}

Point Font::GetSizeText(const std::string& text) const {
	int w, h;
	if (TTF_SizeText(font_, text.c_str(), &w, &h) != 0)
		throw Exception("TTF_SizeText");
	return Point(w, h);
}

Point Font::GetSizeUTF8(const std::string& text) const {
	int w, h;
	if (TTF_SizeUTF8(font_, text.c_str(), &w, &h) != 0)
		throw Exception("TTF_SizeUTF8");
	return Point(w, h);
}

Point Font::GetSizeUNICODE(const Uint16* text) const {
	int w, h;
	if (TTF_SizeUNICODE(font_, text, &w, &h) != 0)
		throw Exception("TTF_SizeUNICODE");
	return Point(w, h);
}

Point Font::GetSizeUNICODE(const std::u16string& text) const {
	std::vector<Uint16> uint16_text(text.length() + 1);
	std::copy(text.begin(), text.end(), uint16_text.begin());
	return GetSizeUNICODE(uint16_text.data());
}

Surface Font::RenderText_Solid(const std::string& text, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderText_Solid");
	return Surface(surface);
}

Surface Font::RenderUTF8_Solid(const std::string& text, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderUTF8_Solid(font_, text.c_str(), fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderUTF8_Solid");
	return Surface(surface);
}

Surface Font::RenderUNICODE_Solid(const Uint16* text, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderUNICODE_Solid(font_, text, fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderUNICODE_Solid");
	return Surface(surface);
}

Surface Font::RenderUNICODE_Solid(const std::u16string& text, SDL_Color fg) {
	std::vector<Uint16> uint16_text(text.length() + 1);
	std::copy(text.begin(), text.end(), uint16_text.begin());
	return Font::RenderUNICODE_Solid(uint16_text.data(), fg);
}

Surface Font::RenderGlyph_Solid(Uint16 ch, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderGlyph_Solid(font_, ch, fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderGlyph_Solid");
	return Surface(surface);
}

Surface Font::RenderText_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg) {
	SDL_Surface* surface = TTF_RenderText_Shaded(font_, text.c_str(), fg, bg);
	if (surface == nullptr)
		throw Exception("TTF_RenderText_Shaded");
	return Surface(surface);
}

Surface Font::RenderUTF8_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg) {
	SDL_Surface* surface = TTF_RenderUTF8_Shaded(font_, text.c_str(), fg, bg);
	if (surface == nullptr)
		throw Exception("TTF_RenderUTF8_Shaded");
	return Surface(surface);
}

Surface Font::RenderUNICODE_Shaded(const Uint16* text, SDL_Color fg, SDL_Color bg) {
	SDL_Surface* surface = TTF_RenderUNICODE_Shaded(font_, text, fg, bg);
	if (surface == nullptr)
		throw Exception("TTF_RenderUNICODE_Shaded");
	return Surface(surface);
}

Surface Font::RenderUNICODE_Shaded(const std::u16string& text, SDL_Color fg, SDL_Color bg) {
	std::vector<Uint16> uint16_text(text.length() + 1);
	std::copy(text.begin(), text.end(), uint16_text.begin());
	return Font::RenderUNICODE_Shaded(uint16_text.data(), fg, bg);
}

Surface Font::RenderGlyph_Shaded(Uint16 ch, SDL_Color fg, SDL_Color bg) {
	SDL_Surface* surface = TTF_RenderGlyph_Shaded(font_, ch, fg, bg);
	if (surface == nullptr)
		throw Exception("TTF_RenderGlyph_Shaded");
	return Surface(surface);
}

Surface Font::RenderText_Blended(const std::string& text, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderText_Blended(font_, text.c_str(), fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderText_Blended");
	return Surface(surface);
}

Surface Font::RenderUTF8_Blended(const std::string& text, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font_, text.c_str(), fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderUTF8_Blended");
	return Surface(surface);
}

Surface Font::RenderUNICODE_Blended(const Uint16* text, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderUNICODE_Blended(font_, text, fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderUNICODE_Blended");
	return Surface(surface);
}

Surface Font::RenderUNICODE_Blended(const std::u16string& text, SDL_Color fg) {
	std::vector<Uint16> uint16_text(text.length() + 1);
	std::copy(text.begin(), text.end(), uint16_text.begin());
	return Font::RenderUNICODE_Blended(uint16_text.data(), fg);
}

Surface Font::RenderGlyph_Blended(Uint16 ch, SDL_Color fg) {
	SDL_Surface* surface = TTF_RenderGlyph_Blended(font_, ch, fg);
	if (surface == nullptr)
		throw Exception("TTF_RenderGlyph_Blended");
	return Surface(surface);
}

}
