#include "include/main_window.hxx"

#include <qgridlayout.h>
#include <qmainwindow.h>
#include <qwidget.h>

#include <memory>

#include "include/about_widget.hxx"
#include "include/setting_widget.hxx"
#include "include/table_widget.hxx"

using Lazyboard::front_end::MainWindow;
using std::make_unique;

using Self = MainWindow;

Self::MainWindow() {
  main_window = make_unique<QMainWindow>();
  auto central_w = make_unique<QWidget>();
  auto layout_w = make_unique<QGridLayout>(central_w.get());

  main_window->setCentralWidget(central_w.get());

  central_widget = central_w.release();
  grid_layout = layout_w.release();
}

Self *Self::init_main_window() {
  main_window->setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
  main_window->setWindowTitle("Lazyboard");
  this->front_end_show();
  main_window->show();

  return this;
}

void Self::front_end_show() {
  table_widget = make_unique<TableWidget>();
  setting_widget = make_unique<SettingWidget>();
  about_widget = make_unique<AboutWidget>();

  table_widget->setup_widget(this->grid_layout);
  setting_widget->setup_widget(this->grid_layout);
  about_widget->setup_widget(this->grid_layout);
}