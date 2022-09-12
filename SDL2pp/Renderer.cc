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

#include <vector>
#include <cassert>

#include <SDL.h>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Texture.hh>

namespace SDL2pp {

Renderer::Renderer(SDL_Renderer* renderer) : renderer_(renderer) {
	assert(renderer);
}

Renderer::Renderer(Window& window, int index, Uint32 flags) {
	if ((renderer_ = SDL_CreateRenderer(window.Get(), index, flags)) == nullptr)
		throw Exception("SDL_CreateRenderer");
}

Renderer::~Renderer() {
	if (renderer_ != nullptr)
		SDL_DestroyRenderer(renderer_);
}

Renderer::Renderer(Renderer&& other) noexcept : renderer_(other.renderer_) {
	other.renderer_ = nullptr;
}

Renderer& Renderer::operator=(Renderer&& other) noexcept {
	if (&other == this)
		return *this;
	if (renderer_ != nullptr)
		SDL_DestroyRenderer(renderer_);
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	return *this;
}

SDL_Renderer* Renderer::Get() const {
	return renderer_;
}

Renderer& Renderer::Present() {
	SDL_RenderPresent(renderer_);
	return *this;
}

Renderer& Renderer::Clear() {
	if (SDL_RenderClear(renderer_) != 0)
		throw Exception("SDL_RenderClear");
	return *this;
}

void Renderer::GetInfo(SDL_RendererInfo& info) {
	if (SDL_GetRendererInfo(renderer_, &info) != 0)
		throw Exception("SDL_GetRendererInfo");
}

Renderer& Renderer::Copy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect) {
	if (SDL_RenderCopy(renderer_, texture.Get(), srcrect ? &*srcrect : nullptr, dstrect ? &*dstrect : nullptr) != 0)
		throw Exception("SDL_RenderCopy");
	return *this;
}

Renderer& Renderer::Copy(Texture& texture, const Optional<Rect>& srcrect, const Point& dstpoint) {
	Rect dstrect(
			dstpoint.x,
			dstpoint.y,
			srcrect ? srcrect->w : texture.GetWidth(),
			srcrect ? srcrect->h : texture.GetHeight()
		);
	return Copy(texture, srcrect, dstrect);
}

Renderer& Renderer::Copy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect, double angle, const Optional<Point>& center, int flip) {
	if (SDL_RenderCopyEx(renderer_, texture.Get(), srcrect ? &*srcrect : nullptr, dstrect ? &*dstrect : nullptr, angle, center ? &*center : nullptr, static_cast<SDL_RendererFlip>(flip)) != 0)
		throw Exception("SDL_RenderCopyEx");
	return *this;
}

Renderer& Renderer::Copy(Texture& texture, const Optional<Rect>& srcrect, const Point& dstpoint, double angle, const Optional<Point>& center, int flip) {
	Rect dstrect(
			dstpoint.x,
			dstpoint.y,
			srcrect ? srcrect->w : texture.GetWidth(),
			srcrect ? srcrect->h : texture.GetHeight()
		);
	return Copy(texture, srcrect, dstrect, angle, center, flip);
}

Renderer& Renderer::FillCopy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect, const Point& offset, int flip) {
	// resolve rectangles
	Rect src = srcrect ? *srcrect : Rect(0, 0, texture.GetWidth(), texture.GetHeight());
	Rect dst = dstrect ? *dstrect : Rect(0, 0, GetOutputWidth(), GetOutputHeight());

	// rectangle for single tile
	Rect start_tile(
			offset.x,
			offset.y,
			src.w,
			src.h
		);

	// ensure tile is leftmost and topmost
	if (start_tile.x + start_tile.w <= 0)
		start_tile.x += (-start_tile.x) / start_tile.w * start_tile.w;
	if (start_tile.x > 0)
		start_tile.x -= (start_tile.x + start_tile.w - 1) / start_tile.w * start_tile.w;

	if (start_tile.y + start_tile.h <= 0)
		start_tile.y += (-start_tile.y) / start_tile.h * start_tile.h;
	if (start_tile.y > 0)
		start_tile.y -= (start_tile.y + start_tile.h - 1) / start_tile.h * start_tile.h;

	// paint tile array
	for (int y = start_tile.y; y < dst.h; y += start_tile.h) {
		for (int x = start_tile.x; x < dst.w; x += start_tile.w) {
			Rect tile_src = src;
			Rect tile_dst(x, y, start_tile.w, start_tile.h);

			// clamp with dstrect
			int xunderflow = -x;
			if (xunderflow > 0) {
				tile_src.w -= xunderflow;
				tile_src.x += xunderflow;
				tile_dst.w -= xunderflow;
				tile_dst.x += xunderflow;
			}

			int yunderflow = -y;
			if (yunderflow > 0) {
				tile_src.h -= yunderflow;
				tile_src.y += yunderflow;
				tile_dst.h -= yunderflow;
				tile_dst.y += yunderflow;
			}

			int xoverflow = tile_dst.x + tile_dst.w - dst.w;
			if (xoverflow > 0) {
				tile_src.w -= xoverflow;
				tile_dst.w -= xoverflow;
			}

			int yoverflow = tile_dst.y + tile_dst.h - dst.h;
			if (yoverflow > 0) {
				tile_src.h -= yoverflow;
				tile_dst.h -= yoverflow;
			}

			// make tile_dst absolute
			tile_dst.x += dst.x;
			tile_dst.y += dst.y;

			if (flip != 0) {
				// mirror tile_src inside src to take flipping into account
				if (flip & SDL_FLIP_HORIZONTAL)
					tile_src.x = src.w - tile_src.x - tile_src.w;

				if (flip & SDL_FLIP_VERTICAL)
					tile_src.y = src.h - tile_src.y - tile_src.h;

				Copy(texture, tile_src, tile_dst, 0.0, NullOpt, flip);
			} else {
				Copy(texture, tile_src, tile_dst);
			}
		}
	}
	return *this;
}

Renderer& Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (SDL_SetRenderDrawColor(renderer_, r, g, b, a) != 0)
		throw Exception("SDL_SetRenderDrawColor");
	return *this;
}

Renderer& Renderer::SetDrawColor(const Color& color) {
	return SetDrawColor(color.r, color.g, color.b, color.a);
}

Renderer& Renderer::SetTarget() {
	if (SDL_SetRenderTarget(renderer_, nullptr) != 0)
		throw Exception("SDL_SetRenderTarget");
	return *this;
}

Renderer& Renderer::SetTarget(Texture& texture) {
	if (SDL_SetRenderTarget(renderer_, texture.Get()) != 0)
		throw Exception("SDL_SetRenderTarget");
	return *this;
}

Renderer& Renderer::SetDrawBlendMode(SDL_BlendMode blendMode) {
	if (SDL_SetRenderDrawBlendMode(renderer_, blendMode) != 0)
		throw Exception("SDL_SetRenderDrawBlendMode");
	return *this;
}

Renderer& Renderer::DrawPoint(int x, int y) {
	if (SDL_RenderDrawPoint(renderer_, x, y) != 0)
		throw Exception("SDL_RenderDrawPoint");
	return *this;
}

Renderer& Renderer::DrawPoint(const Point& p) {
	DrawPoint(p.x, p.y);
	return *this;
}

Renderer& Renderer::DrawPoints(const Point* points, int count) {
	std::vector<SDL_Point> sdl_points;
	sdl_points.reserve(static_cast<size_t>(count));
	for (const Point* p = points; p != points + count; ++p)
		sdl_points.emplace_back(*p);

	if (SDL_RenderDrawPoints(renderer_, sdl_points.data(), count) != 0)
		throw Exception("SDL_RenderDrawPoints");

	return *this;
}

Renderer& Renderer::DrawLine(int x1, int y1, int x2, int y2) {
	if (SDL_RenderDrawLine(renderer_, x1, y1, x2, y2) != 0)
		throw Exception("SDL_RenderDrawLine");
	return *this;
}

Renderer& Renderer::DrawLine(const Point& p1, const Point& p2) {
	DrawLine(p1.x, p1.y, p2.x, p2.y);
	return *this;
}

Renderer& Renderer::DrawLines(const Point* points, int count) {
	std::vector<SDL_Point> sdl_points;
	sdl_points.reserve(static_cast<size_t>(count));
	for (const Point* p = points; p != points + count; ++p)
		sdl_points.emplace_back(*p);

	if (SDL_RenderDrawLines(renderer_, sdl_points.data(), count) != 0)
		throw Exception("SDL_RenderDrawLines");

	return *this;
}

Renderer& Renderer::DrawRect(int x1, int y1, int x2, int y2) {
	SDL_Rect rect = {x1, y1, x2 - x1 + 1, y2 - y1 + 1};
	if (SDL_RenderDrawRect(renderer_, &rect) != 0)
		throw Exception("SDL_RenderDrawRect");
	return *this;
}

Renderer& Renderer::DrawRect(const Point& p1, const Point& p2) {
	DrawRect(p1.x, p1.y, p2.x, p2.y);
	return *this;
}

Renderer& Renderer::DrawRect(const Rect& r) {
	if (SDL_RenderDrawRect(renderer_, &r) != 0)
		throw Exception("SDL_RenderDrawRect");
	return *this;
}

Renderer& Renderer::DrawRects(const Rect* rects, int count) {
	std::vector<SDL_Rect> sdl_rects;
	sdl_rects.reserve(static_cast<size_t>(count));
	for (const Rect* r = rects; r != rects + count; ++r)
		sdl_rects.emplace_back(*r);

	if (SDL_RenderDrawRects(renderer_, sdl_rects.data(), count) != 0)
		throw Exception("SDL_RenderDrawRects");

	return *this;
}

Renderer& Renderer::FillRect(int x1, int y1, int x2, int y2) {
	SDL_Rect rect = {x1, y1, x2 - x1 + 1, y2 - y1 + 1};
	if (SDL_RenderFillRect(renderer_, &rect) != 0)
		throw Exception("SDL_RenderFillRect");
	return *this;
}

Renderer& Renderer::FillRect(const Point& p1, const Point& p2) {
	FillRect(p1.x, p1.y, p2.x, p2.y);
	return *this;
}

Renderer& Renderer::FillRect(const Rect& r) {
	if (SDL_RenderFillRect(renderer_, &r) != 0)
		throw Exception("SDL_RenderFillRect");
	return *this;
}

Renderer& Renderer::FillRects(const Rect* rects, int count) {
	std::vector<SDL_Rect> sdl_rects;
	sdl_rects.reserve(static_cast<size_t>(count));
	for (const Rect* r = rects; r != rects + count; ++r)
		sdl_rects.emplace_back(*r);

	if (SDL_RenderFillRects(renderer_, sdl_rects.data(), count) != 0)
		throw Exception("SDL_RenderFillRects");

	return *this;
}

void Renderer::ReadPixels(const Optional<Rect>& rect, Uint32 format, void* pixels, int pitch) {
	if (SDL_RenderReadPixels(renderer_, rect ? &*rect : nullptr, format, pixels, pitch) != 0)
		throw Exception("SDL_RenderReadPixels");
}

Renderer& Renderer::SetClipRect(const Optional<Rect>& rect) {
	if (SDL_RenderSetClipRect(renderer_, rect ? &*rect : nullptr) != 0)
		throw Exception("SDL_RenderSetClipRect");
	return *this;
}

Renderer& Renderer::SetLogicalSize(int w, int h) {
	if (SDL_RenderSetLogicalSize(renderer_, w, h) != 0)
		throw Exception("SDL_RenderSetLogicalSize");
	return *this;
}

Renderer& Renderer::SetScale(float scaleX, float scaleY) {
	if (SDL_RenderSetScale(renderer_, scaleX, scaleY) != 0)
		throw Exception("SDL_RenderSetScale");
	return *this;
}

Renderer& Renderer::SetViewport(const Optional<Rect>& rect) {
	if (SDL_RenderSetViewport(renderer_, rect ? &*rect : nullptr) != 0)
		throw Exception("SDL_RenderSetViewport");
	return *this;
}

bool Renderer::TargetSupported() const {
	return SDL_RenderTargetSupported(renderer_) == SDL_TRUE;
}

Optional<Rect> Renderer::GetClipRect() const {
	SDL_Rect rect;
	SDL_RenderGetClipRect(renderer_, &rect);

	if (SDL_RectEmpty(&rect))
		return NullOpt;
	else
		return Rect(rect);
}

Point Renderer::GetLogicalSize() const {
	int w, h;
	SDL_RenderGetLogicalSize(renderer_, &w, &h);
	return Point(w, h);
}

int Renderer::GetLogicalWidth() const {
	int w;
	SDL_RenderGetLogicalSize(renderer_, &w, nullptr);
	return w;
}

int Renderer::GetLogicalHeight() const {
	int h;
	SDL_RenderGetLogicalSize(renderer_, nullptr, &h);
	return h;
}

void Renderer::GetScale(float& scalex, float& scaley) const {
	SDL_RenderGetScale(renderer_, &scalex, &scaley);
}

float Renderer::GetXScale() const {
	float scalex;
	SDL_RenderGetScale(renderer_, &scalex, nullptr);
	return scalex;
}

float Renderer::GetYScale() const {
	float scaley;
	SDL_RenderGetScale(renderer_, nullptr, &scaley);
	return scaley;
}

Rect Renderer::GetViewport() const {
	SDL_Rect rect;
	SDL_RenderGetViewport(renderer_, &rect);
	return rect;
}

SDL_BlendMode Renderer::GetDrawBlendMode() const {
	SDL_BlendMode mode;
	if (SDL_GetRenderDrawBlendMode(renderer_, &mode) != 0)
		throw Exception("SDL_GetRenderDrawBlendMode");
	return mode;
}

Color Renderer::GetDrawColor() const {
	Color color;
	GetDrawColor(color.r, color.g, color.b, color.a);
	return color;
}

void Renderer::GetDrawColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a) const {
	if (SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a) != 0)
		throw Exception("SDL_GetRenderDrawColor");
}

Point Renderer::GetOutputSize() const {
	int w, h;
	if (SDL_GetRendererOutputSize(renderer_, &w, &h) != 0)
		throw Exception("SDL_GetRendererOutputSize");
	return Point(w, h);
}

int Renderer::GetOutputWidth() const {
	int w;
	if (SDL_GetRendererOutputSize(renderer_, &w, nullptr) != 0)
		throw Exception("SDL_GetRendererOutputSize");
	return w;
}

int Renderer::GetOutputHeight() const {
	int h;
	if (SDL_GetRendererOutputSize(renderer_, nullptr, &h) != 0)
		throw Exception("SDL_GetRendererOutputSize");
	return h;
}

}
