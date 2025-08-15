#include "include/about_widget.hxx"

#include <qdebug.h>
#include <qgridlayout.h>
#include <qlogging.h>
#include <qobject.h>
#include <qpushbutton.h>

#include <memory>

#include "include/about_window.hxx"

using Lazyboard::front_end::AboutWidget;
using std::make_unique;
using Self = AboutWidget;

AboutWidget::AboutWidget() { show_about = make_unique<QPushButton>(); }

void Self::setup_event() {
	const auto function = [this]() {
		if (!about_window) {
			about_window = make_unique<AboutWindow>();
		}

		about_window->show_window();
	};

	QObject::connect(show_about.get(), &QPushButton::clicked, function);
}

void Self::setup_widget(QGridLayout *grid_layout) {
	show_about->setText("About");
	this->setup_event();
	grid_layout->addWidget(show_about.get(), 1, 1);
}