#include "include/about_window.hxx"

#include <qdialog.h>
#include <qgridlayout.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qpushbutton.h>

#include <QMessageBox>
#include <memory>

#include "../ffi/namespace/include/utils.hxx"
using Lazyboard::front_end::AboutWindow;
using std::make_unique;
using Self = AboutWindow;

AboutWindow::AboutWindow() {
  about_window = make_unique<QDialog>();
  grid_layout = make_unique<QGridLayout>();
  github_button = make_unique<QPushButton>();
}

void Self::on_github_button_clicked() {
  const auto get_source_code = [this] {
    const char *github_url = "https://github.com/reim-developer/zClipboard";

    auto is_ok = Lazyboard::ffi::browser_open(github_url);

    if (!is_ok) {
      QMessageBox::critical(about_window.get(), "Error",
                            "Could not open web browser.");
      return;
    }
  };

  QObject::connect(github_button.get(), &QPushButton::clicked, get_source_code);
}

void Self::setup_buttons() {
  github_button->setText("GitHub | Soure Code");
  this->on_github_button_clicked();

  grid_layout->addWidget(github_button.get(), 0, 0);
}

void Self::setup_front_end() {
  about_window->setLayout(this->grid_layout.get());
  this->setup_buttons();
}

void Self::show_window() {
  about_window->setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
  about_window->setWindowTitle("Lazyboard About");

  this->setup_front_end();
  about_window->exec();
}