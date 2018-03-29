#pragma once

#include <iostream>

#include "common.h"

using namespace std;

namespace schedule_api {
    class GroupSchedule {
    public:
    private:
        string _group_name;
        parity_week_map _group_schedule;
    };
}

