#include "common.h"

namespace scheduler {
    const string Scheduler::_default_schedule_template_file{"jstf.dat"};
    const string Scheduler::_default_schedule_filename{"schedule.xlsx"};
    const uint Scheduler::_max_groups_count = 36;

    Scheduler::Scheduler(): _schedule{_default_schedule_template_file} {
        _schedule.set_file_name(_default_schedule_filename);
    }

    Scheduler::Scheduler(const string &file_name): _schedule{file_name} {
        _parse_schedule();
    }

    const string &Scheduler::get_schedule_filename() const {
        return _schedule.get_file_name();
    }

    void Scheduler::set_schedule_filename(const string &filename) {
        _schedule.set_file_name(filename);
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

    const vector<GroupSchedule> &Scheduler::get_groups() const {
        return _groups;
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

    void Scheduler::add_group(const GroupSchedule &gs) {
        if (_groups.size() < _max_groups_count) {
            if(is_group_in_schedule(gs.get_group_name())) {
                _groups[_get_group_index(gs.get_group_name())] = gs;
            } else {
                _groups.push_back(gs);
            }
        } else {
            throw ScheduleError{"max supported count of groups in schedule file is " + Scheduler::_max_groups_count};
        }
    }

    void Scheduler::remove_group(const string &group_name) {
        if (is_group_in_schedule(group_name)) {
            _groups.erase(_groups.begin() + _get_group_index(group_name));
        } else {
            throw ScheduleError{"group '" + group_name + "' is not in schedule"};
        }
    }

    const string &Scheduler::get_cource_metainfo() const {
        return _schedule_date_and_course_metainfo;
    }

    void Scheduler::set_cource_metainfo(const string &metainfo_string) {
        _schedule_date_and_course_metainfo = metainfo_string;
    }

    const string &Scheduler::get_confirmation_metainfo() const {
        return _confirmation_metainfo;
    }

    void Scheduler::set_confirmation_metainfo(const string &metainfo_string) {
        _confirmation_metainfo = metainfo_string;
    }

    const pair<string, string> Scheduler::get_UMD_head_metainfo() const {
        return _UMD_head_metainfo;
    }

    void Scheduler::set_UMD_head_metainfo(const pair<string, string> &metainfo) {
        _UMD_head_metainfo.first = metainfo.first;
        _UMD_head_metainfo.second = metainfo.second;
    }

    const pair<string, string> Scheduler::get_headmaster_metainfo() const {
        return _headmaster_metainfo;
    }

    void Scheduler::set_headmaster_metainfo(const pair<string, string> &metainfo) {
        _headmaster_metainfo.first = metainfo.first;
        _headmaster_metainfo.second = metainfo.second;
    }

    void Scheduler::save_schedule() {
        _load_schedule_metainfo_into_file();
        _load_groups_into_file();
        _schedule.write();
    }

    string Scheduler::to_string() const {
        string result = "schedule filename: \"" + _schedule.get_file_name() + "\"" +
                        "\nmetainfo:" +
                        "\n\tcource: \"" + _schedule_date_and_course_metainfo + "\"" +
                        "\n\tconfirmation: \"" + _confirmation_metainfo + "\"" +
                        "\n\tUMD head: \"" + _UMD_head_metainfo.first + "\" \"" + _UMD_head_metainfo.second + "\"" +
                        "\n\theadmaster: \"" + _headmaster_metainfo.first + "\" \"" + _headmaster_metainfo.second +
                        "\"\n";
        string separator;
        for (int i = 0; i < 50; i++) {
            separator += "=";
        }
        separator += "\n";
        result += separator;
        for (const GroupSchedule &gs: _groups) {
            result += gs.to_string() + "\n" + separator;
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

        throw ScheduleError{"wrong format for schedule: there is no row with group names"};
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

    bool Scheduler::_check_for_free_day(pair<schedule_index_t, schedule_index_t> start_position) const {
        schedule_index_t row_number = start_position.first, column_number = start_position.second;

        if (_schedule.get_cell(row_number, column_number) != "День") {
            return false;
        }

        string perhaps_free_day_string = _schedule.get_cell(row_number, column_number) + " " +
                                         _schedule.get_cell(row_number + 2, column_number) + " " +
                                         _schedule.get_cell(row_number + 4, column_number);

        return perhaps_free_day_string == "День самостоятельных занятий";
    }

    Lesson Scheduler::_fill_lesson(pair<schedule_index_t, schedule_index_t> start_position) const {
        vector<string> cells;
        for (int i = 0; i < 4; i++) {
            cells.push_back(_schedule.get_cell(start_position.first, start_position.second + i));
        }

        Lesson lesson{cells[0], cells[1], cells[2], cells[3]};
        return lesson;
    }

    void Scheduler::_parse_metainfo_for_group(GroupSchedule &gs,
                                              pair<schedule_index_t, schedule_index_t> start_position) {
        gs.set_group_name(_schedule.get_cell(start_position.first, start_position.second));
        gs.set_group_faculty(_schedule.get_cell(start_position.first, start_position.second + 2));
        gs.set_group_magic_number(_schedule.get_cell(start_position.first, start_position.second + 3));
    }

    void Scheduler::_parse_schedule_for_group(GroupSchedule &gs,
                                              pair<schedule_index_t, schedule_index_t> start_position) {
        schedule_index_t row_number = start_position.first + 2, column_number = start_position.second;
        for (int day = 1; day < 7; day++) {
            for (int lesson_number = 1; lesson_number < 7; lesson_number++) {
                for (int parity = 1; parity < 3; parity++) {
                    string subject_cell = _schedule.get_cell(row_number, column_number);

                    if (subject_cell == "Занятия по адресу:") {
                        string addition_message = subject_cell + " " + _schedule.get_cell(row_number + 1, column_number);
                        gs.add_addition_message(addition_message, day);
                    }

                    if (_check_for_free_day(pair<schedule_index_t, schedule_index_t>{row_number, column_number})) {
                        gs.add_addition_message("День самостоятельных занятий", day);
                    }

                    Lesson lesson = _fill_lesson(pair<schedule_index_t, schedule_index_t>{row_number, column_number});
                    gs.set_lesson(parity, day, lesson_number, lesson);

                    row_number++;
                }
            }
        }
    }

    void Scheduler::_parse_schedule_metainfo() {
        _schedule_date_and_course_metainfo = _schedule.get_cell(0, 1);
        _confirmation_metainfo = _schedule.get_cell(0, 13);

        _UMD_head_metainfo.first = _schedule.get_cell(75, 2);
        _UMD_head_metainfo.second = _schedule.get_cell(75, 8);

        _headmaster_metainfo.first = _schedule.get_cell(75, 11);
        _headmaster_metainfo.second = _schedule.get_cell(75, 14);
    }

    void Scheduler::_parse_schedule() {
        _parse_schedule_metainfo();

        schedule_index_t group_name_row = _get_group_name_row();

        for (schedule_index_t column = 0; column < _schedule.get_max_column_index(); column++) {
            if (GroupSchedule::is_group_name_valid(_schedule.get_cell(group_name_row, column))) {
                GroupSchedule gs;
                pair<schedule_index_t, schedule_index_t> group_position{group_name_row, column};

                _parse_metainfo_for_group(gs, group_position);
                _parse_schedule_for_group(gs, group_position);
                _groups.push_back(gs);
            }
        }
    }

    void Scheduler::_load_schedule_metainfo_into_file() {
        schedule_index_t upper_row = 0, lower_row = 75;
        pair<schedule_index_t, schedule_index_t> upper_row_columns{1, 13};
        pair<schedule_index_t, schedule_index_t> lower_UMD_columns{2, 8};
        pair<schedule_index_t, schedule_index_t> lower_headmaster_columns{11, 14};


        for (uint i = 0; i < _max_groups_count / 3; i++,
                upper_row_columns.first += 17,
                upper_row_columns.second += 17,
                lower_UMD_columns.first += 17,
                lower_UMD_columns.second += 17,
                lower_headmaster_columns.first += 17,
                lower_headmaster_columns.second += 17) {
            _schedule.set_cell(upper_row, upper_row_columns.first, _schedule_date_and_course_metainfo);
            _schedule.set_cell(upper_row, upper_row_columns.second, _confirmation_metainfo);

            _schedule.set_cell(lower_row, lower_UMD_columns.first, _UMD_head_metainfo.first);
            _schedule.set_cell(lower_row, lower_UMD_columns.second, _UMD_head_metainfo.second);

            _schedule.set_cell(lower_row, lower_headmaster_columns.first, _headmaster_metainfo.first);
            _schedule.set_cell(lower_row, lower_headmaster_columns.second, _headmaster_metainfo.second);
        }
    }

    void Scheduler::_load_single_group_into_file(GroupSchedule &gs, schedule_index_t group_row,
                                                 schedule_index_t group_start_position) {
        _schedule.set_cell(group_row, group_start_position, gs.get_group_name());
        _schedule.set_cell(group_row, group_start_position + 2, gs.get_group_faculty());
        _schedule.set_cell(group_row, group_start_position + 3, gs.get_group_magic_number());

        group_row += 2;
        for (int day = 1; day < 7; day++) {
            for (int lesson_number = 1; lesson_number < 7; lesson_number++) {
                for (int parity = 1; parity < 3; parity++) {
                    const Lesson &lesson = gs.get_lesson(parity, day, lesson_number);

                    _schedule.set_cell(group_row, group_start_position, lesson.get_subject_name());
                    _schedule.set_cell(group_row, group_start_position + 1, lesson.get_lesson_type());
                    _schedule.set_cell(group_row, group_start_position + 2, lesson.get_professor());
                    _schedule.set_cell(group_row, group_start_position + 3, lesson.get_room());

                    group_row++;
                }
            }
        }
    }

    void Scheduler::_load_groups_into_file() {
        schedule_index_t group_row = 1;
        schedule_index_t group_column = 5;
        for (uint i = 1; i <= _groups.size(); i++) {
            GroupSchedule &gs = _groups.at(i - 1);
            _load_single_group_into_file(gs, group_row, group_column);

            group_column += 4;

            if (i % 3 == 0) {
                group_column += 5;
            }
        }
    }
}
