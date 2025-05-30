#ifndef GUI_DIALOG_HPP
#define GUI_DIALOG_HPP
#include <QWidget>

namespace zclipboard::zGui {
class GuiDialog {
   private:
    static inline const constexpr int DIALOG_WIDTH = 400;
    static inline const constexpr int DIALOG_HEIGHT = 400;

   public:
    void showInputPassword(QWidget *parent);
};

}  // namespace zclipboard::zGui

#endif  // GUI_DIALOG_HPP