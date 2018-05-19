#include "WMain.h"

WMain::WMain(Scheduler &scheduler_, QWidget *parent) : QMainWindow(parent), scheduler(scheduler_) {
    this->scheduler = scheduler;
    wschedule = new WSchedule(scheduler.get_groups_non_const_ref(), this);

    createWidgets();
}

void WMain::createWidgets() {
    auto *menuBar = new QMenuBar(this);
    QMenu *menu = new QMenu("&Menu", this);
    menu->setTearOffEnabled(true);
    menu->addAction("&Open file", this, SLOT(openFile()), Qt::CTRL + Qt::Key_O);
    menu->addAction("&Save file", this, SLOT(saveFile()), Qt::CTRL + Qt::Key_S);
    menu->addAction("Item&3");
    menu->addAction("&Exit", qApp, SLOT(quit()));

    menuBar->addMenu(menu);

    scroll = new QScrollArea(this);
    setCentralWidget(scroll);
    this->layout()->setMenuBar(menuBar);

    scroll->setWidget(wschedule);
    scroll->update();
}

void WMain::openFile() {
    Scheduler scheduler("resources/schedule_template.xlsx");
    wschedule = new WSchedule(scheduler.get_groups_non_const_ref(), this);
    scroll->setWidget(wschedule);
    scroll->update();
    qDebug() << "opened";
};

void WMain::saveFile() { //todo
    wschedule->saveSchedule();
    cout << scheduler;
    scheduler.save_schedule();
};