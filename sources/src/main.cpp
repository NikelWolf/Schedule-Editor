#include <iostream>
#include <ctime>

#include <xlnt/xlnt.hpp>

#include <common.h>

using namespace std;
using namespace xlnt;

using namespace schedule_api;


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: mirea_schedule schedule.xlsx" << endl;
        return 0;
    }

    GroupSchedule gs;

    gs.set_group_name("TEST-00-00");

    cout << gs.get_group_name() << endl;

    cout << GroupSchedule::is_group_name_valid("ABCD-11-11") << endl;
    cout << GroupSchedule::is_group_name_valid("ASDASDASDA") << endl;

    Lesson l{"sname", "stype", "pname", "rnumber"};
    cout << l << endl;
    l.add_addition("addition");
    cout << l << endl;
    l.add_additions({"addition1", "addition2"});
    cout << l << endl;
    l.set_additions({"addition1_1", "addition1_2", "addition1_3", "addition1_4"});
    cout << l << endl;

    gs.set_lesson(1, 1, 1, l);
    cout << gs << endl;

    auto &l2 = const_cast<Lesson &>(gs.get_lesson(1, 1, 1));
    l2.set_room("tmp");
    cout << gs << endl;

    return 0;

}
