#include "include/main_window_preload.hxx"

#include <qcolor.h>
#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qpalette.h>

#include <memory>
#include <sstream>
#include <string>

#include "../ffi/namespace/include/config.hxx"
#include "../ffi/namespace/include/utils.hxx"

#if defined(LAZY_DEBUG)
	#include <iostream>
using std::cout;
#endif

using Lazyboard::front_end::MainWindowPreload;
using Self = MainWindowPreload;

using std::make_unique;
using std::string;
using std::stringstream;
using namespace Lazyboard::ffi;

void Self::on_gen_default_cfg_error(WriteConfigStatus status,
									QMainWindow *main_window) {
	switch (status) {
		case WriteConfigStatus::OK:
			break;

		case WriteConfigStatus::CREATE_DIR_FAILED:
			QMessageBox::critical(main_window, "Error",
								  "Could not create config directory");

			break;

		case WriteConfigStatus::GET_DATA_LOCAL_FAILED:
			QMessageBox::critical(main_window, "Error",
								  "Could not get application local data");
			break;

		case WriteConfigStatus::CREATE_FILE_FAILED:
			QMessageBox::critical(main_window, "Error",
								  "Could not create configuration file");
			break;

		case WriteConfigStatus::WRITE_FILE_FAILED:
			QMessageBox::critical(main_window, "Error",
								  "Could not write configuration");
			break;

		case WriteConfigStatus::TOML_TO_STRING_FAILED:
			QMessageBox::critical(main_window, "Error",
								  "Could not convert TOML data to string");
			break;
	}
}

void Self::on_read_exists_cfg_error(RawReadAppConfigStatus status,
									QMainWindow *main_window) {
	using Status = RawReadAppConfigStatus;

	switch (status) {
		case Status::READ_OK:
			break;

		case Status::CONVERT_TO_MUT_FAILED:
			QMessageBox::critical(main_window, "Error",
								  "Could not convert to *mut c_char");
			break;

		case Status::PARSE_TOML_FAILED:
			QMessageBox::critical(main_window, "Error",
								  "Parse TOML configuration failed");
			break;

		case Status::READ_FILE_FAILED:
			QMessageBox::critical(main_window, "Error",
								  "Could not read configuration file");
			break;

		case Status::UTF_8_ERROR:
			QMessageBox::critical(main_window, "Error",
								  "UTF-8 error in configuration file");
			break;

		case Status::CONVERT_TO_C_STR_FAILED:
			QMessageBox::critical(
				main_window, "Error",
				"Could not convert value configuration to C string");
			break;
	}
}

string Self::application_config() {
	auto config_dir_raw = ffi::config_dir();

	stringstream string_stream;
	string_stream << config_dir_raw << "/Lazyboard"
				  << "/settings.toml";
	string config_path = string_stream.str();

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
				cout << "[DEBUG] " << "Config path not found, generate at: " << config_path
					<< "\n";
		#endif

		return;
	}

	#if defined(LAZY_DEBUG)
		cout << "[DEBUG] " <<"Found config path at:" << config_path << "\n";
	#endif	// clang-format on
}

void Self::set_application_theme(QMainWindow *main_window,
								 RawAppConfig *app_config) {
	auto bg_color = string(app_config->raw_app_gui_settings.background_color);
	auto fg_color = string(app_config->raw_app_gui_settings.foreground_color);
	auto bg_button_color =
		string(app_config->raw_app_gui_settings.background_button_color);
	auto fg_button_color =
		string(app_config->raw_app_gui_settings.foreground_button_color);

	auto bg_hex = QColor(QString::fromStdString(bg_color));
	auto fg_hex = QColor(QString::fromStdString(fg_color));
	auto bg_btn_hex = QColor(QString::fromStdString(bg_button_color));
	auto fg_btn_hex = QColor(QString::fromStdString(fg_button_color));
	free_cstr_app_config(raw_app_config.get());

	if (!bg_hex.isValid() || !fg_hex.isValid() || !bg_btn_hex.isValid() ||
		!fg_btn_hex.isValid()) {
		stringstream string_stream;

		string_stream << "Invalid HEX color, please check your configuration\n"
					  << "Your 'background_color' setting: " << bg_color << "\n"
					  << "Your 'foreground_color' setting: " << fg_color << "\n"
					  << "Your 'background_button_color' settings: "
					  << bg_button_color << "\n"
					  << "Your 'foreground_button_color' settings: "
					  << fg_button_color << "\n";

		auto error_message = string_stream.str();
		QMessageBox::critical(main_window, "Error", error_message.c_str());

		// clang-format off
		#if defined (LAZY_DEBUG)
			stringstream string_stream_debug;
			string_stream_debug  
				<< "[DEBUG] Found error when load TOML configuration:\n"
				<< "[DEBUG] Error Type: 'Invalid HEX Color'\n"
				<< "[DEBUG] 'bg_color' setting: " << bg_color << "\n"
				<< "[DEBUG] 'fg_color' setting: " << fg_color << "\n"
				<< "[DEBUG] 'bg_button_color' setting: " << bg_button_color << "\n";

			cout << string_stream_debug.str().c_str();

		#endif	// clang-format on

		return;
	}

	QPalette palette;

	palette.setColor(QPalette::Window, bg_hex);
	palette.setColor(QPalette::Base, bg_hex);
	palette.setColor(QPalette::Text, fg_hex);

	// clang-format off
	auto stylesheet = QString(
	R"""(
		QPushButton {
			background-color: %1;
			qproperty-autoFillBackground: true;
			color: %2;
		}
	)""").arg(bg_btn_hex.name(), fg_btn_hex.name());	// clang-format on

	main_window->setPalette(palette);
	main_window->setAutoFillBackground(true);
	main_window->setStyleSheet(stylesheet);
}

void Self::read_if_exists_config(QMainWindow *main_window) {
	raw_app_config = make_unique<RawAppConfig>();
	auto config_path = this->application_config();

	auto status = exists_config(config_path.data(), raw_app_config.get());
	this->on_read_exists_cfg_error(status, main_window);

	// clang-format off
	#if defined(LAZY_DEBUG)
		cout << "[DEBUG] " << "Found config setting 'background_color': "
			<< raw_app_config->raw_app_gui_settings.background_color << "\n";

		cout << "[DEBUG] " << "Found config setting 'foreground_color': "
			<< raw_app_config->raw_app_gui_settings.foreground_color << "\n";
		
		cout << "[DEBUG] " << "Found config setting 'background_button_color': "
			<< raw_app_config->raw_app_gui_settings.background_button_color << "\n";
		
		cout << "[DEBUG] " << "Found config setting 'foreground_button_color': "
			<< raw_app_config->raw_app_gui_settings.foreground_color << "\n";
	#endif	// clang-format on

	this->set_application_theme(main_window, raw_app_config.get());
}
