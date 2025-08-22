#ifndef ABOUT_WINDOW_HXX
#define ABOUT_WINDOW_HXX

#include <qdialog.h>
#include <qgridlayout.h>
#include <qmainwindow.h>
#include <qpushbutton.h>

#include <memory>

#include "../../ffi/include/utils.h"
using std::unique_ptr;

namespace Lazyboard::front_end {
class AboutWindow : public QDialog {
   private:
	unique_ptr<QGridLayout> grid_layout;
	unique_ptr<QPushButton> github_button;
	unique_ptr<QPushButton> github_issue_button;
	unique_ptr<QPushButton> github_pull_button;

   private:
	static constexpr int MIN_WIDTH = 600;
	static constexpr int MIN_HEIGHT = 600;
	const char *GITHUB_URL = "https://github.com/reim-developer/zClipboard";
	const char *GITHUB_ISSUE_URL =
		"https://github.com/reim-developer/zClipboard/issues";
	const char *GITHUB_PULL_URL =
		"https://github.com/reim-developer/zClipboard/pulls";

   private:
	QMainWindow *_main_window = nullptr;

   protected:
	void showEvent(QShowEvent *event) override;

   private:
	void is_open_browser_ok(ResultContext &status);
	void open_browser_when_clicked(QPushButton *button, const char *url);

   private:
	void setup_front_end();
	void setup_buttons();
	void on_closed(QMainWindow *main_window);

   public:
	AboutWindow();
	void show_window();
	void on_about_window_event(QMainWindow *main_window);
};
}  // namespace Lazyboard::front_end

#endif