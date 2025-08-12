#include <QApplication>
#include <memory>

#include "front_end/include/main_window.hxx"

using Lazyboard::front_end::MainWindow;
using std::make_unique;
using std::unique_ptr;

int main(int argc, char *argv[]) {
  unique_ptr<QApplication> application = make_unique<QApplication>(argc, argv);
  unique_ptr<MainWindow> main_window = make_unique<MainWindow>();

  main_window->init_main_window();

  return application->exec();
}