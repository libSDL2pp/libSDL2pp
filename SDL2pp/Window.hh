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

#ifndef SDL2PP_WINDOW_HH
#define SDL2PP_WINDOW_HH

#include <string>

#include <SDL_version.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Export.hh>

struct SDL_Window;

namespace SDL2pp {

class Surface;

////////////////////////////////////////////////////////////
/// \brief GUI window object
///
/// \ingroup windows
///
/// \headerfile SDL2pp/Window.hh
///
/// SDL2pp::Window is a wrapper around SDL_Window structure
/// and related functions which take care of GUI window
/// management.
///
/// Usage example:
/// \code
/// {
///     SDL2pp::SDL sdl(SDL_INIT_VIDEO);
///     SDL2pp::Window window("Test Window",
///                           SDL_WINDOWPOS_UNDEFINED,
///                           SDL_WINDOWPOS_UNDEFINED,
///                           640,
///                           480,
///                           SDL_WINDOW_OPENGL);
///
///     SDL_Delay(3000); // show window for 3 seconds
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Window {
private:
	SDL_Window* window_; ///< Managed SDL2_Window object

public:
	////////////////////////////////////////////////////////////
	/// \brief Construct from existing SDL_Window structure
	///
	/// \param[in] window Existing SDL_Window to manage
	///
	////////////////////////////////////////////////////////////
	explicit Window(SDL_Window* window);

	////////////////////////////////////////////////////////////
	/// \brief Create window with specified title and dimensions
	///
	/// \param[in] title Title of the windows, in UTF-8 encoding
	/// \param[in] x X position of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
	/// \param[in] y X position of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
	/// \param[in] w Width of the window
	/// \param[in] h Height of the window
	/// \param[in] flags 0 or more SDL_WindowFlags OR'd together
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_CreateWindow
	///
	////////////////////////////////////////////////////////////
	Window(const std::string& title, int x, int y, int w, int h, Uint32 flags);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see http://wiki.libsdl.org/SDL_DestroyWindow
	///
	////////////////////////////////////////////////////////////
	virtual ~Window();

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Window object to move data from
	///
	////////////////////////////////////////////////////////////
	Window(Window&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::Window object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Window& operator=(Window&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Window(const Window& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Window& operator=(const Window& other) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to managed SDL_Window structure
	///
	/// \returns Pointer to managed SDL_Window structure
	///
	////////////////////////////////////////////////////////////
	SDL_Window* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Get dimensions of the window
	///
	/// \returns SDL2pp::Point representing dimensions (width and
	///          height) of the window in pixels
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowSize
	///
	////////////////////////////////////////////////////////////
	Point GetSize() const;

	////////////////////////////////////////////////////////////
	/// \brief Get width of the window
	///
	/// \returns Width of the window in pixels
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowSize
	///
	////////////////////////////////////////////////////////////
	int GetWidth() const;

	////////////////////////////////////////////////////////////
	/// \brief Get height of the window
	///
	/// \returns Height of the window in pixels
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowSize
	///
	////////////////////////////////////////////////////////////
	int GetHeight() const;

	////////////////////////////////////////////////////////////
	/// \brief Get drawable dimensions of the window
	///
	/// \returns SDL2pp::Point representing dimensions (width and
	///          height) of the window drawable area in pixels
	///
	/// \see http://wiki.libsdl.org/SDL_GL_GetDrawableSize
	///
	////////////////////////////////////////////////////////////
	Point GetDrawableSize() const;

	////////////////////////////////////////////////////////////
	/// \brief Get drawable width of the window
	///
	/// \returns Width of the window drawable area in pixels
	///
	/// \see http://wiki.libsdl.org/SDL_GL_GetDrawableSize
	///
	////////////////////////////////////////////////////////////
	int GetDrawableWidth() const;

	////////////////////////////////////////////////////////////
	/// \brief Get drawable height of the window
	///
	/// \returns Height of the window drawable area in pixels
	///
	/// \see http://wiki.libsdl.org/SDL_GL_GetDrawableSize
	///
	////////////////////////////////////////////////////////////
	int GetDrawableHeight() const;

	////////////////////////////////////////////////////////////
	/// \brief Set window title
	///
	/// \param[in] title New window title in UTF-8 encoding
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowTitle
	///
	////////////////////////////////////////////////////////////
	Window& SetTitle(const std::string& title);

	////////////////////////////////////////////////////////////
	/// \brief Get window title
	///
	/// \returns Title of the window in UTF-8 format or "" if there is no title
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowTitle
	///
	////////////////////////////////////////////////////////////
	std::string GetTitle() const;

	////////////////////////////////////////////////////////////
	/// \brief Make a window as large as possible
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_MaximizeWindow
	///
	////////////////////////////////////////////////////////////
	Window& Maximize();

	////////////////////////////////////////////////////////////
	/// \brief Minimize a window to an iconic representation
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_MinimizeWindow
	///
	////////////////////////////////////////////////////////////
	Window& Minimize();

	////////////////////////////////////////////////////////////
	/// \brief Hide a window
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_HideWindow
	///
	////////////////////////////////////////////////////////////
	Window& Hide();

	////////////////////////////////////////////////////////////
	/// \brief Restore the size and position of a minimized or maximized window
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_RestoreWindow
	///
	////////////////////////////////////////////////////////////
	Window& Restore();

	////////////////////////////////////////////////////////////
	/// \brief Raise a window above other windows and set the input focus
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_RaiseWindow
	///
	////////////////////////////////////////////////////////////
	Window& Raise();

	////////////////////////////////////////////////////////////
	/// \brief Show a window
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_ShowWindow
	///
	////////////////////////////////////////////////////////////
	Window& Show();

	////////////////////////////////////////////////////////////
	/// \brief Set a window's fullscreen state
	///
	/// \param[in] flags SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP or 0
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowFullscreen
	///
	////////////////////////////////////////////////////////////
	Window& SetFullscreen(Uint32 flags);

	////////////////////////////////////////////////////////////
	/// \brief Set the size of a window's client area
	///
	/// \param[in] w Width of the window in pixels
	/// \param[in] h Height of the window in pixels
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowSize
	///
	////////////////////////////////////////////////////////////
	Window& SetSize(int w, int h);

	////////////////////////////////////////////////////////////
	/// \brief Set the size of a window's client area
	///
	/// \param[in] size Point representing window dimensions
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowSize
	///
	////////////////////////////////////////////////////////////
	Window& SetSize(const Point& size);

	////////////////////////////////////////////////////////////
	/// \brief Get the brightness (gamma multiplier) for the display that owns a given window
	///
	/// \returns Brightness for the display where 0.0 is completely dark and 1.0 is normal brightness
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowBrightness
	///
	////////////////////////////////////////////////////////////
	float GetBrightness() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the brightness (gamma multiplier) for the display that owns a given window
	///
	/// \param[in] brightness Brightness value to set where 0.0 is completely dark and 1.0 is normal brightness
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowBrightness
	///
	////////////////////////////////////////////////////////////
	Window& SetBrightness(float brightness);

	////////////////////////////////////////////////////////////
	/// \brief Get the position of a window
	///
	/// \returns Point representing window position
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowPosition
	///
	////////////////////////////////////////////////////////////
	Point GetPosition() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the position of a window
	///
	/// \param[in] x X coordinate of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
	/// \param[in] y Y coordinate of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowPosition
	///
	////////////////////////////////////////////////////////////
	Window& SetPosition(int x, int y);

	////////////////////////////////////////////////////////////
	/// \brief Set the position of a window
	///
	/// \param[in] pos Point representin position of the a window
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowPosition
	///
	////////////////////////////////////////////////////////////
	Window& SetPosition(const Point& pos);

	////////////////////////////////////////////////////////////
	/// \brief Get the minimum size of a window's client area
	///
	/// \returns Point representing minimum area of window's client area
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowMinimumSize
	///
	////////////////////////////////////////////////////////////
	Point GetMinimumSize() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the minimum size of a window's client area
	///
	/// \param[in] w Minimum width of the window in pixels
	/// \param[in] h Minimum height of the window in pixels
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowMinimumSize
	///
	////////////////////////////////////////////////////////////
	Window& SetMinimumSize(int w, int h);

	////////////////////////////////////////////////////////////
	/// \brief Set the minimum size of a window's client area
	///
	/// \param[in] size Minimum area of the window in pixels
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowMinimumSize
	///
	////////////////////////////////////////////////////////////
	Window& SetMinimumSize(const Point& size);

	////////////////////////////////////////////////////////////
	/// \brief Get the maximum size of a window's client area
	///
	/// \returns Point representing maximum area of window's client area
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowMaximumSize
	///
	////////////////////////////////////////////////////////////
	Point GetMaximumSize() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the maximum size of a window's client area
	///
	/// \param[in] w Maximum width of the window in pixels
	/// \param[in] h Maximum height of the window in pixels
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowMaximumSize
	///
	////////////////////////////////////////////////////////////
	Window& SetMaximumSize(int w, int h);

	////////////////////////////////////////////////////////////
	/// \brief Set the maximum size of a window's client area
	///
	/// \param[in] size Maximum area of the window in pixels
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowMaximumSize
	///
	////////////////////////////////////////////////////////////
	Window& SetMaximumSize(const Point& size);

	////////////////////////////////////////////////////////////
	/// \brief Get a window's input grab mode
	///
	/// \returns True if input is grabbed, flase otherwise
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowGrab
	///
	////////////////////////////////////////////////////////////
	bool GetGrab() const;

	////////////////////////////////////////////////////////////
	/// \brief Set a window's input grab mode
	///
	/// \param[in] grabbed True to grab input, false to release input
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowGrab
	///
	////////////////////////////////////////////////////////////
	Window& SetGrab(bool grabbed);

	////////////////////////////////////////////////////////////
	/// \brief Get the index of the display associated with a window
	///
	/// \returns Index of the display containing the center of the window
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowDisplayIndex
	///
	////////////////////////////////////////////////////////////
	int GetDisplayIndex() const;

	////////////////////////////////////////////////////////////
	/// \brief Get information about the display mode to use when a
	///        window is visible at fullscreen
	///
	/// \param[out] mode SDL_DisplayMode structure filled in with the
	///                  fullscreen display mode
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowDisplayMode
	///
	////////////////////////////////////////////////////////////
	void GetDisplayMode(SDL_DisplayMode& mode) const;

	////////////////////////////////////////////////////////////
	/// \brief Get the window flags
	///
	/// \returns Mask of the SDL_WindowFlags associated with window
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowFlags
	///
	////////////////////////////////////////////////////////////
	Uint32 GetFlags() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the icon for a window
	///
	/// \param[in] icon Surface containing the icon for the window
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowIcon
	///
	/// Icon surface may be destroyed after calling this function
	///
	////////////////////////////////////////////////////////////
	Window& SetIcon(const Surface& icon);

	////////////////////////////////////////////////////////////
	/// \brief Set the border state of a window
	///
	/// \param[in] bordered False to remove border, true to add border
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowBordered
	///
	////////////////////////////////////////////////////////////
	Window& SetBordered(bool bordered = true);

#if SDL_VERSION_ATLEAST(2, 0, 5)
	////////////////////////////////////////////////////////////
	/// \brief Set the opacity for a window
	///
	/// \param[in] opacity The opacity value (0.0f - transparent, 1.0f - opaque)
	///
	/// \returns Reference to self
	///
	/// \throws SDL2pp::Exception
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowOpacity
	///
	////////////////////////////////////////////////////////////
	Window& SetOpacity(float opacity = 1.0f);

	////////////////////////////////////////////////////////////
	/// \brief Get the opacity of a window
	///
	/// \returns Opacity value (0.0f - transparent, 1.0f - opaque)
	///
	/// \throws SDL2pp:Exception
	///
	/// \see http://wiki.libsdl.org/SDL_GetWindowOpacity
	///
	////////////////////////////////////////////////////////////
	float GetOpacity() const;

	////////////////////////////////////////////////////////////
	/// \brief Set user-resizable state of a window
	///
	/// \param[in] resizable True to allow resizing, false to disallow
	///
	/// \returns Reference to self
	///
	/// \see http://wiki.libsdl.org/SDL_SetWindowResizable
	///
	////////////////////////////////////////////////////////////
	Window& SetResizable(bool resizable = true);
#endif
};

}

#endif
