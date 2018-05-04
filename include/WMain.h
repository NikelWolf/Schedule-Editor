#ifndef WMAIN_H
#define WMAIN_H

#include <QMainWindow>
#include <QScrollArea>
#include "scheduler.h"
using namespace scheduler;

class WMain : public QMainWindow {
Q_OBJECT
public:
    explicit WMain(Scheduler &scheduler, QWidget *parent = nullptr);

signals:

public slots:
};

#endif // WMAIN_H
