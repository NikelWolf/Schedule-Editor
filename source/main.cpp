#include <QApplication>
#include "WMain.h"

int main(int argc, char *argv[]) {


    QApplication app(argc, argv);

    WMain wMain;
    wMain.show();

    return QApplication::exec();
}
