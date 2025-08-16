#include "include/theme_manager.hxx"

#include <qmainwindow.h>
#include <qmessagebox.h>

#include <memory>
#include <sstream>
#include <string>

#include "../ffi/namespace/include/config.hxx"

#if defined(LAZY_DEBUG)
	#include <iostream>

	#include "include/error_debug.hxx"
using std::cout;
#endif

using namespace Lazyboard::ffi;

using std::make_unique;
using std::string;
using std::stringstream;
using Self = Lazyboard::front_end::ThemeManager;

void Self::set_main_window_theme(QMainWindow *main_window,
								 RawAppConfig *raw_app_config) {
	auto bg_color =
		string(raw_app_config->raw_app_gui_settings.background_color);
	auto fg_color =
		string(raw_app_config->raw_app_gui_settings.foreground_color);
	auto bg_button_color =
		string(raw_app_config->raw_app_gui_settings.background_button_color);
	auto fg_button_color =
		string(raw_app_config->raw_app_gui_settings.foreground_button_color);
	auto bg_header_table_color = string(
		raw_app_config->raw_app_gui_settings.background_table_header_color);
	auto fg_header_table_color = string(
		raw_app_config->raw_app_gui_settings.foreground_table_header_color);

	auto bg_hex = QColor(QString::fromStdString(bg_color));
	auto fg_hex = QColor(QString::fromStdString(fg_color));
	auto bg_btn_hex = QColor(QString::fromStdString(bg_button_color));
	auto fg_btn_hex = QColor(QString::fromStdString(fg_button_color));
	auto bg_header_table_hex =
		QColor(QString::fromStdString(bg_header_table_color));
	auto fg_header_table_hex =
		QColor(QString::fromStdString(fg_header_table_color));

	ffi::free_cstr_app_config(raw_app_config);

	if (!bg_hex.isValid() || !fg_hex.isValid() || !bg_btn_hex.isValid() ||
		!fg_btn_hex.isValid() || !bg_header_table_hex.isValid() ||
		!fg_header_table_hex.isValid()) {
		QMessageBox::critical(
			main_window, "Error",
			"Invalid HEX color, please check your configuration");

		// clang-format off
		#if defined (LAZY_DEBUG)
			const auto &type_err = error_type().at(ErrorDebugType::INVALID_HEX_COLOR);

			stringstream string_stream_debug;
			string_stream_debug  
				<< "[DEBUG] Found error when load TOML configuration:\n"
				<< "[DEBUG] Error Type: " << type_err << "\n"
				<< "[DEBUG] " << bg_color << "\n"
				<< "[DEBUG] " << fg_color << "\n"
				<< "[DEBUG] " << bg_button_color << "\n"
				<< "[DEBUG] " << fg_button_color << "\n"
				<< "[DEBUG] " << bg_header_table_color << "\n"
				<< "[DEBUG] " << fg_header_table_color << "\n";

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
		
		QHeaderView::section {
			background-color: %3;
			color: %4;
		}
	)""").arg(bg_btn_hex.name(), fg_btn_hex.name(), 
			  bg_header_table_hex.name(), fg_header_table_hex.name());  // clang-format on

	main_window->setPalette(palette);
	main_window->setAutoFillBackground(true);
	main_window->setStyleSheet(stylesheet);
}