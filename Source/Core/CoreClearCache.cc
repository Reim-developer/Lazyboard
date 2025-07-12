#include "Include/CoreClearCache.hpp"
#include <QTimer>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <functional>
#include <QObject>

using std::function;
using ZClipboard::Core::ClearCoreBuilder;

ClearCoreBuilder *ClearCoreBuilder::StartBuild(QPushButton *button) {
    Impl = MakePtr<ParamImpl>();
    
    this
        ->  Impl
        ->  button 
        =   button;
    
    return this;
}

void ClearCoreBuilder::ThenAddListener(function<void()> func) {
    auto button = Impl->button;
    
    QObject::connect(button, &QPushButton::clicked, func);
}
