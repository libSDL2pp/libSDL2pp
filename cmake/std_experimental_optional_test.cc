#include <experimental/optional>
#include <string>

int main() {
	std::experimental::optional<std::string> o;

	return !o;
}
