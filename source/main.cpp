#include <QApplication>
#include "WMain.h"
#include "Logger.h"
#include "scheduler.h"
using namespace scheduler;

int main(int argc, char *argv[]) {
    Scheduler scheduler("/home/nick/Projects/orig.xlsx");

    QApplication app(argc, argv);
    //Logger logger; //todo repair logger

    WMain wmain(scheduler);
    wmain.show();

    return QApplication::exec();
}
