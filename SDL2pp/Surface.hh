/*
  libSDL2pp - C++11 bindings/wrapper for SDL2
  Copyright (C) 2014 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_blendmode.h>

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>

struct SDL_Surface;
struct SDL_PixelFormat;

namespace SDL2pp {

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
class Surface {
private:
	SDL_Surface* surface_; ///< Contained SDL_Texture structure

public:
	////////////////////////////////////////////////////////////
	/// \brief SDL2pp::Surface lock
	/// \ingroup rendering
	///
	/// \details
	/// For direct pixel access, SDL surface may need to be locked.
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
		/// \brief Create lock for specific SDL2pp::Texture
		///
		/// \throws STL2pp::Exception
		///
		/// \see http://wiki.libsdl.org/SDL_LockSurface
		///
		////////////////////////////////////////////////////////////
		LockHandle(Surface* surface);

	public:
		////////////////////////////////////////////////////////////
		/// \brief Create no-op lock
		///
		/// \details
		/// This may be initialized with real lock later with move
		/// assignment operator
		///
		////////////////////////////////////////////////////////////
		LockHandle();

		////////////////////////////////////////////////////////////
		/// \brief Destructor
		///
		/// \details
		/// Releases the lock
		///
		/// \see http://wiki.libsdl.org/SDL_UnlockSurface
		///
		////////////////////////////////////////////////////////////
		~LockHandle();

		////////////////////////////////////////////////////////////
		/// \brief Move constructor
		///
		/// \param other SDL2pp::Surface::LockHandle to move data from
		///
		////////////////////////////////////////////////////////////
		LockHandle(LockHandle&& other) noexcept;

		////////////////////////////////////////////////////////////
		/// \brief Move assignment operator
		///
		/// \param other SDL2pp::Surface::LockHandle to move data from
		///
		/// \returns Reference to self
		///
		////////////////////////////////////////////////////////////
		LockHandle& operator=(LockHandle&& other) noexcept;

		// Deleted copy constructor and assignment
		LockHandle(const LockHandle& other) = delete;
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

private:
	////////////////////////////////////////////////////////////
	/// \brief Create surface taking existing SDL_surface structure
	///
	/// \param surface Existing SDL_surface to manage
	///
	////////////////////////////////////////////////////////////
	Surface(SDL_Surface* surface);

public:
	////////////////////////////////////////////////////////////
	/// \brief Create RGB surface
	///
	/// \param flags Unused and should be set to 0
	/// \param width Width of the surface
	/// \param height Height of the surface
	/// \param depth Depth of the surface in bits
	/// \param Rmask Red mask for the pixels
	/// \param Gmask Green mask for the pixels
	/// \param Bmask Blue mask for the pixels
	/// \param Amask Alpha mask for the pixels
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
	/// \param pixels Pointer to existing pixel data
	/// \param width Width of the surface
	/// \param height Height of the surface
	/// \param depth depth of the surface in bits
	/// \param pitch Number of bytes in a row of pixel data, including padding between lines
	/// \param Rmask Red mask for the pixels
	/// \param Gmask Green mask for the pixels
	/// \param Bmask Blue mask for the pixels
	/// \param Amask Alpha mask for the pixels
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_CreateRGBSurfaceFrom
	///
	////////////////////////////////////////////////////////////
	Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);

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
	/// \param other SDL2pp::Surface object to move data from
	///
	////////////////////////////////////////////////////////////
	Surface(Surface&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment
	///
	/// \param other SDL2pp::Surface object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Surface& operator=(Surface&& other) noexcept;

	// Deleted copy constructor and assignment
	Surface(const Surface&) = delete;
	Surface& operator=(const Surface&) = delete;

    ////////////////////////////////////////////////////////////
	/// \brief Get pointer to contained SDL_Surface structure
	///
	/// \returns Pointer to contained SDL_Surface structure
	///
	////////////////////////////////////////////////////////////
	SDL_Surface* Get() const;

    ////////////////////////////////////////////////////////////
	/// \brief Copy an existing surface into a new one that is
	///        optimized for blitting to a surface of a specified pixel format
	///
	/// \param format SDL_PixelFormat structure that the new surface is optimized for
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
	/// \param pixel_format One of the enumerated values in SDL_PixelFormatEnum
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
	/// \param srcrect Rectangle to be copied, or NullOpt to copy the entire surface
	/// \param dst Blit target surface
	/// \param srcrect Rectangle that is copied into
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
	/// \param srcrect Rectangle to be copied, or NullOpt to copy the entire surface
	/// \param dst Blit target surface
	/// \param srcrect Rectangle that is copied into, or NullOpt to copy into entire surface
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
	/// \param r Variable to be filled in with the current red color value
	/// \param g Variable to be filled in with the current green color value
	/// \param b Variable to be filled in with the current blue color value
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
	/// \param rect SDL22::Rect representing the clipping rectangle, or NullOpt to disable clipping
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetClipRect
	///
	////////////////////////////////////////////////////////////
	void SetClipRect(const Optional<Rect>& rect = NullOpt);

	////////////////////////////////////////////////////////////
	/// \brief Set the color key (transparent pixel) in a surface
	///
	/// \param flag True to enabled color key, false to disable
	/// \param key Transparent pixel value
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetColorKey
	///
	////////////////////////////////////////////////////////////
	void SetColorKey(int flag, Uint32 key);

	////////////////////////////////////////////////////////////
	/// \brief Set an additional alpha value used in blit operations
	///
	/// \param alpha Alpha value multiplied into blit operations
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceAlphaMod
	///
	////////////////////////////////////////////////////////////
	void SetAlphaMod(Uint8 alpha = 255);

	////////////////////////////////////////////////////////////
	/// \brief Set the blend mode used for blit operations
	///
	/// \param blendMode SDL_BlendMode to use for blit blending
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceBlendMode
	///
	////////////////////////////////////////////////////////////
	void SetBlendMode(SDL_BlendMode blendMode);

	////////////////////////////////////////////////////////////
	/// \brief Set an additional color value multiplied into blit operations
	///
	/// \param r Red color value multiplied into blit operations
	/// \param g Green color value multiplied into blit operations
	/// \param b Blue color value multiplied into blit operations
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceColorMod
	///
	////////////////////////////////////////////////////////////
	void SetColorMod(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

	////////////////////////////////////////////////////////////
	/// \brief Set the RLE acceleration hint for a surface
	///
	/// \param flag 0 to disable, non-zero to enable RLE acceleration
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetSurfaceRLE
	///
	////////////////////////////////////////////////////////////
	void SetRLE(int flag);

	////////////////////////////////////////////////////////////
	/// \brief Perform a fast fill of a rectangle with a specific color
	///
	/// \param rect Rectangle to fill, or NullOpt to fill the entire surface
	/// \param color Color to fill with
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_FillRect
	///
	////////////////////////////////////////////////////////////
	void FillRect(const Optional<Rect>& rect, Uint32 color);

	////////////////////////////////////////////////////////////
	/// \brief Perform a fast fill of a set of rectangles with a specific color
	///
	/// \param rects Array rectangles to be filled
	/// \param count Number of rectangles in the array
	/// \param color Color to fill with
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_FillRects
	///
	////////////////////////////////////////////////////////////
	void FillRects(const Rect* rects, int count, Uint32 color);
};

}

#endif
