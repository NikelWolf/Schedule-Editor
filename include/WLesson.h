#ifndef WLESSON_H
#define WLESSON_H

#include <QtWidgets>

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
    void createWidgets(int lessonNumber, QStringList &time);

public:
    QGridLayout *labelsLayout;
    QGridLayout *textLayout;

    std::array<QLabel *, 5> labels;
    std::array<QTextEdit *, 8> textEdits;

    WLesson(int lessonNumber, QStringList &time, QWidget *parent = nullptr);

    ~WLesson() override;

signals:

public slots:
};

#endif // WLESSON_H
