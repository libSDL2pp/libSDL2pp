# Change Log
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## 0.18.1 - 2023-04-17
### Fixed
* Fix SDL2main library link order

## 0.18.0 - 2023-03-27
### Changed
* Switch SDL2_{mixer,mixer,ttf} detection to upstream CMake scripts

## 0.17.0 - 2022-04-28
### Changed
* Switch to modern CMake
* Switch to C++17

## 0.16.2 - 2022-04-25
### Fixed
* Fix font dimensions test

## 0.16.1 - 2020-06-18
### Fixed
* Make `SDLmain` library optional in Unix, since some distros seem to drop it
* Fix using unsupported warning flags on some compilers

## 0.16.0 - 2018-02-11
### Added
* New SDL 2.0.5 `Window` method: `Window::SetResizable()`
* Minor documentation improvements
* Example code fixes

## 0.15.0 - 2017-07-10
### Added
* `Color` class wrapping around `SDL_Color`

## 0.14.1 - 2017-06-28
### Fixed
* `Surface.hh` include was missing from `SDL2pp.hh`

## 0.14.0 - 2017-05-29
### Fixed
* Proper `Size()` handling for custom `RWops`

### Added
* `Window::GetOpacity()` and `Window()::SetOpacity()` wrappers for functions appeared in SDL 2.0.5
* `Music` RWops constructors based on undocumented SDL_mixer functions
* Static standalone build support

### Changed
* libSDL2pp now follows SDL2 include path conventions, finding and using SDL2 headers without SDL2/ prefix

## 0.13.0 - 2016-11-08
### Fixed
* Fixed SDL 2.0.4 specific `AudioDevice` methods: `AudioDevice::QueueAudio()`, `AudioDevice::GetQueuedAudioSize()`
* Fixed MSVC compiler support and .dll generation
* Multiple documentation fixes

### Added
* More tests
* Automatic SDL 2.0.4 detection
* `Texture::Update()` overload which takes rvalue reference to `Surface`

### Changed
* `Renderer::GetClipRect` now returns `Optional<Rect>` instead of (possibly empty) `Rect`
* `Exception` is now derived from `std::runtime_error`

### Removed
* Deprecated `Renderer::GetInfo()` variant which takes pointer (use variant which takes reference)

## 0.12.0 - 2016-01-23
### Fixed
* Link SDL2main library, which is needed on some systems
* Numerous improvements in Windows support
* Documentation fixes
* Multiple fixes in pkg-config and CMake module files

## 0.11.0 - 2015-11-30
### Added
* New `Window` methods: `Window::GetDrawableWidth()`, `Window::GetDrawableHeight()`, `Window::GetDrawableSize()` (@csoren)
* `Point` and `Rect` less-than operators and std::hash support which makes them usable as `std::map`/`std::unordered_map`/`std::set`/`std::unordered_set` keys
* More `Rect` methods and wider constexpr support

### Fixed
* `Rect` documentation fixes
* Unused variable warnings (@vladimirgamalian)
* Incorrect return value handling in `Surface::SetClipRect()`

## 0.10.0 - 2015-10-14
### Fixed
* Improved cygwin compatibility
* Missing `SDL` method implementations
* Fixed return and argument types for some `Window`, `Font` and `Mixer` methods to match upstream API
* Infinite loop in `StreamRWops`
* Documentation improvements
* Build without [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/) support

## 0.9.0 - 2015-09-07
### Added
* [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/) support
* More `Point` operators: `*`, `/`, `%` for integer multiplication, division and remainder by a number or another `Point`
* `Point` and `Rect` better inlining and constexpr support
* New method: `Surface::GetFormat()`
* `Texture::Update()` overload which takes Surface as pixel source

## 0.8.2 - 2015-07-28
### Fixed
* Add missing `Font::IsGlyphProvided()` implementation (@vladimirgamalian)
* Fix glyph rectangle calculation in `Font::GetGlyphRect()` (@vladimirgamalian)

## 0.8.1 - 2015-06-29
### Fixed
* Use correct type flags in `RWops::Size()`, fixing MinGW build (@vladimirgamalian)

## 0.8.0 - 2015-06-10
### Added
* `Render::Copy()` overload which takes target `Point` instead of a `Rect`
* New method `Render::FillCopy()` which fills target rect with repeated texture
* Improved UTF-16 font rendering support
* CMake module file

## 0.7.1 - 2015-03-27
### Fixed
* Miscellaneous style, documentation and build system fixes

## 0.7.0 - 2015-01-22
### Added
* More `Texture`, `Renderer` (both complete now) and `Window` methods
* New methods: `Point::Clamp()`, `Point::Wrap()`, `Rect::Extend()`, `Rect::IntersectLine()`
* STL stream output for `Point` and `Rect` (as in `std::cout << Rect(10, 20, 30 40);`)

### Changed
* Most setters now return reference to self to allow method chaining
* Exception now stores both SDL error and name of function which caused it; `what()` message now includes these both in a readable way, so SDL2pp exceptions may be conveniently handled with `catch (std::exception&)`
* pkg-config file now provides SDL libraries along with SDL2pp, so users don't need to care of SDL2 flags in addition to SDL2pp's

### Removed
* Deprecated `Point` and `Rect` methods: `Null()`, `IsNull()`, `Get()`

### Fixed
* Use move, not copy in constructing `RWops` from `CustomRWops`-derived class

## 0.6.0 - 2015-01-11
### Added
* [Doxygen](http://doxygen.org/) documentation for the whole library
* Wrapper around [SDL_image](https://www.libsdl.org/projects/SDL_image/) initialization/deinitialization: `SDLImage` class
* `Surface``, a wrapepr for [SDL_Surface](https://wiki.libsdl.org/SDL_Surface) including [SDL_image](https://www.libsdl.org/projects/SDL_image/) support. It's now also possible to construct `Texture` from `Surface`.
* Bunch of constructors from existing SDL objects (e.g. `Window::Window(SDL_Window*)`) for `Point`, `Rect`, `Window`, `Renderer`, `Texture`
* Complete [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/) support
* Consistent `GetWidth()`/`GetHeight()`/`GetSize()` for `Texture` and `Surface`
* More operators, constructors and methods for `Point` and `Rect`

### Fixed
* Added proper error checking for SDL_image-using Texture constructors
* Multiple fixes in build system

## 0.5.2 - 2014-12-30
### Fixed
* Added missing include file to installation

## 0.5.1 - 2014-12-27
### Fixed
* Potential problems with SDL2 error handling

## 0.5.0 - 2014-12-26
### Added
* `AudioDevice::LockHandle` is now copyable
* `Rect` now has `+` `-` `+=` `-=` operators to offset it by a `Point`
* `Optional` class to pass optional values
* Possibility to use c++1y standard and detection of available useful c++1y features with c++11
* Default argument for `Texture::Lock()`
* Bunch of `Window` functions: `Window::Maximize()`, `Window::Minimize()`, `Window::Hide()`, `Window::Restore()`, `Window::Raise()`, `Window::Show()`, `Window::SetFullscreen()`, `Window::SetSize()`
* More granular build options for tests and examples

### Changed
* `Point` and `Rect` no longer have invalid (null) states and are now directly derived from [SDL_Point](https://wiki.libsdl.org/SDL_Point) and [SDL_Rect](https://wiki.libsdl.org/SDL_Rect) structures. In places where null states were usable (e.g. usually null `Rect` would mean "whole area", like in `Texture::Lock()`), `Optional` class is now used. Use `NullOpt` instead of `Point::Null()` and `Rect::Null()`

## 0.4.0 - 2014-12-19
### Added
* `StreamRWops` which works with STL streams
* `AudioDevice` and `Texture` `LockHandle`s now have empty constructors and may be initialized after construction
* `RWops` `(Read|Write)(LE|BE)(16|32|64)` methods
* pkg-config file

### Changed
* Plain `ContainerRWops` is now able to work with both const and mutable containers
* Audio callback is now tied to `AudioDevice`, not `AudioSpec`, which is cleaner and easier to use

### Removed
* `ConstContainerRWops` which is no longer needed

### Fixed
* Exception safety when changing audio callback
* Made `-Werror` flag conditional for user convenience

## 0.3.0 - 2014-11-30
### Added
* [SDL audio](https://wiki.libsdl.org/CategoryAudio) functionality

### Fixed
* Proper self-assignment handling in move assignment operators

## 0.2.0 - 2014-11-25
### Added
* Getters for `Texture` properties: `Texture::GetWidth()`, `Texture::GetHeight()`, `Texture::GetFormat()`, `Texture::GetAccess()`
* `Texture` locking
* New `Rect` method `Rect::Contains()` to check if it contains a `Point`

## 0.1.1 - 2014-09-09
### Added
* Installation
* Library version

## 0.1.0 - 2014-09-05
### Added
* [SDL2_image](https://www.libsdl.org/projects/SDL_image/) support
* `RWops` support
* New `Renderer` methods: `Renderer::SetClipRect()`, `Renderer::SetScale()`, `Renderer::SetViewport()`, `Renderer::TargetSupported()`
* New `SDL` methods: `SDL::WasInit()`, `SDL::InitSubsystem()`, `SDL::QuitSubSystem()`
* Basic MSVC support
* Arithmetic operators for `Point`

### Fixed
* GUI tests which are sensible to OpenGL implementation-specific behavior are no longer fatal

## 0.0.2 - 2014-02-11
### Added
* Unit tests
* New `Window` methods: `Window::GetSize()`, `Window::GetWidth()`, `Window::GetHeight()`, `Window::SetTitle()`
* New `Renderer` method: `Renderer::ReadPixels()`
* `Point` and `Rect` setters and comparison operators

## 0.0.1 - 2014-02-01
### Added
* Initial release supporting basic `Window`, `Renderer`, `Texture`, `Rect` and `Point` handling
