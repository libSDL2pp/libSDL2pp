#include "catch.hpp"

#include <SDL2pp/Color.hh>

using namespace SDL2pp;

using Catch::Equals;

auto const TAGS = "[graphics][color]";

TEST_CASE("Test Color class' constructors/comparision", TAGS)
{
	CHECK(Color(1, 2, 3, 4) == Color(1, 2, 3, 4));
	CHECK(Color(1, 2, 3, 4) != Color(0, 2, 3, 4));
	CHECK(Color(1, 2, 3, 4) != Color(1, 0, 3, 4));
	CHECK(Color(1, 2, 3, 4) != Color(0, 2, 3, 4));
	CHECK(Color(1, 2, 3, 4) != Color(1, 2, 3, 0));

	CHECK((SDL_Color{1, 2, 3, 4} == Color(1, 2, 3, 4)));
	CHECK((Color(1, 2, 3, 4) == SDL_Color{1, 2, 3, 4}));

	CHECK(Color() == Color(0, 0, 0, 0));
	CHECK(Color(1, 2, 3) == Color(1, 2, 3, 255));
}

TEST_CASE("Test Color class' getters/getters", TAGS)
{
	Color c(1,2,3,4);

	CHECK((c.r == 1 && c.g == 2 && c.b == 3 && c.a == 4));
	CHECK((c.GetRed() == 1 && c.GetGreen() == 2 && c.GetBlue() == 3 && c.GetAlpha() == 4));

	c = Color(4, 5, 6, 7);

	CHECK((c.r == 4 && c.g == 5 && c.b == 6 && c.a == 7));
	CHECK((c.GetRed() == 4 && c.GetGreen() == 5 && c.GetBlue() == 6 && c.GetAlpha() == 7));

	c.SetRed(8).SetGreen(9).SetBlue(10).SetAlpha(11);

	CHECK((c.r == 8 && c.g == 9 && c.b == 10 && c.a == 11));

	c = SDL_Color{12, 13, 14, 15};

	CHECK((c.r == 12 && c.g == 13 && c.b == 14 && c.a == 15));
}

TEST_CASE("Test Color class' self assignment", TAGS)
{
	// Self assignment
	Color c(1, 2, 3, 4);

	c = c;

	CHECK(c == Color(1, 2, 3, 4));
}

TEST_CASE("Test Color class' self move-assignment", TAGS)
{
	// Self move-assignment
	Color c(1, 2, 3, 4);

	Color& cref = c;
	c = std::move(cref);

	CHECK((c.GetRed() == 1 && c.GetGreen() == 2 && c.GetBlue() == 3 && c.GetAlpha() == 4));
}

TEST_CASE("Test Color class hash methods", TAGS)
{
	// Hashes
	CHECK(std::hash<Color>()(Color(1, 2, 3, 4)) == std::hash<Color>()(Color(1, 2, 3, 4)));
	CHECK(std::hash<Color>()(Color(1, 2, 3, 4)) != std::hash<Color>()(Color(2, 1, 3, 4)));
	CHECK(std::hash<Color>()(Color(1, 2, 3, 4)) != std::hash<Color>()(Color(1, 2, 4, 3)));
}

TEST_CASE("Test Color class' operations with SDL_Color", TAGS)
{
	// Construction from and comparison with SDL objects
	SDL_Color sdlcolor = { 1, 2, 3, 4 };

	CHECK(Color(sdlcolor) == Color(1, 2, 3, 4));

	CHECK(Color(sdlcolor) != Color(0, 2, 3, 4));

	CHECK(Color(1, 2, 3, 4) == sdlcolor);
	CHECK(Color(0, 2, 3, 4) != sdlcolor);
}

TEST_CASE("Test Color class' stream<< operator", TAGS)
{
	// streams
	std::stringstream stream;
	stream << Color(1, 2, 3, 4);
	CHECK_THAT(stream.str(), Equals("[r:1,g:2,b:3,a:4]"));
}
