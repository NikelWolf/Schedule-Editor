#ifndef WGROUP_H
#define WGROUP_H

#include <QtWidgets>
#include <WDay.h>

static const QSize hedSize[] = {
  {30, h},
  {140, h/2},
  {30, h/2},
  {40, h/2},
  {40, h/2},
  {30, h/2},
  {210, h/2},
  {40, h/2},
  {120, h/2},
  {55, h/2},

  {210, h/2},
  {160, h/2},
  {55, h/2}
};

class WGroup : public QWidget
{
  Q_OBJECT
private:
  std::array<WDay*, 6> days;
  std::array<QLabel*, 10> labels;
  std::array<QLineEdit*, 3> lineEdits;




  QStringList headerLabels = {
    {"День недели"},
    {"Группа"},
    {"№ пары"},
    {"Нач. занятий"},
    {"Кон. занятий"},
    {"Неделя"},
    {"Предмет"},
    {"Вид занятий"},
    {"ФИО преподавателя"},
    {"№ ауд."}
  };

  QStringList week = {
    {"П\nо\nн\nе\nд\nе\nл\nь\nн\nи\nк"},//todo
    {"Вт"},
    {"Ср"},
    {"Чт"},
    {"Пт"},
    {"Сб"}
  };

public:
  explicit WGroup(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // WGROUP_H
