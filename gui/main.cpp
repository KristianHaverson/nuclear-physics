#include <QApplication>
#include "MenuWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    MenuWindow window;
    
    // Connect the application's aboutToQuit signal to cleanup
    QObject::connect(&app, &QApplication::aboutToQuit, 
                     &window, &MenuWindow::terminateProcesses);
    
    window.show();
    
    return app.exec();
}