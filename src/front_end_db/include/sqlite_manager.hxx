#ifndef SQLITE_MANAGER_HXX
#define SQLITE_MANAGER_HXX
#include <qmainwindow.h>

#include "../../ffi/include/sqlite.h"
#include "../../ffi/include/utils.h"

namespace Lazyboard::front_end_db {
class SQLiteManager {
   private:
	void on_create_folder_error(const ResultContext &result) noexcept;
	void on_create_clipboard_cache_error(const QueryResult &status) noexcept;

   public:
	void create_clipboard_cache(QMainWindow *main_window);

   private:
	QMainWindow *_main_window;
};
}  // namespace Lazyboard::front_end_db

#endif	// SQLITE_MANAGER_HXX