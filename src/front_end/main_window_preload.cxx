#include "include/main_window_preload.hxx"

#include <qcolor.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qpalette.h>

#include <memory>
#include <print>
#include <string>

#include "../ffi/include/config.h"
#include "../ffi/include/utils.h"
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

using Lazyboard::front_end_utils::error_dialog_show;
using Lazyboard::front_end_utils::ErrorTypes;
using std::format;
using std::make_unique;
using std::string;

void Self::on_gen_default_cfg_error(ConfigResult status,
									QMainWindow *main_window) {
	switch (status) {
		using E = ErrorTypes;

		case ConfigResult::OK:
			break;

		case ConfigResult::CREATE_DIR_FAILED:
			error_dialog_show(main_window, E::CREATE_DIR_FAILED);

			break;

		case ConfigResult::GET_CONFIG_DIR_FAILED:
			error_dialog_show(main_window, E::GET_CONFIG_DIR_FAILED);
			break;

		case ConfigResult::CREATE_FILE_FAILED:
			error_dialog_show(main_window, E::CREATE_FILE_FAILED);
			break;

		case ConfigResult::WRITE_FILE_FAILED:
			error_dialog_show(main_window, E::WRITE_FILE_FAILED);
			break;

		case ConfigResult::TOML_TO_STRING_FAILED:
			error_dialog_show(main_window, E::TOML_TO_STRING_FAILED);
			break;
	}
}

void Self::on_read_exists_cfg_error(ReadConfigResult status,
									QMainWindow *main_window) {
	using Status = ReadConfigResult;
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
			error_dialog_show(main_window, E::UTF_8_ERR);
			break;

		case Status::CONVERT_TO_C_STR_FAILED:
			error_dialog_show(main_window, E::CONVERT_TO_C_STR_ERR);
			break;
	}
}

string Self::application_config() {
	char *out = nullptr;
	auto result = config_dir(&out);
	string config_path = format("{}/Lazyboard/settings.toml", out);

	free_alloc(out);
	return config_path;
}

void Self::create_default_config(QMainWindow *main_window) {
	auto config_path = this->application_config();
	auto is_config_exists = path_exists(config_path.data());

	if (!is_config_exists) {
		auto status = create_default_cfg();
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
	raw_app_config = make_unique<AppConfig>();
	theme_manager = make_unique<ThemeManager>();

	auto config_path = this->application_config();
	auto status = read_exists_config(config_path.data(), raw_app_config.get());
	this->on_read_exists_cfg_error(status, main_window);

	theme_manager->set_main_window_theme(main_window, raw_app_config.get());

	// clang-format off
	#if defined (LAZY_DEBUG)
		dump_ptr_address(raw_app_config.get());
		dump_ptr_address(theme_manager.get());
		dump_ptr_address(main_window);

	#endif	// clang-format on
}
