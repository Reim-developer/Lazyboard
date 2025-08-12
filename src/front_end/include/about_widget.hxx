#ifndef ABOUT_WIDGET_HXX
#define ABOUT_WIDGET_HXX

#include <qgridlayout.h>
#include <qpushbutton.h>

#include <memory>

#include "about_window.hxx"

using std::unique_ptr;

namespace Lazyboard::front_end {
class AboutWidget {
 public:
  AboutWidget();

 private:
  unique_ptr<QPushButton> show_about;
  unique_ptr<AboutWindow> about_window;

 private:
  void setup_event();

 public:
  void setup_widget(QGridLayout *layout);
};

}  // namespace Lazyboard::front_end

#endif  // ABOUT_WIDGET_HXX