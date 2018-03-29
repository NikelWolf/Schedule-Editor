#pragma once

#include <iostream>
#include <unordered_map>

#include <xlnt/xlnt.hpp>

#include "common.h"

using namespace std;
using namespace xlnt;

namespace schedule_api {
    class XlsxFile {
    public:
        explicit XlsxFile(const string &file_name) {
            _wb.load(file_name);
            _ws = _wb.active_sheet();
            _fill_cells_constraints();
            _fill_xlsx_info();
        }

        void write() {
            for (int row = _start_row; row <= _end_row; row++) {
                for (int column = _start_column; column <= _end_column; column++) {
                    _ws.cell(column, row).value(_xlsx_info[{row, column}]);
                }
            }
        }

        const string &operator()(int i, int j) const {
            return _xlsx_info[{i, j}];
        }

        void operator()(int i, int j, const string& value) {
            _xlsx_info[{i, j}] = value;
        }

        int get_start_row() const {
            return _start_row;
        }

        int get_start_column() const {
            return _start_column;
        }

        int get_end_row() const {
            return _end_row;
        }

        int get_end_column() const {
            return _end_column;
        }

        pair<int, int> get_start_indecies() const {
            return {_start_row, _start_column};
        }

        pair<int, int> get_end_indecies() const {
            return {_end_row, _end_column};
        }


    private:
        int _start_row{}, _end_row{};
        int _start_column{}, _end_column{};

        workbook _wb{};
        worksheet _ws;
        unordered_map<pair<int, int>, string> _xlsx_info{};

        void _fill_xlsx_info() {
            for (cell_vector cv: _ws.columns(false)) {
                for (cell c: cv) {
                    _xlsx_info.emplace({{c.row(), c.column().index}, c.to_string()});
                }
            }
        }

        void _fill_cells_constraints() {
            _start_row = _ws.lowest_row();
            _end_row = _ws.highest_row();
            _start_column = _ws.lowest_column().index;
            _end_column = _ws.highest_column().index;
        }
    };
}