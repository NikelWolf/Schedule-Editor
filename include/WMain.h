#ifndef WMAIN_H
#define WMAIN_H

#include <QMainWindow>
#include <QScrollArea>
#include "WSchedule.h"

class WMain : public QMainWindow
{
  Q_OBJECT
public:
  explicit WMain(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // WMAIN_H
