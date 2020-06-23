#include <SDL_main.h>

#include <SDL2pp/Private/Utility.hh>

using namespace SDL2pp::Private;
using namespace std;

int main(int, char*[]) {
	static_assert(Or<true_type, true_type>::value, "OR(true, true) should be true");
	static_assert(Or<true_type, false_type>::value, "OR(true, false) should be true");
	static_assert(Or<false_type, true_type>::value, "OR(false, true) should be true");
	static_assert(!Or<false_type, false_type>::value, "OR(false, false) should be false");
	
	static_assert(And<true_type, true_type>::value, "AND(true, true) should be true");
	static_assert(!And<true_type, false_type>::value, "AND(true, false) should be false");
	static_assert(!And<false_type, true_type>::value, "AND(false, true) should be false");
	static_assert(!And<false_type, false_type>::value, "AND(false, false) should be false");
	
	struct A { };
	struct B { };
	struct C { };
	
	static_assert(TupleHasType<A, tuple<A, B>>::value, "");
	static_assert(TupleHasType<B, tuple<A, B>>::value, "");
	static_assert(!TupleHasType<C, tuple<A, B>>::value, "");
	
	return 0;
}
