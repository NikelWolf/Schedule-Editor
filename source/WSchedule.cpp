#include "WSchedule.h"

WSchedule::WSchedule(const std::vector<GroupSchedule> &groupsVector, QWidget *parent) {
    this->groupsVector = groupsVector;

    for (auto &group : groupsVector) {
        wgroups.push_back(new WGroup(group, this));
    }
    createWidgets();
}
WSchedule::WSchedule(unsigned long groupsCount, QWidget *parent) : QWidget(parent) {
    for (unsigned long i = 0; i < groupsCount; ++i) {
        wgroups.push_back(new WGroup(this));
    }
    createWidgets();
}

void WSchedule::createWidgets() {
    auto *box = new QHBoxLayout(this);
    for (auto &wgroup : wgroups) {
        box->addWidget(wgroup);
    }
}


