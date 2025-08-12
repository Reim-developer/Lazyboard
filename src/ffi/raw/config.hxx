#ifndef CONFIG_RAW_HXX
#define CONFIG_RAW_HXX

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint>

enum WriteConfigStatus : uint8_t {
  OK,
  TOML_TO_STRING_FAILED,
  CREATE_DIR_FAILED,
  CREATE_FILE_FAILED,
  WRITE_FILE_FAILED,
  GET_DATA_LOCAL_FAILED,
};

char *raw_local_data();
WriteConfigStatus raw_write_default_config();

#ifdef __cplusplus
}
#endif
#endif