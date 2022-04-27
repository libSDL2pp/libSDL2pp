# simple command-line tests
set(CLI_TESTS
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
set(LIVE_TESTS
	live_audiodevice
	live_rendering
	live_window
)

if(SDL2PP_WITH_MIXER)
	set(LIVE_TESTS ${LIVE_TESTS}
		live_mixer
	)
endif()

if(SDL2PP_WITH_IMAGE)
	set(CLI_TESTS ${CLI_TESTS}
		test_surface
	)
endif()

if(SDL2PP_WITH_TTF)
	set(CLI_TESTS ${CLI_TESTS}
		test_font
	)
endif()

add_definitions(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

# header tests: these just include specific headers to check if
# they are compilable (e.g., includes and forward declarations are
# complete and do not require extra includes)
foreach(HEADER ${LIBRARY_HEADERS})
	string(REGEX REPLACE [^a-zA-Z0-9] _ HEADER_NORMALIZED ${HEADER})
	configure_file(header_test.cc.in ${HEADER_NORMALIZED}_test.cc)
	add_executable(${HEADER_NORMALIZED}_test ${HEADER_NORMALIZED}_test.cc)
	target_link_libraries(${HEADER_NORMALIZED}_test SDL2pp::SDL2pp)
endforeach()

foreach(TEST ${CLI_TESTS})
	add_executable(${TEST} ${TEST}.cc)
	target_link_libraries(${TEST} SDL2pp::SDL2pp)
	add_test(${TEST} ${TEST})
endforeach()

foreach(TEST ${LIVE_TESTS})
	add_executable(${TEST} ${TEST}.cc)
	target_link_libraries(${TEST} SDL2pp::SDL2pp)
	if(SDL2PP_ENABLE_LIVE_TESTS)
		add_test(${TEST} ${TEST})
	endif()
endforeach()
