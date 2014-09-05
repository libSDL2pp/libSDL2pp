# header tests: these just include specific headers to check if
# they are compilable (e.g., includes and forward declarations are
# complete and do not require extra includes)
SET(HEADER_TESTS
	header_exception
	header_point
	header_rect
	header_renderer
	header_rwops
	header_extrarwops
	header_sdl
	header_sdl2pp
	header_texture
	header_window
)

# simple command-line tests
SET(CLI_TESTS
	test_pointrect
	test_rwops
)

# tests which test graphics functionality and thus requre working
# and OpenGL-enabled X11 display
SET(GUI_TESTS
	gui_rendering
)

ADD_DEFINITIONS(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

FOREACH(TEST ${HEADER_TESTS})
	ADD_EXECUTABLE(${TEST} ${TEST}.cc)
ENDFOREACH(TEST ${TESTS})

FOREACH(TEST ${CLI_TESTS})
	ADD_EXECUTABLE(${TEST} ${TEST}.cc)
	TARGET_LINK_LIBRARIES(${TEST} SDL2pp)
	ADD_TEST(${TEST} ${TEST})
ENDFOREACH(TEST ${TESTS})

FOREACH(TEST ${GUI_TESTS})
	ADD_EXECUTABLE(${TEST} ${TEST}.cc)
	TARGET_LINK_LIBRARIES(${TEST} SDL2pp)
	IF(RUN_GUI_TESTS)
		ADD_TEST(${TEST} ${TEST})
	ENDIF(RUN_GUI_TESTS)
ENDFOREACH(TEST ${TESTS})
