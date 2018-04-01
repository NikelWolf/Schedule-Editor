#pragma once

#include <common.h>

namespace schedule_api {
    class XlsxFile {
    public:
        class XlsxCell {
        public:
            XlsxCell() = default;

            explicit XlsxCell(string value): value{std::move(value)} {}

            virtual ~XlsxCell() = default;

            string value{};
            bool __was_changed = false;
        };


        explicit XlsxFile(const string &file_name) {
            _file_name = file_name;

            try {
                _wb.load(_file_name);
            } catch (xlnt::exception&) {
                throw ScheduleError{"file '" + file_name + "' does not exist"};
            }

            _ws = _wb.active_sheet();
            _load_xlsx_into_info();
        }

        virtual ~XlsxFile() {
            if (_file_was_changed) {
                write();
            }
        }

        unsigned long get_max_row_index() const {
            return _max_row;
        }

        unsigned long get_max_column_index() const {
            return _max_column;
        }

        const vector<vector<XlsxCell>> &get_rows() const {
            return _xlsx_info;
        }

        const vector<XlsxCell> &get_row(unsigned long index) const {
            _check_indices(index, 0);


            return _xlsx_info[index];
        }

        const string &get_cell(unsigned long row, unsigned long column) const {
            _check_indices(row, column);

            return _xlsx_info[row][column].value;
        }

        void set_cell(unsigned long row, unsigned long column, const string& value) {
            _check_indices(row, column);

            _file_was_changed = true;

            _xlsx_info[row][column].value = value;
            _xlsx_info[row][column].__was_changed = true;
        }

        const string &get_file_name() const {
            return _file_name;
        }

        void write() {
            for (unsigned long row = 1; row < _max_row + 1; row++) {
                for (unsigned long column = 1; column < _max_column + 1; column++) {
                    if (_xlsx_info[row - 1][column - 1].__was_changed) {
                        _ws.cell(column, static_cast<row_t>(row)).value(_xlsx_info[row - 1][column - 1].value);
                    }
                }
            }

            _wb.save(_file_name);

            _file_was_changed = false;
        }


    private:
        bool _file_was_changed = false;

        string _file_name;
        workbook _wb;
        worksheet _ws;

        vector<vector<XlsxCell>> _xlsx_info{};

        unsigned long _max_row{}, _max_column{};

        void _load_xlsx_into_info() {
            _max_row = _ws.highest_row();
            _max_column = _ws.highest_column().index;

            for (unsigned long row = 1; row <= _max_row; row++) {
                vector<XlsxCell> row_info;
                for (unsigned long column = 1; column <= _max_column; column++) {
                    try {
                        row_info.emplace_back(XlsxCell{_ws.cell(column, static_cast<row_t>(row)).to_string()});
                    } catch (out_of_range&) {
                        row_info.emplace_back(XlsxCell{});
                    }
                }
                _xlsx_info.push_back(row_info);
            }
        }

        void _check_indices(unsigned long row, unsigned long column) const {
            if (row >= _max_row || row < 0)
                throw ScheduleError{"row " + to_string(row) + " is not accessible"};

            if (column >= _max_column || column < 0)
                throw ScheduleError{"column " + to_string(column) + " is not accessible"};
        }
    };
}
