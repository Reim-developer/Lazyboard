#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>

using std::span;
using std::string;
using std::uint8_t;

enum class UtilsResult : uint8_t {
	OK,
	ALLOC_ERR,
	NULL_DEFERENCE_ERR,
	GET_DIR_ERR,
};

extern "C" bool path_exists(const char *path);
extern "C" UtilsResult cache_dir(char **out);
extern "C" void free_alloc(char *c_str);

int main(int argc, char *argv[]) {
	using R = UtilsResult;

	const auto this_file_span = span(argv, size_t(argc));
	if (this_file_span.empty()) {
		abort();
	}

	const char *file_name = this_file_span[0];
	const char *wrong_path = "../abcxyzw1133";

	char *out = nullptr;
	auto result = cache_dir(&out);
	const string cache_dir = string(out);
	free_alloc(out);

	assert(path_exists(file_name));
	assert(!path_exists(wrong_path));

	assert(result != R::ALLOC_ERR);
	assert(result != R::GET_DIR_ERR);
	assert(result != R::NULL_DEFERENCE_ERR);
	assert(result == R::OK);
	assert(!cache_dir.empty());

	return 0;
}