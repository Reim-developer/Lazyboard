#ifndef ZCLIPBOARD_MAIN_HPP
#define ZCLIPBOARD_MAIN_HPP

namespace zclipboard::preload {
class Application {
   private:
    void setDefaultTheme();

   public:
    void loadTheme();

   private:
    static const constexpr char LINUX_DEFAULT_THEME[] = "Fusion";
    static const constexpr char WINDOWS_DEFAULT_THEME[] = "Windows";
    static const constexpr char MACOS_DEFAULT_THEME[] = "macOS";
};
}  // namespace zclipboard::preload

#endif  // ZCLIPBOARD_MAIN_HPP