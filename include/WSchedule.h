#ifndef WSCHEDULE_H
#define WSCHEDULE_H

#include "WGroup.h"

class WSchedule : public QWidget {
Q_OBJECT
private:
    std::vector<WGroup *> wgroups;

    void createWidgets();

public:
    explicit WSchedule(const std::vector<GroupSchedule> &groupsVector, QWidget *parent);

    explicit WSchedule(unsigned long groupsCount = 16, QWidget *parent = nullptr);

    void saveSchedule();

signals:

public slots:
};

#endif // WSCHEDULE_H
