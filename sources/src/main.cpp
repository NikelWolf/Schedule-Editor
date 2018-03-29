#include <iostream>

#include <xlnt/xlnt.hpp>

#include <schedule_parser.h>
#include <xlsx_file.h>

using namespace std;
using namespace xlnt;
using namespace schedule_api;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: mirea_schedule schedule.xlsx" << endl;
        return 0;
    }

    XlsxFile xlsxFile{argv[1]};
    for (int i = xlsxFile.get_start_row(); i <= xlsxFile.get_end_row(); i++) {
        for (int j = xlsxFile.get_start_column(); i <= xlsxFile.get_end_column(); j++) {
            cout << i << "|" << j << "|" << xlsxFile(i, j) << endl;
        }
    }

    return 0;
}
