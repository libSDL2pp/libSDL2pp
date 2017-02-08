#include <SDL_main.h>
#include <SDL_error.h>

#include <SDL2pp/Exception.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	SDL_SetError("BarError");

	try {
		throw Exception("FooFunction");
	} catch (SDL2pp::Exception& e) {
		// this SDL_SetError should not clobber Exception contents
		SDL_SetError("AnotherError");
		EXPECT_EQUAL(e.GetSDLFunction(), "FooFunction");
		EXPECT_EQUAL(e.GetSDLError(), "BarError");
		EXPECT_EQUAL((std::string)e.what(), "FooFunction failed: BarError");
	}
END_TEST()
