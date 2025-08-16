#ifndef THEME_MANAGER_HXX
#define THEME_MANAGER_HXX

#include <qmainwindow.h>
#include <qwidget.h>

#include <memory>

#include "../../ffi/raw/config.hxx"

using std::unique_ptr;

namespace Lazyboard::front_end {
class ThemeManager {
   public:
	void set_main_window_theme(QMainWindow *main_window,
							   RawAppConfig *raw_app_config);
};
}  // namespace Lazyboard::front_end

#endif