#pragma once

#include <unordered_map>
#include <vector>
#include <regex>
#include <xlnt/xlnt.hpp>

using namespace std;
using namespace xlnt;

namespace schedule_api {
    auto create_map_group_schedule_template() {
        unordered_map<string, string> pair_template{{"subject", ""}, {"type", ""}, {"professor", ""}, {"addition", ""}};
        unordered_map<int, unordered_map<string, string>> day_template;
        for (int i = 1; i < 7; i++) {
            day_template.insert({i, pair_template});
        }
        unordered_map<int, unordered_map<int, unordered_map<string, string>>> week_template;
        for (int i = 1; i < 7; i++) {
            week_template.insert({i, day_template});
        }
        unordered_map<int, unordered_map<int, unordered_map<int, unordered_map<string, string>>>> parity_template;
        for (int i = 1; i < 3; i++) {
            parity_template.insert({i, week_template});
        }
        return parity_template;
    }

    workbook open_schedule_file(const string &file_name) {
        workbook wb;
        wb.load(file_name);
        return wb;
    }

    auto get_cell_constraint(worksheet &ws) -> pair<pair<int, int>, pair<int, int>> {
        return {{ws.lowest_row(), ws.highest_row()},
                {ws.lowest_column().index, ws.highest_column().index}};
    }

    auto get_all_groups(worksheet schedule_sheet) -> vector<pair<string, pair<int, int>>> {
        vector<pair<string, pair<int, int>>> groups;
        regex reg{R"([A-zА-яЁё]{4}-\d{2}-\d{2})"};

        auto cell_constraints = get_cell_constraint(schedule_sheet);
        for (int row = cell_constraints.first.first; row < cell_constraints.first.second; row++) {
            for (int col = cell_constraints.second.first; col < cell_constraints.second.second; col++) {
                string str_cell_value = schedule_sheet.cell(col, (row_t) row).to_string();
                if (regex_search(str_cell_value.begin(), str_cell_value.end(), reg)) {
                    groups.push_back({str_cell_value, {col, row}});
                }
            }
        }

        return groups;
    }
}