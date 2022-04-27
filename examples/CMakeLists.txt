add_definitions(-DTESTDATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

set(EXAMPLES
	audio_sine
	audio_wav
	lines
	rendertarget
	sprites
)

if(SDL2PP_WITH_IMAGE)
	set(EXAMPLES ${EXAMPLES}
		image
		fill
	)
endif()

if(SDL2PP_WITH_MIXER)
	set(EXAMPLES ${EXAMPLES}
		mixer
		mixer_music
		mixer_music_sine
		mixer_effects
	)
endif()

if(SDL2PP_WITH_TTF)
	set(EXAMPLES ${EXAMPLES}
		ttf
	)
endif()

foreach(EXAMPLE ${EXAMPLES})
	add_executable(${EXAMPLE} ${EXAMPLE}.cc)
	target_link_libraries(${EXAMPLE} SDL2pp::SDL2pp)
endforeach()
