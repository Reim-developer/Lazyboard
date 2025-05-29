#ifndef ENCRYPTION_DIALOG_INFO_HPP
#define ENCRYPTION_DIALOG_INFO_HPP
#include <QWidget>
#include <QObject>

namespace zclipboard::encryption {
class DialogInfo : public QObject {
    Q_OBJECT

   private:
    static inline const constexpr unsigned int FIXED_WIDTH = 800;
    static inline const constexpr unsigned int FIXED_HEIGHT = 400;

   public:
    void showHashError(QWidget *widget);
};
}  // namespace zclipboard::encryption

#endif  // ENCRYPTION_DIALOG_INFO_HPP