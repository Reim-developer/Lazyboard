#ifndef CONFIG_RAW_HXX
#define CONFIG_RAW_HXX

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint>

/* From module `utils::fs_utils` in Rust backend */
enum WriteConfigStatus : uint8_t {
	OK,
	TOML_TO_STRING_FAILED,
	CREATE_DIR_FAILED,
	CREATE_FILE_FAILED,
	WRITE_FILE_FAILED,
	GET_DATA_LOCAL_FAILED,
};

char *raw_config_dir();
auto raw_write_default_config() -> WriteConfigStatus;
/* End module */

/* From module `raw_config` in Rust backend */
enum RawReadAppConfigStatus : uint8_t {
	READ_OK,
	READ_FILE_FAILED,
	UTF_8_ERROR,
	PARSE_TOML_FAILED,
	CONVERT_TO_MUT_FAILED,
};

typedef struct {
	bool hide_when_closed;
	bool notification;
} RawAppSettings;

typedef struct {
	char *background_color;
	char *foreground_color;
} RawAppGuiSettings;

typedef struct {
	RawAppSettings raw_app_settings;
	RawAppGuiSettings raw_app_gui_settings;
} RawAppConfig;

RawReadAppConfigStatus raw_exists_config(const char *path,
										 RawAppConfig *config_out);
void raw_free_cstr_app_config(RawAppConfig *config);
/* End module */

#ifdef __cplusplus
}
#endif
#endif