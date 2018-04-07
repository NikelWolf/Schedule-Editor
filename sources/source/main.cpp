#include <iostream>
#include <ctime>
#include <fstream>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

#include <scheduler.h>

using namespace std;

using namespace scheduler;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: mirea_schedule schedule.xlsx" << endl;
        return 0;
    }

    Scheduler scheduler{argv[1]};
    cout << scheduler.get_groups().size() << endl;


    QApplication app(argc, argv);

    QWidget widget;
    widget.resize(640, 480);
    widget.setWindowTitle("Hello, world!!!");

    QGridLayout *gridLayout = new QGridLayout(&widget);

    QLabel * label = new QLabel("Hello, world!!!");
    label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    gridLayout->addWidget(label);

    widget.show();

    return app.exec();
}
