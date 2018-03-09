#!/usr/bin/python

import sys, os, re
import copy
import json
import xlrd


def create_map_group_schedule_template() -> map:
    """create schedule template for group with following format:\n
       1 => parity of week (int: 1 or 2);\n
       2 => day of the week (int: from 1 to 6);\n
       3 => number of pair (int: from 1 to 7);\n
       4 => type of info about pair (string: on value from list ["subject", "type", "professor", "room", "addition").\n\n
       example: subject_info = schedule_object[1][3][2]["subject"]
    """

    pair_template = {"subject": "", "type": "", "professor": "", "room": "", "additions": []}
    day_template = {i: copy.deepcopy(pair_template) for i in range(1, 7)}
    week_template = {i: copy.deepcopy(day_template) for i in range(1, 7)}
    parity_template = {i: copy.deepcopy(week_template) for i in range(1, 3)}
    return parity_template


def open_schedule_file(file_name: str) -> xlrd.Book:
    """open xlsx file and return new object of Book type
    """

    return xlrd.open_workbook(file_name)


def get_cell_indices(schedule_sheet: xlrd.sheet.Sheet) -> tuple:
    """by each call return tuple of indices in sheet in format: (row, column)\n
       example: for row, col in get_cell_indices(sheet): print(f"row={row}\ncol={col}")
    """

    for row in range(schedule_sheet.nrows):
        for col in range(schedule_sheet.ncols):
            yield (row, col)


def get_all_groups(schedule_sheet: xlrd.sheet.Sheet, add_group_start_indices: bool=False) -> list:
    """return list of groups that are in schedule file\n
       group name must be in following format: (4 letters)-(2 digits)-(2 digits)\n
       if add_group_indices is set to True function will return tuple in following format:
       (group name, (row where info starts, column where info starts)) else only tuple with group name in it
       example: first_group = get_all_groups(sheet, True)[0]
    """

    groups = []
    reg = r"[A-zА-яЁё]{4}-\d{2}-\d{2}"

    for row, col in get_cell_indices(schedule_sheet):
        reg_result = re.match(reg, str(schedule_sheet.cell(row, col).value))
        if reg_result:
            groups.append((reg_result.group(0), (row, col)) if add_group_start_indices else reg_result.group(0))

    return groups


def find_group(schedule_sheet: xlrd.sheet.Sheet, group_name) -> tuple:
    """find group in sheet and return tuple in following format:\n
       (group name, (row where info starts, column where info starts))
    """

    for group in get_all_groups(schedule_sheet, True):
        if group_name == group[0]:
            return group

    return ()


def add_addition_message(message: str, group_schedule: map, day_number: int) -> None:
    """add addition message to day in group schedule"""

    for pair_number in range(1, 7):
        for parity in range(1, 3):
            group_schedule[parity][day_number][pair_number]["additions"].append(message)


def check_for_free_day(schedule_sheet: xlrd.sheet.Sheet, group_schedule: map, indices_to_test: tuple) -> bool:
    """check if day in schedule file marked as free from lessons"""

    if schedule_sheet.cell(*indices_to_test).value != u"День":
        return False

    test_cells = schedule_sheet.col_slice(indices_to_test[1], indices_to_test[0], indices_to_test[0] + 5)
    free_day_elements = [cell_value.value for cell_value in test_cells if cell_value.value]

    perhaps_free_day_string = f"{free_day_elements[0]} {free_day_elements[1]} {free_day_elements[2]}"

    return perhaps_free_day_string.lower() == u"День самостоятельных занятий".lower()


def fill_pair(schedule_sheet: xlrd.sheet.Sheet, pair_part_of_schedule: map, indices: tuple) -> None:
    """fill info about pair"""

    info_filler = lambda cell: "|".join(cell.value.strip().split("\n"))

    pair_types = ["subject", "type", "professor", "room"]
    cells = schedule_sheet.row_slice(indices[0], indices[1], indices[1] + 4)

    for i, pair_type in enumerate(pair_types):
        pair_part_of_schedule[pair_type] = info_filler(cells[i])


def get_schedule_for_group(schedule_sheet: xlrd.sheet.Sheet, group: tuple, print_schedule: bool=False, file_to_print=sys.stdout) -> map:
    """return schedule for group"""

    group_schedule = create_map_group_schedule_template()

    free_day = None
    row_number, cell_number = group[1][0]+2, group[1][1]
    for day in range(1, 7):
        for pair_number in range(1, 7):
            if day == free_day:
                break

            for parity in range(1, 3):
                subject_cell = schedule_sheet.cell(row_number, cell_number).value

                if subject_cell == u"Занятия по адресу:":
                    addition_message = f"{subject_cell} {schedule_sheet.cell(row_number + 1, cell_number).value}"
                    add_addition_message(addition_message, group_schedule, day)
                    row_number += 2
                    break

                if check_for_free_day(schedule_sheet, group_schedule, (row_number, cell_number)):
                    add_addition_message("День самостоятельных занятий", group_schedule, day)
                    free_day = day
                    break

                fill_pair(schedule_sheet, group_schedule[parity][day][pair_number], (row_number, cell_number))

                row_number += 1


    if print_schedule:
        print(json.dumps(group_schedule, indent=4, ensure_ascii=False), file=file_to_print)

    return group_schedule


def main(args: list=sys.argv[1:]):
    """main function that will run if script starts as program"""

    if args:
        for arg in args:
            with open_schedule_file(arg) as schedule:
                schedule_sheet = schedule.sheet_by_index(0)

            schedule_dir_name = "".join(os.path.basename(arg).split(".")[0:-1])

            os.mkdir(schedule_dir_name)
            os.chdir(schedule_dir_name)

            groups = get_all_groups(schedule_sheet, True)
            for group in groups:
                with open(f"schedule_for_{group[0]}.json", "w") as group_file:
                    get_schedule_for_group(schedule_sheet, group, True, group_file)

            os.chdir("..")
    else:
        print("usage: schedule_parser.py schedule_file1.xlsx [schedule_file2.xlsx...]")


if __name__ == "__main__":
    main()
