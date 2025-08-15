
#include <cassert>
extern "C" bool raw_is_path_exists(const char *path);

int main() {
	const char *valid_path = "../tests-ffi";
	const char *wrong_path = "../abcxyzw1133";

	assert(raw_is_path_exists(valid_path));
	assert(!raw_is_path_exists(wrong_path));

	return 0;
}