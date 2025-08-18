#include "include/main_window_preload.hxx"

#include <qcolor.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qpalette.h>

#include <memory>
#include <print>
#include <string>

#include "../ffi/namespace/include/config.hxx"
#include "../ffi/namespace/include/utils.hxx"
#include "include/theme_manager.hxx"

#if defined(LAZY_DEBUG)
	#include <format>

	#include "../front_end_utils/include/utils.hxx"
using Lazyboard::front_end_utils::dump_ptr_address;
using std::println;
#endif

#include "../front_end_utils/include/error_types.hxx"
#include "../front_end_utils/include/utils.hxx"

using Lazyboard::front_end::MainWindowPreload;
using Self = MainWindowPreload;

using std::format;
using std::make_unique;
using std::string;
using namespace Lazyboard::ffi;
using Lazyboard::front_end_utils::error_dialog_show;
using Lazyboard::front_end_utils::ErrorTypes;

void Self::on_gen_default_cfg_error(WriteConfigStatus status,
									QMainWindow *main_window) {
	switch (status) {
		using E = ErrorTypes;

		case WriteConfigStatus::OK:
			break;

		case WriteConfigStatus::CREATE_DIR_FAILED:
			error_dialog_show(main_window, E::CREATE_DIR_FAILED);

			break;

		case WriteConfigStatus::GET_CONFIG_DIR_FAILED:
			error_dialog_show(main_window, E::GET_CONFIG_DIR_FAILED);
			break;

		case WriteConfigStatus::CREATE_FILE_FAILED:
			error_dialog_show(main_window, E::CREATE_FILE_FAILED);
			break;

		case WriteConfigStatus::WRITE_FILE_FAILED:
			error_dialog_show(main_window, E::WRITE_FILE_FAILED);
			break;

		case WriteConfigStatus::TOML_TO_STRING_FAILED:
			error_dialog_show(main_window, E::TOML_TO_STRING_FAILED);
			break;
	}
}

void Self::on_read_exists_cfg_error(RawReadAppConfigStatus status,
									QMainWindow *main_window) {
	using Status = RawReadAppConfigStatus;
	using E = ErrorTypes;

	switch (status) {
		case Status::READ_OK:
			break;

		case Status::CONVERT_TO_MUT_FAILED:
			error_dialog_show(main_window, E::CONVERT_TO_MUT_FAILED);
			break;

		case Status::PARSE_TOML_FAILED:
			error_dialog_show(main_window, E::PARSE_TOML_FAILED);
			break;

		case Status::READ_FILE_FAILED:
			error_dialog_show(main_window, E::READ_FILE_FAILED);
			break;

		case Status::UTF_8_ERROR:
			error_dialog_show(main_window, E::UTF_8_ERROR);
			break;

		case Status::CONVERT_TO_C_STR_FAILED:
			error_dialog_show(main_window, E::CONVERT_TO_C_STR_FAILED);
			break;
	}
}

string Self::application_config() {
	auto config_dir_raw = ffi::config_dir();
	string config_path = format("{}/Lazyboard/settings.toml", config_dir_raw);

	ffi::free_c_str(config_dir_raw);
	return config_path;
}

void Self::create_default_config(QMainWindow *main_window) {
	auto config_path = this->application_config();
	auto is_config_exists = ffi::is_exists_path(config_path.data());

	if (!is_config_exists) {
		auto status = ffi::write_default_config();
		on_gen_default_cfg_error(status, main_window);

		// clang-format off
		#if defined(LAZY_DEBUG)
			println("[DEBUG] Config path not found, generate at: {}", config_path);
		#endif 

		return;
	}

	#if defined(LAZY_DEBUG)
		println("[DEBUG] Found config path at: {}", config_path);
	#endif	// clang-format on
}

void Self::read_if_exists_config(QMainWindow *main_window) {
	raw_app_config = make_unique<RawAppConfig>();
	theme_manager = make_unique<ThemeManager>();

	auto config_path = this->application_config();
	auto status = exists_config(config_path.data(), raw_app_config.get());
	this->on_read_exists_cfg_error(status, main_window);

	theme_manager->set_main_window_theme(main_window, raw_app_config.get());

	// clang-format off
	#if defined (LAZY_DEBUG)
		dump_ptr_address(raw_app_config.get());
		dump_ptr_address(theme_manager.get());
		dump_ptr_address(main_window);

	#endif	// clang-format on
}
