#ifndef FRONT_END_UTILS_HXX
#define FRONT_END_UTILS_HXX

#include <qcolor.h>
#include <qcontainerfwd.h>
#include <qicon.h>
#include <qmessagebox.h>
#include <qpixmap.h>
#include <qstringview.h>
#include <qwidget.h>

#include <initializer_list>
#include <type_traits>
#include <vector>

#include "error_types.hxx"

using std::initializer_list;
using std::is_same_v;
using std::stringstream;
using std::vector;

namespace Lazyboard::front_end_utils {

template <typename T>
concept is_qcolor = requires(const T& t) { QColor(t); };

template <is_qcolor... Args>
inline constexpr bool is_valid_hex_color(const Args&... args) noexcept {
	return (
		[&]() {
			QColor color(args);

			if (!color.isValid()) {
				return false;
			}

			return true;
		}(),
		...);
}

inline QIcon image_from_bytes(const initializer_list<uint8_t>& data) noexcept {
	QByteArray bytes_array;
	bytes_array.reserve(static_cast<int>(data.size()));

	for (auto byte : data) {
		bytes_array.append(static_cast<char>(byte));
	}

	QPixmap pixmap;
	if (pixmap.loadFromData(bytes_array)) {
		return QIcon(pixmap);
	}

	return QIcon();
}

inline void error_dialog_show(QWidget* parent, const QString& message,
							  ErrorTypes error_types) noexcept {
	auto error_string = error_to_string(error_types).data();
	auto fmt_msg = QString("%1\nError name: %2").arg(message).arg(error_string);

	QMessageBox::critical(parent, "Error", fmt_msg);
}

}  // namespace Lazyboard::front_end_utils

#endif