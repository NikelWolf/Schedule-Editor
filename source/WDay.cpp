#include "WDay.h"

WDay::WDay(QWidget *parent, QString dayOfWeek_) : QWidget(parent)
{
  QHBoxLayout* dayLayout = new QHBoxLayout;
  QGridLayout* lessonsLayout = new QGridLayout;

  dayLayout->setMargin(1);
  dayLayout->setSpacing(1);
  lessonsLayout->setMargin(1);
  lessonsLayout->setSpacing(1);

  for (int column = 0, i = 0; i < 6; column = 0, ++i){
      lessons[i] = new WLesson(i+1, timeOfLesson[i]);
      lessonsLayout->addLayout(lessons[i]->labelsLayout, i, column++);
      lessonsLayout->addLayout(lessons[i]->textLayout, i, column);
  }

  dayOfWeek = new QLabel(dayOfWeek_);
  dayOfWeek->setFixedSize(lesSize[0].width(), lesSize[0].height()*6.65); //todo
  dayOfWeek->setStyleSheet("background-color: green");
  dayOfWeek->setAlignment(Qt::AlignCenter);

  dayLayout->addWidget(dayOfWeek);
  dayLayout->addLayout(lessonsLayout);
  this->setLayout(dayLayout);
}
