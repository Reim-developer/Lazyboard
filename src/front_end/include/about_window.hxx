#ifndef ABOUT_WINDOW_HXX
#define ABOUT_WINDOW_HXX

#include <qdialog.h>
#include <qgridlayout.h>
#include <qpushbutton.h>

#include <memory>
using std::unique_ptr;

namespace Lazyboard::front_end {
class AboutWindow {
 private:
  unique_ptr<QDialog> about_window;
  unique_ptr<QGridLayout> grid_layout;
  unique_ptr<QPushButton> github_button;

 private:
  static constexpr int MIN_WIDTH = 600;
  static constexpr int MIN_HEIGHT = 600;

 private:
  void on_github_button_clicked();

 private:
  void setup_front_end();
  void setup_buttons();

 public:
  AboutWindow();
  void show_window();
};
}  // namespace Lazyboard::front_end

#endif