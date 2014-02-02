# header tests: these just include specific headers to check if
# they are compilable (e.g., includes and forward declarations are
# complete and do not require extra includes)
SET(HEADER_TESTS
	hdr_exception
	hdr_point
	hdr_rect
	hdr_renderer
	hdr_sdl
	hdr_sdl2pp
	hdr_texture
	hdr_window
)

FOREACH(TEST ${HEADER_TESTS})
	ADD_EXECUTABLE(${TEST} ${TEST}.cc)
ENDFOREACH(TEST ${TESTS})
