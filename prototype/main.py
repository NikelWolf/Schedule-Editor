#!/usr/bin/python

import sys, re
import copy
import json
import xlrd

def get_cell_indecies(schedule_sheet: xlrd.sheet.Sheet) -> tuple:
    for row in range(schedule_sheet.nrows):
        for col in range(schedule_sheet.ncols):
            yield (row, col)


def open_schedule_file(file_name: str) -> xlrd.Book:
    return xlrd.open_workbook(file_name)


def get_all_groups(schedule: xlrd.Book, add_group_start_indecies: bool=None) -> list:
    groups = []
    wb_sheet = schedule.sheet_by_index(0)
    reg = r"[A-zА-яЁё]{4}-\d{2}-\d{2}"

    for row, col in get_cell_indecies(wb_sheet):
        reg_result = re.match(reg, str(wb_sheet.cell(row, col).value))
        if reg_result:
            groups.append((reg_result.group(0), (row, col)) if add_group_start_indecies else reg_result.group(0))

    return groups


def find_group(schedule: xlrd.Book, group_name) -> tuple:
    for group in get_all_groups(schedule, True):
        if group_name == group[0]:
            return group

    return ()


def create_map_group_schedule_template() -> map:
    pair_template = {"subject": "", "type": "", "professor": "", "room": "", "addition": ""}
    day_template_without_parity = {i: copy.deepcopy(pair_template) for i in range(1, 7)}
    day_template_with_parity = {i: copy.deepcopy(day_template_without_parity) for i in range(1, 3)}
    week_template = {i: copy.deepcopy(day_template_with_parity) for i in range(1, 7)}
    return week_template


def get_raw_shedule_for_group(schedule: xlrd.Book, group: tuple) -> map:
    group_schedule = create_map_group_schedule_template()

    raise NotImplementedError


def main(args: list=sys.argv[1:]):
    if args:
        pass


if __name__ == "__main__":
    main()
