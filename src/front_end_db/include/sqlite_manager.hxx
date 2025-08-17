#ifndef SQLITE_MANAGER_HXX
#define SQLITE_MANAGER_HXX
#include <qmainwindow.h>

#include "../../ffi/raw/sqlite.hxx"
#include "../../ffi/raw/utils.hxx"

namespace Lazyboard::front_end_db {
class SQLiteManager {
   private:
	using InitDataResult = InitDatabaseStatus;
	using MkdirResult = CreateFileSystemStatus;

	void on_create_folder_error(const MkdirResult &result) noexcept;
	void on_create_clipboard_cache_error(const InitDataResult &status) noexcept;

   public:
	void create_clipboard_cache(QMainWindow *main_window);

   private:
	QMainWindow *_main_window;
};
}  // namespace Lazyboard::front_end_db

#endif	// SQLITE_MANAGER_HXX