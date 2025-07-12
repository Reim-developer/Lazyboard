#ifndef LANGUAGE_MANAGER_HPP
#define LANGUAGE_MANAGER_HPP
#include <QObject>
#include <QSettings>
#include "../../Utils/Include/Namespace_Macro.hpp"

GUI_NAMESPACE

    class LanguageManager : public QObject {
        Q_OBJECT

    public:
        static LanguageManager &instance();
        void setLanguage(int language);

    signals:
        void languageChanged(int language);

    private:
        explicit LanguageManager(QObject *parent = nullptr);
        QSettings *settings;
    };

END_NAMESPACE

#endif  // LANGUAGE_MANAGER_HPP