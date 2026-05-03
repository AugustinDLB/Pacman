#include "PacmanWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    PacmanWindow window;
    window.setWindowTitle("Pac-Man");
    window.resize(800, 1000);
    window.show();

    return app.exec();
}

