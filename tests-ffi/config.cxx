
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::uint8_t;

enum WriteConfigStatus : uint8_t {
    OK,
    TOML_TO_STRING_FAILED,
    CREATE_DIR_FAILED,
    CREATE_FILE_FAILED,
    WRITE_FILE_FAILED,
    GET_DATA_LOCAL_FAILED,
};

extern "C" char *raw_local_data();
extern "C" void raw_free_c_str(char *str);
extern "C" WriteConfigStatus raw_write_default_config();

void gen_config_test() {
    auto status = raw_write_default_config();

    assert(status != WriteConfigStatus::WRITE_FILE_FAILED);
    assert(status != WriteConfigStatus::CREATE_FILE_FAILED);
    assert(status != WriteConfigStatus::CREATE_DIR_FAILED);
    assert(status != WriteConfigStatus::GET_DATA_LOCAL_FAILED);
    assert(status != WriteConfigStatus::TOML_TO_STRING_FAILED);
    assert(status == WriteConfigStatus::OK);
}

int main() {
    auto raw_result = raw_local_data();
    auto result = string(raw_result);
    raw_free_c_str(raw_result);

    gen_config_test();
    assert(!result.empty());

    return 0;
}