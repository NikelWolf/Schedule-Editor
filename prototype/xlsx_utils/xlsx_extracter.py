#!/usr/bin/python

import sys
import os
import zipfile

def main(file_name: str):
    full_path = os.path.abspath(file_name)

    if os.path.exists(os.path.dirname(file_name)):
        os.chdir(os.path.dirname(file_name))

    os.mkdir(os.path.basename(file_name).replace(".xlsx", "") or file_name.replace(".xlsx", ""))
    os.chdir(os.path.basename(file_name).replace(".xlsx", "") or file_name.replace(".xlsx", ""))

    with zipfile.ZipFile(full_path) as z:
        z.extractall()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: python extract.py filename.xlsx")
        exit()

    main(sys.argv[1])
