
#include <cassert>
#include <cstdint>
#include <filesystem>
using std::uint8_t;
using std::filesystem::remove;

extern "C" enum class QueryResult : uint8_t {
	OK,
	OPEN_DATABASE_ERR,
	C_STR_CONVERT_ERR,
	EXECUTE_SQL_ERR
};

extern "C" struct TextClipboard {
	const char* content;
	const char* content_hash;
	const char* content_type;
	bool is_pinned;
};

extern "C" auto init_clipboard_cache(const char* path) -> QueryResult;
extern "C" QueryResult add_text_clipboard(const char* path,
										  TextClipboard text_clipboard);

int main() {
	using R = QueryResult;

	const char* test_path = "test_init.db";
	remove(test_path);

	auto text_clipboard = TextClipboard{
		.content = "test",
		.content_hash = "test_hash",
		.content_type = "text",
		.is_pinned = true,
	};

	auto init_result = init_clipboard_cache(test_path);
	auto add_text_result = add_text_clipboard(test_path, text_clipboard);

	assert(init_result != R::OPEN_DATABASE_ERR);
	assert(init_result != R::C_STR_CONVERT_ERR);
	assert(init_result != R::EXECUTE_SQL_ERR);
	assert(init_result == R::OK);

	assert(add_text_result != R::C_STR_CONVERT_ERR);
	assert(add_text_result != R::EXECUTE_SQL_ERR);
	assert(add_text_result != R::OPEN_DATABASE_ERR);
	assert(add_text_result == R::OK);

	return 0;
}