#include "include/about_widget.hxx"

#include <qdebug.h>
#include <qgridlayout.h>
#include <qlogging.h>
#include <qmainwindow.h>
#include <qobject.h>
#include <qpushbutton.h>

#include <memory>

#include "include/about_window.hxx"

using Lazyboard::front_end::AboutWidget;
using std::make_unique;
using Self = AboutWidget;

AboutWidget::AboutWidget() { show_about = make_unique<QPushButton>(); }

void Self::setup_event() {
	about_window = make_unique<AboutWindow>();

	// clang-format off
	const auto function = [this]() {
		about_window->show_window();
	};	// clang-format on

	QObject::connect(show_about.get(), &QPushButton::clicked, function);
}

void Self::setup_widget(QGridLayout *grid_layout) {
	show_about->setText("About");
	grid_layout->addWidget(show_about.get(), 1, 1);

	this->setup_event();
}

void Self::setup_about_window_event(QMainWindow *main_window) {
	about_window->on_about_window_event(main_window);
}