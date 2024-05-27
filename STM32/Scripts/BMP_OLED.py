# This script converts monochromatic .bmp file into array suitable for OLED display. 

import struct  
import os

BASE_PATH = os.path.dirname(os.path.realpath( __file__ ))
IMG_PATH = os.path.join(BASE_PATH, "OLED_Assets/linux_logo.bmp")
TEXT_PATH = os.path.join(BASE_PATH, "OLED_Array/array.txt")

IMAGE_NAME = "LINUX_LOGO"

# Read file data

with open(IMG_PATH, 'rb') as bmp:

    # Getting the offset : position 10 -> 4 reads

    bmp.seek(10, 0)
    offset = struct.unpack('I', bmp.read(4))[0]

    # Get the height and width : position 18, 22 -> 4 reads

    bmp.seek(18, 0)
    bmp_w = struct.unpack('I', bmp.read(4))[0]
    bmp_h = struct.unpack('I', bmp.read(4))[0]

    print(bmp_h, bmp_w)

    # Get the size  : position 34 -> 4 reads

    bmp.seek(34, 0)
    bmp_s = struct.unpack('I', bmp.read(4))[0]

    # Get the number of bytes in a row

    bmp_b = int(bmp_s / bmp_h)
    print(bmp_h, bmp_w, bmp_s, bmp_b)

# Read data from the image

    bmp.seek(offset, 0)

    bmp_line = ''
    bmp_list = []
    bmp_list_v = []

    for line in range(bmp_h):

        for byte in range(bmp_b):

            bmp_byte = bmp.read(1)
            bmp_line += format(255-struct.unpack('B', bmp_byte)[0], "08b")

        bmp_list.append(bmp_line[:bmp_w])
        bmp_list_v.append(bmp_line[:bmp_w].replace("0", " "))
        bmp_line = ''

    bmp_list_v.reverse()

    for line in bmp_list_v:
        print(line)

# Reshape the data to adjust to an OLED screen

byte_word = ""
OLED_line = []
OLED_array = []

for line in range(0, bmp_h, 8):
    for bit_num in range(bmp_w):
        for bit in range(line, line + 8):

            if bit > bmp_h - 1:
                byte_word += "0"
            else:
                byte_word += bmp_list[bit][bit_num]

        OLED_line.append(hex(int(byte_word, 2)))
        byte_word = ''

    OLED_array.append(OLED_line)
    OLED_line = []

OLED_array.reverse()

# Save the new array in a text file

with open(TEXT_PATH, 'w') as text_file:

    text_file.write(
        f'static uint8_t {IMAGE_NAME}_ROWS = {len(OLED_array)};\n'
    )

    text_file.write(
        f'static uint8_t {IMAGE_NAME}_COLS = {len(OLED_array[0])};\n'
    )

    text_file.write(f'static const char {IMAGE_NAME}[] = \n')

    text_file.write('{\n')

    for l_cnt, lines in enumerate(OLED_array):
        for cnt, hexa in enumerate(lines):

            text_file.write(f'{hexa}')
            if cnt < len(lines)-1:
                text_file.write(',')

        if l_cnt < len(OLED_array)-1:
            text_file.write(f',\n')
        else:
            text_file.write(f'\n')

    text_file.write('};')