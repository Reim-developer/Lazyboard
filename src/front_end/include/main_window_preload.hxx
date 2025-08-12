#ifndef MAIN_WINDOW_PRELOAD_HXX
#define MAIN_WINDOW_PRELOAD_HXX

#include <qmainwindow.h>

#include "../../ffi/raw/config.hxx"

namespace Lazyboard::front_end {
class MainWindowPreload {
 private:
  void on_error(WriteConfigStatus status, QMainWindow *main_window);

 public:
  void create_default_config(QMainWindow *main_window);
};
}  // namespace Lazyboard::front_end

#endif  // PRELOAD_HXX