
#include <cassert>
#include <cstdint>
using std::uint8_t;

extern "C" enum class QueryResult : uint8_t {
	OK,
	OPEN_DATABASE_ERR,
	C_STR_CONVERT_ERR,
	EXECUTE_SQL_ERR
};

extern "C" auto raw_init_clipboard_cache(const char* path) -> QueryResult;

int main() {
	using R = QueryResult;

	const char* test_path = "test_init.db";
	auto status = raw_init_clipboard_cache(test_path);

	assert(status != R::OPEN_DATABASE_ERR);
	assert(status != R::C_STR_CONVERT_ERR);
	assert(status != R::EXECUTE_SQL_ERR);
	assert(status == R::OK);

	return 0;
}