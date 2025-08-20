#ifndef FRONT_END_UTILS_HXX
#define FRONT_END_UTILS_HXX

#include <qcolor.h>
#include <qcontainerfwd.h>
#include <qicon.h>
#include <qmessagebox.h>
#include <qpixmap.h>
#include <qstringview.h>
#include <qwidget.h>

#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <vector>

#include "error_types.hxx"

using std::abort;
using std::for_each;
using std::forward;
using std::initializer_list;
using std::is_same_v;
using std::stringstream;
using std::vector;

#if defined(LAZY_DEBUG)
	#include <print>
	#include <source_location>
using std::println;
using std::source_location;
#endif

namespace Lazyboard::front_end_utils {
template <typename T>
concept is_qcolor = requires(const T& t) { QColor(t); };

template <is_qcolor... Args>
inline constexpr bool is_valid_hex_color(Args&&... args) noexcept {
	return (... && [&]() {
		QColor color(std::forward<Args>(args));

		if (!color.isValid()) {
			return false;
		}

		return true;
	}());
}

using init_list = initializer_list<uint8_t>;
inline QIcon image_from_bytes(const init_list& data) noexcept {
	QByteArray bytes_array;
	bytes_array.reserve(static_cast<int>(data.size()));

	for_each(data.begin(), data.end(), [&bytes_array](auto bytes) {
		bytes_array.append(static_cast<char>(bytes));
	});

	QPixmap pixmap;
	if (pixmap.loadFromData(bytes_array)) {
		return QIcon(pixmap);
	}

	return QIcon();
}

inline void error_dialog_show(QWidget* parent,
							  ErrorTypes error_types) noexcept {
	auto error_string = error_to_string(error_types).data();

	QMessageBox::critical(parent, "Error", error_string);
	abort();
}

#if defined(LAZY_DEBUG)
const auto green = "\x1b[32m";
const auto white = "\x1b[37m";

using src_loc = source_location;
template <typename T>
inline void dump_ptr_address(T* t,
							 const src_loc& location = src_loc::current()) {
	auto file_name = location.file_name();
	auto file_line = location.line();

	println("{}[MEMORY_DEBUG]{} File: {}", green, white, file_name);
	println("{}[MEMORY_DEBUG]{} Line: {}", green, white, file_line);
	println("{}[MEMORY_DEBUG]{} {}", green, white, static_cast<void*>(t));
}

template <typename T>
concept string_bound = requires(const T& t) { string(t); };

template <typename string_bound>
inline void debug_info(string_bound&& information) {
	auto info = forward<string_bound>(information);

	println("{}[INFO_DEBUG]{} {}", green, white, info);
}

#endif

}  // namespace Lazyboard::front_end_utils

#endif