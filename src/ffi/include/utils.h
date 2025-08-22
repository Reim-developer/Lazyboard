#ifndef UTILS_RAW_HXX
#define UTILS_RAW_HXX

#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif

using std::uint8_t;

// clang-format off
enum class ResultContext : uint8_t { 
	OK, 
	FAILED
};	// clang-format on

ResultContext open_browser(const char *url);
ResultContext new_folder(const char *path);

/***********/

enum class UtilsResult : uint8_t {
	OK,
	ALLOC_ERR,
	NULL_DEFERENCE_ERR,
	GET_DIR_ERR,
};

UtilsResult cache_dir(char **out);
UtilsResult config_dir(char **out);
bool path_exists(const char *path);
void free_alloc(char *c_str);

#ifdef __cplusplus
}
#endif
#endif	// UTILS_RAW_HXX