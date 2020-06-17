#include <string>

#include <SDL_main.h>

#include <SDL2pp/Optional.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	// Engage/disengage
	{
		Optional<int> o;
		int i;

		// disengaged
		EXPECT_TRUE((bool)!o);

		// accessing disengaged fails
		EXPECT_EXCEPTION(i = o.value(), BadOptionalAccess);

		// value_or test
		EXPECT_EQUAL(i = o.value_or(234), 234);

		// engage
		o = 123;

		// engaged
		EXPECT_TRUE((bool)o);

		// accessing value
		EXPECT_EQUAL(o.value(), 123);

		// disengage
		o = NullOpt;

		EXPECT_TRUE((bool)!o);
	}

	// Equality
	{
		Optional<int> o1, o2;

		EXPECT_TRUE(o1 == o2);
		EXPECT_TRUE(o1 == NullOpt);
		EXPECT_TRUE(NullOpt == o1);

		o1 = 123;

		EXPECT_TRUE(!(o1 == o2));

		o2 = 124;

		EXPECT_TRUE(!(o1 == o2));

		o2 = 123;

		EXPECT_TRUE(o1 == o2);
	}

	// Swap
	{
		Optional<int> o1, o2;

		o1 = 123;

		EXPECT_TRUE(!o2);
		EXPECT_TRUE((bool)o1);
		EXPECT_TRUE(o1 == 123);

		std::swap(o1, o2);

		EXPECT_TRUE(!o1);
		EXPECT_TRUE((bool)o2);
		EXPECT_TRUE(o2 == 123);

		o1.swap(o2);

		EXPECT_TRUE(!o2);
		EXPECT_TRUE((bool)o1);
		EXPECT_TRUE(o1 == 123);
	}
END_TEST()
