#ifndef ERROR_TYPES_HXX
#define ERROR_TYPES_HXX

#include <array>
#include <cstdint>
#include <initializer_list>
#include <map>
#include <string_view>
#include <utility>

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
	WRITE_FILE_FAILED,
	CONVERT_TO_MUT_FAILED,
	CONVERT_TO_C_STR_FAILED,
	PARSE_TOML_FAILED,
	READ_FILE_FAILED,
	UTF_8_ERROR,
};

using Types = initializer_list<pair<ErrorTypes, string_view>>;
inline constexpr Types error_types_map() noexcept {
	using E = ErrorTypes;

	const Types error_types = {
		{E::INVALID_HEX_COLOR,
		 "Invalid HEX color, please check your TOML configuration and try "
		 "again"},
		{E::CREATE_DIR_FAILED, "Create directory failed"},
		{E::GET_CONFIG_DIR_FAILED, "Get configuration directory failed"},
		{E::CREATE_FILE_FAILED, "Create file faled"},
		{E::TOML_TO_STRING_FAILED, "Could not convert TOML to string"},
		{E::WRITE_FILE_FAILED, "Could not write file"},
		{E::CONVERT_TO_MUT_FAILED, "Could not convert value to '*mut c_char'"},
		{E::CONVERT_TO_C_STR_FAILED, "Could not convert value to 'c_str'"},
		{E::PARSE_TOML_FAILED,
		 "Could not parse TOML, please check your configuration and try "
		 "again"},
		{E::READ_FILE_FAILED, "Could not read file"},
		{E::UTF_8_ERROR, "UTF-8 error"},

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