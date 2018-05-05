#include "WSchedule.h"

WSchedule::WSchedule(unsigned long groupsCount, QWidget *parent) : QWidget(parent) {
    for (unsigned long i = 0; i < groupsCount; ++i) {
        wgroups.push_back(new WGroup(this));
    }
    createWidgets(groupsCount);
}

WSchedule::WSchedule(const std::vector<GroupSchedule> &groupsVector, QWidget *parent) {
    this->groupsVector = groupsVector;

    for (auto i : groupsVector) {
        wgroups.push_back(new WGroup(i, this));
    }
    createWidgets(groupsVector.size());
}

void WSchedule::createWidgets(unsigned long groupsCount) {
    auto *box = new QHBoxLayout(this);
    for (int i = 0; i < groupsCount; ++i) {
        box->addWidget(wgroups[i]);
    }
}


