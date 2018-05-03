#include <iostream>
#include <scheduler.h>

using namespace std;

using namespace scheduler;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: mirea_schedule schedule.xlsx" << endl;
        return 1;
    }

    Scheduler scheduler{argv[1]};
    cout << scheduler << endl;

    return 0;
}
