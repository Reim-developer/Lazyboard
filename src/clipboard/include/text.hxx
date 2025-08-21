#ifndef TEXT_CLIPBOARD_HXX
#define TEXT_CLIPBOARD_HXX
#include <qclipboard.h>

#include <memory>
#include <string>

#include "../../front_end_db/include/sqlite_manager.hxx"

using Lazyboard::front_end_db::SQLiteManager;
using std::string;
using std::unique_ptr;

namespace Lazyboard::clipboard {
class TextClipboard {
   private:
	QClipboard *clipboard = nullptr;
	unique_ptr<SQLiteManager> sqlite_manager;

   private:
	void save_to_cache();

   public:
	TextClipboard();
	void on_changed();
	string get();
};
}  // namespace Lazyboard::clipboard

#endif	// TEXT_CLIPBOARD_HXX