#ifndef CONFIG_HXX
#define CONFIG_HXX
#include "../../raw/config.hxx"

namespace Lazyboard::ffi {

inline char *local_data() {
  char *result = raw_local_data();

  return result;
}
inline WriteConfigStatus write_default_config() {
  auto result = raw_write_default_config();

  return result;
}
}  // namespace Lazyboard::ffi

#endif  // CONFIG_HXX