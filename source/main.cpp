#include <QApplication>
#include "WMain.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Scheduler scheduler("resources/schedule_template.xlsx");

    WMain wMain(scheduler);
    wMain.show();

    return QApplication::exec();
}
