#ifndef RAW_SQLITE_HXX
#define RAW_SQLITE_HXX

#if defined(__cplusplus)
extern "C" {
#endif

#include <cstdint>
using std::uint8_t;

enum class QueryResult : uint8_t {
	OK,
	OPEN_DATABASE_ERR,
	C_STR_CONVERT_ERR,
	EXECUTE_SQL_ERR
};

auto raw_init_clipboard_cache(const char *path) -> QueryResult;

#if defined(__cplusplus)
}
#endif

#endif	// RAW_SQLITE_HXX