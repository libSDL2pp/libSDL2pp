#include <SDL_main.h>

#include <SDL2pp/Color.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	{
		EXPECT_TRUE(Color(1, 2, 3, 4) == Color(1, 2, 3, 4));
		EXPECT_TRUE(Color(1, 2, 3, 4) != Color(0, 2, 3, 4));
		EXPECT_TRUE(Color(1, 2, 3, 4) != Color(1, 0, 3, 4));
		EXPECT_TRUE(Color(1, 2, 3, 4) != Color(0, 2, 3, 4));
		EXPECT_TRUE(Color(1, 2, 3, 4) != Color(1, 2, 3, 0));

		EXPECT_TRUE(SDL_Color{1, 2, 3, 4} == Color(1, 2, 3, 4));
		EXPECT_TRUE(Color(1, 2, 3, 4) == SDL_Color{1, 2, 3, 4});
	}

	{
		EXPECT_TRUE(Color() == Color(0, 0, 0, 0));
		EXPECT_TRUE(Color(1, 2, 3) == Color(1, 2, 3, 255));

		Color c(1,2,3,4);

		EXPECT_TRUE(c.r == 1 && c.g == 2 && c.b == 3 && c.a == 4);
		EXPECT_TRUE(c.GetRed() == 1 && c.GetGreen() == 2 && c.GetBlue() == 3 && c.GetAlpha() == 4);

		c = Color(4, 5, 6, 7);

		EXPECT_TRUE(c.r == 4 && c.g == 5 && c.b == 6 && c.a == 7);
		EXPECT_TRUE(c.GetRed() == 4 && c.GetGreen() == 5 && c.GetBlue() == 6 && c.GetAlpha() == 7);

		c.SetRed(8).SetGreen(9).SetBlue(10).SetAlpha(11);

		EXPECT_TRUE(c.r == 8 && c.g == 9 && c.b == 10 && c.a == 11);

		c = SDL_Color{12, 13, 14, 15};

		EXPECT_TRUE(c.r == 12 && c.g == 13 && c.b == 14 && c.a == 15);
	}

	{
		// Self assignment
		Color c(1, 2, 3, 4);

		c = c;

		EXPECT_TRUE(c == Color(1, 2, 3, 4));
	}

	{
		// Self move-assignment
		Color c(1, 2, 3, 4);

		Color& cref = c;
		c = std::move(cref);

		EXPECT_TRUE(c.GetRed() == 1 && c.GetGreen() == 2 && c.GetBlue() == 3 && c.GetAlpha() == 4);
	}

	{
		// Hashes
		EXPECT_TRUE(std::hash<Color>()(Color(1, 2, 3, 4)) == std::hash<Color>()(Color(1, 2, 3, 4)));
		EXPECT_TRUE(std::hash<Color>()(Color(1, 2, 3, 4)) != std::hash<Color>()(Color(2, 1, 3, 4)));
		EXPECT_TRUE(std::hash<Color>()(Color(1, 2, 3, 4)) != std::hash<Color>()(Color(1, 2, 4, 3)));
	}

	{
		// Construction from and comparison with SDL objects
		SDL_Color sdlcolor = { 1, 2, 3, 4 };

		EXPECT_TRUE(Color(sdlcolor) == Color(1, 2, 3, 4));

		EXPECT_TRUE(Color(sdlcolor) != Color(0, 2, 3, 4));

		EXPECT_TRUE(Color(1, 2, 3, 4) == sdlcolor);
		EXPECT_TRUE(Color(0, 2, 3, 4) != sdlcolor);
	}

	{
		// streams
		std::stringstream stream;
		stream << Color(1, 2, 3, 4);
		EXPECT_EQUAL(stream.str(), "[r:1,g:2,b:3,a:4]");
	}
END_TEST()
