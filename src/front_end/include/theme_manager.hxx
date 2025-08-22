#ifndef THEME_MANAGER_HXX
#define THEME_MANAGER_HXX

#include <qmainwindow.h>
#include <qwidget.h>

#include <memory>
#include <string_view>

#include "../../ffi/include/config.h"

using std::string_view;
using std::unique_ptr;

namespace Lazyboard::front_end {
class ThemeManager {
   private:
	const char *data(string_view sv) noexcept { return sv.data(); }

   private:
	struct GuiSettings {
		string_view background_color;
		string_view foreground_color;
		string_view background_button_color;
		string_view foreground_button_color;
		string_view background_table_header_color;
		string_view foreground_table_header_color;
	};

   private:
	void on_invalid_hex_color_error(QMainWindow *main_window);
	auto gui_settings(AppConfig *raw_app_config) noexcept -> GuiSettings;

   public:
	void set_main_window_theme(QMainWindow *main_window,
							   AppConfig *raw_app_config) noexcept;
};
}  // namespace Lazyboard::front_end

#endif