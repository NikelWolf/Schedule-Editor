#include "WSchedule.h"
WSchedule::WSchedule(QWidget *parent) : QWidget(parent)
{
  QHBoxLayout* box = new QHBoxLayout(this);

  std::vector<WGroup*> groups;

  for(int i=0; i < 4;++i){
      groups.push_back(new WGroup);
      box->addWidget(groups[i]);
    }

  this->setLayout(box);
}
