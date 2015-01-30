# simple command-line tests
SET(CLI_TESTS
	test_pointrect
	test_rwops
	test_optional
	test_error
)

# tests which test graphics functionality and thus requre working
# and OpenGL-enabled X11 display
SET(GUI_TESTS
	gui_rendering
)

# disable self-move warning: it's deliberately used in tests
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-Wno-self-move" COMPILER_SUPPORTS_WNOSELFMOVE)
IF(COMPILER_SUPPORTS_WNOSELFMOVE)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-self-move")
ENDIF(COMPILER_SUPPORTS_WNOSELFMOVE)

ADD_DEFINITIONS(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

# header tests: these just include specific headers to check if
# they are compilable (e.g., includes and forward declarations are
# complete and do not require extra includes)
FOREACH(HEADER ${LIBRARY_HEADERS})
	STRING(REGEX REPLACE [^a-zA-Z0-9] _ HEADER_NORMALIZED ${HEADER})
	CONFIGURE_FILE(header_test.cc.in ${HEADER_NORMALIZED}_test.cc)
	ADD_EXECUTABLE(${HEADER_NORMALIZED}_test ${HEADER_NORMALIZED}_test.cc)
ENDFOREACH(HEADER ${TESTS})

FOREACH(TEST ${CLI_TESTS})
	ADD_EXECUTABLE(${TEST} ${TEST}.cc)
	TARGET_LINK_LIBRARIES(${TEST} SDL2pp)
	ADD_TEST(${TEST} ${TEST})
ENDFOREACH(TEST ${TESTS})

FOREACH(TEST ${GUI_TESTS})
	ADD_EXECUTABLE(${TEST} ${TEST}.cc)
	TARGET_LINK_LIBRARIES(${TEST} SDL2pp)
	IF(SDL2PP_ENABLE_GUI_TEST)
		ADD_TEST(${TEST} ${TEST})
	ENDIF(SDL2PP_ENABLE_GUI_TEST)
ENDFOREACH(TEST ${TESTS})
