#pragma once

#include <unordered_map>
#include <utility>
#include <vector>
#include <regex>
#include <sstream>

#include <xlnt/xlnt.hpp>

using namespace std;
using namespace xlnt;

namespace schedule_api {
    class ScheduleError;
    class Lesson;

    using cell_constraints = pair<pair<int, int>, pair<int, int>>;

    using day_map = unordered_map<int, Lesson>;
    using week_map = unordered_map<int, day_map>;
    using parity_week_map = unordered_map<int, week_map>;

    class ScheduleError : public runtime_error {
    public:
        explicit ScheduleError(const string &message) : runtime_error{message} {}

        explicit ScheduleError(const char *message) : runtime_error(message) {}
    };

    class Lesson {
    public:
        Lesson(): _subject_name(""), _lesson_type(""), _professor(""), _additions{} {}

        Lesson(string subject_name, string lesson_type, string professor):
                _subject_name{move(subject_name)}, _lesson_type{move(lesson_type)},
                _professor{move(professor)}, _additions{} {}

        Lesson(const Lesson &lesson) = default;

        Lesson(Lesson &&lesson) noexcept {
            _subject_name = lesson._subject_name;
            _lesson_type = lesson._lesson_type;
            _professor = lesson._professor;
            _additions = move(lesson._additions);

            lesson._additions.clear();
        }

        Lesson &operator=(const Lesson &lesson) = default;

        Lesson &operator=(Lesson &&lesson) noexcept {
            _subject_name = lesson._subject_name;
            _lesson_type = lesson._lesson_type;
            _professor = lesson._professor;
            _additions = lesson._additions;

            lesson._subject_name = "";
            lesson._lesson_type = "";
            lesson._professor = "";
            lesson._additions.clear();

            return *this;
        }

        const string &get_subject_name() const {
            return _subject_name;
        }

        void set_subject_name(const string &subject_name) {
            _subject_name = subject_name;
        }

        const string &get_lesson_type() const {
            return _lesson_type;
        }

        void set_lesson_type(const string &lesson_type) {
            _lesson_type = lesson_type;
        }

        const string &get_professor() const {
            return _professor;
        }

        void set_professor(const string &professor) {
            _professor = professor;
        }

        void add_addition(const string &addition) {
            _additions.push_back(const_cast<string &>(addition));
        }

        const vector<string> &get_additions() const {
            return _additions;
        }

        friend ostream &operator<<(ostream &os, const Lesson &lesson) {
            os << "Lesson: {\n\tsubject: \"" << lesson._subject_name << "\",\n\ttype: \"" << lesson._lesson_type
               << "\",\n\tprofessor: \"" << lesson._professor << "\",\n\tadditions: [";
            string addition_repr;
            for (int i = 0; i < lesson._additions.size(); i++) {
                addition_repr += "\n\t\t\"" + lesson._additions[i] + (i != lesson._additions.size() - 1 ? "\"," : "\"");
            }
            os << addition_repr << "\n\t]\n}";
            return os;
        }

    private:
        string _subject_name;
        string _lesson_type;
        string _professor;
        vector<string> _additions;
    };

    workbook open_schedule_file(const string &file_name) {
        workbook wb;
        wb.load(file_name);
        return wb;
    }

    auto get_cells_constraints(const worksheet &ws) -> cell_constraints {
        return {{ws.lowest_row(), ws.highest_row()},
                {ws.lowest_column().index, ws.highest_column().index}};
    }

    auto create_map_group_schedule_template() -> parity_week_map {
        day_map day_template;
        week_map week_template;
        parity_week_map parity_template;

        for (int i = 1; i < 7; i++) day_template.insert({i, {}});
        for (int i = 1; i < 7; i++) week_template.insert({i, day_template});
        for (int i = 1; i < 3; i++) parity_template.insert({i, week_template});

        return parity_template;
    }

    int find_group_names_row(const worksheet &schedule_sheet) {
        regex reg{R"([A-zА-яЁё]{4}-\d{2}-\d{2})"};

        for (cell_vector cells: schedule_sheet.columns()) {
            for (cell c: cells) {
                string str_cell_value = c.to_string();

                if (regex_search(str_cell_value.begin(), str_cell_value.end(), reg)) {
                    return c.row();
                }
            }
        }

        return 0;
    }

    auto get_all_groups(const worksheet &schedule_sheet) -> vector<pair<string, pair<int, int>>> {
        vector<pair<string, pair<int, int>>> groups;
        vector<pair<int, int>> error_cells;

        regex reg{R"([A-zА-яЁё]{4}-\d{2}-\d{2})"};

        int row_with_group_names = find_group_names_row(schedule_sheet);
        if (row_with_group_names == 0) {
            throw ScheduleError{"row with names of groups in format \"LLLL-DD-DD\" was not found"};
        }

        auto schedule_cells_constraints = get_cells_constraints(schedule_sheet);
        for (int col = schedule_cells_constraints.second.first; col < schedule_cells_constraints.second.second; col++) {
            try {
                string str_cell_value = schedule_sheet.cell(col, static_cast<row_t>(row_with_group_names)).to_string();

                if (regex_search(str_cell_value.begin(), str_cell_value.end(), reg)) {
                    groups.push_back({str_cell_value, {col, row_with_group_names}});
                }
            } catch (out_of_range&) {}
        }

        return groups;
    }

    /* TODO
     * replace find group for more optimized version that will be search in vector previously founded by get_all_groups
    */
    pair<string, pair<int, int>> &find_group(worksheet &schedule_sheet, const string &group_name) {
        for (auto &group: get_all_groups(schedule_sheet)) {
            if (group_name == group.first) {
                return group;
            }
        }

        throw ScheduleError{"can not find group with name '" + group_name + "'"};
    };


}