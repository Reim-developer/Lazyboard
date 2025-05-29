#include "include/encryption.hpp"
#include "../zUtils/include/zUtils.hpp"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QDialog>

using zclipboard::core::HashState;
using zclipboard::encryption::EncryptionManager;

void EncryptionManager::removeClipboardData() {
    const auto cachePath = zUtils::getCachePath();
    QDir cacheDir(cachePath);

    if (cacheDir.exists()) {
        cacheDir.removeRecursively();
    }
}

auto EncryptionManager::addHashFile() -> HashState {
    const auto CACHE_PATH = zUtils::getCachePath();
    const auto HASH_FILE_LOCATION = CACHE_PATH + PATH_SLASH + Z_ENCRYPT_FOLDER;
    const auto ENCRYPTION_FILE_PATH = HASH_FILE_LOCATION + PATH_SLASH + HASH_FILE_NAME;

    QDir directory;
    // clang-format off
    #if defined(Z_DEBUG)
        qDebug() << HASH_FILE_LOCATION;
        qDebug() << ENCRYPTION_FILE_PATH;
    #endif
    // clang-format on

    if (!directory.exists(HASH_FILE_LOCATION)) {
        removeClipboardData();

        // clang-format off
        /*
        * Debug macro, use with CMake flag:
        * -DZ_DEBUG=1
        */
        QDir newDirectory;
        #if defined(Z_DEBUG)
            const auto result = newDirectory.mkpath(HASH_FILE_LOCATION);
            qDebug() << "Cache Path Directory: " << CACHE_PATH;
            qDebug() << "Hash File Location: " << HASH_FILE_LOCATION;
            
            if(!result) {
                qDebug() << "Could not create path directory";
            }
            qDebug() << "Create directory successfully.";
            
            QFile encryptionFile(ENCRYPTION_FILE_PATH);
            if(!encryptionFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                qDebug() << "Could not open and write file.";
                qDebug() << encryptionFile.errorString();
            }

            qDebug() << "Created file successfully.";
            encryptionFile.close();

        #else
            newDirectory.mkpath(HASH_FILE_LOCATION);
            QFile encryptionFile(ENCRYPTION_FILE_PATH);

            encryptionFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            encryptionFile.close();
        #endif
        // clang-format on

        return HashState::DELETED;
    }

    return HashState::HASH_OK;
}