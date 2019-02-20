cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# meta
project(libSDL2pp)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SDL2PP_VERSION_MAJOR 0)
set(SDL2PP_VERSION_MINOR 17)
set(SDL2PP_VERSION_PATCH 0)

set(SDL2PP_VERSION "${SDL2PP_VERSION_MAJOR}.${SDL2PP_VERSION_MINOR}.${SDL2PP_VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(SDL2PP_BUNDLED OFF)
	set(SDL2PP_STANDALONE ON)
else()
	set(SDL2PP_BUNDLED ON)
	set(SDL2PP_STANDALONE OFF)
endif()


if(SDL2PP_STANDALONE)
	option(SDL2PP_WITH_IMAGE "Enable SDL2_image support" ON)
	option(SDL2PP_WITH_TTF "Enable SDL2_ttf support" ON)
	option(SDL2PP_WITH_MIXER "Enable SDL2_mixer support" ON)

	option(SDL2PP_WITH_EXAMPLES "Build examples" ON)
	option(SDL2PP_WITH_TESTS "Build tests" ON)
	option(SDL2PP_ENABLE_LIVE_TESTS "Enable live tests (require X11 display and audio device)" ON)
	option(SDL2PP_STATIC "Build static library instead of shared one" OFF)
else()
	set(SDL2PP_STATIC ON CACHE BOOL "Build static library instead of shared one")
	# please set SDL2PP_WITH_IMAGE, SDL2PP_WITH_TTF, SDL2PP_WITH_MIXER in parent project as needed
endif()

# depends
find_package(SDL2 REQUIRED)
set(SDL2_ALL_LIBRARIES SDL2::SDL2)
set(SDL2_ALL_PKGCONFIG_MODULES sdl2)

if(MINGW)
	set(MINGW32_LIBRARY "mingw32" CACHE STRING "mingw32 library")
	set(SDL2PP_EXTRA_LIBRARIES ${MINGW32_LIBRARY} ${SDL2PP_EXTRA_LIBRARIES})
	set(SDL2PP_EXTRA_PKGCONFIG_LIBRARIES "-l${MINGW32_LIBRARY} ${SDL2PP_EXTRA_PKGCONFIG_LIBRARIES}")
endif()

if(SDL2PP_WITH_IMAGE)
	find_package(SDL2_image REQUIRED)
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} SDL2::SDL2_image)
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_image")
else()
	message(STATUS "SDL2_image support disabled")
endif()

if(SDL2PP_WITH_TTF)
	find_package(SDL2_ttf REQUIRED)
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} SDL2::SDL2_ttf)
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_ttf")
else()
	message(STATUS "SDL2_ttf support disabled")
endif()

if(SDL2PP_WITH_MIXER)
	find_package(SDL2_mixer REQUIRED)
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} SDL2::SDL2_mixer)
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_mixer")
else()
	message(STATUS "SDL2_mixer support disabled")
endif()

# compiler flags & definitions
include(CheckCXXSourceCompiles)

set(CMAKE_REQUIRED_FLAGS -std=c++11)  # hack, as CMAKE_CXX_STANDARD is not propagated

check_cxx_source_compiles(
	"#include <optional>\nint main() { std::optional<int> o; return !o; }"
	SDL2PP_WITH_STD_OPTIONAL
)

check_cxx_source_compiles(
	"#include <experimental/optional>\nint main() { std::experimental::optional<int> o; return !o; }"
	SDL2PP_WITH_EXPERIMENTAL_OPTIONAL
)

# config.h
configure_file(
	SDL2pp/Config.hh.in
	SDL2pp/Config.hh
)

# sources
set(LIBRARY_SOURCES
	SDL2pp/AudioDevice.cc
	SDL2pp/AudioLock.cc
	SDL2pp/AudioSpec.cc
	SDL2pp/Color.cc
	SDL2pp/Exception.cc
	SDL2pp/Point.cc
	SDL2pp/RWops.cc
	SDL2pp/Rect.cc
	SDL2pp/Renderer.cc
	SDL2pp/SDL.cc
	SDL2pp/Surface.cc
	SDL2pp/SurfaceLock.cc
	SDL2pp/Texture.cc
	SDL2pp/TextureLock.cc
	SDL2pp/Wav.cc
	SDL2pp/Window.cc
)

set(LIBRARY_HEADERS
	SDL2pp/AudioDevice.hh
	SDL2pp/AudioSpec.hh
	SDL2pp/Color.hh
	SDL2pp/ContainerRWops.hh
	SDL2pp/Exception.hh
	SDL2pp/Optional.hh
	SDL2pp/Point.hh
	SDL2pp/RWops.hh
	SDL2pp/Rect.hh
	SDL2pp/Renderer.hh
	SDL2pp/SDL.hh
	SDL2pp/SDL2pp.hh
	SDL2pp/StreamRWops.hh
	SDL2pp/Surface.hh
	SDL2pp/Texture.hh
	SDL2pp/Wav.hh
	SDL2pp/Window.hh
)

set(LIBRARY_EXTERNAL_HEADERS
	SDL2pp/external/libcpp_optional.hh
)

# optional sources
if(SDL2PP_WITH_TTF)
	set(LIBRARY_SOURCES
		${LIBRARY_SOURCES}
		SDL2pp/SDLTTF.cc
		SDL2pp/Font.cc
	)
	set(LIBRARY_HEADERS
		${LIBRARY_HEADERS}
		SDL2pp/SDLTTF.hh
		SDL2pp/Font.hh
	)
endif()

if(SDL2PP_WITH_IMAGE)
	set(LIBRARY_SOURCES
		${LIBRARY_SOURCES}
		SDL2pp/SDLImage.cc
	)
	set(LIBRARY_HEADERS
		${LIBRARY_HEADERS}
		SDL2pp/SDLImage.hh
	)
endif()

if(SDL2PP_WITH_MIXER)
	set(LIBRARY_SOURCES
		${LIBRARY_SOURCES}
		SDL2pp/Chunk.cc
		SDL2pp/Mixer.cc
		SDL2pp/Music.cc
		SDL2pp/SDLMixer.cc
	)
	set(LIBRARY_HEADERS
		${LIBRARY_HEADERS}
		SDL2pp/Chunk.hh
		SDL2pp/Mixer.hh
		SDL2pp/Music.hh
		SDL2pp/SDLMixer.hh
	)
endif()

# targets
include(GenerateExportHeader)

if(SDL2PP_STATIC)
	add_library(SDL2pp STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	set_target_properties(SDL2pp PROPERTIES
		POSITION_INDEPENDENT_CODE ON
	)
else()
	add_library(SDL2pp SHARED ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	set_target_properties(SDL2pp PROPERTIES
		VERSION 8.3.0
		SOVERSION 8
		C_VISIBILITY_PRESET hidden
	)
endif()
target_include_directories(SDL2pp PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
	$<INSTALL_INTERFACE:include>
)
target_link_libraries(SDL2pp PUBLIC ${SDL2_ALL_LIBRARIES})
generate_export_header(SDL2pp EXPORT_FILE_NAME SDL2pp/Export.hh)

add_library(SDL2pp::SDL2pp ALIAS SDL2pp)

if(SDL2PP_STANDALONE)
	# examples and tests
	if(SDL2PP_WITH_EXAMPLES)
		add_subdirectory(examples)
	endif()

	if(SDL2PP_WITH_TESTS)
		enable_testing()
		add_subdirectory(tests)
	endif()

	# doxygen
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doxygen
			${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	endif()

	# pkgconfig module
	configure_file(sdl2pp.pc.in sdl2pp.pc @ONLY)
	configure_file(SDL2ppConfig.cmake.in SDL2ppConfig.cmake @ONLY)

	# install
	set(PKGCONFIGDIR lib/pkgconfig CACHE STRING "directory where to install pkg-config files")
	if(CMAKE_SYSTEM_NAME MATCHES "FreeBSD" OR CMAKE_SYSTEM_NAME MATCHES "DragonFly")
		SET(PKGCONFIGDIR libdata/pkgconfig)
	endif()

	install(FILES
		${LIBRARY_HEADERS}
		${PROJECT_BINARY_DIR}/SDL2pp/Config.hh
		${PROJECT_BINARY_DIR}/SDL2pp/Export.hh
		DESTINATION include/SDL2pp
	)
	install(FILES ${LIBRARY_EXTERNAL_HEADERS} DESTINATION include/SDL2pp/external)
	install(TARGETS SDL2pp
		EXPORT SDL2pp
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
	install(FILES ${PROJECT_BINARY_DIR}/sdl2pp.pc DESTINATION ${PKGCONFIGDIR})

	install(EXPORT SDL2pp NAMESPACE SDL2pp:: DESTINATION lib/cmake/SDL2pp FILE SDL2ppTargets.cmake)
	install(FILES
		${PROJECT_BINARY_DIR}/SDL2ppConfig.cmake
		cmake/FindSDL2.cmake
		cmake/FindSDL2_image.cmake
		cmake/FindSDL2_ttf.cmake
		cmake/FindSDL2_mixer.cmake
		DESTINATION lib/cmake/SDL2pp
	)
endif()
