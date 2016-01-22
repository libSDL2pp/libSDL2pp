# Change Log
All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [0.11.0] - 2015-11-30
### Added
* GetDrawable{Width,Height,Size} Window functions (@csoren)
* Point and Rect less-than operators and std::hash support
* Rect: more methods, wider constexpr support

### Fixed
* Rect documentation fixes
* Unused variable warnings (@vladimirgamalian)
* Incorrect return value handling in Surface::SetClipRect

## [0.10.0] - 2015-10-14
### Fixed
* Improved cygwin compatibility
* Missing SDL2pp::SDL methods
* Return and argument types to match upstream API (SDL2pp::Window, SDL2pp::Font, SDL2pp::Mixer)
* Infinite loop in StreamRWops
* Documentation improvements
* Build without SDL_mixer support

## [0.9.0] - 2015-09-07
### Added
* SDL_mixer support
* more Point operators: remainder; multiplication, division and remainder counterparts which take another Point
* Point and Rect better inlining and constexpr support
* Surface::GetFormat()
* Texture::Update() taking pixels from Surface

## [0.8.2] - 2015-07-28
### Fixed
* Add missing Font::IsGlyphProvided implementation (@vladimirgamalian)
* Fix glyph rectangle calculation in Font::GetGlyphRect (@vladimirgamalian)

## [0.8.1] - 2015-06-29
### Fixed
* Use correct type flags in RWops::Size, fixing mingw build (@vladimirgamalian)

## [0.8.0] - 2015-06-10
### Added
* Render::Copy() overload which takes target Point instead of a Rect
* Render::FillCopy() which fills target rect with repeated texture
* Improved UTF-16 font rendering support
* CMake module file

## [0.7.1] - 2015-03-27
### Fixed
* Miscellaneous style, documentation and build system fixes

## [0.7.0] - 2015-01-22
### Added
* More Texture, Renderer (both complete now) and Window methods
* Point::Clamp(), Point::Wrap(), Rect::Extend(), Rect::IntersectLine()
* Stream output for Point and Rect

### Changed
* Most setters now return reference to self to allow method chaining
* Exception now stores both SDL error and name of function which caused it; what() message now contains these both, so SDL2pp exceptions may be conveniently handled with ```catch (std::exception&)```
* pkg-config file now provides SDL libraries along with SDL2pp, so users don't need to care of SDL2 flags in addition to SDL2pp's.

### Removed
* Deprecated Point and Rect methods (Null(), IsNull(), Get())

### Fixed
* Use move, not copy in constructing RWops from CustomRWops-derived class

## [0.6.0] - 2015-01-11

### Added
* Doxygen documentation for the whole library
* Wrapper over SDL_image initialization/deinitialization
* SDL_Surface wrapper with SDL_image support; it's now possible to construct Texture from Surface
* Bunch of constructors from existing SDL objects (e.g. Window(SDL_Window*)) for Point, Rect, Window, Renderer, Texture
* Complete SDL_ttf support
* Consistent GetWidth()/GetHeight()/GetSize() for Texture and Surface
* More operators, constructors and methods for Point and Rect

### Fixed
* Added proper error checking for SDL_image-using Texture constructors
* Multiple fixes in build system

## [0.5.2] - 2014-12-30
### Fixed
* Added missing include file to installation

## [0.5.1] - 2014-12-27
### Fixed
* Potential problems with SDL2 error handling

## [0.5.0] - 2014-12-26
### Added
* AudioDevice::LockHandle is now copyable
* + - += -= operators supported to offset a Rect by a Point
* Optional class to pass optional values
* possibility to use c++1y and detection of available useful c++1y features with c++11
* default argument for Texture::Lock()
* bunch of Window functions (Maximize(), Minimize(), Hide(), Restore(), Raise(), Show(), SetFullscreen(), SetSize())
* More granular build options for tests and examples

### Changed
* Point and Rect no longer have invalid (Null) states and are now directly derived from SDL_Point and SDL_Rect. In places where null states were usable (e.g. usually null Rect would mean "whole area", like in Texture::Lock()), Optional is now used. Use SDL2pp::NullOpt instead of SDL2pp::(Point|Rect)::Null().

## [0.4.0] - 2014-12-19
### Added
* StreamRWops which work with STL streams
* AudioDevice and Texture LockHandle's now have empty constructors, so you may create them in one place and initialize later
* (Read|Write)(LE|BE)(16|32|64) RWops functions
* pkg-config file

### Changed
* Plain ContainerRWops is able to work with both const and non-const containers, so ConstContainerRWops class is no longer needed
* Audio callback is now tied to AudioDevice, not AudioSpec. This is cleaner and easier to use.

### Fixed
* Exception safety when changing audio callback
* Make -Werror conditional for user convenience

## [0.3.0] - 2014-11-30
### Added
* SDL audio functionality

### Fixed
* Proper self-assignment handling in move assignment operators

## [0.2.0] - 2014-11-25
### Added
* Getters for texture properties (width/height/format/access)
* Texture locking
* Rect method to check if it contains a Point

## [0.1.1] - 2014-09-09
### Added
* Installation
* Library version

## [0.1.0] - 2014-09-05
### Added
* SDL2_image support
* RWops
* New Renderer methods: SetClipRect(), SetScale(), SetViewport(), TargetSupported()
* New SDL methods: WasInit(), InitSubsystem(), QuitSubSystem()
* Basic MSVC support
* Arithmetic operators for Point

### Fixed
* GUI tests which are sensible to OpenGL implementation behavior are no longer fatal

## [0.0.2] - 2014-02-11
### Added
* Tests
* New Window methods: GetSize(), GetWidth(), GetHeight(), SetTitle()
* New Renderer method: ReadPixels()
* Point and Rect setters and comparison operators

## [0.0.1] - 2014-02-01
### Added
* Initial release supporting basic Window, Renderer, Texture, Rect and Point handling.
