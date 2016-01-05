#include <SDL2/SDL_main.h>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
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

	{
		constexpr SDL_Rect sr{0, 0, 1, 1};
		constexpr Rect r1;
		constexpr Rect r2(sr);
		constexpr Rect r3(Point(0, 0), Point(1, 1));
		constexpr Rect r4(0, 0, 1, 1);
		constexpr Rect r5(r4);

		EXPECT_EQUAL(r4, r2);
		EXPECT_EQUAL(r5, r3);

		constexpr bool b1 = r2 == r3;
		constexpr bool b2 = r1 != r3;

		EXPECT_TRUE(b1);
		EXPECT_TRUE(b2);

		constexpr int x = r5.GetX();
		constexpr int y = r5.GetY();
		constexpr int w = r5.GetW();
		constexpr int h = r5.GetH();
		constexpr int x2 = r5.GetX2();
		constexpr int y2 = r5.GetY2();

		EXPECT_TRUE(x == y);
		EXPECT_TRUE(w == h);
		EXPECT_TRUE(x2 == y2);

		constexpr Rect add = r1 + Point(1, 1);
		constexpr Rect sub = r1 - Point(1, 1);

		EXPECT_EQUAL(add - Point(2, 2), sub);

		constexpr bool b3 = r2.Contains(0, 0);
		constexpr bool b4 = r2.Contains(Point(0, 0));
		constexpr bool b5 = r2.Contains(Rect(0, 0, 1, 1));
		constexpr bool b6 = r2.Intersects(Rect(0, 0, 1, 1));

		EXPECT_TRUE(b3 && b4 && b5 && b6);
	}
END_TEST()
