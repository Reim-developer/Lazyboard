#ifndef ZTABLE_HPP
#define ZTABLE_HPP
#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QObject>
#include <QClipboard>
#include <QDialog>
#include <QIcon>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QSet>
#include <QString>
#include <memory>
#include "TableModel.hpp"
#include "ClipboardDialog.hpp"
#include "../../Database/Include/DatabaseManager.hpp"
#include "../../Clipboard/Include/ClipboardImage.hpp"
#include "../../Clipboard/Include/ClipboardText.hpp"
#include "../../Utils/Include/Namespace_Macro.hpp"
#include "../Toolkit/Include/MainWindow_Components.hpp"
#include "../../Lib_Memory/Include/Memory.hpp"
#include "TableModel.hpp"

using std::unique_ptr;
using ZClipboard::Clipboard::ClipboardImage;
using ZClipboard::Clipboard::ClipboardText;
using ZClipboard::GUI::TableModel;
using ZClipboard::Database::DatabaseManager;
using ZClipboard::GUI::ClipboardDialog;
using ZClipboard::Lib_Memory::PtrUnique;
using ZClipboard::GUI::Toolkit::MainWindowComponentsManager;

GUI_NAMESPACE

    class TableView : public QObject {
        Q_OBJECT

        private:
                using Self = TableView;
                using ComponentsManager = MainWindowComponentsManager;

        public:
                Self *UseToolkit(ComponentsManager *componentsManager);
                void SetupTableView();
                TableModel *GetTableModel();
                DatabaseManager &GetDatabase();
                QClipboard *GetClipboard();

        private:
                static const constexpr int CONTENT_COLUMN = 1;
        
        private:
                void SetupTableProperty();

        private:
                ComponentsManager *componentsManager;
                QClipboard *clipboard;
                QTableView *tableView;
                TableModel *tableModel;

                unique_ptr<ClipboardImage> imageClipboard;
                unique_ptr<ClipboardText> textClipboard;

                QSet<QString> existingContents;
                QSet<QString> existingImages;

                DatabaseManager databaseManager;
                ClipboardDialog *clipboardDialog;

        public slots:
                void onContentClicked(const QModelIndex &current);
    };

END_NAMESPACE

#endif