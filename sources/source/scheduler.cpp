#include "common.h"

namespace scheduler {
    Scheduler::Scheduler(const string &file_name): _schedule{file_name} {
        _parse_schedule();
    }

    bool Scheduler::is_group_in_schedule(const string &group_name) const {
        if (!GroupSchedule::is_group_name_valid(group_name)) {
            return false;
        }

        for (const GroupSchedule &gs: _groups) {
            if (gs.get_group_name() == group_name) {
                return true;
            }
        }

        return false;
    }

    const GroupSchedule &Scheduler::get_group(const string &group_name) const {
        if (!GroupSchedule::is_group_name_valid(group_name)) {
            throw ScheduleError{"group name '" + group_name + "' is invalid"};
        }

        for (const GroupSchedule &gs: _groups) {
            if (gs.get_group_name() == group_name) {
                return gs;
            }
        }

        throw ScheduleError{"group '" + group_name + "' is not in schedule"};
    }

    const vector<GroupSchedule> &Scheduler::get_groups() const {
        return _groups;
    }

    void Scheduler::add_group(const GroupSchedule &gs) {
        if (_groups.size() < 36) {
            if(is_group_in_schedule(gs.get_group_name())) {
                _groups[_get_group_index(gs.get_group_name())] = gs;
            } else {
                _groups.push_back(gs);
            }
        } else {
            throw ScheduleError{"max supported count of groups in schedule file is 36"};
        }
    }

    void Scheduler::remove_group(const string &group_name) {
        if (is_group_in_schedule(group_name)) {
            _groups.erase(_groups.begin() + _get_group_index(group_name));
        } else {
            throw ScheduleError{"group '" + group_name + "' is not in schedule"};
        }
    }

    string Scheduler::to_string() const {
        string result;
        for (const GroupSchedule &gs: _groups) {
            result += gs.to_string() + "\n";
        }
        return result;
    }

    ostream &operator<<(ostream &os, const Scheduler &scheduler) {
        os << scheduler.to_string();
        return os;
    }

    schedule_index_t Scheduler::_get_group_name_row() const {
        for (schedule_index_t row = 0; row < _schedule.get_max_row_index(); row++) {
            for (schedule_index_t column = 0; column < _schedule.get_max_column_index(); column++) {
                if (GroupSchedule::is_group_name_valid(_schedule.get_cell(row, column))) {
                    return row;
                }
            }
        }
    }

    int Scheduler::_get_group_index(const string &group_name) const {
        int group_index = 0;
        for (auto &gs: _groups) {
            if (gs.get_group_name() == group_name) {
                break;
            }

            group_index++;
        }

        return group_index;
    }

    bool Scheduler::_check_for_free_day(GroupSchedule &gs, pair<schedule_index_t, schedule_index_t> start_position) const {
        schedule_index_t row_number = start_position.first, column_number = start_position.second;

        if (_schedule.get_cell(row_number, column_number) != "День") {
            return false;
        }

        string perhaps_free_day_string = _schedule.get_cell(row_number, column_number) + " " +
                                         _schedule.get_cell(row_number + 2, column_number) + " " +
                                         _schedule.get_cell(row_number + 4, column_number);

        return perhaps_free_day_string == "День самостоятельных занятий";
    }

    string Scheduler::_filter_cell_info(const string &cell_value) const {
        string trimmed_value = string_trim(cell_value);
        vector<string> splitted_value = string_split(trimmed_value, "\n");
        return string_join(splitted_value, "|");
    }

    Lesson Scheduler::_fill_lesson(GroupSchedule &gs, pair<schedule_index_t, schedule_index_t> start_position) const {
        vector<string> cells;
        for (int i = 0; i < 4; i++) {
            cells.push_back(_filter_cell_info(_schedule.get_cell(start_position.first, start_position.second + i)));
        }

        Lesson lesson{cells[0], cells[1], cells[2], cells[3]};
        return lesson;
    }

    void Scheduler::_get_schedule_for_group(GroupSchedule &gs, pair<schedule_index_t, schedule_index_t> start_position) {
        int free_day = 0;
        schedule_index_t row_number = start_position.first + 2, column_number = start_position.second;
        for (int day = 1; day < 7; day++) {
            for (int pair_number = 1; pair_number < 7; pair_number++) {
                if (day == free_day) {
                    break;
                }

                for (int parity = 1; parity < 3; parity++) {
                    string subject_cell = _schedule.get_cell(row_number, column_number);

                    if (subject_cell == "Занятия по адресу:") {
                        string addition_message = subject_cell + " " + _schedule.get_cell(row_number + 1, column_number);
                        gs.add_addition_message(addition_message, day);
                        row_number += 2;
                        break;
                    }

                    if (_check_for_free_day(gs, pair<schedule_index_t, schedule_index_t>{row_number, column_number})) {
                        gs.add_addition_message("День самостоятельных занятий", day);
                        free_day = day;
                        break;
                    }

                    Lesson lesson = _fill_lesson(gs, pair<schedule_index_t, schedule_index_t>{row_number, column_number});
                    gs.set_lesson(parity, day, pair_number, lesson);

                    row_number++;
                }
            }
        }
    }

    void Scheduler::_parse_schedule() {
        schedule_index_t group_name_row = _get_group_name_row();

        for (schedule_index_t column = 0; column < _schedule.get_max_column_index(); column++) {
            if (GroupSchedule::is_group_name_valid(_schedule.get_cell(group_name_row, column))) {
                GroupSchedule gs{_schedule.get_cell(group_name_row, column)};
                gs.set_group_faculty(_schedule.get_cell(group_name_row, column + 2));
                gs.set_group_magic_number(_schedule.get_cell(group_name_row, column + 3));

                _get_schedule_for_group(gs, pair<schedule_index_t, schedule_index_t>{group_name_row, column});
                _groups.push_back(gs);
            }
        }
    }

    // TODO: implent filling information about group into schedule
    void Scheduler::_write_groups_into_schedule() {
        throw ScheduleError{"not implemented"};

        int groups_counter = 0;
        schedule_index_t names_row = 1;
        schedule_index_t current_column = 5;
        for (GroupSchedule &gs: _groups) {
            if (groups_counter != 0 && groups_counter % 3 == 0) {
                current_column += 5;
            }

            _schedule.set_cell(names_row, current_column, gs.get_group_name());
            _schedule.set_cell(names_row, current_column + 2, gs.get_group_faculty());
            _schedule.set_cell(names_row, current_column + 3, gs.get_group_magic_number());

            for (int day = 1; day < 7; day++) {
                for (int lesson_number = 1; lesson_number < 7; lesson_number++) {
                    for (int parity = 1; parity < 3; parity++) {
                        const Lesson &l = gs.get_lesson(parity, day, lesson_number);


                    }
                }
            }

            current_column += 4;
            groups_counter++;
        }
    }
}