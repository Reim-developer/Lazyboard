#include "include/sqlite_manager.hxx"

#include <qmainwindow.h>

#include <format>
#include <string>

#include "../ffi/namespace/include/sqlite.hxx"
#include "../ffi/namespace/include/utils.hxx"
#include "../front_end_utils/include/utils.hxx"

#if defined(LAZY_DEBUG)
	#include <iostream>
using std::cout;
#endif

using Lazyboard::ffi::cache_dir;
using Lazyboard::ffi::free_c_str;
using Lazyboard::ffi::init_clipboard_cache;
using Lazyboard::ffi::new_folder;
using Lazyboard::front_end_db::SQLiteManager;
using Lazyboard::front_end_utils::error_dialog_show;
using Lazyboard::front_end_utils::ErrorTypes;
using Self = SQLiteManager;
using std::format;
using std::string;
using Status = QueryResult;

void Self::on_create_clipboard_cache_error(
	const InitDataResult& result) noexcept {
	using E = ErrorTypes;
	using R = InitDataResult;

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

void Self::on_create_folder_error(const MkdirResult& result) noexcept {
	using E = ErrorTypes;
	using Result = MkdirResult;

	switch (result) {
		case Result::OK:
			break;

		case Result::WRAP_RAW_C_FAILED:
			error_dialog_show(this->_main_window, E::WRAP_C_STR_ERR);
			break;

		case Result::FAILED:
			error_dialog_show(this->_main_window, E::CREATE_DIR_FAILED);
			break;
	}
}

void Self::create_clipboard_cache(QMainWindow* main_window) {
	this->_main_window = main_window;

	auto raw_cache_directory = cache_dir();
	string cache_dir_string = format("{}/Lazyboard", raw_cache_directory);
	auto database_path = format("{}/clipboard_cache.db", cache_dir_string);
	free_c_str(raw_cache_directory);

	const auto create_dir_result = new_folder(cache_dir_string.data());
	on_create_folder_error(create_dir_result);

	const auto status = init_clipboard_cache(database_path.data());
	on_create_clipboard_cache_error(status);

	// clang-format off
	#if defined (LAZY_DEBUG)
		cout << "Found cache directory path: " << database_path << "\n";
	#endif	// clang-format on
}