/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2013-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2/SDL.h>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Texture.hh>

namespace SDL2pp {

Renderer::Renderer(SDL_Renderer* renderer) : renderer_(renderer) {
}

Renderer::Renderer(Window& window, int index, Uint32 flags) {
	if ((renderer_ = SDL_CreateRenderer(window.Get(), index, flags)) == nullptr)
		throw Exception("SDL_CreateRenderer failed");
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

void Renderer::Present() {
	SDL_RenderPresent(renderer_);
}

void Renderer::Clear() {
	if (SDL_RenderClear(renderer_) != 0)
		throw Exception("SDL_RenderClear failed");
}

void Renderer::GetInfo(SDL_RendererInfo* info) {
	if (SDL_GetRendererInfo(renderer_, info) != 0)
		throw Exception("SDL_GetRendererInfo failed");
}

void Renderer::GetInfo(SDL_RendererInfo& info) {
	if (SDL_GetRendererInfo(renderer_, &info) != 0)
		throw Exception("SDL_GetRendererInfo failed");
}

void Renderer::Copy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect) {
	if (SDL_RenderCopy(renderer_, texture.Get(), srcrect ? &*srcrect : nullptr, dstrect ? &*dstrect : nullptr) != 0)
		throw Exception("SDL_RenderCopy failed");
}

void Renderer::Copy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect, double angle, const Optional<Point>& center, int flip) {
	if (SDL_RenderCopyEx(renderer_, texture.Get(), srcrect ? &*srcrect : nullptr, dstrect ? &*dstrect : nullptr, angle, center ? &*center : nullptr, static_cast<SDL_RendererFlip>(flip)) != 0)
		throw Exception("SDL_RenderCopyEx failed");
}

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	if (SDL_SetRenderDrawColor(renderer_, r, g, b, a) != 0)
		throw Exception("SDL_SetRenderDrawColor failed");
}

void Renderer::SetTarget() {
	if (SDL_SetRenderTarget(renderer_, nullptr) != 0)
		throw Exception("SDL_SetRenderTarget failed");
}

void Renderer::SetTarget(Texture& texture) {
	if (SDL_SetRenderTarget(renderer_, texture.Get()) != 0)
		throw Exception("SDL_SetRenderTarget failed");
}

void Renderer::SetDrawBlendMode(SDL_BlendMode blendMode) {
	if (SDL_SetRenderDrawBlendMode(renderer_, blendMode) != 0)
		throw Exception("SDL_SetRenderDrawBlendMode failed");
}

void Renderer::DrawPoint(int x, int y) {
	if (SDL_RenderDrawPoint(renderer_, x, y) != 0)
		throw Exception("SDL_RenderDrawPoint failed");
}

void Renderer::DrawPoint(const Point& p) {
	DrawPoint(p.x, p.y);
}

void Renderer::DrawPoints(const Point* points, int count) {
	std::vector<SDL_Point> sdl_points;
	sdl_points.reserve(count);
	for (const Point* p = points; p != points + count; ++p)
		sdl_points.emplace_back(*p);

	if (SDL_RenderDrawPoints(renderer_, sdl_points.data(), sdl_points.size()) != 0)
		throw Exception("SDL_RenderDrawPoints failed");
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2) {
	if (SDL_RenderDrawLine(renderer_, x1, y1, x2, y2) != 0)
		throw Exception("SDL_RenderDrawLine failed");
}

void Renderer::DrawLine(const Point& p1, const Point& p2) {
	DrawLine(p1.x, p1.y, p2.x, p2.y);
}

void Renderer::DrawLines(const Point* points, int count) {
	std::vector<SDL_Point> sdl_points;
	sdl_points.reserve(count);
	for (const Point* p = points; p != points + count; ++p)
		sdl_points.emplace_back(*p);

	if (SDL_RenderDrawLines(renderer_, sdl_points.data(), sdl_points.size()) != 0)
		throw Exception("SDL_RenderDrawLines failed");
}

void Renderer::DrawRect(int x1, int y1, int x2, int y2) {
	SDL_Rect rect = {x1, y1, x2 - x1 + 1, y2 - y1 + 1};
	if (SDL_RenderDrawRect(renderer_, &rect) != 0)
		throw Exception("SDL_RenderDrawRect failed");
}

void Renderer::DrawRect(const Point& p1, const Point& p2) {
	DrawRect(p1.x, p1.y, p2.x, p2.y);
}

void Renderer::DrawRect(const Rect& r) {
	if (SDL_RenderDrawRect(renderer_, &r) != 0)
		throw Exception("SDL_RenderDrawRect failed");
}

void Renderer::DrawRects(const Rect* rects, int count) {
	std::vector<SDL_Rect> sdl_rects;
	sdl_rects.reserve(count);
	for (const Rect* r = rects; r != rects + count; ++r)
		sdl_rects.emplace_back(*r);

	if (SDL_RenderDrawRects(renderer_, sdl_rects.data(), sdl_rects.size()) != 0)
		throw Exception("SDL_RenderDrawRects failed");
}

void Renderer::FillRect(int x1, int y1, int x2, int y2) {
	SDL_Rect rect = {x1, y1, x2 - x1 + 1, y2 - y1 + 1};
	if (SDL_RenderFillRect(renderer_, &rect) != 0)
		throw Exception("SDL_RenderFillRect failed");
}

void Renderer::FillRect(const Point& p1, const Point& p2) {
	FillRect(p1.x, p1.y, p2.x, p2.y);
}

void Renderer::FillRect(const Rect& r) {
	if (SDL_RenderFillRect(renderer_, &r) != 0)
		throw Exception("SDL_RenderFillRect failed");
}

void Renderer::FillRects(const Rect* rects, int count) {
	std::vector<SDL_Rect> sdl_rects;
	sdl_rects.reserve(count);
	for (const Rect* r = rects; r != rects + count; ++r)
		sdl_rects.emplace_back(*r);

	if (SDL_RenderFillRects(renderer_, sdl_rects.data(), sdl_rects.size()) != 0)
		throw Exception("SDL_RenderFillRects failed");
}

void Renderer::ReadPixels(const Optional<Rect>& rect, Uint32 format, void* pixels, int pitch) {
	if (SDL_RenderReadPixels(renderer_, rect ? &*rect : nullptr, format, pixels, pitch) != 0)
		throw Exception("SDL_RenderReadPixels failed");
}

void Renderer::SetClipRect(const Optional<Rect>& rect) {
	if (SDL_RenderSetClipRect(renderer_, rect ? &*rect : nullptr) != 0)
		throw Exception("SDL_RenderSetClipRect failed");
}

void Renderer::SetLogicalSize(int w, int h) {
	if (SDL_RenderSetLogicalSize(renderer_, w, h) != 0)
		throw Exception("SDL_RenderSetLogicalSize failed");
}

void Renderer::SetScale(float scaleX, float scaleY) {
	if (SDL_RenderSetScale(renderer_, scaleX, scaleY) != 0)
		throw Exception("SDL_RenderSetScale failed");
}

void Renderer::SetViewport(const Optional<Rect>& rect) {
	if (SDL_RenderSetViewport(renderer_, rect ? &*rect : nullptr) != 0)
		throw Exception("SDL_RenderSetViewport failed");
}

bool Renderer::TargetSupported() {
	return SDL_RenderTargetSupported(renderer_) == SDL_TRUE;
}

Rect Renderer::GetClipRect() const {
	SDL_Rect rect;
	SDL_RenderGetClipRect(renderer_, &rect);
	return rect;
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
		throw Exception("SDL_GetRenderDrawBlendMode failed");
	return mode;
}

void Renderer::GetDrawColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a) const {
	if (SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a) != 0)
		throw Exception("SDL_GetRenderDrawColor failed");
}

}
