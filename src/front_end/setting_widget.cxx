#include "include/setting_widget.hxx"

#include <qgridlayout.h>
#include <qpushbutton.h>

#include <memory>

using Lazyboard::front_end::SettingWidget;
using std::make_unique;
using Self = SettingWidget;

SettingWidget::SettingWidget() { open_setting = make_unique<QPushButton>(); }

void Self::setup_widget(QGridLayout *grid_layout) {
    open_setting->setText("Settings");

    grid_layout->addWidget(open_setting.get(), 0, 1);
}