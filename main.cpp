
#include "src/window.h"
#include "src/stringException.h"

#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    try {
        char** temp;
        int a;
        QApplication app(a,temp);

        QSurfaceFormat fmt;
        fmt.setSamples(4);
        QSurfaceFormat::setDefaultFormat(fmt);

        Window window(argc, argv);
        window.show();
        return app.exec();

    } catch (std::exception& a) {
        std::cout<<a.what()<<std::endl;
        return 1;
    }

}
