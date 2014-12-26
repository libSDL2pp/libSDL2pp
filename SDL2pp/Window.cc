/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2013-2014 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2/SDL.h>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Exception.hh>

namespace SDL2pp {

Window::Window(const std::string& title, int x, int y, int w, int h, Uint32 flags) {
	if ((window_ = SDL_CreateWindow(title.c_str(), x, y, w, h, flags)) == nullptr)
		throw Exception("SDL_CreateWindow failed");
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

Point Window::GetSize() const {
	int w, h;
	SDL_GetWindowSize(window_, &w, &h);
	return Point(w, h);
}

int Window::GetWidth() const {
	int w, h;
	SDL_GetWindowSize(window_, &w, &h);
	return w;
}

int Window::GetHeight() const {
	int w, h;
	SDL_GetWindowSize(window_, &w, &h);
	return h;
}

void Window::SetTitle(const std::string& title) {
	SDL_SetWindowTitle(window_, title.c_str());
}

SDL_Window* Window::Get() const {
	return window_;
}

void Window::Maximize() {
	SDL_MaximizeWindow(window_);
}

void Window::Minimize() {
	SDL_MinimizeWindow(window_);
}

void Window::Hide() {
	SDL_HideWindow(window_);
}

void Window::Restore() {
	SDL_RestoreWindow(window_);
}

void Window::Raise() {
	SDL_RaiseWindow(window_);
}

void Window::Show() {
	SDL_ShowWindow(window_);
}

void Window::SetFullscreen(int flags) {
	if (SDL_SetWindowFullscreen(window_, flags) != 0)
		throw Exception("SDL_SetWindowFullscreen failed");
}

void Window::SetSize(int w, int h) {
	SDL_SetWindowSize(window_, w, h);
}

void Window::SetSize(const Point& size) {
	SDL_SetWindowSize(window_, size.x, size.y);
}

}
