# simple command-line tests
SET(CLI_TESTS
	test_color
	test_color_constexpr
	test_error
	test_optional
	test_pointrect
	test_pointrect_constexpr
	test_rwops
	test_wav
)

# live tests require X11 display and/or audio output
SET(LIVE_TESTS
	live_audiodevice
	live_rendering
	live_window
)

IF(SDL2PP_WITH_MIXER)
	SET(LIVE_TESTS ${LIVE_TESTS}
		live_mixer
	)
ENDIF(SDL2PP_WITH_MIXER)

IF(SDL2PP_WITH_IMAGE)
	SET(CLI_TESTS ${CLI_TESTS}
		test_surface
	)
ENDIF(SDL2PP_WITH_IMAGE)

IF(SDL2PP_WITH_TTF)
	SET(CLI_TESTS ${CLI_TESTS}
		test_font
	)
ENDIF(SDL2PP_WITH_TTF)

ADD_DEFINITIONS(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

# header tests: these just include specific headers to check if
# they are compilable (e.g., includes and forward declarations are
# complete and do not require extra includes)
FOREACH(HEADER ${LIBRARY_HEADERS})
	STRING(REGEX REPLACE [^a-zA-Z0-9] _ HEADER_NORMALIZED ${HEADER})
	CONFIGURE_FILE(header_test.cc.in ${HEADER_NORMALIZED}_test.cc)
	ADD_EXECUTABLE(${HEADER_NORMALIZED}_test ${HEADER_NORMALIZED}_test.cc)
	TARGET_LINK_LIBRARIES(${HEADER_NORMALIZED}_test ${SDL2PP_LIBRARIES})
ENDFOREACH(HEADER ${TESTS})

FOREACH(TEST ${CLI_TESTS})
	ADD_EXECUTABLE(${TEST} ${TEST}.cc)
	TARGET_LINK_LIBRARIES(${TEST} ${SDL2PP_LIBRARIES})
	ADD_TEST(${TEST} ${TEST})
ENDFOREACH(TEST ${TESTS})

FOREACH(TEST ${LIVE_TESTS})
	ADD_EXECUTABLE(${TEST} ${TEST}.cc)
	TARGET_LINK_LIBRARIES(${TEST} ${SDL2PP_LIBRARIES})
	IF(SDL2PP_ENABLE_LIVE_TESTS)
		ADD_TEST(${TEST} ${TEST})
	ENDIF(SDL2PP_ENABLE_LIVE_TESTS)
ENDFOREACH(TEST ${TESTS})
