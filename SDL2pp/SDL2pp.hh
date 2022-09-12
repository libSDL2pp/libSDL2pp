/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2013-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

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

#ifndef SDL2PP_SDL2PP_HH
#define SDL2PP_SDL2PP_HH

#include <SDL2pp/Config.hh>

////////////////////////////////////////////////////////////
/// \defgroup general General
///
/// \brief SDL library initialization and shutdown functions
///        and error handling
///
////////////////////////////////////////////////////////////
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Optional.hh>

////////////////////////////////////////////////////////////
/// \defgroup audio Audio
///
/// \brief Audio device management and audio playback
///
////////////////////////////////////////////////////////////
#include <SDL2pp/AudioDevice.hh>
#include <SDL2pp/AudioSpec.hh>
#include <SDL2pp/Wav.hh>

////////////////////////////////////////////////////////////
/// \defgroup graphics Graphics
///
/// \brief Graphics output
///
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
/// \defgroup windows Window management
///
/// \brief Display and window management
///
/// \ingroup graphics
///
////////////////////////////////////////////////////////////
#include <SDL2pp/Window.hh>

////////////////////////////////////////////////////////////
/// \defgroup rendering 2D rendering
///
/// \brief 2D accelerated rendering
///
/// \ingroup graphics
///
////////////////////////////////////////////////////////////
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Color.hh>

////////////////////////////////////////////////////////////
/// \defgroup geometry 2D geometry
///
/// \brief 2D rectangle and point functions
///
/// \ingroup graphics
///
////////////////////////////////////////////////////////////
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Point.hh>

////////////////////////////////////////////////////////////
/// \defgroup io I/O abstraction
///
/// \brief Functions that extend file-like operations onto arbitrary
///        objects such as memory, streams, STL containers etc.
///
////////////////////////////////////////////////////////////
#include <SDL2pp/RWops.hh>
#include <SDL2pp/ContainerRWops.hh>
#include <SDL2pp/StreamRWops.hh>

#ifdef SDL2PP_WITH_TTF
////////////////////////////////////////////////////////////
/// \defgroup ttf SDL_ttf
///
/// \brief Text rendering through SDL_ttf library
///
////////////////////////////////////////////////////////////
#	include <SDL2pp/SDLTTF.hh>
#	include <SDL2pp/Font.hh>
#endif

#ifdef SDL2PP_WITH_IMAGE
////////////////////////////////////////////////////////////
/// \defgroup image SDL_image
///
/// \brief Functions that are specific to SDL_image library
///
////////////////////////////////////////////////////////////
#	include <SDL2pp/SDLImage.hh>
#endif

#ifdef SDL2PP_WITH_MIXER
////////////////////////////////////////////////////////////
/// \defgroup mixer SDL_mixer
///
/// \brief Functions that are specific to SDL_mixer library
///
////////////////////////////////////////////////////////////
#	include <SDL2pp/Chunk.hh>
#	include <SDL2pp/Mixer.hh>
#	include <SDL2pp/Music.hh>
#	include <SDL2pp/SDLMixer.hh>
#endif

#endif
