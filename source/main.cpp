#include <QApplication>
#include "WMain.h"

int main(int argc, char *argv[]) {
    Scheduler scheduler{"resources/schedule_template.xlsx"};
    scheduler.get_groups_non_const_ref().at(0).get_lesson_non_const_ref(1, 1, 1).set_subject_name("tmp");
    cout << scheduler << endl;
    scheduler.save_schedule_as("tmp.xlsx");
}
