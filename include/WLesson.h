#ifndef WLESSON_H
#define WLESSON_H

#include <QtWidgets>
#include "scheduler.h"

using namespace scheduler;

const unsigned int h = 71;

constexpr QSize lesSize[] = {
        {30,  h}, //пара 0
        {40,  h}, //нач/кон зан 1
        {30,  h / 2}, //четность 2
        {210, h / 2}, //предмет 3
        {40,  h / 2}, //вид занятий 4
        {120, h / 2}, //фио 5
        {55,  h / 2}, //кабинет 6
};

class WLesson : public QWidget {
Q_OBJECT
private:

    std::array<QLabel *, 5> labels;
    std::array<QTextEdit *, 8> textEdits;
    std::array<Lesson, 2> lessons;

    QGridLayout *labelsLayout;
    QGridLayout *textLayout;

    void createWidgets(int lessonNumber, QStringList &time);

public:

    WLesson(int lessonNumber, QStringList &time,
            std::array<Lesson,2> &lessons, QWidget *parent = nullptr);

    WLesson(int lessonNumber, QStringList &time, QWidget *parent = nullptr);

    ~WLesson() override;

    QGridLayout *getLabelsLayout();

    QGridLayout *getTextLayout();

signals:

public slots:
};

#endif // WLESSON_H
