#include "WDay.h"

WDay::WDay(const QString &dayOfWeek, QWidget *parent) : QWidget(parent) {
    for (int column = 0, i = 0; i < 6; column = 0, ++i) {
        wlessons[i] = new WLesson(i + 1, timeOfLesson[i], this);
    }
    createWidgets(dayOfWeek);
}

WDay::WDay(const QString &dayOfWeek, std::array<Lesson, 6> lessons, QWidget *parent) : QWidget(parent) {
    for (int column = 0, i = 0; i < 6; column = 0, ++i) {
        wlessons[i] = new WLesson(i + 1, timeOfLesson[i], lessons[i], this);
    }
    createWidgets(dayOfWeek);

}

void WDay::createWidgets(const QString &dayOfWeek) {
    auto *dayLayout = new QHBoxLayout(this);
    auto *lessonsLayout = new QGridLayout();

    for (int column = 0, i = 0; i < 6; column = 0, ++i) {
        lessonsLayout->addLayout(wlessons[i]->labelsLayout, i, column++);
        lessonsLayout->addLayout(wlessons[i]->textLayout, i, column);
    }

    wdayOfWeek = new QLabel(dayOfWeek, this);
    wdayOfWeek->setFixedSize(lesSize[0].width(), lesSize[0].height() * 6.65); //todo day of week size
    wdayOfWeek->setStyleSheet("background-color: gray");
    wdayOfWeek->setAlignment(Qt::AlignCenter);

    dayLayout->addWidget(wdayOfWeek);
    dayLayout->addLayout(lessonsLayout);

    dayLayout->setMargin(1);
    dayLayout->setSpacing(1);
    lessonsLayout->setMargin(1);
    lessonsLayout->setSpacing(1);
}
