#ifndef UTILS_HXX
#define UTILS_HXX
#include "../../raw/utils.hxx"

namespace Lazyboard::ffi {
inline bool browser_open(const char *url) {
  auto result = open_browser(url);

  return result;
}
}  // namespace Lazyboard::ffi

#endif  // UTILS_HXX