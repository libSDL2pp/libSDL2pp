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
			PATH_SUFFIXES
			bitstream-vera
		)
	ENDIF(NOT SDL2PP_EXAMPLE_FONT)
	IF(SDL2PP_EXAMPLE_FONT)
		MESSAGE(STATUS "Using example font: ${SDL2PP_EXAMPLE_FONT}")
	ELSE(SDL2PP_EXAMPLE_FONT)
		MESSAGE(FATAL_ERROR "Cannot find font to use with ttf example (Vera.ttf). You need to either install it, add path to it into examples/CMakeLists.txt (and submit this chnage upstream) or specify path (to any .ttf file) manually with SDL2PP_EXAMPLE_FONT variable")
	ENDIF(SDL2PP_EXAMPLE_FONT)
	ADD_DEFINITIONS(-DEXAMPLE_FONT="${SDL2PP_EXAMPLE_FONT}")
	ADD_EXECUTABLE(ttf ttf.cc)
	TARGET_LINK_LIBRARIES(ttf SDL2pp)
ENDIF(SDL2PP_WITH_TTF)
