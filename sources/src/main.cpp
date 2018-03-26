#include <iostream>

#include <xlnt/xlnt.hpp>

#include <schedule_parser.hpp>

using namespace std;
using namespace xlnt;
using namespace schedule_api;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: mirea_schedule schedule.xlsx" << endl;
        return 0;
    }

    auto wb = open_schedule_file(argv[1]);
    auto ws = wb.active_sheet();
    for (auto group: get_all_groups(ws)) {
        cout << group.first << " => (" << group.second.first << ", " << group.second.second << ")\n";
    }

    auto group = find_group(ws, "ИКБО-13-17");
    cout << group.first << " " << group.second.first << ", " << group.second.second << endl;

    return 0;
}
