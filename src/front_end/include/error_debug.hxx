#ifndef ERROR_DEBUG_HXX
#define ERROR_DEBUG_HXX

#if !defined(LAZY_DEBUG)
	#error "Could not include 'error_debug' if 'LAZY_DEBUG' is disabled.
#endif
#include <cstdint>
#include <map>
#include <string_view>

namespace Lazyboard::front_end {
using std::map;
using std::string_view;
using std::uint8_t;

// clang-format off
enum class ErrorDebugType : uint8_t{
	INVALID_HEX_COLOR = 1,
};	// clang-format on

inline const map<ErrorDebugType, string_view> &error_type() {
	static const map<ErrorDebugType, string_view> error_type = {
		{ErrorDebugType::INVALID_HEX_COLOR, "INVALID_HEX_COLOR"},
	};

	return error_type;
}

}  // namespace Lazyboard::front_end
#endif	// ERROR_DEBUG_HXX