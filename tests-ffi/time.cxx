#include <cassert>
#include <cstdint>
#include <string>

using std::string;
using std::uint8_t;

extern "C" enum class AllocResult : uint8_t {
	OK,
	NULL_DEFERENCE_ERR,
	CONVERT_TO_STR_FAILED,
};

extern "C" AllocResult time_now(char **out);
extern "C" void raw_free_c_str(char *str);

void null_deference_test() {
	using R = AllocResult;

	auto result = time_now(nullptr);
	assert(result != R::CONVERT_TO_STR_FAILED);
	assert(result != R::OK);
	assert(result == R::NULL_DEFERENCE_ERR);
}

void time_now_test() {
	using R = AllocResult;

	char *out = nullptr;
	auto result = time_now(&out);
	auto time_now_string = string(out);
	raw_free_c_str(out);

	assert(result != R::CONVERT_TO_STR_FAILED);
	assert(result != R::NULL_DEFERENCE_ERR);
	assert(result == R::OK);
	assert(!time_now_string.empty());
}

int main() {
	null_deference_test();
	time_now_test();
	return 0;
}