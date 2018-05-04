#ifndef WSCHEDULE_H
#define WSCHEDULE_H

#include <QWidget>
#include "WGroup.h"

class WSchedule : public QWidget {
Q_OBJECT
private:
     std::vector<GroupSchedule> groupsVector;
    std::vector<WGroup *> wgroups;
public:
    explicit WSchedule( unsigned long groupsCount = 16, QWidget *parent = nullptr);

    explicit WSchedule( const std::vector<GroupSchedule> &groupsVector, QWidget *parent );

    void createWidgets(unsigned long groupsCount);
signals:

public slots:
};

#endif // WSCHEDULE_H
