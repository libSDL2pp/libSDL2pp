/*
  libSDL2pp - C++ wrapper for libSDL2
  Copyright (C) 2013 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2/SDL_rect.h>

#include <SDL2pp/Rect.hh>

namespace SDL2pp {

Rect::Rect() {
}

Rect::~Rect() {
}

Rect::Rect(int x, int y, int w, int h) : rect_(new SDL_Rect) {
	rect_->x = x;
	rect_->y = y;
	rect_->w = w;
	rect_->h = h;
}

Rect Rect::Null() {
	return Rect();
}

Rect::Rect(const Rect& other) {
	if (!other.rect_) {
		rect_.reset(nullptr);
	} else if (rect_ != other.rect_) {
		rect_.reset(new SDL_Rect);
		rect_->x = other.rect_->x;
		rect_->y = other.rect_->y;
		rect_->w = other.rect_->w;
		rect_->h = other.rect_->h;
	}
}

Rect::Rect(Rect&&) noexcept = default;

Rect& Rect::operator=(const Rect& other) {
	if (!other.rect_) {
		rect_.reset(nullptr);
	} else if (rect_ != other.rect_) {
		rect_.reset(new SDL_Rect);
		rect_->x = other.rect_->x;
		rect_->y = other.rect_->y;
		rect_->w = other.rect_->w;
		rect_->h = other.rect_->h;
	}
	return *this;
}

Rect& Rect::operator=(Rect&&) noexcept = default;

bool Rect::operator==(const Rect& other) const {
	if (!rect_ || !other.rect_)
		return rect_ == other.rect_; // true only if both null
	return rect_->x == other.rect_->x && rect_->y == other.rect_->y &&
	       rect_->w == other.rect_->w && rect_->h == other.rect_->h;
}

bool Rect::operator!=(const Rect& other) const {
	return !(*this == other);
}

SDL_Rect* Rect::Get() {
	return rect_.get();
}

const SDL_Rect* Rect::Get() const {
	return rect_.get();
}

Rect Rect::FromCenter(int cx, int cy, int w, int h) {
	return Rect(cx - w/2, cy - h/2, cx + w - w/2, cy + h - h/2);
}

bool Rect::IsNull() const {
	return rect_ == nullptr;
}

int Rect::GetX() const {
	assert(!IsNull());
	return rect_->x;
}

void Rect::SetX(int x) {
	assert(!IsNull());
	rect_->x = x;
}

int Rect::GetY() const {
	assert(!IsNull());
	return rect_->y;
}

void Rect::SetY(int y) {
	assert(!IsNull());
	rect_->y = y;
}

int Rect::GetW() const {
	assert(!IsNull());
	return rect_->w;
}

void Rect::SetW(int w) {
	assert(!IsNull());
	rect_->w = w;
}

int Rect::GetH() const {
	assert(!IsNull());
	return rect_->h;
}

void Rect::SetH(int h) {
	assert(!IsNull());
	rect_->h = h;
}

int Rect::GetX2() const {
	assert(!IsNull());
	return rect_->x + rect_->w - 1;
}

void Rect::SetX2(int x2) {
	assert(!IsNull());
	rect_->w = x2 - rect_->x + 1;
}

int Rect::GetY2() const {
	assert(!IsNull());
	return rect_->y + rect_->h - 1;
}

void Rect::SetY2(int y2) {
	assert(!IsNull());
	rect_->h = y2 - rect_->y + 1;
}

}
