
#include <cassert>
#include <cstdint>
using std::uint8_t;

extern "C" enum class InitDatabaseStatus : uint8_t {
	OK,
	CREATE_DATABASE_FAILED,
	C_STR_CONVERT_FAILED,
	EXECUTE_SQL_FAILED
};

extern "C" InitDatabaseStatus raw_init_clipboard_cache(const char* path);

int main() {
	using Status = InitDatabaseStatus;

	const char* test_path = "test_init.db";
	auto status = raw_init_clipboard_cache(test_path);

	assert(status != Status::CREATE_DATABASE_FAILED);
	assert(status != Status::C_STR_CONVERT_FAILED);
	assert(status != Status::EXECUTE_SQL_FAILED);
	assert(status == Status::OK);

	return 0;
}