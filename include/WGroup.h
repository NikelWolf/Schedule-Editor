#ifndef WGROUP_H
#define WGROUP_H

#include <WLesson.h>


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

    QVector<QStringList> lessonsTimeList = {
            {" 9-00", "10-30"},
            {"10-40", "12-10"},
            {"13-00", "14-30"},
            {"14-40", "16-10"},
            {"16-20", "17-50"},
            {"18-00", "19-30"},
    };

    QVBoxLayout *groupVerLayout;

    array<QLabel *, 10> wlabels;
    array<QLineEdit *, 3> wlineEdits;
    vector<WLesson *> wlessons;

    reference_wrapper<GroupSchedule> groupScheduleRef;

private:
    void createWidgets();

public:
    WGroup(GroupSchedule &groupSchedule, QWidget *parent);

    void saveGroup();

};

#endif // WGROUP_H
