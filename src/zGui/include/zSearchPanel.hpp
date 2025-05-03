#ifndef zSearchPanel_HPP
#define zSearchPanel_HPP
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>

namespace zclipboard::zGui {
    class SearchArea : public QObject {
        Q_OBJECT
        
        public:
            void addSearchPanel(QWidget *zWindow, QGridLayout *zLayout);

        private:
            QLineEdit *zLineEdit;
    };
}

#endif // zSearchPanel_HPP