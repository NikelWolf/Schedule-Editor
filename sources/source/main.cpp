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
}
