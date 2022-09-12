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

#ifndef SDL2PP_SURFACE_HH
#define SDL2PP_SURFACE_HH

#include <SDL_stdinc.h>
#include <SDL_blendmode.h>

#include <SDL2pp/Config.hh>
#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Export.hh>
#include <SDL2pp/Color.hh>

struct SDL_Surface;
struct SDL_PixelFormat;

namespace SDL2pp {

class RWops;

////////////////////////////////////////////////////////////
/// \brief Image stored in system memory with direct access
///        to pixel data
///
/// \ingroup rendering
///
/// \headerfile SDL2pp/Surface.hh
///
/// \see http://wiki.libsdl.org/SDL_Surface
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Surface {
private:
	SDL_Surface* surface_; ///< Managed SDL_Surface object

public:
	////////////////////////////////////////////////////////////
	/// \brief SDL2pp::Surface lock
	///
	/// \ingroup rendering
	///
	/// \headerfile SDL2pp/Surface.hh
	///
	/// For direct pixel access, %SDL surface may need to be locked.
	/// This class represents the lock and controls its lifetime
	/// as the lock is released as soon as LockHandle is destroyed.
	///
	////////////////////////////////////////////////////////////
	class LockHandle {
		friend class Surface;
	private:
		Surface* surface_;  ///< SDL2pp::Surface this lock belongs to

	private:
		////////////////////////////////////////////////////////////
		/// \brief Create lock for specific SDL2pp::Surface
		///
		/// \throws STL2pp::Exception
		///
		/// \see http://wiki.libsdl.org/SDL_LockSurface
		///
		////////////////////////////////////////////////////////////
		explicit LockHandle(Surface* surface);

	public:
		////////////////////////////////////////////////////////////
		/// \brief Create no-op lock
		///
		/// This may be initialized with real lock later via move
		/// assignment
		///
		////////////////////////////////////////////////////////////
		LockHandle();

		////////////////////////////////////////////////////////////
		/// \brief Destructor
		///
		/// Releases the lock
		///
		/// \see http://wiki.libsdl.org/SDL_UnlockSurface
		///
		////////////////////////////////////////////////////////////
		~LockHandle();

		////////////////////////////////////////////////////////////
		/// \brief Move constructor
		///
		/// \param[in] other SDL2pp::Surface::LockHandle to move data from
		///
		////////////////////////////////////////////////////////////
		LockHandle(LockHandle&& other) noexcept;

		////////////////////////////////////////////////////////////
		/// \brief Move assignment operator
		///
		/// \param[in] other SDL2pp::Surface::LockHandle to move data from
		///
		/// \returns Reference to self
		///
		////////////////////////////////////////////////////////////
		LockHandle& operator=(LockHandle&& other) noexcept;

		////////////////////////////////////////////////////////////
		/// \brief Deleted copy constructor
		///
		/// This class is not copyable
		///
		////////////////////////////////////////////////////////////
		LockHandle(const LockHandle& other) = delete;

		////////////////////////////////////////////////////////////
		/// \brief Deleted assignment operator
		///
		/// This class is not copyable
		///
		////////////////////////////////////////////////////////////
		LockHandle& operator=(const LockHandle& other) = delete;

		////////////////////////////////////////////////////////////
		/// \brief Get pointer to raw pixel data of locked region
		///
		/// \returns Pointer to raw pixel data of locked region
		///
		////////////////////////////////////////////////////////////
		void* GetPixels() const;

		////////////////////////////////////////////////////////////
		/// \brief Get pitch of locked pixel data
		///
		/// \returns Number of bytes in a row of pixel data, including
		///          padding between lines
		///
		////////////////////////////////////////////////////////////
		int GetPitch() const;

		////////////////////////////////////////////////////////////
		/// \brief Get pixel format of the surface
		///
		/// \returns Format of the pixels stored in the surface
		///
		////////////////////////////////////////////////////////////
		const SDL_PixelFormat& GetFormat() const;
	};

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct from existing SDL_Surface structure
	///
	/// \param[in] surface Existing SDL_Surface to manage
	///
	////////////////////////////////////////////////////////////
	explicit Surface(SDL_Surface* surface);

	////////////////////////////////////////////////////////////
	/// \brief Create RGB surface
	///
	/// \param[in] flags Unused and should be set to 0
	/// \param[in] width Width of the surface
	/// \param[in] height Height of the surface
	/// \param[in] depth Depth of the surface in bits
	/// \param[in] Rmask Red mask for the pixels
	/// \param[in] Gmask Green mask for the pixels
	/// \param[in] Bmask Blue mask for the pixels
	/// \param[in] Amask Alpha mask for the pixels
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_CreateRGBSurface
	///
	////////////////////////////////////////////////////////////
	Surface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);

	////////////////////////////////////////////////////////////
	/// \brief Create RGB surface with existing pixel data
	///
	/// \param[in] pixels Pointer to existing pixel data
	/// \param[in] width Width of the surface
	/// \param[in] height Height of the surface
	/// \param[in] depth Depth of the surface in bits
	/// \param[in] pitch Number of bytes in a row of pixel data, including padding between lines
	/// \param[in] Rmask Red mask for the pixels
	/// \param[in] Gmask Green mask for the pixels
	/// \param[in] Bmask Blue mask for the pixels
	/// \param[in] Amask Alpha mask for the pixels
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
	///
	////////////////////////////////////////////////////////////
	Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);

#ifdef SDL2PP_WITH_IMAGE
	////////////////////////////////////////////////////////////
	/// \brief Create surface loading it via RWops
	///
	/// \param[in] rwops RWops used to access an image file
	///
	/// \throws SDL2pp::Exception
	///
	////////////////////////////////////////////////////////////
	explicit Surface(RWops& rwops);

	////////////////////////////////////////////////////////////
	/// \brief Create surface loading it from file
	///
	/// \param[in] filename Path to an image file
	///
	/// \throws SDL2pp::Exception
	///
	////////////////////////////////////////////////////////////
	explicit Surface(const std::string& filename);
#endif

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see http://wiki.libsdl.org/SDL_FreeSurface
	///
	////////////////////////////////////////////////////////////
	virtual ~Surface();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Surface object to move data from
	///
	////////////////////////////////////////////////////////////
	Surface(Surface&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment
	///
	/// \param[in] other SDL2pp::Surface object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Surface& operator=(Surface&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Surface(const Surface&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Surface& operator=(const Surface&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to managed SDL_Surface structure
	///
	/// \returns Pointer to managed SDL_Surface structure
	///
	////////////////////////////////////////////////////////////
	SDL_Surface* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Copy an existing surface into a new one that is
	///        optimized for blitting to a surface of a specified pixel format
	///
	/// \param[in] format SDL_PixelFormat structure that the new surface is optimized for
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_ConvertSurface
	///
	////////////////////////////////////////////////////////////
	Surface Convert(const SDL_PixelFormat& format);

	////////////////////////////////////////////////////////////
	/// \brief Copy an existing surface to a new surface of the specified format
	///
	/// \param[in] pixel_format One of the enumerated values in SDL_PixelFormatEnum
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_PixelFormatEnum
	/// \see http://wiki.libsdl.org/SDL_ConvertSurfaceFormat
	///
	////////////////////////////////////////////////////////////
	Surface Convert(Uint32 pixel_format);

	////////////////////////////////////////////////////////////
	/// \brief Fast surface copy to a destination surface
	///
	/// \param[in] srcrect Rectangle to be copied, or NullOpt to copy the entire surface
	/// \param[in] dst Blit target surface
	/// \param[in] dstrect Rectangle that is copied into
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_BlitSurface
	///
	////////////////////////////////////////////////////////////
	void Blit(const Optional<Rect>& srcrect, Surface& dst, const Rect& dstrect);

	////////////////////////////////////////////////////////////
	/// \brief Scaled surface copy to a destination surface
	///
	/// \param[in] srcrect Rectangle to be copied, or NullOpt to copy the entire surface
	/// \param[in] dst Blit target surface
	/// \param[in] dstrect Rectangle that is copied into, or NullOpt to copy into entire surface
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_BlitScaled
	///
	////////////////////////////////////////////////////////////
	void BlitScaled(const Optional<Rect>& srcrect, Surface& dst, const Optional<Rect>& dstrect);

	////////////////////////////////////////////////////////////
	/// \brief Lock surface for direct pixel access
	///
	/// \return Lock handle used to access pixel data and to control lock lifetime
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_LockSurface
	///
	////////////////////////////////////////////////////////////
	LockHandle Lock();

	////////////////////////////////////////////////////////////
	/// \brief Get the clipping rectangle for a surface
	///
	/// \return Rect filled in with the clipping rectangle for the surface
	///
	/// \see http://wiki.libsdl.org/SDL_GetClipRect
	///
	////////////////////////////////////////////////////////////
	Rect GetClipRect() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the color key (transparent pixel) for a surface
	///
	/// \return Transparent pixel value
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetColorKey
	///
	////////////////////////////////////////////////////////////
	Uint32 GetColorKey() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the additional alpha value used in blit operations
	///
	/// \return Current alpha value
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetSurfaceAlphaMod
	///
	////////////////////////////////////////////////////////////
	Uint8 GetAlphaMod() const;

	////////////////////////////////////////////////////////////
	/// \brief Get blend mode used for blit operations
	///
	/// \return Current SDL_BlendMode
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetSurfaceBlendMode
	///
	////////////////////////////////////////////////////////////
	SDL_BlendMode GetBlendMode() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the additional color value multiplied into blit operations
	///
	/// \return Color object with the values used to do blit operations
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetSurfaceAlphaMod
	/// \see http://wiki.libsdl.org/SDL_GetSurfaceColorMod
	///
	////////////////////////////////////////////////////////////
	Color GetColorAndAlphaMod() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the additional color value multiplied into blit operations
	///
	/// \param[out] r Variable to be filled in with the current red color value
	/// \param[out] g Variable to be filled in with the current green color value
	/// \param[out] b Variable to be filled in with the current blue color value
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetSurfaceColorMod
	///
	////////////////////////////////////////////////////////////
	void GetColorMod(Uint8& r, Uint8& g, Uint8& b) const;

	////////////////////////////////////////////////////////////
	/// \brief Set the clipping rectangle for a surface
	///
	/// \param[in] rect Rect representing the clipping rectangle, or NullOpt to disable clipping
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetClipRect
	///
	////////////////////////////////////////////////////////////
	Surface& SetClipRect(const Optional<Rect>& rect = NullOpt);

	////////////////////////////////////////////////////////////
	/// \brief Set the color key (transparent pixel) in a surface
	///
	/// \param[in] flag True to enabled color key, false to disable
	/// \param[in] key Transparent pixel value
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetColorKey
	///
	////////////////////////////////////////////////////////////
	Surface& SetColorKey(bool flag, Uint32 key);

	////////////////////////////////////////////////////////////
	/// \brief Set an additional alpha value used in blit operations
	///
	/// \param[in] alpha Alpha value multiplied into blit operations
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceAlphaMod
	///
	////////////////////////////////////////////////////////////
	Surface& SetAlphaMod(Uint8 alpha = 255);

	////////////////////////////////////////////////////////////
	/// \brief Set the blend mode used for blit operations
	///
	/// \param[in] blendMode SDL_BlendMode to use for blit blending
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceBlendMode
	///
	////////////////////////////////////////////////////////////
	Surface& SetBlendMode(SDL_BlendMode blendMode);

	////////////////////////////////////////////////////////////
	/// \brief Set an additional color value multiplied into blit operations
	///
	/// \param[in] r Red color value multiplied into blit operations
	/// \param[in] g Green color value multiplied into blit operations
	/// \param[in] b Blue color value multiplied into blit operations
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceColorMod
	///
	////////////////////////////////////////////////////////////
	Surface& SetColorMod(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

	////////////////////////////////////////////////////////////
	/// \brief Set an additional color value multiplied into blit operations
	///
	/// \param[in] color Color to be multiplied into blit operations
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceAlphaMod
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceColorMod
	///
	////////////////////////////////////////////////////////////
	Surface& SetColorAndAlphaMod(const Color& color);

	////////////////////////////////////////////////////////////
	/// \brief Set the RLE acceleration hint for a surface
	///
	/// \param[in] flag False to disable, true to enable RLE acceleration
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceRLE
	///
	////////////////////////////////////////////////////////////
	Surface& SetRLE(bool flag);

	////////////////////////////////////////////////////////////
	/// \brief Perform a fast fill of a rectangle with a specific color
	///
	/// \param[in] rect Rectangle to fill, or NullOpt to fill the entire surface
	/// \param[in] color Color to fill with
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_FillRect
	///
	////////////////////////////////////////////////////////////
	Surface& FillRect(const Optional<Rect>& rect, Uint32 color);

	////////////////////////////////////////////////////////////
	/// \brief Perform a fast fill of a set of rectangles with a specific color
	///
	/// \param[in] rects Array rectangles to be filled
	/// \param[in] count Number of rectangles in the array
	/// \param[in] color Color to fill with
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_FillRects
	///
	////////////////////////////////////////////////////////////
	Surface& FillRects(const Rect* rects, int count, Uint32 color);

	////////////////////////////////////////////////////////////
	/// \brief Get surface width
	///
	/// \return Surface width in pixels
	///
	////////////////////////////////////////////////////////////
	int GetWidth() const;

	////////////////////////////////////////////////////////////
	/// \brief Get surface height
	///
	/// \return Surface height in pixels
	///
	////////////////////////////////////////////////////////////
	int GetHeight() const;

	////////////////////////////////////////////////////////////
	/// \brief Get surface size
	///
	/// \return SDL2pp::Point representing surface dimensions in pixels
	///
	////////////////////////////////////////////////////////////
	Point GetSize() const;

	////////////////////////////////////////////////////////////
	/// \brief Get texture format
	///
	/// \return Surface raw format
	///
	/// \see http://wiki.libsdl.org/SDL_Surface
	/// \see http://wiki.libsdl.org/SDL_PixelFormatEnum
	///
	////////////////////////////////////////////////////////////
	Uint32 GetFormat() const;
};

}

#endif
