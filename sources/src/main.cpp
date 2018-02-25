#include <iostream>
#include <exception>
#include <xlnt/xlnt.hpp>

using namespace xlnt;
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: mirea_schedule file_to_print.xlsx" << endl;
        return 1;
    }

    workbook wb;
    wb.load(string(argv[1]));
    auto ws = wb.active_sheet();
    clog << "Processing spread sheet" << endl;
    for (auto row : ws.rows(false)) {
        for (auto cell : row) {
            clog << cell.to_string() << endl;
        }
    }
    clog << "Processing complete" << endl;

    return 0;
}
