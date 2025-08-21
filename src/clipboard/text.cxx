#include "include/text.hxx"

#include <qapplication.h>
#include <qclipboard.h>
#include <qobject.h>

#include <memory>

using Lazyboard::clipboard::TextClipboard;
using Self = TextClipboard;
using std::make_unique;

Self::TextClipboard() {
	if (!this->clipboard) {
		this->clipboard = QApplication::clipboard();
	}

	sqlite_manager = make_unique<SQLiteManager>();
}

void Self::save_to_cache() {}

void Self::on_changed() {
	using O = QObject;

	O::connect(this->clipboard, &QClipboard::dataChanged, [] {

	});
}

string Self::get() {
	auto clipboard_text = this->clipboard->text();

	return clipboard_text.toStdString();
}