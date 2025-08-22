#ifndef CONFIG_RAW_H
#define CONFIG_RAW_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint>

/* From module `utils::fs_utils` in Rust backend */
enum ConfigResult : uint8_t {
	OK,
	TOML_TO_STRING_FAILED,
	CREATE_DIR_FAILED,
	CREATE_FILE_FAILED,
	WRITE_FILE_FAILED,
	GET_CONFIG_DIR_FAILED,
};

auto create_default_cfg() -> ConfigResult;
/* End module */

/* From module `config` in Rust backend */
enum ReadConfigResult : uint8_t {
	READ_OK,
	READ_FILE_FAILED,
	UTF_8_ERROR,
	PARSE_TOML_FAILED,
	CONVERT_TO_MUT_FAILED,
	CONVERT_TO_C_STR_FAILED,
};

typedef struct {
	bool hide_when_closed;
	bool notification;
} AppSettings;

typedef struct {
	char *background_color;
	char *foreground_color;
	char *background_button_color;
	char *foreground_button_color;
	char *background_table_header_color;
	char *foreground_table_header_color;
} AppGuiSettings;

typedef struct {
	AppSettings raw_app_settings;
	AppGuiSettings raw_app_gui_settings;
} AppConfig;

ReadConfigResult read_exists_config(const char *path, AppConfig *config_out);
void free_app_config(AppConfig *config);
/* End module */

#ifdef __cplusplus
}
#endif
#endif	// CONFIG_H