#include "include/main_window_preload.hxx"

#include <qmainwindow.h>
#include <qmessagebox.h>

#include <sstream>
#include <string>

#include "../ffi/namespace/include/config.hxx"
#include "../ffi/namespace/include/utils.hxx"

#if defined(LAZY_DEBUG)
#include <qdebug.h>
#include <qstring.h>
#endif

using Lazyboard::front_end::MainWindowPreload;
using Self = MainWindowPreload;

using std::string;
using std::stringstream;
using namespace Lazyboard::ffi;

void Self::on_error(WriteConfigStatus status, QMainWindow* main_window) {
    switch (status) {
        case WriteConfigStatus::OK:
            break;

        case WriteConfigStatus::CREATE_DIR_FAILED:
            QMessageBox::critical(main_window, "Error",
                                  "Could not create config directory");
            break;

        case WriteConfigStatus::GET_DATA_LOCAL_FAILED:
            QMessageBox::critical(main_window, "Error",
                                  "Could not get application local data");
            break;

        case WriteConfigStatus::CREATE_FILE_FAILED:
            QMessageBox::critical(main_window, "Error",
                                  "Could not create configuration file");
            break;

        case WriteConfigStatus::WRITE_FILE_FAILED:
            QMessageBox::critical(main_window, "Error",
                                  "Could not write configuration");
            break;

        case WriteConfigStatus::TOML_TO_STRING_FAILED:
            QMessageBox::critical(main_window, "Error",
                                  "Could not convert TOML data to string");
            break;
    }
}

void Self::create_default_config(QMainWindow* main_window) {
    auto config_dir_raw = ffi::config_dir();

    stringstream string_stream;
    string_stream << config_dir_raw << "/Lazyboard" << "/settings.toml";
    string config_path = string_stream.str();

    auto is_config_exists = ffi::is_exists_path(config_path.data());
    ffi::free_c_str(config_dir_raw);

    if (!is_config_exists) {
        // clang-format off
      #if defined (LAZY_DEBUG)
        auto q_string_value = QString::fromStdString(config_path);

        qDebug() << "Config path not found, generate at: " <<  q_string_value << "\n";
      #endif
        // clang-format on

        auto status = ffi::write_default_config();
        on_error(status, main_window);
    }

    // clang-format off
    #if defined (LAZY_DEBUG)
      auto q_string_value = QString::fromStdString(config_path);

      qDebug() << "Found config path at: " << q_string_value << "\n";
    #endif
    // clang-format on
}