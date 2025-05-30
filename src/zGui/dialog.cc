#include "include/dialog.hpp"
#include "../language/include/language.hpp"
#include "../zUtils/include/config.hpp"
#include "../zUtils/include/settings.hpp"
#include <QSettings>
#include <QDialog>

// clang-format off
#if defined(Z_DEBUG)
    #include <QDebug>
#endif
// clang-format on

using zclipboard::zGui::GuiDialog;

void GuiDialog::showInputPassword(QWidget *parent) {
    QDialog *dialog = new QDialog(parent);
    QSettings settings(AUTHOR_NAME, APP_NAME);

    const int LANGUAGUE_TYPE = settings.value(LANGUAGE_SETTING).toInt();
    const auto DIALOG_TITLE = LANGUAGUE_TYPE ? INPUT_PASSWORD_DIALOG_VI : INPUT_PASSWORD_DIALOG_EN;

    // clang-format off
    /*
    * Debug flag only.
    * Use with CMake: -DZ_DEBUG=1
    */
    #if defined(Z_DEBUG)
        qDebug() << "Current language setting: " << LANGUAGUE_TYPE;
        qDebug() << "Current dialog title: " << DIALOG_TITLE;
    #endif
    // clang-format on

    dialog->setWindowTitle(DIALOG_TITLE);
    dialog->resize(DIALOG_WIDTH, DIALOG_HEIGHT);
    dialog->exec();
}