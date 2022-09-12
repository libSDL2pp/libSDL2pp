/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2013-2017 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL.h>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Window::Window(SDL_Window* window) : window_(window) {
	assert(window);
}

Window::Window(const std::string& title, int x, int y, int w, int h, Uint32 flags) {
	if ((window_ = SDL_CreateWindow(title.c_str(), x, y, w, h, flags)) == nullptr)
		throw Exception("SDL_CreateWindow");
}

Window::~Window() {
	if (window_ != nullptr)
		SDL_DestroyWindow(window_);
}

Window::Window(Window&& other) noexcept : window_(other.window_) {
	other.window_ = nullptr;
}

Window& Window::operator=(Window&& other) noexcept {
	if (&other == this)
		return *this;
	if (window_ != nullptr)
		SDL_DestroyWindow(window_);
	window_ = other.window_;
	other.window_ = nullptr;
	return *this;
}

SDL_Window* Window::Get() const {
	return window_;
}

Point Window::GetSize() const {
	int w, h;
	SDL_GetWindowSize(window_, &w, &h);
	return Point(w, h);
}

int Window::GetWidth() const {
	int w;
	SDL_GetWindowSize(window_, &w, nullptr);
	return w;
}

int Window::GetHeight() const {
	int h;
	SDL_GetWindowSize(window_, nullptr, &h);
	return h;
}

Point Window::GetDrawableSize() const {
	int w, h;
	SDL_GL_GetDrawableSize(window_, &w, &h);
	return Point(w, h);
}

int Window::GetDrawableWidth() const {
	int w;
	SDL_GL_GetDrawableSize(window_, &w, nullptr);
	return w;
}

int Window::GetDrawableHeight() const {
	int h;
	SDL_GL_GetDrawableSize(window_, nullptr, &h);
	return h;
}

Window& Window::SetTitle(const std::string& title) {
	SDL_SetWindowTitle(window_, title.c_str());
	return *this;
}

std::string Window::GetTitle() const {
	return SDL_GetWindowTitle(window_);
}

Window& Window::Maximize() {
	SDL_MaximizeWindow(window_);
	return *this;
}

Window& Window::Minimize() {
	SDL_MinimizeWindow(window_);
	return *this;
}

Window& Window::Hide() {
	SDL_HideWindow(window_);
	return *this;
}

Window& Window::Restore() {
	SDL_RestoreWindow(window_);
	return *this;
}

Window& Window::Raise() {
	SDL_RaiseWindow(window_);
	return *this;
}

Window& Window::Show() {
	SDL_ShowWindow(window_);
	return *this;
}

Window& Window::SetFullscreen(Uint32 flags) {
	if (SDL_SetWindowFullscreen(window_, flags) != 0)
		throw Exception("SDL_SetWindowFullscreen");
	return *this;
}

Window& Window::SetSize(int w, int h) {
	SDL_SetWindowSize(window_, w, h);
	return *this;
}

Window& Window::SetSize(const Point& size) {
	SDL_SetWindowSize(window_, size.x, size.y);
	return *this;
}

float Window::GetBrightness() const {
	return SDL_GetWindowBrightness(window_);
}

Window& Window::SetBrightness(float brightness) {
	if (SDL_SetWindowBrightness(window_, brightness) != 0)
		throw Exception("SDL_SetWindowBrightness");
	return *this;
}

Point Window::GetPosition() const {
	int x, y;
	SDL_GetWindowPosition(window_, &x, &y);
	return Point(x, y);
}

Window& Window::SetPosition(int x, int y) {
	SDL_SetWindowPosition(window_, x, y);
	return *this;
}

Window& Window::SetPosition(const Point& pos) {
	SDL_SetWindowPosition(window_, pos.x, pos.y);
	return *this;
}

Point Window::GetMinimumSize() const {
	int w, h;
	SDL_GetWindowMinimumSize(window_, &w, &h);
	return Point(w, h);
}

Window& Window::SetMinimumSize(int w, int h) {
	SDL_SetWindowMinimumSize(window_, w, h);
	return *this;
}

Window& Window::SetMinimumSize(const Point& size) {
	SDL_SetWindowMinimumSize(window_, size.x, size.y);
	return *this;
}

Point Window::GetMaximumSize() const {
	int w, h;
	SDL_GetWindowMaximumSize(window_, &w, &h);
	return Point(w, h);
}

Window& Window::SetMaximumSize(int w, int h) {
	SDL_SetWindowMaximumSize(window_, w, h);
	return *this;
}

Window& Window::SetMaximumSize(const Point& size) {
	SDL_SetWindowMaximumSize(window_, size.x, size.y);
	return *this;
}

bool Window::GetGrab() const {
	return SDL_GetWindowGrab(window_) == SDL_TRUE;
}

Window& Window::SetGrab(bool grabbed) {
	SDL_SetWindowGrab(window_, grabbed ? SDL_TRUE : SDL_FALSE);
	return *this;
}

int Window::GetDisplayIndex() const {
	int index = SDL_GetWindowDisplayIndex(window_);
	if (index < 0)
		throw SDL2pp::Exception("SDL_GetWindowDisplayIndex");
	return index;
}

void Window::GetDisplayMode(SDL_DisplayMode& mode) const {
	if (SDL_GetWindowDisplayMode(window_, &mode) != 0)
		throw SDL2pp::Exception("SDL_GetWindowDisplayMode");
}

Uint32 Window::GetFlags() const {
	return SDL_GetWindowFlags(window_);
}

Window& Window::SetIcon(const Surface& icon) {
	SDL_SetWindowIcon(window_, icon.Get());
	return *this;
}

Window& Window::SetBordered(bool bordered) {
	SDL_SetWindowBordered(window_, bordered ? SDL_TRUE : SDL_FALSE);
	return *this;
}

#if SDL_VERSION_ATLEAST(2, 0, 5)
Window& Window::SetOpacity(float opacity) {
	if (SDL_SetWindowOpacity(window_, opacity))
		throw SDL2pp::Exception("SDL_SetWindowOpacity");
	return *this;
}

float Window::GetOpacity() const {
	float opacity;
	if (SDL_GetWindowOpacity(window_, &opacity) == -1)
		throw SDL2pp::Exception("SDL_GetWindowOpacity");

	return opacity;
}

Window& Window::SetResizable(bool resizable) {
	SDL_SetWindowResizable(window_, resizable ? SDL_TRUE : SDL_FALSE);
	return *this;
}
#endif

}
