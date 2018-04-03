#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <cstdint>

#include <xlnt/xlnt.hpp>

using namespace std;
using namespace xlnt;

namespace scheduler {
    class Lesson;

    using day_template = unordered_map<int, Lesson>;
    using week_template = unordered_map<int, day_template>;
    using parity_week_template = unordered_map<int, week_template>;
}

#include "schedule_error.h"
#include "lesson.h"
#include "xlsx_file.h"
#include "group_schedule.h"
#include "scheduler.h"