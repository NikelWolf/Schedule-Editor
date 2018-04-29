/**
 * \file
 * \brief Header file with common for project definitions
 *
 * common.h gathers all project headers and other useful definitions in one file
 * like std headers for input/output or data structures like map and vector or third-party header for xlnt library
 */

#pragma once

#include <iostream>
#include <string>
#include <sstream>
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

    using schedule_index_t = uint64_t;
    using day_template = unordered_map<int, Lesson>;
    using week_template = unordered_map<int, day_template>;
    using parity_week_template = unordered_map<int, week_template>;

    void string_ltrim_ref(string &s);

    void string_rtrim_ref(string &s);

    void string_trim_ref(string &s);

    string string_ltrim(string s);

    string string_rtrim(string s);

    string string_trim(string s);

    vector<string> string_split(const string& input, const string& regex=R"(\s+)");

    string string_join(vector<string> &strings, const string &connector="");
}

#include "schedule_error.h"
#include "lesson.h"
#include "xlsx_file.h"
#include "group_schedule.h"
#include "scheduler.h"