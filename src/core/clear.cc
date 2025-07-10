#include "include/clear.hpp"
#include <QTimer>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <functional>
#include <QObject>

using std::function;
using zclipboard::core::ClearCoreBuilder;

ClearCoreBuilder *ClearCoreBuilder::StartBuild(QPushButton *button) {
    params = MakePtr<ParamImpl>();
    this->params->button = button;
    
    return this;
}

void ClearCoreBuilder::ThenAddListener(function<void()> func) {
    auto button = params->button;
    
    QObject::connect(button, &QPushButton::clicked, func);
}
