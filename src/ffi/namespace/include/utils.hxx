#ifndef UTILS_HXX
#define UTILS_HXX
#include "../../raw/utils.hxx"

namespace Lazyboard::ffi {
inline OpenBrowserStatus open_browser(const char *url) {
  auto result = raw_open_browser(url);

  return result;
}

inline CreateFileSystemStatus new_folder(const char *path) {
  auto result = raw_new_folder(path);

  return result;
}

inline bool is_exists_path(const char *path) {
  auto result = raw_is_exists_path(path);

  return result;
}

inline void free_c_str(const char *c_str) { raw_free_c_str(c_str); }
}  // namespace Lazyboard::ffi

#endif  // UTILS_HXX