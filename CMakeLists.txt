cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# meta
project(libSDL2pp LANGUAGES CXX VERSION 0.18.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	option(SDL2PP_WITH_IMAGE "Enable SDL2_image support" ON)
	option(SDL2PP_WITH_TTF "Enable SDL2_ttf support" ON)
	option(SDL2PP_WITH_MIXER "Enable SDL2_mixer support" ON)

	option(SDL2PP_WITH_EXAMPLES "Build examples" ON)
	option(SDL2PP_WITH_TESTS "Build tests" ON)
	option(SDL2PP_ENABLE_LIVE_TESTS "Enable live tests (require X11 display and audio device)" ON)
	option(SDL2PP_STATIC "Build static library instead of shared one" OFF)
else()
	# please set SDL2PP_WITH_IMAGE, SDL2PP_WITH_TTF, SDL2PP_WITH_MIXER in parent project as needed
endif()

# depends
find_package(SDL2 REQUIRED)
set(SDL2_ALL_LIBRARIES SDL2::SDL2)
set(SDL2_ALL_PKGCONFIG_MODULES sdl2)

if(TARGET SDL2::SDL2main)
	set(SDL2_ALL_LIBRARIES SDL2::SDL2main ${SDL2_ALL_LIBRARIES})
endif()

if(MINGW)
	set(MINGW32_LIBRARY "mingw32" CACHE STRING "mingw32 library")
	set(SDL2PP_EXTRA_LIBRARIES ${MINGW32_LIBRARY} ${SDL2PP_EXTRA_LIBRARIES})
	set(SDL2PP_EXTRA_PKGCONFIG_LIBRARIES "-l${MINGW32_LIBRARY} ${SDL2PP_EXTRA_PKGCONFIG_LIBRARIES}")
endif()

if(SDL2PP_WITH_IMAGE)
	find_package(SDL2_image REQUIRED)
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} SDL2_image::SDL2_image)
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_image")
else()
	message(STATUS "SDL2_image support disabled")
endif()

if(SDL2PP_WITH_TTF)
	find_package(SDL2_ttf REQUIRED)
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} SDL2_ttf::SDL2_ttf)
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_ttf")
else()
	message(STATUS "SDL2_ttf support disabled")
endif()

if(SDL2PP_WITH_MIXER)
	find_package(SDL2_mixer REQUIRED)
	set(SDL2_ALL_LIBRARIES ${SDL2_ALL_LIBRARIES} SDL2_mixer::SDL2_mixer)
	set(SDL2_ALL_PKGCONFIG_MODULES "${SDL2_ALL_PKGCONFIG_MODULES} SDL2_mixer")
else()
	message(STATUS "SDL2_mixer support disabled")
endif()

# compiler flags & definitions
#if(MSVC)
#	set(SDL2PP_WARNINGS "${SDL2PP_WARNINGS} /W3")
#else()
#	set(SDL2PP_WARNINGS "${SDL2PP_WARNINGS} -Wall -Wextra -pedantic")
#
#	if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#		set(SDL2PP_WARNINGS "${SDL2PP_WARNINGS} -Wmissing-prototypes -Wtautological-compare -Wshorten-64-to-32")
#
#		# For adventurous
#		#set(SDL2PP_WARNINGS "${SDL2PP_WARNINGS} -Weverything -Wno-c++98-compat -Wno-padded")
#	endif()
#endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SDL2PP_WARNINGS}")

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

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
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

	# install
	include(GNUInstallDirs)

	install(TARGETS SDL2pp
		EXPORT SDL2pp-targets
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
	install(
		FILES
			${LIBRARY_HEADERS}
			${PROJECT_BINARY_DIR}/SDL2pp/Config.hh
			${PROJECT_BINARY_DIR}/SDL2pp/Export.hh
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SDL2pp
	)

	configure_file(sdl2pp.pc.in sdl2pp.pc @ONLY)
	install(
		FILES
			${PROJECT_BINARY_DIR}/sdl2pp.pc
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
	)

	configure_file(cmake/SDL2ppConfig.cmake.in cmake/SDL2ppConfig.cmake @ONLY)
	install(EXPORT SDL2pp-targets
		FILE SDL2ppTargets.cmake
		NAMESPACE SDL2pp::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SDL2pp
	)
	install(FILES ${PROJECT_BINARY_DIR}/cmake/SDL2ppConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SDL2pp)
endif()
