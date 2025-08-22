#include <cassert>
#include <cstdint>
#include <memory>
#include <string>

using std::make_unique;
using std::string;
using std::uint8_t;
using std::unique_ptr;

extern "C" enum ReadAppConfigStatus : uint8_t {
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
} AppSettings;

extern "C" typedef struct {
	char *background_color;
	char *foreground_color;
	char *background_button_color;
	char *foreground_button_color;
	char *background_table_header_color;
	char *foreground_table_header_color;
} AppGuiSettings;

extern "C" typedef struct {
	AppSettings raw_app_settings;
	AppGuiSettings raw_app_gui_settings;
} AppConfig;

extern "C" ReadAppConfigStatus read_exists_config(const char *file_path,
												  AppConfig *out);

extern "C" void free_app_config(AppConfig *config);

int main() {
	using Status = ReadAppConfigStatus;

	const char *path = "demo.toml";
	unique_ptr<AppConfig> raw = make_unique<AppConfig>();

	auto result = read_exists_config(path, raw.get());
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

	free_app_config(raw.get());

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