cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# meta
project(libSDL2pp)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SDL2PP_MAJOR_VERSION 0)
set(SDL2PP_MINOR_VERSION 16)
set(SDL2PP_PATCH_VERSION 0)

set(SDL2PP_VERSION "${SDL2PP_MAJOR_VERSION}.${SDL2PP_MINOR_VERSION}.${SDL2PP_PATCH_VERSION}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# there are functions present on wiki, but not yet in stable SDL2 releases;
# we hide these under following options
option(SDL2PP_WITH_WERROR "Make warnings fatal" OFF)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	OPTION(SDL2PP_WITH_IMAGE "Enable SDL2_image support" ON)
	OPTION(SDL2PP_WITH_TTF "Enable SDL2_ttf support" ON)
	OPTION(SDL2PP_WITH_MIXER "Enable SDL2_mixer support" ON)
else()
	# please set SDL2PP_WITH_IMAGE, SDL2PP_WITH_TTF, SDL2PP_WITH_MIXER in parent project as needed
endif()

# depends
find_package(SDL2 REQUIRED)
set(SDL2_ALL_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
set(SDL2_ALL_LIBRARIES ${SDL2_LIBRARY})
set(SDL2_ALL_PKGCONFIG_MODULES sdl2)
set(SDL2PP_EXTRA_LIBRARIES ${SDL2MAIN_LIBRARY})
set(SDL2PP_EXTRA_PKGCONFIG_LIBRARIES ${SDL2MAIN_LIBRARY})

if(MINGW)
	set(MINGW32_LIBRARY "mingw32" CACHE STRING "mingw32 library")
	set(SDL2PP_EXTRA_LIBRARIES ${MINGW32_LIBRARY} ${SDL2PP_EXTRA_LIBRARIES})
	set(SDL2PP_EXTRA_PKGCONFIG_LIBRARIES "-l${MINGW32_LIBRARY} ${SDL2PP_EXTRA_PKGCONFIG_LIBRARIES}")
endif()

if(SDL2PP_WITH_IMAGE)
	find_package(SDL2_image REQUIRED)
	set(SDL2_ALL_INCLUDE_DIRS ${SDL2_ALL_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} ${SDL2_IMAGE_LIBRARY})
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_image")
else()
	message(STATUS "SDL2_image support disabled")
endif()

if(SDL2PP_WITH_TTF)
	find_package(SDL2_ttf REQUIRED)
	set(SDL2_ALL_INCLUDE_DIRS ${SDL2_ALL_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} ${SDL2_TTF_LIBRARY})
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_ttf")
else()
	message(STATUS "SDL2_ttf support disabled")
endif()

if(SDL2PP_WITH_MIXER)
	find_package(SDL2_mixer REQUIRED)
	set(SDL2_ALL_INCLUDE_DIRS ${SDL2_ALL_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIR})
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} ${SDL2_MIXER_LIBRARY})
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_mixer")
else()
	message(STATUS "SDL2_mixer support disabled")
endif()

# compiler flags & definitions
if(MSVC)
	set(SDL2PP_WARNINGS "${SDL2PP_WARNINGS} /W3")
	set(SDL2PP_WERROR_FLAG "/WX")
else()
	set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
	set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
	set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")

	set(SDL2PP_WARNINGS "${SDL2PP_WARNINGS} -Wall -Wextra -pedantic")
	set(SDL2PP_WERROR_FLAG "-Werror")

	include(AppendCXXFlagIfSupported)

	# enable for more cleanups
	#APPEND_CXX_FLAG_IF_SUPPORTED(-Weverything SDL2PP_WARNINGS)

	# always enables some -Weverything warnings
	APPEND_CXX_FLAG_IF_SUPPORTED(-Wmissing-prototypes SDL2PP_WARNINGS)
	APPEND_CXX_FLAG_IF_SUPPORTED(-Wtautological-compare SDL2PP_WARNINGS)
	APPEND_CXX_FLAG_IF_SUPPORTED(-Wshorten-64-to-32 SDL2PP_WARNINGS)

	# disable some -Weverything warnings
	#APPEND_CXX_FLAG_IF_SUPPORTED(-Wno-c++98-compat SDL2PP_WARNINGS)
	#APPEND_CXX_FLAG_IF_SUPPORTED(-Wno-padded SDL2PP_WARNINGS)
endif()

list(REMOVE_DUPLICATES SDL2_ALL_INCLUDE_DIRS)

include_directories(BEFORE ${PROJECT_SOURCE_DIR})
include_directories(SYSTEM ${SDL2_ALL_INCLUDE_DIRS})

include(CheckCompile)
check_compile(
	SDL2PP_WITH_EXPERIMENTAL_OPTIONAL
	"#include <experimental/optional>\nint main() { std::experimental::optional<int> o; return !o; }"
	"experimental/optional header"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2PP_WARNINGS}")

if(SDL2PP_WITH_WERROR)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2PP_WERROR_FLAG}")
endif()

# config.h
configure_file(
	SDL2pp/Config.hh.in
	SDL2pp/Config.hh
)

include_directories(BEFORE ${PROJECT_BINARY_DIR})

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

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	# options
	option(SDL2PP_WITH_EXAMPLES "Build examples" ON)
	option(SDL2PP_WITH_TESTS "Build tests" ON)
	option(SDL2PP_ENABLE_LIVE_TESTS "Enable live tests (require X11 display and audio device)" ON)
	option(SDL2PP_STATIC "Build static library instead of shared one" OFF)

	# library
	if(SDL2PP_STATIC)
		ADD_LIBRARY(SDL2pp STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	else()
		ADD_LIBRARY(SDL2pp SHARED ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
		TARGET_LINK_LIBRARIES(SDL2pp ${SDL2_ALL_LIBRARIES})
		SET_TARGET_PROPERTIES(SDL2pp PROPERTIES VERSION 8.3.0 SOVERSION 8)
	endif()

	generate_export_header(SDL2pp EXPORT_FILE_NAME SDL2pp/Export.hh)

	set(SDL2PP_LIBRARIES ${SDL2PP_EXTRA_LIBRARIES} SDL2pp ${SDL2_ALL_LIBRARIES})

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

	# pkgconfig and cmake modules
	set(CMAKEMODDIR share/cmake/Modules CACHE STRING "directory where to install cmake module")
	set(PKGCONFIGDIR lib/pkgconfig CACHE STRING "directory where to install pkg-config files")
	if(CMAKE_SYSTEM_NAME MATCHES "FreeBSD" OR CMAKE_SYSTEM_NAME MATCHES "DragonFly")
		SET(PKGCONFIGDIR libdata/pkgconfig)
	endif()

	include(Join)

	JOIN_QUOTED("${SDL2PP_EXTRA_LIBRARIES}" SDL2PP_EXTRA_LIBRARIES_STR)
	JOIN_QUOTED("${SDL2_ALL_LIBRARIES}" SDL2_ALL_LIBRARIES_STR)
	JOIN_QUOTED("${SDL2_ALL_INCLUDE_DIRS}" SDL2_ALL_INCLUDE_DIRS_STR)

	configure_file(
		sdl2pp.pc.in
		sdl2pp.pc
		@ONLY
	)

	configure_file(
		FindSDL2PP.cmake.in
		FindSDL2PP.cmake
		@ONLY
	)

	# install
	install(FILES
		${LIBRARY_HEADERS}
		${PROJECT_BINARY_DIR}/SDL2pp/Config.hh
		${PROJECT_BINARY_DIR}/SDL2pp/Export.hh
		DESTINATION include/SDL2pp
	)
	install(FILES ${LIBRARY_EXTERNAL_HEADERS} DESTINATION include/SDL2pp/external)
	install(TARGETS SDL2pp
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
	install(FILES ${PROJECT_BINARY_DIR}/sdl2pp.pc DESTINATION ${PKGCONFIGDIR})
	install(FILES ${PROJECT_BINARY_DIR}/FindSDL2PP.cmake DESTINATION ${CMAKEMODDIR})

	message(STATUS "libSDL2pp ${SDL2PP_VERSION} standalone build")
else()
	# library
	add_library(SDL2pp STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
	generate_export_header(SDL2pp EXPORT_FILE_NAME SDL2pp/Export.hh)

	# provide variables to parent
	set(SDL2PP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${SDL2_ALL_INCLUDE_DIRS} PARENT_SCOPE)
	set(SDL2PP_LIBRARIES ${SDL2PP_EXTRA_LIBRARIES} SDL2pp ${SDL2_ALL_LIBRARIES} PARENT_SCOPE)

	message(STATUS "libSDL2pp ${SDL2PP_VERSION} bundled build")
endif()
