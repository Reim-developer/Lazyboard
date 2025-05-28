#ifndef CORE_SETTING_HPP
#define CORE_SETTING_HPP
#include <QComboBox>
#include <QDialog>
#include <QObject>
#include <QSettings>
#include <QLabel>
#include <QCheckBox>

namespace zclipboard::core {

// clang-format off
struct SettingCoreParams {
    QDialog *dialog;
    QSettings *settings;
    
    QLabel *languageDescription;
    QLabel *themeDescription;

    QComboBox *languageBox;
    QComboBox *themeBox;

    QCheckBox *autoHideCheckBox;
    QCheckBox *autoNotificatonCheckBox;
    QCheckBox *checkBox;
};
// clang-format on

class SettingCore : public QObject {
    Q_OBJECT
   public:
    void addLanguageSetting(const SettingCoreParams &params);
    void addHideSetting(const SettingCoreParams &params);
    void addNotificationSetting(const SettingCoreParams &params);
    void onLanguageSettingChanged(const SettingCoreParams &params);
    void onThemeSettingChanged(const SettingCoreParams &params);
    void addThemeSetting(const SettingCoreParams &params);
};
}  // namespace zclipboard::core

#endif  // CORE_SETTING_HPP