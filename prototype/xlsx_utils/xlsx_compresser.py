#!/usr/bin/python

import sys
import os
import zipfile

def main(folder_name: str):
    os.chdir(folder_name)

    files = ["[Content_Types].xml", "_rels/.rels", "xl/_rels/workbook.xml.rels", "xl/workbook.xml", "xl/sharedStrings.xml", "xl/worksheets/_rels/sheet1.xml.rels", "xl/theme/theme1.xml", "xl/styles.xml", "xl/worksheets/sheet1.xml", "docProps/core.xml", "xl/printerSettings/printerSettings1.bin", "docProps/app.xml"]

    with zipfile.ZipFile(os.path.basename(folder_name) + ".xlsx", "w") as z:
        for file in files:
            try:
                z.write(file)
            except FileNotFoundError:
                print(f"{file} was not found")

    os.rename(os.path.basename(folder_name) + ".xlsx", os.curdir + "/../" + os.path.basename(folder_name) + ".xlsx")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: python compress.py folder_name")
        exit()

    main(sys.argv[1])
