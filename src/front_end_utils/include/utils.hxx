#ifndef FRONT_END_UTILS_HXX
#define FRONT_END_UTILS_HXX

#include <qcolor.h>

#include <type_traits>

using std::is_same_v;
using std::stringstream;
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

}  // namespace Lazyboard::front_end_utils

#endif