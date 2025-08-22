
#include <cassert>
#include <cstdint>
using std::uint8_t;

enum class UtilsResult : uint8_t {
	OK,
	ALLOC_ERR,
	NULL_DEFERENCE_ERR,
	GET_DIR_ERR,
};

extern "C" UtilsResult config_dir(char **out);

void test_config_dir() {
	using R = UtilsResult;

	char *out = nullptr;
	auto result = config_dir(&out);

	assert(result != R::ALLOC_ERR);
	assert(result != R::NULL_DEFERENCE_ERR);
	assert(result != R::GET_DIR_ERR);
	assert(result == R::OK);
}

int main() {
	test_config_dir();

	return 0;
}