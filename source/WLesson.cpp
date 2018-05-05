#include "WLesson.h"

WLesson::WLesson(int lessonNumber, QStringList &time, QWidget *parent) : QWidget(parent) {
    createWidgets(lessonNumber, time);
}

WLesson::WLesson(int lessonNumber, QStringList &time,
                 Lesson lesson[], QWidget *parent)
        : QWidget(parent) {
    createWidgets(lessonNumber, time);

    for(unsigned int i=0; i < textEdits.size(); ++i){

    }
    textEdits[0]->setText(QString::fromStdString(
            lesson[0].get_subject_name()));
    textEdits[1]->setText(QString::fromStdString(
            lesson[1].get_subject_name()));

    textEdits[2]->setText(QString::fromStdString(
            lesson[0].get_lesson_type()));
    textEdits[3]->setText(QString::fromStdString(
            lesson[1].get_lesson_type()));

    textEdits[4]->setText(QString::fromStdString(
            lesson[0].get_professor()));
    textEdits[5]->setText(QString::fromStdString(
            lesson[1].get_professor()));

    textEdits[6]->setText(QString::fromStdString(
            lesson[0].get_room()));
    textEdits[7]->setText(QString::fromStdString(
            lesson[1].get_room()));
}

WLesson::~WLesson() {
    //delete labelsLayout;
    //delete textLayout;
    //todo check memory with valgrind
}

void WLesson::createWidgets(int lessonNumber, QStringList &time) {
    labelsLayout = new QGridLayout;
    textLayout = new QGridLayout;

    labels[0] = new QLabel(QString::number(lessonNumber), this);
    labels[0]->setFixedSize(lesSize[0]);

    unsigned int i = 0;
    for (i = 1; i < 3; ++i) {
        labels[i] = new QLabel(time[i - 1], this);
        labels[i]->setFixedSize(lesSize[1]);
    }

    labels[3] = new QLabel(" I", this);
    labels[4] = new QLabel("II", this);

    labels[3]->setFixedSize(lesSize[2]);
    labels[4]->setFixedSize(lesSize[2]);

    QFont font = labels[0]->font();
    font.setPointSize(10);
    for (i = 0; i < labels.size(); ++i) {
        labels[i]->setStyleSheet("background-color: orange");
        labels[i]->setAlignment(Qt::AlignCenter);
        labels[i]->setFont(font);
    }
    for (i = 0; i < 3; ++i) {
        labelsLayout->addWidget(labels[i], 0, i, 2, 1);
    }
    labelsLayout->addWidget(labels[3], 0, i);
    labelsLayout->addWidget(labels[4], 1, i);


    for (i = 0; i < 8; ++i) {
        textEdits[i] = new QTextEdit(this);
        textEdits[i]->setLineWrapMode(QTextEdit::NoWrap);
        textEdits[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdits[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdits[i]->setFontPointSize(10);
    }

    unsigned int k = 0;
    for (i = 0; i < 8; i += 2) {
        textLayout->addWidget(textEdits[i], 0, k++);
    }

    k = 0;
    for (i = 1; i < 8; i += 2) {
        textLayout->addWidget(textEdits[i], 1, k++);
    }

    k = 3;
    for (i = 0; i < 8; i += 2, ++k) {
        textEdits[i]->setFixedSize(lesSize[k]);
        textEdits[i + 1]->setFixedSize(lesSize[k]);
    }

    labelsLayout->setSpacing(1);
    labelsLayout->setMargin(1);
    textLayout->setSpacing(1);
    textLayout->setMargin(1);

}
