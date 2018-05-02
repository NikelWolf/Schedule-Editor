#include "common.h"

namespace scheduler {
    XlsxFile::XlsxFile(const string &file_name) {
        _file_name = file_name;

        try {
            _wb.load(_file_name);
        } catch (xlnt::exception&) {
            throw ScheduleError{"file '" + file_name + "' does not exist"};
        }

        _ws = _wb.active_sheet();
        _load_xlsx_into_info();
    }

    XlsxFile::~XlsxFile() {
        if (_file_was_changed && _file_was_saved) {
            write();
        }
    }

    schedule_index_t XlsxFile::get_max_row_index() const {
        return _max_row;
    }

    schedule_index_t XlsxFile::get_max_column_index() const {
        return _max_column;
    }

    const vector<vector<XlsxFile::XlsxCell>> &XlsxFile::get_rows() const {
        return _xlsx_info;
    }

    const vector<XlsxFile::XlsxCell> &XlsxFile::get_row(schedule_index_t index) const {
        _check_indices(index, 0);

        return _xlsx_info[index];
    }

    const string &XlsxFile::get_cell(schedule_index_t row, schedule_index_t column) const {
        _check_indices(row, column);

        return _xlsx_info[row][column].value;
    }

    void XlsxFile::set_cell(schedule_index_t row, schedule_index_t column, const string& value) {
        _check_indices(row, column);

        _file_was_changed = true;
        _file_was_saved = false;

        _xlsx_info[row][column].value = value;
        _xlsx_info[row][column].__was_changed = true;
    }

    const string &XlsxFile::get_file_name() const {
        return _file_name;
    }

    void XlsxFile::set_file_name(const string& new_filename) {
        _file_name = new_filename;

        if (new_filename.find(".xlsx") != new_filename.size() - 5) {
            _file_name += ".xlsx";
        }
    }

    void XlsxFile::write_as(const string& new_filename) {
        set_file_name(new_filename);
        write();
    }

    void XlsxFile::write() {
        for (schedule_index_t row = 1; row < _max_row + 1; row++) {
            for (schedule_index_t column = 1; column < _max_column + 1; column++) {
                if (_xlsx_info[row - 1][column - 1].__was_changed) {
                    _ws.cell(column, static_cast<row_t>(row)).value(_xlsx_info[row - 1][column - 1].value);
                }
            }
        }

        _wb.save(_file_name);

        _file_was_changed = false;
        _file_was_saved = true;
    }

    void XlsxFile::save() {
        _file_was_saved = true;
    }

    void XlsxFile::discard_saving() {
        _file_was_saved = false;
    }

    void XlsxFile::_load_xlsx_into_info() {
        _max_row = _ws.highest_row();
        _max_column = _ws.highest_column().index;

        for (schedule_index_t row = 1; row <= _max_row; row++) {
            vector<XlsxCell> row_info;
            for (schedule_index_t column = 1; column <= _max_column; column++) {
                try {
                    row_info.emplace_back(XlsxCell{_ws.cell(column, static_cast<row_t>(row)).to_string()});
                } catch (out_of_range&) {
                    row_info.emplace_back(XlsxCell{});
                }
            }
            _xlsx_info.push_back(row_info);
        }
    }

    void XlsxFile::_check_indices(schedule_index_t row, schedule_index_t column) const {
        if (row >= _max_row || row < 0)
            throw ScheduleError{"row " + to_string(row) + " is not accessible"};

        if (column >= _max_column || column < 0)
            throw ScheduleError{"column " + to_string(column) + " is not accessible"};
    }
}