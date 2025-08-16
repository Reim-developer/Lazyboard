#include <cassert>
#include <cstdint>
#include <memory>
#include <string>

using std::make_unique;
using std::string;
using std::uint8_t;
using std::unique_ptr;

extern "C" enum RawReadAppConfigStatus : uint8_t {
	OK,
	READ_FILE_FAILED,
	UTF_8_ERROR,
	PARSE_TOML_FAILED,
	CONVERT_TO_MUT_FAILED,
	CONVERT_TO_C_STR_FAILED,
};

extern "C" typedef struct {
	bool hide_when_closed;
	bool notification;
} RawAppSettings;

extern "C" typedef struct {
	char *background_color;
	char *foreground_color;
	char *background_button_color;
	char *foreground_button_color;
	char *background_table_header_color;
	char *foreground_table_header_color;
} RawAppGuiSettings;

extern "C" typedef struct {
	RawAppSettings raw_app_settings;
	RawAppGuiSettings raw_app_gui_settings;
} RawAppConfig;

extern "C" RawReadAppConfigStatus raw_exists_config(const char *file_path,
													RawAppConfig *config_out);

extern "C" void raw_free_cstr_app_config(RawAppConfig *config);

int main() {
	using Status = RawReadAppConfigStatus;

	const char *path = "demo.toml";
	unique_ptr<RawAppConfig> raw = make_unique<RawAppConfig>();

	auto result = raw_exists_config(path, raw.get());
	auto bg_color = string(raw->raw_app_gui_settings.background_color);
	auto fg_color = string(raw->raw_app_gui_settings.foreground_color);
	auto bg_btn_color =
		string(raw->raw_app_gui_settings.background_button_color);
	auto fg_btn_color =
		string(raw->raw_app_gui_settings.foreground_button_color);
	auto bg_header_table_color =
		string(raw->raw_app_gui_settings.background_table_header_color);
	auto fg_header_table_color =
		string(raw->raw_app_gui_settings.foreground_table_header_color);

	raw_free_cstr_app_config(raw.get());

	assert(result != Status::UTF_8_ERROR);
	assert(result != Status::PARSE_TOML_FAILED);
	assert(result != Status::READ_FILE_FAILED);
	assert(result != Status::CONVERT_TO_MUT_FAILED);
	assert(result != Status::CONVERT_TO_C_STR_FAILED);
	assert(result == Status::OK);

	assert(raw->raw_app_settings.hide_when_closed != true);
	assert(raw->raw_app_settings.hide_when_closed == false);
	assert(raw->raw_app_settings.notification != false);
	assert(raw->raw_app_settings.notification == true);

	assert(!bg_color.empty());
	assert(!fg_color.empty());
	assert(!bg_btn_color.empty());
	assert(!fg_btn_color.empty());
	assert(!bg_header_table_color.empty());
	assert(!fg_header_table_color.empty());

	assert(fg_header_table_color != "&!$!$?");
	assert(bg_header_table_color != "$!&#&!");
	assert(fg_header_table_color == "#ffffff");
	assert(bg_header_table_color == "#2f3136");

	assert(bg_color != "717841xx18");
	assert(fg_color != "81388181");
	assert(bg_btn_color != "31831d$");
	assert(bg_btn_color == "#2f3136");

	assert(fg_btn_color != "#&$!&!&");
	assert(fg_btn_color == "#ffffff");
	assert(bg_color == "#2f3136");
	assert(fg_color == "#ffffff");

	return 0;
}