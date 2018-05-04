#include "WMain.h"
#include <WSchedule.h>

WMain::WMain(Scheduler &scheduler, QWidget *parent) : QMainWindow(parent) {
    auto *menuBar = new QMenuBar(this);
    QMenu *menu = new QMenu("&Menu", this);
    menu->setTearOffEnabled(true);
    menu->addAction("Item&1");
    menu->addAction("Item&2");
    menu->addAction("Item&3");
    menu->addAction("&Exit");

    menuBar->addMenu(menu);

    auto *scroll = new QScrollArea(this);
    setCentralWidget(scroll);
    this->layout()->setMenuBar(menuBar);

    auto *schedule = new WSchedule(scheduler.get_groups(), this);
    scroll->setWidget(schedule);
}
