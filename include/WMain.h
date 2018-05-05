#ifndef WMAIN_H
#define WMAIN_H

#include <QMainWindow>
#include <QScrollArea>
#include "WSchedule.h"

class WMain : public QMainWindow {
Q_OBJECT
private:
    WSchedule *wschedule;
    Scheduler scheduler;

    void createWidgets();
public:
    explicit WMain(const Scheduler &scheduler, QWidget *parent = nullptr);
    explicit WMain(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // WMAIN_H
