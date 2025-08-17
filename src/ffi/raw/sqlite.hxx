#ifndef RAW_SQLITE_HXX
#define RAW_SQLITE_HXX

#if defined(__cplusplus)
extern "C" {
#endif

#include <cstdint>
using std::uint8_t;

enum class InitDatabaseStatus : uint8_t {
	OK,
	CREATE_DATABASE_FAILED,
	C_STR_CONVERT_FAILED,
	EXECUTE_SQL_FAILED
};

auto raw_init_clipboard_cache(const char *path) -> InitDatabaseStatus;

#if defined(__cplusplus)
}
#endif

#endif	// RAW_SQLITE_HXX