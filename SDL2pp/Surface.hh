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
    /// \see http://wiki.libsdl.org/SDL_DestroyTexture
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
};

}

#endif
