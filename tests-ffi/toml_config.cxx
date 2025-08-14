#include <cassert>
#include <cstdint>
#include <memory>

using std::make_unique;
using std::uint8_t;
using std::unique_ptr;

extern "C" enum RawReadAppConfigStatus : uint8_t {
    OK,
    READ_FILE_FAILED,
    UTF_8_ERROR,
    PARSE_TOML_FAILED,
    CONVERT_TO_MUT_FAILED
};

extern "C" struct RawAppSettings {
    bool hide_when_closed;
    bool notification;
};

extern "C" RawReadAppConfigStatus raw_exists_config(const char *file_path,
                                                    RawAppSettings *config_out);

int main() {
    using Status = RawReadAppConfigStatus;

    const char *path = "demo.toml";
    struct unique_ptr<RawAppSettings> raw = make_unique<RawAppSettings>();
    auto result = raw_exists_config(path, raw.get());

    assert(result != Status::UTF_8_ERROR);
    assert(result != Status::PARSE_TOML_FAILED);
    assert(result != Status::READ_FILE_FAILED);
    assert(result != Status::CONVERT_TO_MUT_FAILED);
    assert(result == Status::OK);

    assert(raw->hide_when_closed != true);
    assert(raw->hide_when_closed == false);
    assert(raw->notification != false);
    assert(raw->notification == true);

    return 0;
}