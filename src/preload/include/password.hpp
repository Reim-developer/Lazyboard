#ifndef PRELOAD_PASSWORD_HPP
#define PRELOAD_PASSWORD_HPP
#include <QObject>
#include <QSettings>
#include <QDialog>
#include <memory>
#include "../../core/include/enum.hpp"

using std::unique_ptr;
using zclipboard::core::HashState;
using zclipboard::core::LoginState;

namespace zclipboard::preload {
class PreloadPassword : public QObject {
    Q_OBJECT

   private:
    int setLoginFormGui(const QSettings &settings);

   public slots:
    void onLoginSubmit(HashState hashState);

   private:
    unique_ptr<QDialog> dialog;

   public:
    auto showLoginForm() -> LoginState;
};
}  // namespace zclipboard::preload

#endif  // PRELOAD_PASSWORD_HPP