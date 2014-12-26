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

////////////////////////////////////////////////////////////
/// \brief 2D rendering context
///
/// \ingroup rendering
///
/// \headerfile SDL2pp/Renderer.hh
///
////////////////////////////////////////////////////////////
class Renderer {
private:
	SDL_Renderer* renderer_; ///< Contained SDL_Renderer object

public:
	////////////////////////////////////////////////////////////
	/// \brief Create renderer
	///
	/// \param window Window where rendering is displayed
	/// \param index Index of the rendering driver to initialize,
	///              or -1 to initialize the first one supporting
	///              the requested flags
	/// \param flags 0 or more SDL_RendererFlags OR'ed together
	///
	////////////////////////////////////////////////////////////
	Renderer(Window& window, int index, Uint32 flags);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~Renderer();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param other SDL2pp::Renderer object to move data from
	///
	////////////////////////////////////////////////////////////
	Renderer(Renderer&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param other SDL2pp::Renderer object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Renderer& operator=(Renderer&& other) noexcept;

	// Deleted copy constructor and assignment
	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to contained SDL_Renderer structure
	///
	/// \returns Pointer to contained SDL_Renderer structure
	///
	////////////////////////////////////////////////////////////
	SDL_Renderer* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Update the screen with any rendering performed
	///        since the previous call
	///
	/// SDL's rendering functions operate on a backbuffer; that
	/// is, calling a rendering function such as SDL_RenderDrawLine()
	/// does not directly put a line on the screen, but rather
	/// updates the backbuffer. As such, you compose your entire
	/// scene and present the composed backbuffer to the screen as
	/// a complete picture.
	///
	/// Therefore, when using SDL's rendering API, one does all
	/// drawing intended for the frame, and then calls this function
	/// once per frame to present the final drawing to the user.
	///
	/// \see http://wiki.libsdl.org/SDL_RenderPresent
	///
	////////////////////////////////////////////////////////////
	void Present();

	////////////////////////////////////////////////////////////
	/// \brief Clear the current rendering target with the drawing color
	///
	/// \see http://wiki.libsdl.org/SDL_RenderClear
	///
	////////////////////////////////////////////////////////////
	void Clear();

	////////////////////////////////////////////////////////////
	/// \brief Get information about a rendering context
	///
	/// \param info SDL_RendererInfo structure to be filled with
	///             information about the current renderer
	///
	/// \see http://wiki.libsdl.org/SDL_GetRendererInfo
	///
	////////////////////////////////////////////////////////////
	void GetInfo(SDL_RendererInfo* info);

	////////////////////////////////////////////////////////////
	/// \brief Copy a portion of the texture to the current rendering
	///        target
	///
	/// \param texture Source texture
	/// \param srcrect Source rectangle, NullOpt for the entire texture
	/// \param dstrect Destination rectangle, NullOpt for the entire
	///                rendering target
	///
	/// \see http://wiki.libsdl.org/SDL_RenderCopy
	///
	////////////////////////////////////////////////////////////
	void Copy(Texture& texture, const Optional<Rect>& srcrect = NullOpt, const Optional<Rect>& dstrect = NullOpt);

	////////////////////////////////////////////////////////////
	/// \brief Copy a portion of the texture to the current rendering
	///        target with optional rotating or flipping
	///
	/// \param texture Source texture
	/// \param srcrect Source rectangle, NullOpt for the entire texture
	/// \param dstrect Destination rectangle, NullOpt for the entire
	///                rendering target
	/// \param angle Angle in degrees that indicates the rotation that
	///              will be applied to dstrect
	/// \param center Point indicating the point around which dstrect
	///               will be rotated (NullOpt to rotate around dstrect
	///               center)
	/// \param flip SDL_RendererFlip value stating which flipping
	///             actions should be performed on the texture
	///
	/// \see http://wiki.libsdl.org/SDL_RendererFlip
	/// \see http://wiki.libsdl.org/SDL_RenderCopyEx
	///
	////////////////////////////////////////////////////////////
	void Copy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect, double angle, const Optional<Point>& center = NullOpt, int flip = 0);

	////////////////////////////////////////////////////////////
	/// \brief Set color user for drawing operations
	///
	/// \param r Red value used to draw on the rendering target
	/// \param g Green value used to draw on the rendering target
	/// \param b Blue value used to draw on the rendering target
	/// \param a Alpha value used to draw on the rendering target
	///
	/// \see http://wiki.libsdl.org/SDL_SetRenderDrawColor
	///
	////////////////////////////////////////////////////////////
	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

	////////////////////////////////////////////////////////////
	/// \brief Set current render target to default
	///
	/// \see http://wiki.libsdl.org/SDL_SetRenderTarget
	///
	////////////////////////////////////////////////////////////
	void SetTarget();

	////////////////////////////////////////////////////////////
	/// \brief Set current render target to specified texture
	///
	/// \param texture Target texture, SDL2pp::Texture created with
	///                SDL_TEXTUREACCESS_TARGET
	///
	/// \see http://wiki.libsdl.org/SDL_SetRenderTarget
	///
	////////////////////////////////////////////////////////////
	void SetTarget(Texture& texture);

	////////////////////////////////////////////////////////////
	/// \brief Set the blend mode used for drawing operations
	///
	/// \param blendMode SDL_BlendMode to use for blending
	///
	/// \see http://wiki.libsdl.org/SDL_BlendMode
	/// \see http://wiki.libsdl.org/SDL_SetRenderDrawBlendMode
	///
	////////////////////////////////////////////////////////////
	void SetDrawBlendMode(SDL_BlendMode blendMode);

	////////////////////////////////////////////////////////////
	/// \brief Draw a point on the current rendering target
	///
	/// \param x X coordinate of the point
	/// \param y Y coordinate of the point
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawPoint
	///
	////////////////////////////////////////////////////////////
	void DrawPoint(int x, int y);

	////////////////////////////////////////////////////////////
	/// \brief Draw a point on the current rendering target
	///
	/// \param p Coordinates of the point
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawPoint
	///
	////////////////////////////////////////////////////////////
	void DrawPoint(const Point& p);

	////////////////////////////////////////////////////////////
	/// \brief Draw multiple points on the current rendering target
	///
	/// \param points Array of coordinates of points to draw
	/// \param count Number of points to draw
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawPoints
	///
	////////////////////////////////////////////////////////////
	void DrawPoints(const Point* points, int count);

	////////////////////////////////////////////////////////////
	/// \brief Draw a line on the current rendering target
	///
	/// \param x1 X coordinate of the start point
	/// \param y1 Y coordinate of the start point
	/// \param x2 X coordinate of the end point
	/// \param y2 Y coordinate of the end point
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawLine
	///
	////////////////////////////////////////////////////////////
	void DrawLine(int x1, int y1, int x2, int y2);

	////////////////////////////////////////////////////////////
	/// \brief Draw a line on the current rendering target
	///
	/// \param p1 Coordinates of the start point
	/// \param p2 Coordinates of the end point
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawLine
	///
	////////////////////////////////////////////////////////////
	void DrawLine(const Point& p1, const Point& p2);

	////////////////////////////////////////////////////////////
	/// \brief Draw a polyline on the current rendering target
	///
	/// \param points Array of coordinates of points along the polyline
	/// \param count Number of points to draw count-1 polyline segments
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawLines
	///
	////////////////////////////////////////////////////////////
	void DrawLines(const Point* points, int count);

	////////////////////////////////////////////////////////////
	/// \brief Draw a rectangle on the current rendering target
	///
	/// \param x1 X coordinate of the start corner
	/// \param y1 Y coordinate of the start corner
	/// \param x2 X coordinate of the end corner
	/// \param y2 Y coordinate of the end corner
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawRect
	///
	////////////////////////////////////////////////////////////
	void DrawRect(int x1, int y1, int x2, int y2);

	////////////////////////////////////////////////////////////
	/// \brief Draw a rectangle on the current rendering target
	///
	/// \param p1 Coordinates of the start corner
	/// \param p2 Coordinates of the end corner
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawRect
	///
	////////////////////////////////////////////////////////////
	void DrawRect(const Point& p1, const Point& p2);

	////////////////////////////////////////////////////////////
	/// \brief Draw a rectangle on the current rendering target
	///
	/// \param r Rectange to draw
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawRect
	///
	////////////////////////////////////////////////////////////
	void DrawRect(const Rect& r);

	////////////////////////////////////////////////////////////
	/// \brief Draw multiple rectangles on the current rendering target
	///
	/// \param rects Array of rectangles to draw
	/// \param count Number of rectangles
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawRects
	///
	////////////////////////////////////////////////////////////
	void DrawRects(const Rect* rects, int count);

	////////////////////////////////////////////////////////////
	/// \brief Fill a rectangle on the current rendering target
	///
	/// \param x1 X coordinate of the start corner
	/// \param y1 Y coordinate of the start corner
	/// \param x2 X coordinate of the end corner
	/// \param y2 Y coordinate of the end corner
	///
	/// \see http://wiki.libsdl.org/SDL_RenderFillRect
	///
	////////////////////////////////////////////////////////////
	void FillRect(int x1, int y1, int x2, int y2);

	////////////////////////////////////////////////////////////
	/// \brief Fill a rectangle on the current rendering target
	///
	/// \param p1 Coordinates of the start corner
	/// \param p2 Coordinates of the end corner
	///
	/// \see http://wiki.libsdl.org/SDL_RenderFillRect
	///
	////////////////////////////////////////////////////////////
	void FillRect(const Point& p1, const Point& p2);

	////////////////////////////////////////////////////////////
	/// \brief Fill a rectangle on the current rendering target
	///
	/// \param r Rectange to draw
	///
	/// \see http://wiki.libsdl.org/SDL_RenderFillRect
	///
	////////////////////////////////////////////////////////////
	void FillRect(const Rect& r);

	////////////////////////////////////////////////////////////
	/// \brief Fill multiple rectangles on the current rendering target
	///
	/// \param rects Array of rectangles to draw
	/// \param count Number of rectangles
	///
	/// \see http://wiki.libsdl.org/SDL_RenderFillRects
	///
	////////////////////////////////////////////////////////////
	void FillRects(const Rect* rects, int count);

	////////////////////////////////////////////////////////////
	/// \brief Read pixels from the current rendering target
	///
	/// \param rect Area to read or NullOpt for the entire render
	///             target
	/// \param format Desired format of the pixel data, or 0 to
	///               use the format of the rendering target
	/// \param pixels Pointer to memory to be filled with pixel
	///               data
	/// \param pitch Pitch (row width) of the pixels parameter
	///
	/// \see http://wiki.libsdl.org/SDL_RenderReadPixels
	///
	////////////////////////////////////////////////////////////
	void ReadPixels(const Optional<Rect>& rect, Uint32 format, void* pixels, int pitch);

	////////////////////////////////////////////////////////////
	/// \brief Set the clipping rectange for rendering
	///
	/// \param rect New clipping rectangle or NullOpt to dusable
	///             clipping
	///
	/// \see http://wiki.libsdl.org/SDL_RenderSetClipRect
	///
	////////////////////////////////////////////////////////////
	void SetClipRect(const Optional<Rect>& rect = NullOpt);

	////////////////////////////////////////////////////////////
	/// \brief Set a device independent resolution for rendering
	///
	/// \param w Width of the logical resolution
	/// \param h Heigth of the logical resolution
	///
	/// \see http://wiki.libsdl.org/SDL_RenderSetLogicalSize
	///
	////////////////////////////////////////////////////////////
	void SetLogicalSize(int w, int h);

	////////////////////////////////////////////////////////////
	/// \brief Set the drawing scale for rendering on the current target
	///
	/// \param scaleX Horizontal scaling factor
	/// \param scaleY Vertical scaling factor
	///
	/// \see http://wiki.libsdl.org/SDL_RenderSetScale
	///
	////////////////////////////////////////////////////////////
	void SetScale(float scaleX, float scaleY);

	////////////////////////////////////////////////////////////
	/// \brief Set the drawing area for rendering on the current target
	///
	/// \param rect Rectangle representing the drawing area or
	///             NullOpt to set the viewport to the entire target
	///
	/// \see http://wiki.libsdl.org/SDL_RenderSetViewport
	///
	////////////////////////////////////////////////////////////
	void SetViewport(const Optional<Rect>& rect = NullOpt);

	////////////////////////////////////////////////////////////
	/// \brief Determine whether a window supports the use of
	///        render targets
	///
	/// \returns True if render targets are supported
	///
	/// \see http://wiki.libsdl.org/SDL_RenderTargetSupported
	///
	////////////////////////////////////////////////////////////
	bool TargetSupported();
};

}

#endif
