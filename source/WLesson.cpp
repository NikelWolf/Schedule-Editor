#include "WLesson.h"

WLesson::WLesson(int lessonNumber, QStringList &time, QWidget *parent) : QWidget(parent)
{    
  labelsLayout = new QGridLayout;
  textLayout   = new QGridLayout;
  labelsLayout->setSpacing(1);
  textLayout->setSpacing(1);

  labelsLayout->setMargin(1);
  textLayout->setMargin(1);

  settingLabels(lessonNumber, time);
  settingTextEdits();
}

WLesson::~WLesson(){
  //todo
}

void WLesson::settingLabels(int lessonNumber, QStringList &time){
  labels[0] = new QLabel( QString::number(lessonNumber) );
  labels[0]->setFixedSize(lesSize[0]);

  unsigned int i = 0;
  for ( i = 1; i < 3; ++i){
      labels[i] = new QLabel(time[i-1]);
      labels[i]->setFixedSize(lesSize[1]);
  }


  labels[3] = new QLabel(" I");
  labels[4] = new QLabel("II");

  labels[3]->setFixedSize(lesSize[2]);
  labels[4]->setFixedSize(lesSize[2]);

  QFont font = labels[0]->font();
  font.setPointSize(10);
  for(i = 0; i < labels.size(); ++i){
      labels[i]->setStyleSheet("background-color: orange");
      labels[i]->setAlignment(Qt::AlignCenter);
      labels[i]->setFont(font);
  }
  for (i = 0; i < 3; ++i){
      labelsLayout->addWidget(labels[i], 0, i, 2, 1);
  }
  labelsLayout->addWidget(labels[3], 0, i);
  labelsLayout->addWidget(labels[4], 1, i);
}

void WLesson::settingTextEdits(){
  unsigned int i;
  for (i = 0; i < 8; ++i){
      textEdits[i] = new QTextEdit();
      textEdits[i]->setLineWrapMode(QTextEdit::NoWrap);
      textEdits[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      textEdits[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      textEdits[i]->setFontPointSize(10);
  }

  unsigned int k = 0;
  for (i = 0; i < 8; i+=2){
      textLayout->addWidget(textEdits[i], 0, k++ );
  }

  k = 0;
  for (i = 1; i < 8; i+=2){
      textLayout->addWidget(textEdits[i], 1, k++);
  }

  k=3;
  for (i = 0; i < 8; i+=2, ++k){
      textEdits[i]->setFixedSize(lesSize[k]);
      textEdits[i+1]->setFixedSize(lesSize[k]);
  }
}
