#include <QApplication>
#include <gtk/gtk.h>
#include "gui_qt.cpp"
#include "gui_gtk.cpp"

int main(int argc, char *argv[]) {
#ifdef _WIN32
    QApplication app(argc, argv);
    DisplayManagerWindow window;
    window.show();
    return app.exec();
#elif __linux__
    gtk_init(&argc, &argv);
    create_window();
    gtk_main();
    return 0;
#endif
}
