#include <QApplication>
#include "WMain.h"
#include "Logger.h"
#include "scheduler.h"
using namespace scheduler;

int main(int argc, char *argv[]) {
    Scheduler scheduler("resources/MIREA_IT_1_2.xlsx");

    QApplication app(argc, argv);
    //Logger logger; //todo repair logger

    WMain wmain(scheduler);
    wmain.show();

    return QApplication::exec();
}
