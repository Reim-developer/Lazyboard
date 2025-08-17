#include "include/theme_manager.hxx"

#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qtypes.h>

#include <memory>
#include <sstream>
#include <string>

#include "../ffi/namespace/include/config.hxx"
#include "../front_end_utils/include/error_types.hxx"
#include "../front_end_utils/include/utils.hxx"

#if defined(LAZY_DEBUG)
	#include <iostream>
using std::cout;
#endif

using namespace Lazyboard::ffi;
using Lazyboard::front_end_utils::error_to_string;
using Lazyboard::front_end_utils::ErrorTypes;
using Lazyboard::front_end_utils::is_valid_hex_color;

using std::make_unique;
using std::string;
using std::stringstream;
using Self = Lazyboard::front_end::ThemeManager;

auto Self::gui_settings(RawAppConfig *raw_app_config) noexcept -> GuiSettings {
	// clang-format off
	auto raw_background_color = raw_app_config->raw_app_gui_settings.background_color;
	auto raw_foreground_color = raw_app_config->raw_app_gui_settings.foreground_color;
	auto raw_background_button_color = raw_app_config->raw_app_gui_settings.background_button_color;
	auto raw_foreground_button_color = raw_app_config->raw_app_gui_settings.foreground_button_color;
	auto raw_background_header_table_color = raw_app_config->raw_app_gui_settings.background_table_header_color;
	auto raw_foreground_header_table_color = raw_app_config->raw_app_gui_settings.foreground_table_header_color;


	auto settings_gui = GuiSettings {
		.background_color = raw_background_color,
		.foreground_color = raw_foreground_color,
		.background_button_color = raw_background_button_color,
		.foreground_button_color = raw_foreground_color,
		.background_table_header_color = raw_background_header_table_color,
		.foreground_table_header_color = raw_foreground_header_table_color,
	};	// clang-format on

	return settings_gui;
}

void Self::on_invalid_hex_color_error(QMainWindow *main_window) {
	// clang-format off
	const auto error_name = error_to_string(ErrorTypes::INVALID_HEX_COLOR);
	const auto error_message = QString(R"(
Invalid HEX color, please check your TOML configuration
Error name: %1
		)").arg(error_name.data());	 // clang-format on

	QMessageBox::critical(main_window, "Error", error_message);
}

void Self::set_main_window_theme(QMainWindow *main_window,
								 RawAppConfig *raw_app_config) noexcept {
	auto settings_gui = this->gui_settings(raw_app_config);

	// clang-format off
	auto bg_color = data(settings_gui.background_color);
	auto fg_color = data(settings_gui.foreground_color);
	auto bg_button_color = data(settings_gui.background_button_color);
	auto fg_button_color = data(settings_gui.foreground_button_color);
	auto bg_header_table_color = data(settings_gui.background_table_header_color);
	auto fg_header_table_color = data(settings_gui.foreground_table_header_color);
	// clang-format on

	auto bg_hex = QColor(bg_color);
	auto fg_hex = QColor(fg_color);
	auto bg_btn_hex = QColor(bg_button_color);
	auto fg_btn_hex = QColor(fg_button_color);
	auto bg_header_table_hex = QColor(bg_header_table_color);
	auto fg_header_table_hex = QColor(fg_header_table_color);
	ffi::free_cstr_app_config(raw_app_config);

	const auto valid_color =
		is_valid_hex_color(bg_hex, fg_hex, bg_btn_hex, fg_btn_hex,
						   bg_header_table_hex, fg_header_table_hex);

	if (!valid_color) {
		on_invalid_hex_color_error(main_window);

		// clang-format off
		#if defined (LAZY_DEBUG)
			const auto error_name = error_to_string(ErrorTypes::INVALID_HEX_COLOR);
			stringstream string_stream_debug;

			string_stream_debug  
				<< "[DEBUG] Found error when load TOML configuration:\n"
				<< "[DEBUG] Error Type: " << error_name << "\n"
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