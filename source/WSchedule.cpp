#include "WSchedule.h"

WSchedule::WSchedule(vector<GroupSchedule> &groupsVector_, QWidget *parent)
        : QWidget(parent), groupsVector(groupsVector_) {

    qDebug()<<"groups push start";
    for (auto &group : groupsVector) {
        wgroups.push_back(new WGroup(group, this));
    }
    qDebug()<<"groups pushed";

    createWidgets();
}

void WSchedule::createWidgets() {
    auto *box = new QHBoxLayout(this);
    for (auto &wgroup : wgroups) {
        box->addWidget(wgroup);
    }
}

void WSchedule::saveSchedule() {
    for(WGroup *wgrp: wgroups){
        wgrp->saveGroup();
    }
}



