#include <SDL2/SDL_error.h>

#include <SDL2pp/Exception.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST()
	SDL_SetError("foo");

	try {
		throw Exception("");
	} catch (SDL2pp::Exception& e) {
		SDL_SetError("bar");
		EXPECT_EQUAL((std::string)e.GetSDLError(), "foo");
	}
END_TEST()
