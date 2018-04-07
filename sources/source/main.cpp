#include <iostream>
#include <ctime>
#include <fstream>

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

    return 0;

}
