#ifndef SQLITE_HXX
#define SQLITE_HXX
#include "../../raw/sqlite.hxx"

namespace Lazyboard::ffi {
inline auto init_clipboard_cache(const char *path) -> InitDatabaseStatus {
	auto status = raw_init_clipboard_cache(path);

	return status;
}
}  // namespace Lazyboard::ffi

#endif	// SQLITE_HXX