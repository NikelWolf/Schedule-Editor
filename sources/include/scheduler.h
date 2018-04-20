#pragma once

#include "common.h"

// TODO: create separate library from scheduler sources

namespace scheduler {
    class Scheduler {
    public:
        // TODO: implement creating new schedule file for 36 max groups with color support and right schedule cells format
        Scheduler(): _schedule{""} { throw ScheduleError{"not implemented"}; }

        explicit Scheduler(const string &file_name);

        bool is_group_in_schedule(const string &group_name) const;

        const vector<GroupSchedule> &get_groups() const;

        const GroupSchedule &get_group(const string &group_name) const;

        void add_group(const GroupSchedule &gs);

        void remove_group(const string &group_name);

        string to_string() const;

        friend ostream &operator<<(ostream &os, const Scheduler &scheduler);

    private:
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

        // TODO: implement
        void _write_groups_into_schedule();
    };
}