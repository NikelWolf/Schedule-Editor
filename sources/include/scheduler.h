#pragma once

#include "common.h"

// TODO: create separate library from scheduler sources

namespace scheduler {
    class Scheduler {
    public:
        explicit Scheduler(const string &file_name);

        bool is_group_in_schedule(const string &group_name) const;

        const GroupSchedule &get_group(const string &group_name) const;

        const vector<GroupSchedule> &get_groups() const;

        // TODO: implement adding group into schedule
        void add_group(const GroupSchedule &gs);

        friend ostream &operator<<(ostream &os, const Scheduler &scheduler);

    private:
        XlsxFile _schedule;
        vector<GroupSchedule> _groups{};

        cell_index_t _get_group_name_row() const;

        bool _check_for_free_day(GroupSchedule &gs, pair<cell_index_t, cell_index_t> start_position) const;

        string _filter_cell_info(const string &cell_value) const;

        Lesson _fill_lesson(GroupSchedule &gs, pair<cell_index_t, cell_index_t> start_position) const;

        void _get_schedule_for_group(GroupSchedule &gs, pair<cell_index_t, cell_index_t> start_position);

        void _parse_schedule();
    };
}