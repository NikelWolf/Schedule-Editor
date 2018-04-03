#include <iostream>
#include <ctime>

#include <scheduler.h>

using namespace std;

using namespace scheduler;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: mirea_schedule schedule.xlsx" << endl;
        return 0;
    }

    XlsxFile file{argv[1]};
    cout << file.get_cell(1, 1);
    file.set_cell(1, 1, "tmp");
    cout << file.get_cell(1, 1);
    file.save();


    return 0;

}
