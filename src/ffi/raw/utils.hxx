#ifndef UTILS_RAW_HXX
#define UTILS_RAW_HXX

#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif

using std::uint8_t;

enum class OpenBrowserStatus : uint8_t {
  OK,
  WRAP_RAW_C_FAILED,
  URL_IS_EMPTY,
  OPEN_BROWSER_FAILED,
};

enum class CreateFileSystemStatus : uint8_t {
  OK,
  WRAP_RAW_C_FAILED,
  FAILED,
};

OpenBrowserStatus raw_open_browser(const char *url);
CreateFileSystemStatus raw_new_folder(const char *path);
bool raw_is_exists_path(const char *path);
void raw_free_c_str(const char *c_str);

#ifdef __cplusplus
}
#endif
#endif  // UTILS_RAW_HXX