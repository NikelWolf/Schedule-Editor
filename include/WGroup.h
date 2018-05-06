#ifndef WGROUP_H
#define WGROUP_H

#include <WDay.h>

static const QSize hedSize[] = { //todo wgroup size
        {30,  h},
        {140, h / 2},
        {30,  h / 2},
        {40,  h / 2},
        {40,  h / 2},
        {30,  h / 2},
        {210, h / 2},
        {40,  h / 2},
        {120, h / 2},
        {55,  h / 2},

        {210, h / 2},
        {160, h / 2},
        {55,  h / 2}
};

class WGroup : public QWidget {
Q_OBJECT
private:

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
            {"Пн"},
            {"Вт"},
            {"Ср"},
            {"Чт"},
            {"Пт"},
            {"Сб"}
    };
    std::array<WDay *, 6> wdays;
    std::array<QLabel *, 10> wlabels;
    std::array<QLineEdit *, 3> wlineEdits;

    GroupSchedule group;

    void createWidgets();

public:
    explicit WGroup(QWidget *parent = nullptr);

    WGroup(const GroupSchedule &group, QWidget *parent);

    void saveGroup();

    signals:

public slots:
};

#endif // WGROUP_H
