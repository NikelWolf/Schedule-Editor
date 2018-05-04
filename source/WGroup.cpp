#include "WGroup.h"
#include <QtWidgets>

WGroup::WGroup(QWidget *parent) : QWidget(parent) {
    for (unsigned int i = 0; i < wdays.size(); ++i) {
        wdays[i] = new WDay(week[i], this);
    }
    createWidgets();
}

WGroup::WGroup(const GroupSchedule &group, QWidget *parent) : QWidget(parent) {
    this->group = group;
    for (unsigned int i = 0; i < wdays.size(); ++i) {
        wdays[i] = new WDay(week[i], this);
    }
    createWidgets();
    QString str = QString::fromStdString(group.get_group_name());
    qDebug()<<str;
    std::cout<<group.get_group_name()<< "!!!!!!!!!!!!!!!!!!!!!!!!";

    wlineEdits[0]->setText(str);
    str = QString::fromStdString(group.get_group_faculty());
    qDebug()<<str;
    std::cout<<group.get_group_faculty();

    wlineEdits[1]->setText(str);
    str = QString::fromStdString(group.get_group_magic_number());
    qDebug()<<str;
    std::cout<<group.get_group_magic_number();
    wlineEdits[2]->setText(str);
}

void WGroup::createWidgets() {
    auto *groupLayout = new QVBoxLayout(this);
    auto *headerLayout = new QGridLayout();

    groupLayout->setMargin(1);
    groupLayout->setSpacing(1);

    headerLayout->setMargin(1);
    headerLayout->setSpacing(1);

    unsigned int i;
    for (i = 0; i < wlabels.size(); ++i) {
        wlabels[i] = new QLabel(headerLabels[i], this);
        wlabels[i]->setFixedSize(hedSize[i]);
        wlabels[i]->setStyleSheet("background-color: gray");
    }
    for (i = 0; i < wlineEdits.size(); ++i) {
        wlineEdits[i] = new QLineEdit(this);
        wlineEdits[i]->setFixedSize(hedSize[i + 10]);
    }

    unsigned int r = 0, c = 0;
    headerLayout->addWidget(wlabels[0], r, c, 2, 1);
    headerLayout->addWidget(wlabels[1], r++, ++c, 1, 4);
    for (i = 2; i < 6; ++i) {
        headerLayout->addWidget(wlabels[i], r, c++);
    }
    for (i = 6; i < wlabels.size(); ++i) {
        headerLayout->addWidget(wlabels[i], r, c++);
    }

    r = 0, c = 5;
    headerLayout->addWidget(wlineEdits[0], r, c++);
    headerLayout->addWidget(wlineEdits[1], r, c, 1, 2);
    c += 2;
    headerLayout->addWidget(wlineEdits[2], r, c);


    groupLayout->addLayout(headerLayout);

    for (i = 0; i < wdays.size(); ++i) {
        groupLayout->addWidget(wdays[i]);
    }
}
