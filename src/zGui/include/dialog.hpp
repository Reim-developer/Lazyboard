#ifndef GUI_DIALOG_HPP
#define GUI_DIALOG_HPP
#include <QDialog>
#include <QObject>

namespace zclipboard::zGui {
class GuiDialog : public QObject {
    Q_OBJECT

   private:
    static inline const constexpr int DIALOG_WIDTH = 400;
    static inline const constexpr int DIALOG_HEIGHT = 400;

   public:
    void showInputPassword(QDialog *parent);
};

}  // namespace zclipboard::zGui

#endif  // GUI_DIALOG_HPP