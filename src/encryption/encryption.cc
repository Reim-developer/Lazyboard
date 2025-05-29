#include "include/encryption.hpp"
#include "../zUtils/include/zUtils.hpp"

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
    const auto HASH_FILE = CACHE_PATH + "/" + HASH_FILE_NAME;
    QFileInfo hashFilePath(HASH_FILE);

    if (!hashFilePath.exists()) {
        removeClipboardData();

        return HashState::MODIFIED;
    }

    return HashState::HASH_OK;
}