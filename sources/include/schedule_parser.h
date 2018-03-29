#pragma once

#include <unordered_map>
#include <utility>
#include <vector>
#include <regex>
#include <sstream>

#include <xlnt/xlnt.hpp>

#include "common.h"
#include "lesson.h"
#include "group_schedule.h"
#include "schedule_error.h"

using namespace std;
using namespace xlnt;

namespace schedule_api {
    class ScheduleParser {
    public:
        explicit ScheduleParser(const string &file_name) {
            _schedule_file.load(file_name);
            _main_sheet = _schedule_file.active_sheet();
            _parse_schedule();
        }
    private:
        workbook _schedule_file;
        worksheet _main_sheet;
        vector<GroupSchedule> _schedules;
        vector<pair<string, pair<int, int>>> _schedule_meta_information;

        void _parse_schedule() {

        }
    };


//    auto create_map_group_schedule_template() -> parity_week_map {
//        day_map day_template;
//        week_map week_template;
//        parity_week_map parity_template;
//
//        for (int i = 1; i < 7; i++) day_template.emplace(pair<int, Lesson>{i, {}});
//        for (int i = 1; i < 7; i++) week_template.emplace(pair<int, day_map>{i, day_template});
//        for (int i = 1; i < 3; i++) parity_template.emplace(pair<int, week_map>{i, week_template});
//
//        return parity_template;
//    }
//
//    int find_group_names_row(const worksheet &schedule_sheet) {
//        regex reg{R"([A-zА-яЁё]{4}-\d{2}-\d{2})"};
//
//        for (cell_vector cells: schedule_sheet.columns()) {
//            for (cell c: cells) {
//                string str_cell_value = c.to_string();
//
//                if (regex_search(str_cell_value.begin(), str_cell_value.end(), reg)) {
//                    return c.row();
//                }
//            }
//        }
//
//        return 0;
//    }

//    auto get_all_groups(const worksheet &schedule_sheet) -> vector<pair<string, pair<int, int>>> {
//        vector<pair<string, pair<int, int>>> groups;
//        vector<pair<int, int>> error_cells;
//
//        regex reg{R"([A-zА-яЁё]{4}-\d{2}-\d{2})"};
//
//        int row_with_group_names = find_group_names_row(schedule_sheet);
//        if (row_with_group_names == 0) {
//            throw ScheduleError{"row with names of groups in format \"LLLL-DD-DD\" was not found"};
//        }
//
//        auto schedule_cells_constraints = get_cells_constraints(schedule_sheet);
//        for (int col = schedule_cells_constraints.second.first; col < schedule_cells_constraints.second.second; col++) {
//            try {
//                string str_cell_value = schedule_sheet.cell(col, static_cast<row_t>(row_with_group_names)).to_string();
//
//                if (regex_search(str_cell_value.begin(), str_cell_value.end(), reg)) {
//                    groups.push_back({str_cell_value, {col, row_with_group_names}});
//                }
//            } catch (out_of_range&) {}
//        }
//
//        return groups;
//    }

//    cell_info &find_group(const worksheet &schedule_sheet, const string &group_name) {
//        for (auto &group: get_all_groups(schedule_sheet)) {
//            if (group_name == group.first) {
//                return group;
//            }
//        }
//
//        throw ScheduleError{"can not find group with name '" + group_name + "'"};
//    }
}