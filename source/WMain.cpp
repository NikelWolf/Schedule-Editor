#include "WMain.h"

WMain::WMain(const Scheduler &scheduler, QWidget *parent) : QMainWindow(parent) {
    this->scheduler = scheduler;
    wschedule = new WSchedule(scheduler.get_groups(), this);

    createWidgets();
}

WMain::WMain(QWidget *parent) {
    wschedule = new WSchedule(16, this);
    createWidgets();
}

void WMain::createWidgets(){
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

    scroll->setWidget(wschedule);
}