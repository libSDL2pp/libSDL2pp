ADD_DEFINITIONS(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

ADD_EXECUTABLE(sprites sprites.cc)
TARGET_LINK_LIBRARIES(sprites SDL2pp)

ADD_EXECUTABLE(lines lines.cc)
TARGET_LINK_LIBRARIES(lines SDL2pp)

ADD_EXECUTABLE(rendertarget rendertarget.cc)
TARGET_LINK_LIBRARIES(rendertarget SDL2pp)

ADD_EXECUTABLE(audio_sine audio_sine.cc)
TARGET_LINK_LIBRARIES(audio_sine SDL2pp)

ADD_EXECUTABLE(audio_wav audio_wav.cc)
TARGET_LINK_LIBRARIES(audio_wav SDL2pp)

IF(SDL2PP_WITH_IMAGE)
	ADD_EXECUTABLE(image image.cc)
	TARGET_LINK_LIBRARIES(image SDL2pp)
ENDIF(SDL2PP_WITH_IMAGE)

IF(SDL2PP_WITH_TTF)
	IF(NOT SDL2PP_EXAMPLE_FONT)
		FIND_FILE(SDL2PP_EXAMPLE_FONT Vera.ttf
			PATHS
			/usr/local/lib/X11/fonts
			/usr/lib/X11/fonts
			/usr/share/fonts/truetype
			/usr/share/fonts/TTF
			/usr/local/share/fonts/X11/TTF
			/usr/share/fonts/X11/TTF
			PATH_SUFFIXES
			bitstream-vera
			ttf-bitstream-vera
		)
	ENDIF(NOT SDL2PP_EXAMPLE_FONT)

	IF(SDL2PP_EXAMPLE_FONT)
		MESSAGE(STATUS "Using example font: ${SDL2PP_EXAMPLE_FONT}")
		ADD_DEFINITIONS(-DEXAMPLE_FONT="${SDL2PP_EXAMPLE_FONT}")
		ADD_EXECUTABLE(ttf ttf.cc)
		TARGET_LINK_LIBRARIES(ttf SDL2pp)
	ELSE(SDL2PP_EXAMPLE_FONT)
		MESSAGE(WARNING "Cannot find font to use with ttf example (Vera.ttf), ttf example will not be built.\nYou need to install the font if it's not installed, else you may need to either add path to the font into list in examples/CMakeLists.txt or manually specify path to any .ttf file with SDL2PP_EXAMPLE_FONT CMake variable")
	ENDIF(SDL2PP_EXAMPLE_FONT)
ENDIF(SDL2PP_WITH_TTF)
