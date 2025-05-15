#ifndef SETTING_BUTTON_HPP
#define SETTING_BUTTON_HPP
#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QObject>
#include <QCheckBox>
#include <QGridLayout>
#include <QSettings>

namespace zclipboard::zGui {

struct SettingWidget {
    QCheckBox *checkbox;
    QSettings *settings;
};

class SettingButton : public QObject {
    Q_OBJECT

   public:
    void addSettingButton(QWidget *window, QGridLayout *layout);

   private:
    void showSettingDialog(QWidget *parent);
    void addGui(QGridLayout *layout);
    void addHideSetting(const SettingWidget &settingWidget);
    void addNotificationSetting(const SettingWidget &settingWidget);

   private:
    QPushButton *settingButton;
    QGridLayout *layout;
    QCheckBox *autoHideCheckBox;
    QCheckBox *autoNotificatonCheckBox;
};
}  // namespace zclipboard::zGui

#endif  // SETTING_BUTTON_HPP