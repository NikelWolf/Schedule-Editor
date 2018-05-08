#include "WGroup.h"

WGroup::WGroup(GroupSchedule &groupSchedule, QWidget *parent)
        : QWidget(parent), groupScheduleRef(groupSchedule) {
    for (int day = 0; day < 6; ++day) {
        for (int lesNum = 0; lesNum < 6; ++lesNum) {
            WLesson *wLesson = new WLesson(lesNum + 1, lessonsTimeList[lesNum]);
            wlessons.push_back(wLesson);

            for (int parity = 0; parity < 2; ++parity) {
                const Lesson &lesson = groupScheduleRef.get().get_lesson(parity + 1, day + 1, lesNum + 1);
                wLesson->setSubject(parity,
                                    QString::fromStdString(lesson.get_subject_name()));
                wLesson->setType(parity,
                                 QString::fromStdString(lesson.get_lesson_type()));
                wLesson->setProffesor(parity,
                                      QString::fromStdString(lesson.get_professor()));
                wLesson->setRoom(parity,
                                 QString::fromStdString(lesson.get_room()));
            }
        }
    }
    createWidgets();

    wlineEdits[0]->setText(
            QString::fromStdString(groupScheduleRef.get().get_group_name())
    );
    wlineEdits[1]->setText(
            QString::fromStdString(groupScheduleRef.get().get_group_faculty())
    );
    wlineEdits[2]->setText(QString::fromStdString(groupScheduleRef.get().get_group_magic_number())
    );

}

void WGroup::createWidgets() {
    //header
    auto headerLayout = new QGridLayout();
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
    //end header

    groupVerLayout = new QVBoxLayout(this);
    groupVerLayout->setSpacing(1);
    groupVerLayout->addLayout(headerLayout);

    for (int lesNum = 0, day = 0; day < 6; ++day) {
        auto lessonsVerLayout = new QVBoxLayout();
        auto dayHorLayout = new QHBoxLayout();

        lessonsVerLayout->setSpacing(1);
        dayHorLayout->setSpacing(1);

        auto dayLabel = new QLabel(week[day]);
        dayLabel->setFixedSize(lesSize[0].width(), lesSize[0].height() * 8);
        dayLabel->setStyleSheet("background-color: gray");
        dayLabel->setAlignment(Qt::AlignCenter);

        dayHorLayout->addWidget(dayLabel);

        for (i = 0; i < 6; ++i) {
            lessonsVerLayout->addWidget(wlessons[lesNum++]);
        }
        dayHorLayout->addLayout(lessonsVerLayout);
        groupVerLayout->addLayout(dayHorLayout);
    }
}

void WGroup::saveGroup() { //todo save groupScheduleRef
    string str = wlineEdits[0]->text().toStdString();
    groupScheduleRef.get().set_group_name(str);

    str = wlineEdits[1]->text().toStdString();
    groupScheduleRef.get().set_group_faculty(str);

    str = wlineEdits[2]->text().toStdString();
    groupScheduleRef.get().set_group_magic_number(str);

    for (int k = 0; k < 36; ++k) {
        for (int parity = 0; parity < 2; ++parity) {
            //todo indexs
            Lesson &lesson = const_cast<Lesson &>(groupScheduleRef.get().get_lesson(parity, k / 6, k % 6));
            lesson.set_subject_name(
                    wlessons[k]->getSubject(parity).toStdString()
            );
            lesson.set_lesson_type(
                    wlessons[k]->getType(parity).toStdString()
            );
            lesson.set_professor(
                    wlessons[k]->getProffesor(parity).toStdString()
            );
            lesson.set_room(
                    wlessons[k]->getRoom(parity).toStdString()
            );
            groupScheduleRef.get().set_lesson(parity, k % 6, 1, lesson);
        }
    }
}