#ifndef LAUCH_APP_IMPL_HPP
#define LAUCH_APP_IMPL_HPP

#define __Z_LAUNCH_APP__ \
        int main(int argc, char *argv[]) { \
        return Lauch_App(argc, argv); \
    }

int Lauch_App(int argc, char *argv[]);

#endif // LAUCH_APP_IMPL_HPP