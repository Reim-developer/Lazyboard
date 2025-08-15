#ifndef CONFIG_HXX
#define CONFIG_HXX
#include "../../raw/config.hxx"

namespace Lazyboard::ffi {

inline char *config_dir() {
	char *result = raw_config_dir();

	return result;
}

inline WriteConfigStatus write_default_config() {
	auto result = raw_write_default_config();

	return result;
}

inline RawReadAppConfigStatus exists_config(const char *path,
											RawAppConfig *config_out) {
	auto result = raw_exists_config(path, config_out);

	return result;
}

inline void free_cstr_app_config(RawAppConfig *config_out) {
	raw_free_cstr_app_config(config_out);
}

}  // namespace Lazyboard::ffi

#endif	// CONFIG_HXX