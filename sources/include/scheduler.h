#pragma once

#include "common.h"

namespace scheduler {
    class Scheduler {
    public:
        Scheduler();

        explicit Scheduler(const string &file_name);

        bool is_group_in_schedule(const string &group_name) const;

        const vector<GroupSchedule> &get_groups() const;

        const GroupSchedule &get_group(const string &group_name) const;

        void add_group(const GroupSchedule &gs);

        void remove_group(const string &group_name);

        string to_string() const;

        friend ostream &operator<<(ostream &os, const Scheduler &scheduler);

    private:
        const static string _default_schedule_template_file;
        const static string _default_schedule_filename;
        const static uint _max_groups_count;

        XlsxFile _schedule;
        vector<GroupSchedule> _groups{};

        schedule_index_t _get_group_name_row() const;

        int _get_group_index(const string &group_name) const;

        bool _check_for_free_day(GroupSchedule &gs, pair<schedule_index_t, schedule_index_t> start_position) const;

        string _filter_cell_info(const string &cell_value) const;

        Lesson _fill_lesson(GroupSchedule &gs, pair<schedule_index_t, schedule_index_t> start_position) const;

        void _get_metainfo_for_group(GroupSchedule &gs, pair<schedule_index_t, schedule_index_t> start_position);

        void _get_schedule_for_group(GroupSchedule &gs, pair<schedule_index_t, schedule_index_t> start_position);

        void _parse_schedule();
    };
}