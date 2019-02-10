#!/usr/bin/env python3

def bin_to_hex(num):

    hstr = '%0*X' % ((len(num) + 3) // 4, int(num, 2))
    return hstr

def hex_to_bytes(num):
    byte = bytes.fromhex(num)
    return byte

def clean_number(num):
    return num.replace(" ", "")

if __name__ == "__main__":
    print(bin_to_hex("0000010010001101"))
    hexify = hex_to_bytes(clean_number("70 38 04 80 20 c0 90 04"))
    print(len(hexify), hexify)
#TODO
# Define a test for this function
