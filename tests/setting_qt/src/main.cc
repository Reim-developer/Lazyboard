#include <QSettings>
#include <QDebug>
#include "../../../src/zUtils/include/settings.hpp"

int main() {
    QSettings *settings = new QSettings("ReimEmp", "zClipboard");
    if (!settings->contains(LANGUAGE_SETTING)) {
        qDebug() << "Key: " << LANGUAGE_SETTING << " doesn't exists.";
        return 1;
    }

    qDebug() << settings->value(LANGUAGE_SETTING);
    return 0;
}
