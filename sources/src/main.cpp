#include <iostream>
#include <xlnt/xlnt.hpp>
#include <schedule_parser.h>

using namespace std;
using namespace xlnt;
using namespace schedule_api;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: mirea_schedule schedule.xlsx" << endl;
        return 0;
    }
    auto wb = open_schedule_file(argv[1]);
    for (auto group: get_all_groups(wb.active_sheet())) {
        cout << group.first << " => (" << group.second.first << ", " << group.second.second << ")\n";
    }

    return 0;
}
