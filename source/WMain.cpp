#include "WMain.h"

WMain::WMain(QWidget *parent) : QMainWindow(parent)
{       
  QMenuBar* menuBar = new QMenuBar(this);
  QMenu*  menu  = new QMenu("&Menu", this);
  menu->setTearOffEnabled(true);
  menu->addAction("Item&1");
  menu->addAction("Item&2");
  menu->addAction("Item&3");
  menu->addAction("&Exit");

  menuBar->addMenu(menu);

  WSchedule* schedule = new WSchedule(this);
  QScrollArea* scroll = new QScrollArea(this);
  scroll->setWidget(schedule);
  setCentralWidget(scroll);
  this->layout()->setMenuBar(menuBar);
}
