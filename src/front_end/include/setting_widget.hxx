#ifndef SETTING_WIDGET_HXX
#define SETTING_WIDGET_HXX

#include <qgridlayout.h>
#include <qpushbutton.h>

#include <memory>

using std::unique_ptr;

namespace Lazyboard::front_end {
class SettingWidget {
   private:
    unique_ptr<QPushButton> open_setting;

   public:
    SettingWidget();
    void setup_widget(QGridLayout* grid_layout);
};

}  // namespace Lazyboard::front_end

#endif