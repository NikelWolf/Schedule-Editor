#include "WMain.h"

WMain::WMain(QWidget *parent) : QMainWindow(parent) {
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

    Scheduler scheduler("/home/nick/Projects/orig.xlsx");

    std::cout <<scheduler.get_groups().at(0).get_group_magic_number() << endl;

    //std::cout <<scheduler.get_groups().at(0).get_group_magic_number();
    //auto *schedule = new WSchedule(scheduler.get_groups(), this);
    //scroll->setWidget(schedule);
}
