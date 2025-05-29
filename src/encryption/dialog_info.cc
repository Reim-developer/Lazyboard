#include "include/dialog_info.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/settings.hpp"
#include "../zUtils/include/config.hpp"
#include <QDialog>
#include <QSettings>
#include <QLabel>
#include <QGridLayout>

using zclipboard::encryption::DialogInfo;

void DialogInfo::showHashError(QWidget *parent) {
    QDialog *dialog = new QDialog(parent);
    QLabel *label = new QLabel(parent);
    QSettings settings(AUTHOR_NAME, APP_NAME, parent);
    QGridLayout *layout = new QGridLayout(dialog);

    const auto LANGUAGE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
    const auto WINDOW_TITLE = LANGUAGE_TYPE ? WARNING_DIALOG_TITLE_VI : WARNING_DIALOG_TITLE_EN;
    const auto INFO_MSG = LANGUAGE_TYPE ? HASH_FILE_MODIFY_MSG_VI : HASH_FILE_MODIFY_MSG_EN;

    label->setText(INFO_MSG);
    layout->addWidget(label, 0, 0);

    dialog->setWindowTitle(WINDOW_TITLE);
    dialog->setFixedSize(FIXED_WIDTH, FIXED_HEIGHT);
    dialog->setLayout(layout);
    dialog->exec();
}
