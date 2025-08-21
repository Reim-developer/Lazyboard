#include <stdlib.h>

#include <cassert>
#include <cstdint>
#include <string>

// clang-format off
enum class GetShaResult : uint8_t {
	OK,
	C_STRING_CONVERT_ERR
};	 // clang-format on
extern "C" GetShaResult text_sha256(const char* text, char** out);
extern "C" void raw_free_c_str(char* str);

using std::string;

int main() {
	using R = GetShaResult;

	const char* my_text = "Hello";
	const char* real_result =
		"185f8db32271fe25f561a6fc938b2e264306ec304eda518007d1764826381969";
	char* out = nullptr;

	auto result = text_sha256(my_text, &out);
	string hash_result = string(out);
	raw_free_c_str(out);

	assert(!hash_result.empty());
	assert(result != R::C_STRING_CONVERT_ERR);
	assert(hash_result == real_result);
	assert(result == R::OK);

	return 0;
}