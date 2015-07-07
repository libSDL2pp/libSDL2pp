#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST()
	// note that this is merely a compilation test; EXPECT_s are mainly
	// used to silence `unused variable' warnings
	{
		constexpr SDL_Point sp{1, 2};
		constexpr Point p1;
		constexpr Point p2(sp);
		constexpr Point p3(1, 2);
		constexpr Point p4(p2);

		constexpr bool b1 = p2 == p4;
		constexpr bool b2 = p1 != p2;

		EXPECT_TRUE(b1);
		EXPECT_TRUE(b2);
	}
END_TEST()
