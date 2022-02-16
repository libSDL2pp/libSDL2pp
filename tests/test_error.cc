#include "catch.hpp"

#include <SDL_error.h>

#include <SDL2pp/Exception.hh>

using namespace SDL2pp;

using Catch::Equals;

auto const TAGS = "[general][error]";

TEST_CASE("Test throwing Exception class", TAGS) {
	SDL_SetError("BarError");

	try {
		throw Exception("FooFunction");
	} catch (SDL2pp::Exception& e) {
		// this SDL_SetError should not clobber Exception contents
		SDL_SetError("AnotherError");
		CHECK_THAT(e.GetSDLFunction(), Equals("FooFunction"));
		CHECK_THAT(e.GetSDLError(), Equals("BarError"));
		CHECK_THAT(e.what(), Equals("FooFunction failed: BarError"));
	}
}
