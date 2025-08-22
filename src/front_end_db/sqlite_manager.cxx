#include "include/sqlite_manager.hxx"

#include <qmainwindow.h>

#include <format>
#include <string>

#include "../ffi/include/sqlite.h"
#include "../ffi/include/utils.h"
#include "../front_end_utils/include/utils.hxx"

#if defined(LAZY_DEBUG)
	#include <iostream>
using std::cout;
#endif

using Lazyboard::front_end_db::SQLiteManager;
using Lazyboard::front_end_utils::error_dialog_show;
using Lazyboard::front_end_utils::ErrorTypes;
using Self = SQLiteManager;
using std::format;
using std::string;
using Status = QueryResult;

void Self::on_create_clipboard_cache_error(const QueryResult& result) noexcept {
	using E = ErrorTypes;
	using R = QueryResult;

	switch (result) {
		case R::OK:
			break;

		case R::C_STR_CONVERT_ERR:
			error_dialog_show(this->_main_window, E::CONVERT_TO_C_STR_ERR);
			break;

		case R::OPEN_DATABASE_ERR:
			error_dialog_show(this->_main_window, E::OPEN_DATABASE_ERR);
			break;

		case R::EXECUTE_SQL_ERR:
			error_dialog_show(this->_main_window, E::EXECUTE_SQL_ERR);
	}
}

void Self::on_create_folder_error(const ResultContext& result) noexcept {
	using E = ErrorTypes;
	using R = ResultContext;

	switch (result) {
		case R::OK:
			break;

		case R::FAILED:
			error_dialog_show(this->_main_window, E::CREATE_DIR_FAILED);
			break;
	}
}

void Self::create_clipboard_cache(QMainWindow* main_window) {
	this->_main_window = main_window;

	char* out = nullptr;
	auto result = cache_dir(&out);

	string cache_dir_string = format("{}/Lazyboard", out);
	auto database_path = format("{}/clipboard_cache.db", cache_dir_string);
	free_alloc(out);

	const auto create_dir_result = new_folder(cache_dir_string.data());
	on_create_folder_error(create_dir_result);

	const auto status = init_clipboard_cache(database_path.data());
	on_create_clipboard_cache_error(status);

	// clang-format off
	#if defined (LAZY_DEBUG)
		cout << "Found cache directory path: " << database_path << "\n";
	#endif	// clang-format on
}