#ifndef ABOUT_WINDOW_HXX
#define ABOUT_WINDOW_HXX

#include <qdialog.h>
#include <qgridlayout.h>
#include <qpushbutton.h>

#include <memory>

#include "../../ffi/raw/utils.hxx"
using std::unique_ptr;

namespace Lazyboard::front_end {
class AboutWindow {
 private:
  unique_ptr<QDialog> about_window;
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
  void is_open_browser_ok(OpenBrowserStatus status);
  void open_browser_when_clicked(QPushButton *button, const char *url);

 private:
  void setup_front_end();
  void setup_buttons();

 public:
  AboutWindow();
  void show_window();
};
}  // namespace Lazyboard::front_end

#endif