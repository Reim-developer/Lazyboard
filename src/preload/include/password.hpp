#ifndef PRELOAD_PASSWORD_HPP
#define PRELOAD_PASSWORD_HPP
#include <QObject>
#include <QSettings>
#include "../../core/include/enum.hpp"

using zclipboard::core::LoginState;

namespace zclipboard::preload {
class PreloadPassword : public QObject {
    Q_OBJECT

   private:
    void setLoginFormGui(const QSettings &settings);

   public:
    auto showLoginForm() -> LoginState;
};
}  // namespace zclipboard::preload

#endif  // PRELOAD_PASSWORD_HPP