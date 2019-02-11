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
    hexify = hex_to_bytes(clean_number("0068600000000002001663917580999078150000000000000006000001871120080217002100336391758099907815d1501521199377342f32323030303030313232303030303031202020202020203933388b8869d4bde6420c0006303030303134"))
    print(len(hexify), hexify)
#TODO
# Define a test for this function
