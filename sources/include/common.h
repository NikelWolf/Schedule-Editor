#pragma

#include <iostream>
#include <unordered_map>

#include "lesson.h"

using namespace std;

namespace schedule_api {
    using cell_constraints = pair<pair<int, int>, pair<int, int>>;

    using day_map = unordered_map<int, Lesson>;
    using week_map = unordered_map<int, day_map>;
    using parity_week_map = unordered_map<int, week_map>;

    using cell_info = pair<string, pair<int, int>>;
}