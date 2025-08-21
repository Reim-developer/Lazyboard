#include <stdlib.h>

#include <cassert>
#include <cstdint>
#include <string>

// clang-format off
enum class AllocResult : uint8_t {
	OK,
	NULL_DEFERENCE_ERR,
	C_STRING_CONVERT_ERR
};	// clang-format on
extern "C" AllocResult text_sha256(const char* text, char** out);
extern "C" void raw_free_c_str(char* str);

using std::string;

void test_success() {
	using R = AllocResult;

	const char* my_text = "Hello";
	const char* real_result =
		"185f8db32271fe25f561a6fc938b2e264306ec304eda518007d1764826381969";
	char* out = nullptr;

	auto result = text_sha256(my_text, &out);
	string hash_result = string(out);
	raw_free_c_str(out);

	assert(!hash_result.empty());
	assert(hash_result == real_result);

	assert(result != R::C_STRING_CONVERT_ERR);
	assert(result != R::NULL_DEFERENCE_ERR);
	assert(result == R::OK);
}

void test_deference_err() {
	using R = AllocResult;

	const char* my_text = nullptr;
	char* out = nullptr;

	auto result = text_sha256(my_text, nullptr);
	raw_free_c_str(out);

	assert(result != R::OK);
	assert(result != R::C_STRING_CONVERT_ERR);
	assert(result == R::NULL_DEFERENCE_ERR);
}

void test_sha_mismatch_err() {
	using R = AllocResult;

	const char* my_text = "Hello but my SHA will mismatch, to sad...";
	const char* real_result = "185f8db32271fe25f561a6...";
	char* out = nullptr;

	auto result = text_sha256(my_text, &out);
	string hash_result = string(out);
	raw_free_c_str(out);

	assert(result != R::C_STRING_CONVERT_ERR);
	assert(result != R::NULL_DEFERENCE_ERR);
	assert(result == R::OK);

	assert(!hash_result.empty());
	assert(hash_result != real_result);
}

int main() {
	test_success();
	test_deference_err();
	test_sha_mismatch_err();
	return 0;
}