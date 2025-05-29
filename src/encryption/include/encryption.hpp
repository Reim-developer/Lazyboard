#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP
#include "../../zSQL/include/zSQL.hpp"
#include "../../core/include/enum.hpp"
#include <QWidget>

using zclipboard::core::HashState;
using zclipboard::zSQL::zManagerSQL;

namespace zclipboard::encryption {
class EncryptionManager {
   private:
    static inline const constexpr char HASH_FILE_NAME[] = "zClipboard.bin";

   public:
    void removeClipboardData();
    auto addHashFile() -> HashState;
};
}  // namespace zclipboard::encryption

#endif  // ENCRYPTION_HPP