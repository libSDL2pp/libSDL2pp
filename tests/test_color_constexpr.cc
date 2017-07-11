#include <SDL_main.h>

#include <SDL2pp/Color.hh>

using namespace SDL2pp;

int main(int, char*[]) {
	constexpr SDL_Color sc{1, 2, 3, 4};
	constexpr Color c1;
	constexpr Color c2(sc);
	constexpr Color c3(1, 2, 3, 4);
	constexpr Color c4(c2);
	constexpr Color c5(1, 2, 3);

	constexpr bool b1 = c2 == c4;
	constexpr bool b2 = c1 != c2;

	static_assert(b1, "");
	static_assert(b2, "");

	constexpr int r = c1.GetRed();
	constexpr int g = c1.GetGreen();
	constexpr int b = c1.GetBlue();
	constexpr int a = c1.GetAlpha();

	static_assert(r == 0 && g == 0 && b == 0 && a == 0, "");

	return 0;
}
