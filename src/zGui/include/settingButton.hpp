#ifndef SETTING_BUTTON_HPP
#define SETTING_BUTTON_HPP
#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QObject>

namespace zclipboard::zGui {
class SettingButton : public QObject {
    Q_OBJECT

   public:
    void addSettingButton(QWidget *window, QGridLayout *layout);

   private:
    void showSettingDialog(QWidget *parent);
    QPushButton *settingButton;
};
}  // namespace zclipboard::zGui

#endif  // SETTING_BUTTON_HPP