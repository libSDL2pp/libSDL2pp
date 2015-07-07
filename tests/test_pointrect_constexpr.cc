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

		constexpr int x = p1.GetX();
		constexpr int y = p1.GetY();

		EXPECT_TRUE(x == 0 && y == 0);

		constexpr Point neg = -p1;
		constexpr Point sum = p1 + p2;
		constexpr Point diff = p1 - p2;
		constexpr Point mul1 = p1 * p2;
		constexpr Point mul2 = p1 * 2;
		constexpr Point div1 = p1 / p2;
		constexpr Point div2 = p1 * 2;
		constexpr Point rem1 = p1 % p2;
		constexpr Point rem2 = p1 % 2;

		EXPECT_EQUAL(neg + sum + diff + mul1 + mul2 + div1 + div2 + rem1 + rem2, Point(0, 0));
	}
END_TEST()
