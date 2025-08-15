#include "include/about_window.hxx"

#include <qdialog.h>
#include <qgridlayout.h>
#include <qlogging.h>
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
	github_issue_button = make_unique<QPushButton>();
	github_pull_button = make_unique<QPushButton>();
}

void Self::is_open_browser_ok(OpenBrowserStatus status) {
	switch (status) {
		case OpenBrowserStatus::OK:
			break;

		case OpenBrowserStatus::OPEN_BROWSER_FAILED:
			QMessageBox::critical(about_window.get(), "Error",
								  "Could not open your browser");
			break;

		case OpenBrowserStatus::WRAP_RAW_C_FAILED:
			QMessageBox::critical(about_window.get(), "Error",
								  "Could not wrap C raw to safety string");

			break;
		case OpenBrowserStatus::URL_IS_EMPTY:
			QMessageBox::critical(about_window.get(), "Error", "Url is empty");
			break;
	}
}

void Self::open_browser_when_clicked(QPushButton *button, const char *url) {
	const auto open_browser = [this, url] {
		auto status = Lazyboard::ffi::open_browser(url);
		is_open_browser_ok(status);
	};

	QObject::connect(button, &QPushButton::clicked, open_browser);
}

void Self::setup_buttons() {
	github_button->setText("GitHub | Source Code");
	github_button->setToolTip("Get Lazyboard source code");

	github_issue_button->setText("Issue | Bug Report");
	github_issue_button->setToolTip("Report issue/bug");

	github_pull_button->setText("Pull Request | Contribute");
	github_pull_button->setToolTip("Contribute");

	this->open_browser_when_clicked(github_button.get(), GITHUB_URL);
	this->open_browser_when_clicked(github_issue_button.get(),
									GITHUB_ISSUE_URL);
	this->open_browser_when_clicked(github_pull_button.get(), GITHUB_PULL_URL);

	grid_layout->addWidget(github_button.get(), 0, 0);
	grid_layout->addWidget(github_issue_button.get(), 0, 1);
	grid_layout->addWidget(github_pull_button.get(), 1, 0);
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