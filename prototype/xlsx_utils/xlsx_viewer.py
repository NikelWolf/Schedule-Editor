#!/usr/bin/python

import sys
import os
import zipfile

def main(file_name: str):
    if os.path.exists(os.path.dirname(file_name)):
        os.chdir(os.path.dirname(file_name))

    with zipfile.ZipFile(os.path.basename(file_name)) as z:
        z.printdir()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: python compress.py file_name.xlsx")
        exit()

    main(sys.argv[1])
