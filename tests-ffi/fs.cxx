#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <span>
#include <string>

using std::span;
using std::string;

extern "C" bool raw_is_path_exists(const char *path);
extern "C" char *raw_cache_dir();
extern "C" void raw_free_c_str(char *c_str);

int main(int argc, char *argv[]) {
	const auto this_file_span = span(argv, size_t(argc));

	if (this_file_span.empty()) {
		abort();
	}

	const char *file_name = this_file_span[0];
	const char *wrong_path = "../abcxyzw1133";

	char *raw_cache_dir_value = raw_cache_dir();
	const string cache_dir = string(raw_cache_dir_value);
	raw_free_c_str(raw_cache_dir_value);

	assert(raw_is_path_exists(file_name));
	assert(!raw_is_path_exists(wrong_path));
	assert(!cache_dir.empty());

	return 0;
}