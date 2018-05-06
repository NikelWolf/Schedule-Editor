#include "WMain.h"

//WMain::WMain(const Scheduler &scheduler, QWidget *parent) : QMainWindow(parent) {
//    this->scheduler = scheduler;
//    wschedule = new WSchedule(scheduler.get_groups(), this);
//
//    createWidgets();
//}

WMain::WMain(QWidget *parent) {
    wschedule = new WSchedule(16, this);
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
}

void WMain::openFile() {
    Scheduler scheduler("resources/MIREA_IT_1_2.xlsx");
    wschedule = new WSchedule(scheduler.get_groups(), this);
    scroll->setWidget(wschedule);
    scroll->update();
    qDebug() << "opened";
};

void WMain::saveFile() { //todo
    wschedule->saveSchedule();
    scheduler.save_schedule();
};