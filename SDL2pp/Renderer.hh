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

#ifndef SDL2PP_RENDERER_HH
#define SDL2PP_RENDERER_HH

#include <SDL_stdinc.h>
#include <SDL_blendmode.h>

#include <SDL2pp/Config.hh>
#include <SDL2pp/Optional.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Export.hh>
#include <SDL2pp/Color.hh>

struct SDL_RendererInfo;
struct SDL_Renderer;

namespace SDL2pp {

class Window;
class Texture;
class Point;

////////////////////////////////////////////////////////////
/// \brief 2D rendering context
///
/// \ingroup rendering
///
/// \headerfile SDL2pp/Renderer.hh
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Renderer {
private:
	SDL_Renderer* renderer_; ///< Managed SDL_Renderer object

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct from existing SDL_Renderer structure
	///
	/// \param[in] renderer Existing SDL_Renderer to manage
	///
	////////////////////////////////////////////////////////////
	explicit Renderer(SDL_Renderer* renderer);

	////////////////////////////////////////////////////////////
	/// \brief Create renderer
	///
	/// \param[in] window Window where rendering is displayed
	/// \param[in] index Index of the rendering driver to initialize,
	///                  or -1 to initialize the first one supporting
	///                  the requested flags
	/// \param[in] flags 0 or more SDL_RendererFlags OR'ed together
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_CreateRenderer
	///
	////////////////////////////////////////////////////////////
	Renderer(Window& window, int index, Uint32 flags);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see http://wiki.libsdl.org/SDL_DestroyRenderer
	///
	////////////////////////////////////////////////////////////
	virtual ~Renderer();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Renderer object to move data from
	///
	////////////////////////////////////////////////////////////
	Renderer(Renderer&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::Renderer object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Renderer& operator=(Renderer&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Renderer(const Renderer& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Renderer& operator=(const Renderer& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to managed SDL_Renderer structure
	///
	/// \returns Pointer to managed SDL_Renderer structure
	///
	////////////////////////////////////////////////////////////
	SDL_Renderer* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Update the screen with any rendering performed
	///        since the previous call
	///
	/// %SDL's rendering functions operate on a backbuffer; that
	/// is, calling a rendering function such as SDL_RenderDrawLine()
	/// does not directly put a line on the screen, but rather
	/// updates the backbuffer. As such, you compose your entire
	/// scene and present the composed backbuffer to the screen as
	/// a complete picture.
	///
	/// Therefore, when using %SDL's rendering API, one does all
	/// drawing intended for the frame, and then calls this function
	/// once per frame to present the final drawing to the user.
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_RenderPresent
	///
	////////////////////////////////////////////////////////////
	Renderer& Present();

	////////////////////////////////////////////////////////////
	/// \brief Clear the current rendering target with the drawing color
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderClear
	///
	////////////////////////////////////////////////////////////
	Renderer& Clear();

	////////////////////////////////////////////////////////////
	/// \brief Get information about a rendering context
	///
	/// \param[out] info SDL_RendererInfo structure to be filled with
	///                  information about the current renderer
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetRendererInfo
	///
	////////////////////////////////////////////////////////////
	void GetInfo(SDL_RendererInfo& info);

	////////////////////////////////////////////////////////////
	/// \brief Copy a portion of the texture to the current rendering
	///        target
	///
	/// \param[in] texture Source texture
	/// \param[in] srcrect Source rectangle, NullOpt for the entire texture
	/// \param[in] dstrect Destination rectangle, NullOpt for the entire
	///                    rendering target
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderCopy
	///
	////////////////////////////////////////////////////////////
	Renderer& Copy(Texture& texture, const Optional<Rect>& srcrect = NullOpt, const Optional<Rect>& dstrect = NullOpt);

	////////////////////////////////////////////////////////////
	/// \brief Copy a portion of the texture to the current rendering
	///        target (preserve texture dimensions)
	///
	/// \param[in] texture Source texture
	/// \param[in] srcrect Source rectangle, NullOpt for the entire texture
	/// \param[in] dstpoint Target point for source top left corner
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderCopy
	///
	////////////////////////////////////////////////////////////
	Renderer& Copy(Texture& texture, const Optional<Rect>& srcrect, const Point& dstpoint);

	////////////////////////////////////////////////////////////
	/// \brief Copy a portion of the texture to the current rendering
	///        target with optional rotating or flipping
	///
	/// \param[in] texture Source texture
	/// \param[in] srcrect Source rectangle, NullOpt for the entire texture
	/// \param[in] dstrect Destination rectangle, NullOpt for the entire
	///                    rendering target
	/// \param[in] angle Angle in degrees that indicates the rotation that
	///                  will be applied to dstrect
	/// \param[in] center Point indicating the point around which dstrect
	///                   will be rotated (NullOpt to rotate around dstrect
	///                   center)
	/// \param[in] flip SDL_RendererFlip value stating which flipping
	///                 actions should be performed on the texture
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RendererFlip
	/// \see http://wiki.libsdl.org/SDL_RenderCopyEx
	///
	////////////////////////////////////////////////////////////
	Renderer& Copy(Texture& texture, const Optional<Rect>& srcrect, const Optional<Rect>& dstrect, double angle, const Optional<Point>& center = NullOpt, int flip = 0);

	////////////////////////////////////////////////////////////
	/// \brief Copy a portion of the texture to the current rendering
	///        target with optional rotating or flipping (preserve texture
	///        dimensions)
	///
	/// \param[in] texture Source texture
	/// \param[in] srcrect Source rectangle, NullOpt for the entire texture
	/// \param[in] dstpoint Target point for source top left corner
	/// \param[in] angle Angle in degrees that indicates the rotation that
	///                  will be applied to dstrect
	/// \param[in] center Point indicating the point around which dstrect
	///                   will be rotated (NullOpt to rotate around dstrect
	///                   center)
	/// \param[in] flip SDL_RendererFlip value stating which flipping
	///                 actions should be performed on the texture
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RendererFlip
	/// \see http://wiki.libsdl.org/SDL_RenderCopyEx
	///
	////////////////////////////////////////////////////////////
	Renderer& Copy(Texture& texture, const Optional<Rect>& srcrect, const SDL2pp::Point& dstpoint, double angle, const Optional<Point>& center = NullOpt, int flip = 0);

	////////////////////////////////////////////////////////////
	/// \brief Fill the target with repeated source texture
	///
	/// \param[in] texture Source texture
	/// \param[in] srcrect Source rectangle, NullOpt for the entire texture
	/// \param[in] dstrect Destination rectangle, NullOpt for the entire
	///                    rendering target
	/// \param[in] offset Offset of tiled texture in pixels relative to
	///                   dstrect
	/// \param[in] flip SDL_RendererFlip value stating which flipping
	///                 actions should be performed on the texture
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RendererFlip
	/// \see http://wiki.libsdl.org/SDL_RenderCopy
	/// \see http://wiki.libsdl.org/SDL_RenderCopyEx
	///
	////////////////////////////////////////////////////////////
	Renderer& FillCopy(Texture& texture, const Optional<Rect>& srcrect = NullOpt, const Optional<Rect>& dstrect = NullOpt, const Point& offset = Point(0, 0), int flip = 0);

	////////////////////////////////////////////////////////////
	/// \brief Set color user for drawing operations
	///
	/// \param[in] r Red value used to draw on the rendering target
	/// \param[in] g Green value used to draw on the rendering target
	/// \param[in] b Blue value used to draw on the rendering target
	/// \param[in] a Alpha value used to draw on the rendering target
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetRenderDrawColor
	///
	////////////////////////////////////////////////////////////
	Renderer& SetDrawColor(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);

	////////////////////////////////////////////////////////////
	/// \brief Set color user for drawing operations
	///
	/// \param[in] color Color to draw on the rendering target
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetRenderDrawColor
	///
	////////////////////////////////////////////////////////////
	Renderer& SetDrawColor(const Color& color);

	////////////////////////////////////////////////////////////
	/// \brief Set current render target to default
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetRenderTarget
	///
	////////////////////////////////////////////////////////////
	Renderer& SetTarget();

	////////////////////////////////////////////////////////////
	/// \brief Set current render target to specified texture
	///
	/// \param[in] texture Target texture, SDL2pp::Texture created with
	///                    SDL_TEXTUREACCESS_TARGET
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetRenderTarget
	///
	////////////////////////////////////////////////////////////
	Renderer& SetTarget(Texture& texture);

	////////////////////////////////////////////////////////////
	/// \brief Set the blend mode used for drawing operations
	///
	/// \param[in] blendMode SDL_BlendMode to use for blending
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_BlendMode
	/// \see http://wiki.libsdl.org/SDL_SetRenderDrawBlendMode
	///
	////////////////////////////////////////////////////////////
	Renderer& SetDrawBlendMode(SDL_BlendMode blendMode = SDL_BLENDMODE_NONE);

	////////////////////////////////////////////////////////////
	/// \brief Draw a point on the current rendering target
	///
	/// \param[in] x X coordinate of the point
	/// \param[in] y Y coordinate of the point
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawPoint
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawPoint(int x, int y);

	////////////////////////////////////////////////////////////
	/// \brief Draw a point on the current rendering target
	///
	/// \param[in] p Coordinates of the point
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawPoint
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawPoint(const Point& p);

	////////////////////////////////////////////////////////////
	/// \brief Draw multiple points on the current rendering target
	///
	/// \param[in] points Array of coordinates of points to draw
	/// \param[in] count Number of points to draw
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawPoints
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawPoints(const Point* points, int count);

	////////////////////////////////////////////////////////////
	/// \brief Draw a line on the current rendering target
	///
	/// \param[in] x1 X coordinate of the start point
	/// \param[in] y1 Y coordinate of the start point
	/// \param[in] x2 X coordinate of the end point
	/// \param[in] y2 Y coordinate of the end point
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawLine
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawLine(int x1, int y1, int x2, int y2);

	////////////////////////////////////////////////////////////
	/// \brief Draw a line on the current rendering target
	///
	/// \param[in] p1 Coordinates of the start point
	/// \param[in] p2 Coordinates of the end point
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawLine
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawLine(const Point& p1, const Point& p2);

	////////////////////////////////////////////////////////////
	/// \brief Draw a polyline on the current rendering target
	///
	/// \param[in] points Array of coordinates of points along the polyline
	/// \param[in] count Number of points to draw count-1 polyline segments
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawLines
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawLines(const Point* points, int count);

	////////////////////////////////////////////////////////////
	/// \brief Draw a rectangle on the current rendering target
	///
	/// \param[in] x1 X coordinate of the start corner
	/// \param[in] y1 Y coordinate of the start corner
	/// \param[in] x2 X coordinate of the end corner
	/// \param[in] y2 Y coordinate of the end corner
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawRect
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawRect(int x1, int y1, int x2, int y2);

	////////////////////////////////////////////////////////////
	/// \brief Draw a rectangle on the current rendering target
	///
	/// \param[in] p1 Coordinates of the start corner
	/// \param[in] p2 Coordinates of the end corner
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawRect
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawRect(const Point& p1, const Point& p2);

	////////////////////////////////////////////////////////////
	/// \brief Draw a rectangle on the current rendering target
	///
	/// \param[in] r Rectangle to draw
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawRect
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawRect(const Rect& r);

	////////////////////////////////////////////////////////////
	/// \brief Draw multiple rectangles on the current rendering target
	///
	/// \param[in] rects Array of rectangles to draw
	/// \param[in] count Number of rectangles
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderDrawRects
	///
	////////////////////////////////////////////////////////////
	Renderer& DrawRects(const Rect* rects, int count);

	////////////////////////////////////////////////////////////
	/// \brief Fill a rectangle on the current rendering target
	///
	/// \param[in] x1 X coordinate of the start corner
	/// \param[in] y1 Y coordinate of the start corner
	/// \param[in] x2 X coordinate of the end corner
	/// \param[in] y2 Y coordinate of the end corner
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderFillRect
	///
	////////////////////////////////////////////////////////////
	Renderer& FillRect(int x1, int y1, int x2, int y2);

	////////////////////////////////////////////////////////////
	/// \brief Fill a rectangle on the current rendering target
	///
	/// \param[in] p1 Coordinates of the start corner
	/// \param[in] p2 Coordinates of the end corner
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderFillRect
	///
	////////////////////////////////////////////////////////////
	Renderer& FillRect(const Point& p1, const Point& p2);

	////////////////////////////////////////////////////////////
	/// \brief Fill a rectangle on the current rendering target
	///
	/// \param[in] r Rectangle to draw
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderFillRect
	///
	////////////////////////////////////////////////////////////
	Renderer& FillRect(const Rect& r);

	////////////////////////////////////////////////////////////
	/// \brief Fill multiple rectangles on the current rendering target
	///
	/// \param[in] rects Array of rectangles to draw
	/// \param[in] count Number of rectangles
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderFillRects
	///
	////////////////////////////////////////////////////////////
	Renderer& FillRects(const Rect* rects, int count);

	////////////////////////////////////////////////////////////
	/// \brief Read pixels from the current rendering target
	///
	/// \param[in] rect Area to read or NullOpt for the entire render
	///                 target
	/// \param[in] format Desired format of the pixel data, or 0 to
	///                   use the format of the rendering target
	/// \param[in] pixels Pointer to memory to be filled with pixel
	///                   data
	/// \param[in] pitch Number of bytes in a row of pixel data, including
	///                  padding between lines
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderReadPixels
	///
	////////////////////////////////////////////////////////////
	void ReadPixels(const Optional<Rect>& rect, Uint32 format, void* pixels, int pitch);

	////////////////////////////////////////////////////////////
	/// \brief Set the clipping rectangle for rendering
	///
	/// \param[in] rect New clipping rectangle or NullOpt to disable
	///                 clipping
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderSetClipRect
	///
	////////////////////////////////////////////////////////////
	Renderer& SetClipRect(const Optional<Rect>& rect = NullOpt);

	////////////////////////////////////////////////////////////
	/// \brief Set a device independent resolution for rendering
	///
	/// \param[in] w Width of the logical resolution
	/// \param[in] h Height of the logical resolution
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderSetLogicalSize
	///
	////////////////////////////////////////////////////////////
	Renderer& SetLogicalSize(int w, int h);

	////////////////////////////////////////////////////////////
	/// \brief Set the drawing scale for rendering on the current target
	///
	/// \param[in] scaleX Horizontal scaling factor
	/// \param[in] scaleY Vertical scaling factor
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderSetScale
	///
	////////////////////////////////////////////////////////////
	Renderer& SetScale(float scaleX, float scaleY);

	////////////////////////////////////////////////////////////
	/// \brief Set the drawing area for rendering on the current target
	///
	/// \param[in] rect Rectangle representing the drawing area or
	///                 NullOpt to set the viewport to the entire target
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_RenderSetViewport
	///
	////////////////////////////////////////////////////////////
	Renderer& SetViewport(const Optional<Rect>& rect = NullOpt);

	////////////////////////////////////////////////////////////
	/// \brief Determine whether a window supports the use of
	///        render targets
	///
	/// \returns True if render targets are supported
	///
	/// \see http://wiki.libsdl.org/SDL_RenderTargetSupported
	///
	////////////////////////////////////////////////////////////
	bool TargetSupported() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the clip rectangle for the current target
	///
	/// \returns Rect representing current clipping area or
	///          NullOpt if clipping is disabled
	///
	/// \see http://wiki.libsdl.org/SDL_RenderGetClipRect
	///
	////////////////////////////////////////////////////////////
	Optional<Rect> GetClipRect() const;

	////////////////////////////////////////////////////////////
	/// \brief Get device independent resolution for rendering
	///
	/// \returns Point representing logical resolution
	///
	/// \see http://wiki.libsdl.org/SDL_RenderGetLogicalSize
	///
	/// \note If this function is called on an Renderer who never had
	///       its logical size set by SetLogicalSize(), this function
	///       returns {0, 0}
	///
	////////////////////////////////////////////////////////////
	Point GetLogicalSize() const;

	////////////////////////////////////////////////////////////
	/// \brief Get device independent width resolution for rendering
	///
	/// \returns Logical resolution width
	///
	/// \see http://wiki.libsdl.org/SDL_RenderGetLogicalSize
	///
	/// \note If this function is called on an Renderer who never had
	///       its logical size set by SetLogicalSize(), this function
	///       returns 0
	///
	////////////////////////////////////////////////////////////
	int GetLogicalWidth() const;

	////////////////////////////////////////////////////////////
	/// \brief Get device independent width resolution for rendering
	///
	/// \returns Logical resolution height
	///
	/// \see http://wiki.libsdl.org/SDL_RenderGetLogicalSize
	///
	/// \note If this function is called on an Renderer who never had
	///       its logical size set by SetLogicalSize(), this function
	///       returns 0
	///
	////////////////////////////////////////////////////////////
	int GetLogicalHeight() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the drawing scale for the current target
	///
	/// \param[out] scalex Variable to be filled with the horizontal scaling factor
	/// \param[out] scaley Variable to be filled with the vertical scaling factor
	///
	/// \see http://wiki.libsdl.org/SDL_RenderGetScale
	///
	////////////////////////////////////////////////////////////
	void GetScale(float& scalex, float& scaley) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the drawing scale for the current target
	///
	/// \returns Horizontal scaling factor
	///
	/// \see http://wiki.libsdl.org/SDL_RenderGetScale
	///
	////////////////////////////////////////////////////////////
	float GetXScale() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the drawing scale for the current target
	///
	/// \returns Vertical scaling factor
	///
	/// \see http://wiki.libsdl.org/SDL_RenderGetScale
	///
	////////////////////////////////////////////////////////////
	float GetYScale() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the drawing area for the current target
	///
	/// \returns Rect representing current drawing area
	///
	/// \see http://wiki.libsdl.org/SDL_RenderGetViewport
	///
	////////////////////////////////////////////////////////////
	Rect GetViewport() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the blend mode used for drawing operations
	///
	/// \return Current SDL_BlendMode
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetRenderDrawBlendMode
	///
	////////////////////////////////////////////////////////////
	SDL_BlendMode GetDrawBlendMode() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the additional color value multiplied into render copy operations
	///
	/// \return Color object with the value used to do render copy operations
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetRenderDrawColor
	///
	////////////////////////////////////////////////////////////
	Color GetDrawColor() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the additional color value multiplied into render copy operations
	///
	/// \param[out] r Variable to be filled in with red value used to draw on the rendering target
	/// \param[out] g Variable to be filled in with green value used to draw on the rendering target
	/// \param[out] b Variable to be filled in with blue value used to draw on the rendering target
	/// \param[out] a Variable to be filled in with alpha value used to draw on the rendering target
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetRenderDrawColor
	///
	////////////////////////////////////////////////////////////
	void GetDrawColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the output size of a rendering context
	///
	/// \returns Point representing output size
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetRendererOutputSize
	///
	////////////////////////////////////////////////////////////
	Point GetOutputSize() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the output width of a rendering context
	///
	/// \returns Output width
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetRendererOutputSize
	///
	////////////////////////////////////////////////////////////
	int GetOutputWidth() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the output height of a rendering context
	///
	/// \returns Output height
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetRendererOutputSize
	///
	////////////////////////////////////////////////////////////
	int GetOutputHeight() const;
};

}

#endif
