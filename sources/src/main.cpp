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
    Lesson tmp_lesson{"Test subject", "Test", "Test professor", "t000"};
    for (const GroupSchedule &gs: scheduler.get_groups()) {
        auto &non_const_gs = const_cast<GroupSchedule &>(gs);
        for (int parity = 1; parity < 3; parity++) {
            for (int day = 1; day <7; day++) {
                for (int lesson_number = 1; lesson_number < 7; lesson_number++) {
                    non_const_gs.set_lesson(parity, day, lesson_number, tmp_lesson);
                }
            }
        }
    }

    return 0;

}
