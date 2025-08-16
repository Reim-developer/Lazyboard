#ifndef ERROR_TYPES_HXX
#define ERROR_TYPES_HXX

#include <array>
#include <initializer_list>
#include <utility>
#if !defined(LAZY_DEBUG)
	#error "Could not include 'error_debug' if 'LAZY_DEBUG' is disabled.
#endif
#include <cstdint>
#include <map>
#include <string_view>

namespace Lazyboard::front_end_utils {

using std::array;
using std::initializer_list;
using std::map;
using std::pair;
using std::string_view;
using std::uint8_t;

enum class ErrorTypes : uint8_t {
	INVALID_HEX_COLOR = 1,
	CREATE_DIR_FAILED,
	GET_CONFIG_DIR_FAILED,
	CREATE_FILE_FAILED,
	TOML_TO_STRING_FAILED,
};

using Types = initializer_list<pair<ErrorTypes, string_view>>;
inline constexpr Types error_types_map() noexcept {
	using E = ErrorTypes;

	const Types error_types = {
		pair{E::INVALID_HEX_COLOR, "INVALID_HEX_COLOR"},
		pair{E::CREATE_DIR_FAILED, "CREATE_DIR_FAILED"},
		pair{E::GET_CONFIG_DIR_FAILED, "GET_CONFIG_DIR_FAILED"},
		pair{E::CREATE_FILE_FAILED, "CREATE_FILE_FAILED"},
		pair{E::TOML_TO_STRING_FAILED, "TOML_TO_STRING_FAILED"},
	};

	return error_types;
}

inline constexpr string_view error_to_string(ErrorTypes error) noexcept {
	for (const auto &error_types : error_types_map()) {
		if (error_types.first == error) {
			return error_types.second;
		}
	}

	return "UNKOWN_ERROR";
}

}  // namespace Lazyboard::front_end_utils
#endif	// ERROR_TYPES_HXX