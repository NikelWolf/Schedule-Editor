#include "WGroup.h"
#include <QtWidgets>

WGroup::WGroup(QWidget *parent) : QWidget(parent)
{
  QVBoxLayout* groupLayout = new QVBoxLayout;
  QGridLayout* headerLayout = new QGridLayout;

  unsigned int i;
  for(i=0; i < labels.size(); ++i){
      labels[i] = new QLabel(headerLabels[i]);
      labels[i]->setFixedSize(hedSize[i]);
      labels[i]->setStyleSheet("background-color: green");
    }
  for(i=0; i < lineEdits.size(); ++i){
      lineEdits[i] = new QLineEdit();
      lineEdits[i]->setFixedSize(hedSize[i+10]);
    }

  unsigned int r=0, c=0;
  headerLayout->addWidget(labels[0], r, c, 2, 1);
  headerLayout->addWidget(labels[1], r++, ++c, 1, 4);
  for(i=2; i < 6; ++i){
      headerLayout->addWidget(labels[i], r, c++);
    }
  for(i=6; i < labels.size(); ++i){
      headerLayout->addWidget(labels[i], r, c++);
    }

  r=0, c=5;
  headerLayout->addWidget(lineEdits[0], r, c++);
  headerLayout->addWidget(lineEdits[1], r, c, 1, 2);
  c+=2;
  headerLayout->addWidget(lineEdits[2], r, c);


  groupLayout->addLayout(headerLayout);

  for(i=0; i < days.size(); ++i){
      days[i] = new WDay(this, week[i]);
      groupLayout->addWidget(days[i]);
    }


  groupLayout->setMargin(1);
  groupLayout->setSpacing(1);

  headerLayout->setMargin(1);
  headerLayout->setSpacing(1);
  this->setLayout(groupLayout);
}
