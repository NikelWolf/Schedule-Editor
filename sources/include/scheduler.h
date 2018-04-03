#pragma once

#include "common.h"

// TODO: create separate library from scheduler sources

namespace scheduler {
    class Scheduler {
    public:
        explicit Scheduler(const string &file_name): _schedule{file_name} {

        }

        bool is_group_in_schedule(const string &group_name) {
            if (!GroupSchedule::is_group_name_valid(group_name)) {
                return false;
            }

            for (GroupSchedule &gs: _groups) {
                if (gs.get_group_name() == group_name) {
                    return true;
                }
            }

            return false;
        }

        const GroupSchedule &get_group(const string &group_name) {
            if (!GroupSchedule::is_group_name_valid(group_name)) {
                throw ScheduleError{"group name '" + group_name + "' is invalid"};
            }

            for (GroupSchedule &gs: _groups) {
                if (gs.get_group_name() == group_name) {
                    return gs;
                }
            }

            throw ScheduleError{"group '" + group_name + "' is not in schedule"};
        }

    private:
        XlsxFile _schedule;
        vector<GroupSchedule> _groups{};
    };
}