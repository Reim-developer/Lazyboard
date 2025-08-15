#ifndef MAIN_WINDOW_PRELOAD_HXX
#define MAIN_WINDOW_PRELOAD_HXX

#include <qmainwindow.h>

#include <memory>
#include <string>

#include "../../ffi/raw/config.hxx"

using std::string;
using std::unique_ptr;

namespace Lazyboard::front_end {
class MainWindowPreload {
   private:
	unique_ptr<RawAppConfig> raw_app_config;

   private:
	void on_gen_default_cfg_error(WriteConfigStatus status,
								  QMainWindow *main_window);

	void on_read_exists_cfg_error(RawReadAppConfigStatus status,
								  QMainWindow *main_window);

	string application_config();
	void set_application_theme(QMainWindow *main_window,
							   RawAppConfig *app_config);

   public:
	void create_default_config(QMainWindow *main_window);
	void read_if_exists_config(QMainWindow *main_window);
};
}  // namespace Lazyboard::front_end

#endif	// PRELOAD_HXX