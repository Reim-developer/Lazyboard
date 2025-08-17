#ifndef MAIN_WINDOWS_HXX
#define MAIN_WINDOWS_HXX

#include <qmainwindow.h>
#include <qobject.h>

#include <QGridLayout>
#include <memory>
#include <string>

#include "../../front_end_db/include/sqlite_manager.hxx"
#include "about_widget.hxx"
#include "main_window_preload.hxx"
#include "setting_widget.hxx"
#include "table_widget.hxx"

using Lazyboard::front_end_db::SQLiteManager;
using std::string;
using std::unique_ptr;

namespace Lazyboard::front_end {
class MainWindow {
   private:
	using Self = MainWindow;
	using Window = QMainWindow;
	using Layout = QGridLayout;

   private:
	static constexpr int MIN_WIDTH = 600;
	static constexpr int MIN_HEIGHT = 400;

   public:
	MainWindow();

   private:
	Layout *grid_layout;
	QWidget *central_widget;

   private:
	unique_ptr<Window> main_window;
	unique_ptr<TableWidget> table_widget;
	unique_ptr<SettingWidget> setting_widget;
	unique_ptr<AboutWidget> about_widget;
	unique_ptr<MainWindowPreload> main_window_preload;
	unique_ptr<SQLiteManager> sqlite_manager;

   public:
	Self *init_main_window();
	void front_end_show();
};
}  // namespace Lazyboard::front_end

#endif	// MAIN_WINDOWS_HXX