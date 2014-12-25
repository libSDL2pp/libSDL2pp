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

#ifndef SDL2PP_RENDERER_HH
#define SDL2PP_RENDERER_HH

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_blendmode.h>

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

struct SDL_RendererInfo;
struct SDL_Renderer;

namespace SDL2pp {

class Window;
class Texture;
class Rect;
class Point;

class Renderer {
private:
	SDL_Renderer* renderer_;

public:
	Renderer(Window& window, int index, Uint32 flags);
	virtual ~Renderer();

	Renderer(const Renderer& other) = delete;
	Renderer(Renderer&& other) noexcept;
	Renderer& operator=(const Renderer& other) = delete;
	Renderer& operator=(Renderer&& other) noexcept;

	SDL_Renderer* Get() const;

	void Present();
	void Clear();

	void GetInfo(SDL_RendererInfo* info);

	void Copy(Texture& texture, const Optional<Rect>& srcrect = NullOpt, const Optional<Rect>& dstrect = NullOpt);
	void Copy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect, double angle, const Optional<Point>& center = NullOpt, int flip = 0);

	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	void SetTarget();
	void SetTarget(Texture& texture);

	void SetDrawBlendMode(SDL_BlendMode blendMode);

	void DrawPoint(int x, int y);
	void DrawPoint(const Point& p);
	void DrawPoints(const Point* points, int count);

	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(const Point& p1, const Point& p2);
	void DrawLines(const Point* points, int count);

	void DrawRect(int x1, int y1, int x2, int y2);
	void DrawRect(const Point& p1, const Point& p2);
	void DrawRect(const Rect& r);
	void DrawRects(const Rect* rects, int count);

	void FillRect(int x1, int y1, int x2, int y2);
	void FillRect(const Point& p1, const Point& p2);
	void FillRect(const Rect& r);
	void FillRects(const Rect* rects, int count);

	void ReadPixels(const Rect& rect, Uint32 format, void* pixels, int pitch);

	void SetClipRect(const Rect& rect);
	void SetLogicalSize(int w, int h);
	void SetScale(float scaleX, float scaleY);
	void SetViewport(const Rect& rect);

	bool TargetSupported();
};

}

#endif
