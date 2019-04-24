# -*- coding: cp936 -*-
# Battle Animation with 31 colors and customized command.
# by laqieer
# 2019-4-15

from PIL import Image, ImageMath, ImageDraw
import imagehash
import tkinter as tk
import tkinter.messagebox
import math
import copy
import json
import os
import sys
import getopt
from operator import methodcaller, attrgetter
import GBAImage
import bin2c
import nlzss

# to split frame into objects and make sheet
obj_conf = [{'width': 64, 'height': 64, 'threshold': 7},
            {'width': 32, 'height': 64, 'threshold': 3},
            {'width': 64, 'height': 32, 'threshold': 3},
            {'width': 32, 'height': 32, 'threshold': 3},
            {'width': 16, 'height': 32, 'threshold': 1},
            {'width': 8, 'height': 32, 'threshold': 0},
            {'width': 32, 'height': 16, 'threshold': 1},
            {'width': 16, 'height': 16, 'threshold': 1},
            {'width': 8, 'height': 16, 'threshold': 0},
            {'width': 32, 'height': 8, 'threshold': 0},
            {'width': 16, 'height': 8, 'threshold': 0},
            {'width': 8, 'height': 8, 'threshold': 0}]

# Auto recolor for palette group
# Format: blue = (red, green, purple)

# From: FEditor Adv\src\Model\PortableClassAnimation.java
color_table_FEA = {0x7F73 : (0x766C, 0x6168, 0x5085), # Light blue
                   0x4B5F : (0x225F, 0x001A, 0x0410), # Mid blue
                   0x5BFB : (0x1BE7, 0x26C8, 0x19C3), # Dark blue
                   0x737B : (0x5EB6, 0x4E0F, 0x3929)} # Darker blue
# From: FEBuilderGBA/bin/Debug/config/data/battleanime_auto_recolor_ALL.txt
color_table_FEB = { 0x5FBD : (0x6BBE, 0x6F9E, 0x03DE),
                    0x3ADA : (0x4F18, 0x52B8, 0x3A7B),
                    0x0910 : (0x45ED, 0x7ECD, 0x04D0),
                    0x08AC : (0x3529, 0x7145, 0x0CCB),
                    0x11B3 : (0x35D1, 0x35D1, 0x04EF),
                    0x14E8 : (0x14A5, 0x018F, 0xA9),
                    0x7B70 : (0x4AFF, 0x4BF9, 0x6AF7),
                    0x7B4A : (0x25FF, 0x1BE7, 0x62B5),
                    0x7622 : (0x1D, 0x0F40, 0x4DEF),
                    0x5963 : (0x0416, 0x0E41, 0x3149),
                    0x04FA : (0x04FA, 0x324E, 0x39F1),
                    0x0C90 : (0x0C90, 0x2549, 0x2929),
                    0x7798 : (0x5B1C, 0x5378, 0x5EF7),
                    0x6EF3 : (0x423D, 0x4F71, 0x56B5),
                    0x5E50 : (0x3199, 0x36AF, 0x4631),
                    0x3D69 : (0x18D1, 0x2168, 0x2D6B),
                    0x011C : (0x011C, 0x234D, 0x4A52),
                    0x0876 : (0x0876, 0x126C, 0x318C),
                    0x0C6F : (0x0C6F, 0x0586, 0x18C6),
                    0x7FB3 : (0x1D, 0x2768, 0x5EB4),
                    0x7A89 : (0x0417, 0x22A7, 0x51EF),
                    0x5562 : (0x0410, 0x2207, 0x3D4A),
                    0x7E2B : (0x153B, 0x0B47, 0x5A93),
                    0x7332 : (0x463F, 0x3FF8, 0x6F38),
                    0x6105 : (0x11, 0x1985, 0x3929),
                    0x7FF0 : (0x225F, 0x3FF8, 0x7359),
                    0x7EE8 : (0x089E, 0x0B47, 0x5EB3),
                    0x6D65 : (0x0476, 0x2648, 0x49AD),
                    0x3637 : (0x737B, 0x327F, 0x1BBF),
                    0x2171 : (0x62D6, 0x091D, 0x1A9E),
                    0x14EC : (0x49CE, 0x0C92, 0x0531),
                    0x7FF5 : (0x431F, 0x4BF9, 0x737B),
                    0x7F69 : (0x1A3F, 0x1BE7, 0x62B5),
                    0x7E0A : (0x19, 0x1E84, 0x4DEF),
                    0x60E7 : (0x0410, 0x19C5, 0x3D4A),
                    0x7EF0 : (0x19DF, 0x1BE7, 0x62B5),
                    0x7587 : (0x18, 0x1AC6, 0x45AD),
                    0x4400 : (0x2C, 0x1143, 0x30E7),
                    0x7FAD : (0x225F, 0x27EA, 0x6F37),
                    0x68E7 : (0x0410, 0x1DE6, 0x3D4A),
                    0x60C6 : (0x086F, 0x19E5, 0x416B),
                    0x7E6D : (0x1B, 0x0B47, 0x5672),
                    0x3BFB : (0x7F55, 0x43FF, 0x7EDF),
                    0x1FAA : (0x7E8E, 0x1F3F, 0x6DFB),
                    0x0649 : (0x696B, 0x1597, 0x5934),
                    0x7FF6 : (0x575F, 0x5BFB, 0x737B),
                    0x7F8B : (0x1E1F, 0x23E9, 0x5AB5),
                    0x61AA : (0x0439, 0x2728, 0x4E0F),
                    0x27F6 : (0x6EF5, 0x157F, 0x1BBF),
                    0x1EB1 : (0x562C, 0x0496, 0x1A9E),
                    0x7F0F : (0x2A1E, 0x1BE7, 0x5AF6),
                    0x79A8 : (0x043A, 0x2728, 0x5230),
                    0x5484 : (0x0410, 0x1DE6, 0x3D4A),
                    0x22FC : (0x471D, 0x471D, 0x22FC),
                    0x7E70 : (0x2A1E, 0x1BE7, 0x5F17),
                    0x112D : (0x1D4E, 0x1D4E, 0x112D),
                    0x7F8E : (0x25FF, 0x1BE7, 0x5F17),
                    0x7DC8 : (0x0439, 0x2728, 0x4E0F),
                    0x75C8 : (0x043A, 0x2728, 0x5230),
                    0x2EBD : (0x2F1C, 0x3AFC, 0x2EBD),
                    0x27FF : (0x03FF, 0x53FE, 0x27FF),
                    0x7F72 : (0x0C52, 0x1AA7, 0x3D4A),
                    0x7FB6 : (0x431F, 0x4BF9, 0x777C),
                    0x7AD1 : (0x1E5D, 0x1FC9, 0x62B5),
                    0x7989 : (0x19, 0x1AE7, 0x4DEF),
                    0x54E8 : (0x0410, 0x1DE6, 0x3D4A),
                    0x7FFB : (0x7FBD, 0x7FFB, 0x7FBD),
                    0x66F2 : (0x66D5, 0x6713, 0x66D5),
                    0x4E2C : (0x4E0E, 0x4E4C, 0x4E0E),
                    0x5D44 : (0x0C52, 0x0A23, 0x3D2A),
                    0x7FDE : (0x431F, 0x4BF9, 0x775C),
                    0x7F39 : (0x1E5D, 0x1FC9, 0x6295),
                    0x6E73 : (0x19, 0x1AE7, 0x4DCF),
                    0x5DEF : (0x0410, 0x1DE6, 0x3D2A),
                    0x5D28 : (0x0410, 0x1DE6, 0x3D4A),
                    0x59EB : (0x15B6, 0x3271, 0x4A0E),
                    0x5E8F : (0x2657, 0x36F6, 0x5EB2),
                    0x40D1 : (0x0410, 0x1DE6, 0x3D4A),
                    0x5177 : (0x19, 0x1AC6, 0x4DEF),
                    0x15B6 : (0x15B6, 0x3271, 0x4A0E),
                    0x623F : (0x1E5D, 0x1BE7, 0x62B5),
                    0x2657 : (0x2657, 0x36F6, 0x5EB2),
                    0x7F7F : (0x431F, 0x4BF9, 0x6F39),
                    0x0911 : (0x45ED, 0x7ECD, 0x04D0),
                    0x15B3 : (0x35D1, 0x35D1, 0x04EF),
                    0xA9 : (0x14A5, 0x018F, 0xA9),
                    0x7B96 : (0x4AFF, 0x4BF9, 0x6AF7),
                    0x7F2F : (0x25FF, 0x1BE7, 0x62B5),
                    0x724C : (0x1D, 0x0F40, 0x4DEF),
                    0x5168 : (0x0416, 0x0E41, 0x3149),
                    0x7F6C : (0x211F, 0x4BC2, 0x7EB6),
                    0x4F5A : (0x473F, 0x0F99, 0x537B),
                    0x2E31 : (0x19FA, 0x0AD0, 0x3673),
                    0x7EB7 : (0x7EB7, 0x5AFA, 0x5F57),
                    0x7F2A : (0x129F, 0x2FB2, 0x56F5),
                    0x6E88 : (0x2DD8, 0x0323, 0x4230),
                    0x59E3 : (0x1912, 0x0A41, 0x2DAB),
                    0x71A7 : (0x18, 0x42C0, 0x59AE),
                    0x7EE5 : (0x1F, 0x4BC2, 0x7EB6),
                    0x4B19 : (0x7EB7, 0x4F16, 0x5F57),
                    0x6BAF : (0x527B, 0x37D5, 0x56F5),
                    0x4EE9 : (0x39D4, 0x22AF, 0x4230),
                    0x3628 : (0x294F, 0x262B, 0x2DAB),
                    0x2985 : (0x1CED, 0x1D68, 0x2148),
                    0x537B : (0x537B, 0x537B, 0x6B18),
                    0x3673 : (0x3673, 0x3673, 0x4E10),
                    0x7398 : (0x527B, 0x37D5, 0x6296),
                    0x6735 : (0x39D4, 0x22AF, 0x49D0),
                    0x56B1 : (0x294F, 0x262B, 0x3D4C),
                    0x39CA : (0x1CED, 0x1D68, 0x30E9),
                    0x7E6B : (0x19DF, 0x0F93, 0x62B4),
                    0x77F3 : (0x779F, 0x67F7, 0x737B),
                    0x6F89 : (0x6EFD, 0x57AF, 0x6718),
                    0x6F08 : (0x5E79, 0x3F25, 0x5694),
                    0x3141 : (0x312D, 0x0DA3, 0x394A),
                    0x7F50 : (0x19DF, 0x0F93, 0x62B4),
                    0x7F6E : (0x729D, 0x57AF, 0x6718),
                    0x7EAE : (0x6259, 0x3F25, 0x5694),
                    0x5441 : (0x312D, 0x0DA3, 0x394A),
                    0x378E : (0x7F33, 0x5AF6, 0x36BE),
                    0x1E69 : (0x7E10, 0x39EE, 0x201F),
                    0x3FF9 : (0x6718, 0x3EBF, 0x7E5A),
                    0x2773 : (0x5A73, 0x10FC, 0x6195),
                    0x1E2B : (0x458C, 0x0473, 0x3CCE),
                    0x7AEC : (0x225F, 0x3BD5, 0x6F37),
                    0x6567 : (0x1B, 0x2728, 0x5672),
                    0x5442 : (0x0410, 0x2207, 0x3D4A),
                    0x7F19 : (0x37B9, 0x6BE8, 0x2B3F),
                    0x7E95 : (0x1B69, 0x5AE2, 0x1A3F),
                    0x658E : (0x01E7, 0x49E2, 0x0558),
                    0x0FEF : (0x6718, 0x3EBF, 0x7E5A),
                    0x0F2C : (0x5A73, 0x10FC, 0x6195),
                    0x05E5 : (0x458C, 0x0473, 0x3CCE),
                    0x776C : (0x1E1D, 0x3BD5, 0x6F37),
                    0x58A5 : (0x0D, 0x19A6, 0x394A),
                    0x7F76 : (0x1BBF, 0x7EDF, 0x4ADE),
                    0x7E8E : (0x1A9E, 0x6DFB, 0x201F),
                    0x696B : (0x0531, 0x5934, 0x52),
                    0x4E7F : (0x72D6, 0x4E9F, 0x7678),
                    0x10FD : (0x55EF, 0x115F, 0x59B3),
                    0x0473 : (0x414D, 0x0473, 0x3D0F),
                    0x5EFF : (0x7F18, 0x5AFF, 0x7EDB),
                    0x0FFC : (0x3BD5, 0x7EDF, 0x4ADE),
                    0x0DF7 : (0x2207, 0x5934, 0x201F),
                    0x7B50 : (0x225F, 0x3BD5, 0x6F37),
                    0x6A4B : (0x1B, 0x2728, 0x5672),
                    0x4527 : (0x0410, 0x2207, 0x3D4A),
                    0x6D63 : (0x0D, 0x0D82, 0x416B),
                    0x7FCB : (0x225F, 0x3BF3, 0x7FBD),
                    0x7F8A : (0x2E5F, 0x3BF3, 0x7FBD),
                    0x7E27 : (0x091D, 0x0B47, 0x7317),
                    0x4C67 : (0x0A, 0x1DC7, 0x456C),
                    0x5651 : (0x562F, 0x5651, 0x562F),
                    0x41AD : (0x3DAB, 0x41AD, 0x3DAB),
                    0x3169 : (0x3548, 0x3169, 0x3548),
                    0x2EBB : (0x4797, 0x7F73, 0x2E9F),
                    0x09B7 : (0x36D3, 0x7EAE, 0x0D7E),
                    0x010E : (0x1DEA, 0x6965, 0x92),
                    0x7F94 : (0x4B7F, 0x57D9, 0x737B),
                    0x72CE : (0x46FF, 0x2B68, 0x62D6),
                    0x61A9 : (0x1139, 0x2689, 0x49CE),
                    0x5065 : (0x0870, 0x19C5, 0x3D29),
                    0xCF3F : (0xC797, 0xAE9F, 0xFF73),
                    0xAE3D : (0xB6D3, 0x0D7E, 0xFEAE),
                    0x2592 : (0x1DEA, 0x92, 0x6965),
                    0xFFF5 : (0xBB3F, 0xD7D9, 0xF37B),
                    0xFE0A : (0x04D4, 0xA689, 0x49CE),
                    0x4EFE : (0x4797, 0x2E9F, 0x7F73),
                    0x2DF8 : (0x36D3, 0x0D7E, 0x7EAE),
                    0x192E : (0x1DEA, 0x92, 0x6965),
                    0x05D8 : (0x1279, 0x7EAE, 0x6A9A),
                    0x010F : (0x0DB1, 0x6123, 0x4D70),
                    0x7E4B : (0x051A, 0x2F2B, 0x5A31),
                    0x77B0 : (0x4AFF, 0x53F3, 0x7F9C),
                    0x7E68 : (0x097C, 0x2B68, 0x5652),
                    0x6DA6 : (0x04F5, 0x2689, 0x45AD),
                    0x54A5 : (0x2C, 0x19C5, 0x3D29),
                    0x22BF : (0x22BF, 0x22BF, 0x22FF),
                    0x3259 : (0x2B68, 0x04BE, 0x1B7F),
                    0x1D6F : (0x1A29, 0x92, 0x09F7),
                    0x6BF2 : (0x6BF2, 0x6BF2, 0x77F2),
                    0x6F03 : (0x6F03, 0x6F03, 0x6F43),
                    0x7BB1 : (0x115F, 0x33D2, 0x6ED9),
                    0x6566 : (0x14, 0x2268, 0x498B),
                    0x4484 : (0x0C69, 0x1564, 0x34E7),
                    0x7FCC : (0x531F, 0x3F97, 0x5AF6),
                    0x7ECF : (0x263D, 0x1BE7, 0x5A72),
                    0x7108 : (0x19, 0x1683, 0x49CD),
                    0x4C63 : (0x11, 0x1183, 0x3929),
                    0x7FFA : (0x6FBC, 0x77FA, 0x77DD),
                    0x7733 : (0x66F5, 0x6354, 0x6B57),
                    0x4106 : (0x0D, 0x1183, 0x3527),
                    0x43FB : (0x7F19, 0x2B3F, 0x6BE8),
                    0x1734 : (0x7E95, 0x1A3F, 0x5AE2),
                    0x020A : (0x658E, 0x0558, 0x49E2),
                    0x6338 : (0x72D9, 0x3FD9, 0x7359),
                    0x18FA : (0x5E33, 0x1734, 0x5EB3),
                    0x0C8F : (0x492D, 0x020A, 0x49AD),
                    0x5294 : (0x297F, 0x73FC, 0x72D9),
                    0x3DEF : (0x18FA, 0x4F38, 0x5E33),
                    0x2529 : (0x0C8F, 0x260D, 0x492D),
                    0x3D45 : (0x0410, 0x19C5, 0x3508),
                    0x770D : (0x225F, 0x27EA, 0x6F37),
                    0x69C9 : (0x1B, 0x1AC6, 0x5672),
                    0x40E6 : (0x0410, 0x1DE6, 0x3D4A),
                    0x58D5 : (0x1B, 0x1F26, 0x5672),
                    0x386D : (0x0410, 0x2207, 0x3D4A),
                    0x5BFF : (0x1F3C, 0x5BFF, 0x1F3C),
                    0x4B1F : (0x0E78, 0x4B1F, 0x0E78),
                    0x1592 : (0x6B37, 0x1592, 0x6B37),
                    0x07FF : (0x4E2C, 0x07FF, 0x4E2C),
                    0x173B : (0x7FFF, 0x173B, 0x7FFF),
                    0x1677 : (0x53DB, 0x1677, 0x53DB),
                    0x6D9B : (0x2B4A, 0x6D9B, 0x2B4A),
                    0x4CF2 : (0x2267, 0x4CF2, 0x2267),
                    0x344B : (0x17DE, 0x344B, 0x17DE),
                    0x093D : (0x235D, 0x093D, 0x235D),
                    0x54 : (0x16B9, 0x54, 0x16B9),
                    0x438C : (0x09F4, 0x438C, 0x09F4),
                    0x2E87 : (0x054C, 0x2E87, 0x054C) }

def automake_palette_group(palette: list):
    """
    Make red/green/purple palette from blue platte.
    """
    pal_blue = GBAImage.Palette(palette)
    s = '\t' + pal_blue.tostring_raw() + '\n\t'
    # output red palette
    for color in pal_blue.color_list:
        color_blue = color.to_short()
        if color_blue in color_table_FEA:
            s += '0x%04X,' % color_table_FEA[color_blue][0]
        elif color_blue in color_table_FEB:
            s += '0x%04X,' % color_table_FEB[color_blue][0]
        else:
            s += color_blue
    s += '\n\t'
    # output green palette
    for color in pal_blue.color_list:
        color_blue = color.to_short()
        if color_blue in color_table_FEA:
            s += '0x%04X,' % color_table_FEA[color_blue][1]
        elif color_blue in color_table_FEB:
            s += '0x%04X,' % color_table_FEB[color_blue][1]
        else:
            s += color_blue
    s += '\n\t'
    # output purple palette
    for color in pal_blue.color_list:
        color_blue = color.to_short()
        if color_blue in color_table_FEA:
            s += '0x%04X,' % color_table_FEA[color_blue][2]
        elif color_blue in color_table_FEB:
            s += '0x%04X,' % color_table_FEB[color_blue][2]
        else:
            s += color_blue
    s += '\n\t' + pal_blue.tostring_raw() + '\n'
    return s


def clear_rectangle(image: Image, x=0, y=0, width=8, height=8):
    """
    Fill in a rectangle area with transparent color.
    """
    draw = ImageDraw.Draw(image)
    draw.rectangle([x, y, min(x + width, image.width), min(y + height, image.height)], fill=0)


def is_transparent(image: Image):
    """
    Check if an image is totally transparent.
    :param image:
    :return: bool.
    """
    return ImageMath.eval('not a', a=image)


def image_crop_s(image: Image, box=None):
    """
    Image.crop has out of range problem. This is a safe version.
    """
    x1 = min(box[0], image.width)
    x2 = min(box[2], image.width)
    y1 = min(box[1], image.height)
    y2 = min(box[3], image.height)
    return image.crop((x1, y1, x2, y2))


def hash_image(image: Image):
    # return imagehash.dhash(image)
    # return imagehash.whash(image)
    s = [str(i) for i in list(image.getdata())]
    s = ''.join(s)
    return hash(s)


def get_obj_size(image: Image):
    w = image.width
    h = image.height
    if w <= 8 and h <= 8:
        w_obj = 8
        h_obj = 8
    elif w <= 16 and h <= 8:
        w_obj = 16
        h_obj = 8
    elif w <= 8 and h <= 16:
        w_obj = 8
        h_obj = 16
    elif w <= 16 and h <= 16:
        w_obj = 16
        h_obj = 16
    elif w <= 32 and h <= 8:
        w_obj = 32
        h_obj = 8
    elif w <= 8 and h <= 32:
        w_obj = 8
        h_obj = 32
    elif w <= 32 and h <= 16:
        w_obj = 32
        h_obj = 16
    elif w <= 16 and h <= 32:
        w_obj = 16
        h_obj = 32
    elif w <= 32 and h <= 32:
        w_obj = 32
        h_obj = 32
    elif w <= 32 and h <= 64:
        w_obj = 32
        h_obj = 64
    elif w <= 64 and h <= 32:
        w_obj = 64
        h_obj = 32
    elif w <= 64 and h <= 64:
        w_obj = 64
        h_obj = 64
    else:
        w_obj = 64
        h_obj = 64
    return w_obj, h_obj


def split_palette(image: Image):
    """
    Split one 31 color image to two 16 color image.
    :param image:
    :return: image1, image2
    """
    if image.mode != "P":
        image = image.convert(mode="P", colors=31, palette=Image.ADAPTIVE, dither=Image.NONE)
    w = image.width
    h = image.height
    palette = image.getpalette()
    palette_1 = palette[: 3 * 16] + palette[:3] * 16 * 15
    palette_2 = palette[3 * 16: 3 * 16 * 2] + palette[:3] * 16 * 15
    palette_1s = palette[: 3 * 16] + palette[: 3] * 16 + palette[:3] * 16 * 14
    palette_2s = palette[: 3] * 16 + palette[3 * 16: 3 * 16 * 2] + palette[:3] * 16 * 14
    image_1s = image.copy()
    image_1s.putpalette(palette_1s)
    image_2s = image.copy()
    image_2s.putpalette(palette_2s)
    image_1 = set_palette(image_1s, palette_1)
    image_2 = set_palette(image_2s, palette_2)
    return image_1, image_2


def find_rectangle_col_first(image: Image, width=8, height=8, threshold=0):
    """
    Find rectangle area in an image. Column first.
    :param: image
    :param: width: rectangle width
    :param: height: ractangle height
    :param: threshold: allowed blank tile number
    :return: x, y (unit: pixel). -1, -1 if fails.
    """
    for i in range(max(image.width - width, 0) + 1):
        for j in range(max(image.height - height, 0) + 1):
##            im_box = image.crop((i, j, i + width, j + height))
            blank_tiles = 0
            for x in range(i, i + width, 8):
                for y in range(j, j + height, 8):
                    im_tile = image_crop_s(image, (x, y, x + 8, y + 8))
                    if is_transparent(im_tile):
                        blank_tiles += 1
                    if blank_tiles > threshold:
                        break
                if blank_tiles > threshold:
                    break
            if blank_tiles <= threshold:
##                im_box.show()
##                print(i, j, width, height, blank_tiles)
                return i, j
    return -1, -1


def find_rectangle_row_first(image: Image, width=8, height=8, threshold=0):
    """
    Find rectangle area in an image. Row first.
    :param: image
    :param: width: rectangle width
    :param: height: ractangle height
    :param: threshold: allowed blank tile number
    :return: x, y (unit: pixel). -1, -1 if fails.
    """
    for i in range(max(image.height - height, 0) + 1):
        for j in range(max(image.width - width, 0) + 1):
            im_box = image_crop_s(image, (j, i, j + width, i + height))
            blank_tiles = 0
            for x in range(0, width, 8):
                for y in range(0, height, 8):
                    im_tile = image_crop_s(image, (x, y, x + 8, y + 8))
                    if is_transparent(im_tile):
                        blank_tiles += 1
                    if blank_tiles > threshold:
                        break
                if blank_tiles > threshold:
                    break
            if blank_tiles <= threshold:
                return j, i
    return -1, -1


def split_frame(image: Image, split_conf=None):
    """
    Split frame into parts.
    """
##    image.show()
    if split_conf is None:
        conf = obj_conf
    else:
        conf = split_conf
    im_rest = image.copy()
    part_list = []
    while not is_transparent(im_rest):
        for obj in conf:
            if im_rest.width + 8 >= obj['width'] and im_rest.height + 8 >= obj['height']:
                x, y = find_rectangle_col_first(im_rest, obj['width'], obj['height'], obj['threshold'])
##                print(obj['width'], obj['height'], x, y)
                if x >= 0 and y >= 0:
                    part_list.append({'x': x, 'y': y, 'width': obj['width'], 'height': obj['height'],
                                      'hash': hash_image(image_crop_s(image, (x, y, x + obj['width'], y + obj['height'])))})
                    break
        clear_rectangle(im_rest, x, y, obj['width'], obj['height'])
##        if x >= 0 and y >= 0:
##            im_rest.show()
##    print(part_list)
    return part_list


def read_palette_top_right(image: Image):
    """
    Read palette from the top-right of the image.
    :param image: It has 4 rows of pixels at top-right for palette.
    :return: palette. RGB list.
    """
    palette = []
    for i in range(4):
        for j in range(8):
            pixel = image.getpixel((image.width - j - 1, i))
            if image.mode == "RGB":
                palette += list(pixel)
            elif image.mode == "P":
                palette += image.getpalette()[3 * pixel: 3 * (pixel + 1)]
    return palette


def set_palette(image: Image, palette: list):
    """
    Set image palette.
    :param image:
    :param palette:
    :return: Image.
    """
    if image.mode == "P":
        image = image.convert("RGB")
    im_palette = Image.new("P", (8, 8), tuple(palette[:3]))
    im_palette.putpalette(palette)
    image = image.quantize(colors=32, palette=im_palette, dither=0)
    return image


def set_palette_top_right(image: Image):
    """
    Set palette accoding to top right 4 rows.
    :param image:
    :return: image
    """
    if image.mode == "RGB":
        palette_data = []
        for i in range(4):
            for j in range(8):
                palette_data += list(image.getpixel((image.width - j - 1, i)))
        im_pal = Image.new("P", (16, 2))
        im_pal.putpalette(palette_data)
        image = image.quantize(colors=32, palette=im_pal, dither=Image.NONE)
    elif image.mode == "P":
        dest_map = [image.getpixel((image.width - 1, 0))] * 256
        for i in range(4):
            for j in range(8):
                dest_map[8 * i + j] = image.getpixel((image.width - j - 1, i))
        image = image.remap_palette(dest_map=dest_map)
    return image


def standardize_image(image: Image):
    """
    Adjust image size and palette.
    :return: Image.
    """
    if image.width == 248:
        image = set_palette_top_right(image)
        image = image.crop((0, 0, 240, 160))
    elif image.width == 240:
        if image.mode != "P":
            image = image.convert(mode='P', colors=31, palette=Image.ADAPTIVE, dither=Image.NONE)
        palette = image.getpalette()
        if palette[0] != palette[3 * 16] or palette[1] != palette[3 * 16 + 1] or palette[2] != palette[3 * 16 + 2]:
            transparent_color = image.getpixel((0, 0))
            dest_map = [transparent_color]
            for i in range(31):
                if i != transparent_color:
                    dest_map.append(i)
            dest_map.insert(16, transparent_color)
            image = image.remap_palette(dest_map=dest_map)
    else:
        tk.messagebox.showerror(title="Error", message="Image %s has an invalid width: %d. 240 required."
                                                       % (image.filename, image.width))
        image = None
    return image


class FramePart:
    """
    One object.
    """
    def __init__(self, width, height, x0, y0, x, y, palette_number=0, side='right'):
        self.width = width
        self.height = height
        self.x0 = x0
        self.y0 = y0
        self.x = x
        self.y = y
        self.palette_number = palette_number & 1
        self.side = side

    def tostring(self):
        if self.side == 'left':
            s = "OBJL_P "
        else:
            s = "OBJR_P "
        s += "_%dx%d, %d, %d, %d, %d, %d\n" % (self.width, self.height, self.x0, self.y0, self.x, self.y,
                                               self.palette_number)
        return s


class Sheet:
    """
    One sheet.
    """
    def __init__(self, palette: list, index):
        self.index = index
        self.image = Image.new("P", (256, 64))
        self.image.putpalette(palette)
        self.occupied_matrix = [([0] * 32) for i in range(8)]
        self.occupied_tiles = 0
        self.hash_dict = {}

    def get_usable_tiles(self):
        return 32 * 8 - self.occupied_tiles

    def get_transparent_tiles(self):
        transparent_tiles = 0
        for i in range(8):
            for j in range(32):
                if is_transparent(self.image.crop((8 * j, 8 * i, 8 * (j + 1), 8 * (i + 1)))):
                    transparent_tiles += 1
        return transparent_tiles

    def add(self, image: Image, x0=0, y0=0, width=0, height=0):
        self.image.paste(image, box=(x0, y0))
        self.hash_dict[hash_image(image)] = (x0, y0, 0, 0)
        self.hash_dict[hash_image(image.transpose(Image.FLIP_LEFT_RIGHT))] = (x0, y0, 1, 0)
        self.hash_dict[hash_image(image.transpose(Image.FLIP_TOP_BOTTOM))] = (x0, y0, 0, 1)
        self.hash_dict[hash_image(image.transpose(Image.FLIP_LEFT_RIGHT).transpose(Image.FLIP_TOP_BOTTOM))] = (x0, y0, 1, 1)
        for i in range(math.ceil(height / 8)):
            for j in range(math.ceil(width / 8)):
                self.occupied_matrix[y0 // 8 + i][x0 // 8 + j] = 1
        self.occupied_tiles += math.ceil(height / 8) * math.ceil(width / 8)

    def find_blank_area_row_first(self, width, height):
        """
        Find blank rectangle area in the sheet.
        :param width:
        :param height:
        :return:x0, y0 in sheet. -1, -1 if fails.
        """
        w = math.ceil(width / 8)
        h = math.ceil(height / 8)
        if w * h + self.occupied_tiles <= 32 * 8:
            for i in range(8 - h + 1):
                for j in range(32 - w + 1):
                    if self.occupied_matrix[i][j] == 0:
                        is_occupied = False
                        for y in range(h):
                            for x in range(w):
                                if self.occupied_matrix[i + y][j + x] == 1:
                                    is_occupied = True
                                    break
                            if is_occupied:
                                break
                        if not is_occupied:
                            return 8 * j, 8 * i
        return -1, -1

    def find_blank_area_col_first(self, width, height):
        """
        Find blank rectangle area in the sheet.
        :param width:
        :param height:
        :return:x0, y0 in sheet. -1, -1 if fails.
        """
        w = math.ceil(width / 8)
        h = math.ceil(height / 8)
        if w * h + self.occupied_tiles <= 32 * 8:
            for i in range(32 - w + 1):
                for j in range(8 - h + 1):
                    if self.occupied_matrix[j][i] == 0:
                        is_occupied = False
                        for x in range(w):
                            for y in range(h):
                                if self.occupied_matrix[j + y][i + x] == 1:
                                    is_occupied = True
                                    break
                            if is_occupied:
                                break
                        if not is_occupied:
                            return 8 * i, 8 * j
        return -1, -1

    def find_blank_rectangles(self, part_list: list):
        space_list = []
        occupied_matrix = copy.deepcopy(self.occupied_matrix)
        for part in part_list:
            if part['hash'] in self.hash_dict:
                (x0, y0, h_flip, v_flip) = self.hash_dict[part['hash']]
            else:
                x0, y0 = self.find_blank_area_col_first(part['width'], part['height'])
                if x0 == -1 or y0 == -1:
                    self.occupied_matrix = occupied_matrix
                    return None
                for row in range(y0 // 8, (y0 + part['height']) // 8):
                    for col in range(x0 // 8, (x0 + part['width']) // 8):
                        self.occupied_matrix[row][col] = 1
                h_flip = 0
                v_flip = 0
            space_list.append({'x': part['x'], 'y': part['y'], 'width': part['width'], 'height': part['height'],
                               'x0': x0, 'y0': y0, 'hash': part['hash'], 'h_flip': h_flip, 'v_flip': v_flip})
        self.occupied_matrix = occupied_matrix
        return space_list

    def add_parts(self, image: Image, space_list: list):
        for space in space_list:
            if space['hash'] not in self.hash_dict:
                self.add(image_crop_s(image, (space['x'], space['y'], space['x'] + space['width'],
                                              space['y'] + space['height'])), space['x0'], space['y0'],
                         space['width'], space['height'])

    def try_to_add(self, image: Image, priority='col', width=0, height=0):
        """
        Try to add image to the sheet.
        :param image: image to add.
        :param priority: 'col' (default) or 'row'
        :param width: OBJ width
        :param height: OBJ height
        :return: x0, y0 if succeeds, -1, -1 if fails.
        """
        if priority == 'row':
            x0, y0 = self.find_blank_area_row_first(width, height)
        else:
            x0, y0 = self.find_blank_area_col_first(width, height)
        if x0 >= 0 and y0 >= 0:
            self.add(image, x0, y0, width, height)
        return x0, y0

    def save_as_image(self, fp):
        self.image.save(fp)

    def search_part(self, part_hash):
        return self.hash_dict.get(part_hash)

    def get_duplicated_tiles(self, part_list: list):
        duplicated_tiles = 0
        for part in part_list:
            if part['hash'] in self.hash_dict:
                duplicated_tiles += (part['width'] // 8) * (part['height'] // 8)
        return duplicated_tiles

    def get_duplicated_parts(self, part_list: list):
        duplicated_parts = 0
        for part in part_list:
            if part['hash'] in self.hash_dict:
                duplicated_parts += 1
        return duplicated_parts

    def tostring(self, name=''):
        s = '\nconst unsigned char %s_sheet_%d[] __attribute__((aligned(4)))= ' % (name, self.index)
        s += GBAImage.TileSet(self.image).tostring() + ';\n'
        return s

    def tostring_lz77(self, name=''):
        s = '\n//lz77 compressed\nconst unsigned char %s_sheet_%d[] __attribute__((aligned(4)))=' % (name, self.index)
        s += GBAImage.TileSet(self.image).tostring_lz77() + '\n'
        return s


class SheetSet:
    """
    All sheets.
    """
    def __init__(self, palette: list):
        self.sheet_list = []
        self.palette = palette

    def append(self):
        self.sheet_list.append(Sheet(self.palette, len(self.sheet_list)))

    def add(self, image: Image, width=0, height=0, start_sheet_number=0):
        for i, sheet in enumerate(self.sheet_list[start_sheet_number: ]):
            x0, y0 = sheet.try_to_add(image, width, height)
            if x0 >= 0 and y0 >= 0:
                return i + start_sheet_number, x0, y0
        self.append()
        self.sheet_list[-1].add(image=image, x0=0, y0=0, width=width, height=height)
        return len(self.sheet_list) - 1, 0, 0

    def find_space(self, width=0, height=0, start_sheet_number=0):
        for i, sheet in enumerate(self.sheet_list[start_sheet_number: ]):
            x0, y0 = sheet.find_blank_area_col_first(width, height)
            if x0 >= 0 and y0 >= 0:
                return i + start_sheet_number, x0, y0
        return len(self.sheet_list), 0, 0

    def save_as_images(self, prefix='sheet_'):
##        self.sheet_list.sort(key=attrgetter('index'))
        for i, sheet in enumerate(self.sheet_list):
            sheet.save_as_image(prefix + str(sheet.index) + '.png')

    def find_space_for_parts(self, part_list: list):
        s = sorted(self.sheet_list, key=methodcaller('get_duplicated_parts', part_list), reverse=True)
        s = sorted(s, key=methodcaller('get_duplicated_tiles', part_list), reverse=True)
        for i, sheet in enumerate(s):
            space_list = sheet.find_blank_rectangles(part_list)
            if space_list is not None:
                return sheet.index, space_list
        self.append()
        return len(self.sheet_list) - 1, self.sheet_list[-1].find_blank_rectangles(part_list)

    def add_parts(self, image: Image, space_list: list, sheet_id):
        if 'x0' not in space_list[0] or 'y0' not in space_list[0]:
            space_list = self.sheet_list[sheet_id].find_blank_rectangles(space_list)
        self.sheet_list[sheet_id].add_parts(image, space_list)
        return space_list

    def tostring(self, name=''):
        s = ''
        for sheet in self.sheet_list:
            s += sheet.tostring(name)
        return s

    def tostring_lz77(self, name=''):
        s = ''
        for sheet in self.sheet_list:
            s += sheet.tostring_lz77(name)
        return s

    def save_to_c_file(self, name='', path='', comp='lz77'):
        c_file = os.path.join(path, name + '_sheets.c')
        with open(c_file, 'w') as f_c:
            f_c.write('//This file is made by BattleAnimation.py automatically. Don\'t edit it.\n')
            if comp == 'lz77':
                f_c.write(self.tostring_lz77(name))
            else:
                f_c.write(self.tostring(name).replace('{\n\t0x10,0x0,0x20,0x0,', '{\n\t0x0,0x0,0x20,0x0,'))


class Frame:
    """
    One frame.
    """
    sheets = SheetSet([0] * 3 * 256)
    parsed_frames = {}

    def __init__(self, image: Image, split_conf=None):
        if split_conf is None:
            self.split_conf = obj_conf
        else:
            self.split_conf = split_conf
        self.image = standardize_image(image)
        self.bbox = self.image.getbbox()
        self.im_core = self.image.crop(self.bbox)
        self.hash_core = hash_image(self.im_core)
        if self.hash_core in self.parsed_frames:
            self.sheet_index = self.parsed_frames[self.hash_core]['sheet_index']
            self.space_list_p1 = self.parsed_frames[self.hash_core]['space_list_p1']
            self.space_list_p2 = self.parsed_frames[self.hash_core]['space_list_p2']
            bbox = self.parsed_frames[self.hash_core]['bbox']
            bbox_p1 = self.parsed_frames[self.hash_core]['bbox_p1']
            bbox_p2 = self.parsed_frames[self.hash_core]['bbox_p2']
            if len(self.space_list_p1) > 0:
                self.bbox_p1 = []
                # element 2 & 3 are useless, so omitted
                self.bbox_p1[0] = bbox_p1[0] - bbox[0] + self.bbox[0]
                self.bbox_p1[1] = bbox_p1[1] - bbox[1] + self.bbox[1]
                self.bbox_p1 = tuple(self.bbox_p1)
            if len(self.space_list_p2) > 0:
                self.bbox_p2 = []
                # element 2 & 3 are useless, so omitted
                self.bbox_p2[0] = bbox_p2[0] - bbox[0] + self.bbox[0]
                self.bbox_p2[1] = bbox_p2[1] - bbox[1] + self.bbox[1]
                self.bbox_p2 = tuple(self.bbox_p2)
        else:
            self.im_p1, self.im_p2 = split_palette(self.image)
            self.bbox_p1 = self.im_p1.getbbox()
            self.im_p1 = self.im_p1.crop(self.bbox_p1)
            self.bbox_p2 = self.im_p2.getbbox()
            self.im_p2 = self.im_p2.crop(self.bbox_p2)
            if self.sheets.palette == [0] * 3 * 256:
                self.sheets.palette = self.image.getpalette()
            if not is_transparent(self.im_p1):
                part_list_p1 = split_frame(self.im_p1, self.split_conf)
            else:
                part_list_p1 = []
            if not is_transparent(self.im_p2):
                part_list_p2 = split_frame(self.im_p2, self.split_conf)
            else:
                part_list_p2 = []
            self.sheet_index, _ = self.sheets.find_space_for_parts(part_list_p1 + part_list_p2)
            if len(part_list_p1) > 0:
                self.space_list_p1 = self.sheets.add_parts(self.im_p1, part_list_p1, self.sheet_index)
            else:
                self.space_list_p1 = []
            if len(part_list_p2) > 0:
                self.space_list_p2 = self.sheets.add_parts(self.im_p2, part_list_p2, self.sheet_index)
            else:
                self.space_list_p2 = []
            self.parsed_frames[self.hash_core] = {'sheet_index': self.sheet_index,
                                                   'space_list_p1': self.space_list_p1, 'space_list_p2': self.space_list_p2,
                                                   'bbox': self.bbox, 'bbox_p1': self.bbox_p1, 'bbox_p2': self.bbox_p2}
##        print(self.space_list_p1)
##        print(self.space_list_p2)

    def tostring(self, side='right'):
        s = ''
        if len(self.space_list_p1) > 0:
            for space in self.space_list_p1:
                dimension = '_%dx%d' % (space['width'], space['height'])
                x0 = space['x0']
                y0 = space['y0']
                dx = space['x'] + self.bbox_p1[0] - 148
                dy = space['y'] + self.bbox_p1[1] - 88
                h_flip = space['h_flip']
                v_flip = space['v_flip']
                if side == 'left':
                    dx = - dx - space['width']
                    h_flip = 1 - h_flip
                s += '\tOBJ_U %s, %d, %d, %d, %d, 0, %d, %d\n' % (dimension, x0, y0, dx, dy, h_flip, v_flip)
        if len(self.space_list_p2) > 0:
            for space in self.space_list_p2:
                dimension = '_%dx%d' % (space['width'], space['height'])
                x0 = space['x0']
                y0 = space['y0']
                dx = space['x'] + self.bbox_p1[0] - 148
                dy = space['y'] + self.bbox_p1[1] - 88
                h_flip = space['h_flip']
                v_flip = space['v_flip']
                if side == 'left':
                    dx = - dx - space['width']
                    h_flip = 1 - h_flip
                s += '\tOBJ_U %s, %d, %d, %d, %d, 1, %d, %d\n' % (dimension, x0, y0, dx, dy, h_flip, v_flip)
        s += '\tEndFrame\n'
        return s

    def tostring_r(self):
        return self.tostring(side='right')

    def tostring_l(self):
        return self.tostring(side='left')

    def __hash__(self):
        return hash_image(self.image)

    def __eq__(self, other):
        return hash_image(self.image) == hash_image(other.image)

    def __ne__(self, other):
        return hash_image(self.image) != hash_image(other.image)


class FrameSet:
    """
    All frames.
    """
    def __init__(self, split_conf_file=None):
        self.frame_list = []
        if split_conf_file is None:
            self.split_conf = obj_conf
        else:
            self.read_split_conf(split_conf_file)

    def read_split_conf(self, split_conf_file: str):
        with open(split_conf_file, 'r') as f:
            self.split_conf = json.load(f)

    def index(self, image: Image):
        image = standardize_image(image)
        for i, frame in enumerate(self.frame_list):
            if hash_image(image) == hash_image(frame.image):
                return i
        return None

    def add(self, image: Image):
        index = self.index(image)
        if index is None:
            self.frame_list.append(Frame(image, self.split_conf))
            index = len(self.frame_list) - 1
        return index

    def tostring(self, name, side='right'):
        s = '\t.align 4\n'
        if side == 'left':
            s += '%s_oam_l:\n%s_frame_l_0:\n\tEndFrame\n' % (name, name)
        else:
            s += '%s_oam_r:\n%s_frame_r_0:\n\tEndFrame\n' % (name, name)
        for i, frame in enumerate(self.frame_list):
            if side == 'left':
                s += '%s_frame_l_%d:\n' % (name, i + 1)
            else:
                s += '%s_frame_r_%d:\n' % (name, i + 1)
            s += frame.tostring(side=side)
        s += '\n\tEndOAMInfo\n'
        return s

    def tostring_r(self, name):
        return self.tostring(name, side='right')

    def tostring_l(self, name):
        return self.tostring(name, side='left')


def f_default(s: str):
    return '@' + s


def f_comment(s: str):
    return '@' + s[1:]


def f_85(s: str):
    return 'Cmd 0x%s' % s[1:3]


def f_sound(s: str):
    return 'SFX 0x%s' % s[1:5]


def f_effect(s: str):
    return 'EFX 0x%s' % s[1:5]


def f_loop(s: str):
    # todo count frames between L and C01 to add Loop command automatically
    return '@Loop begin'


def f_next_mode(current_mode: int):
    # handle it in caller function
    return ''


def f_inline_assembly(s: str):
    return s[1:]


def f_raw_binary(s: str):
    return '.word 0x' + s[1:]


def f_trans(s: str):
    return 'Trans ' + s[1:]


parse_func = {'/': f_comment, '#': f_comment, '@': f_comment, ';': f_comment,
              'C': f_85, 'S': f_sound, 'E': f_effect, 'L': f_loop, '~': f_next_mode,
              '^': f_inline_assembly, '$': f_raw_binary, 'T': f_trans}


def parse_line(s: str):
    parse_function = parse_func.get(s[0], f_default)
    if parse_function:
        return parse_function(s)
    return ''


def output_palette_lz77(name, fp, palette: list):
    palette_bytes = GBAImage.Palette(palette).to_bytes()
    with open('palette_group_temp.bin', 'wb') as f_temp:
        f_temp.write(palette_bytes)
    nlzss.encode_file('palette_group_temp.bin', 'palette_group_temp_nlzss.bin')
    fp.write('// LZ77 compressed\n')
    fp.write(bin2c.bin2c('palette_group_temp_nlzss.bin', varname=name + '_pal').replace('=', '__attribute__((aligned(4)))=') + '\n')
    os.remove('palette_group_temp.bin')
    os.remove('palette_group_temp_nlzss.bin')


def output_double_palette(name, fp, palette: list):
    # add 4 0xFF at the head to distinguish with single palette
    fp.write('const unsigned short %s_pal[] __attribute__((aligned(4)))= {0xFFFF,0xFFFF,' % name)
    fp.write(GBAImage.Palette(palette).tostring_raw())
    fp.write('};\n')


def output_animation_c_file(name: str, palette: list, path='', abbr=''):
    palette_file = os.path.join(path, name + '_animation.c')
    with open(palette_file, 'w') as f_c:
        f_c.write('//This file is made by BattleAnimation.py automatically.\n//You can set the abbr for the animation.\n')
        f_c.write('//It is required to add &%s_animation into BattleAnimationPointerBank[].\n' % name)
        f_c.write('#include "FE7JBattleAnimation.h"\n')
        f_c.write('#include "%s_animation.h"\n' % name)
        if palette[3 * 16: 3 * 16 * 2] == palette[3 * 16: 3 * 16 + 3] * 16:
            # lz77 compression avoids the weak 0x10 detection in my hacked game routine
            output_palette_lz77(name, f_c, palette[: 3 * 16] * 4)
        else:
##            output_double_palette(name, f_c, palette[: 3 * 16 * 2] * 5)
            f_c.write('const unsigned short %s_pal[] __attribute__((aligned(4)))= {0xFFFF,0xFFFF,\n' % name)
            f_c.write(automake_palette_group(palette[: 3 * 32]) + '};\n')
        f_c.write('const BattleAnimation %s_animation __attribute__((aligned(4)))= {"%s",&%s_modes,&%s_script,&%s_oam_r,&%s_oam_l,&%s_pal};' % tuple([name, abbr[:11]] + [name] * 5))


def output_animation_header_file(name: str, path=''):
    header_file = os.path.join(path, name + '_animation.h')
    with open(header_file, 'w') as f_header:
        f_header.write('//This file is made by BattleAnimation.py automatically.\n')
        f_header.write('//It is required to include this file in BattleAnimationData.c.\n')
        f_header.write('#pragma once\n')
        f_header.write('extern const BattleAnimation %s_animation;\n' % name)
        f_header.write('extern const unsigned char %s_modes[];\n' % name)
        f_header.write('extern const unsigned char %s_script[];\n' % name)
        f_header.write('extern const unsigned char %s_oam_r[];\n' % name)
        f_header.write('extern const unsigned char %s_oam_l[];\n' % name)


def parse_modes(name, f_text, f_asm, script_file=None, split_conf_file=None, abbr=''):
    if f_text is not None and f_asm is not None:
##        pos_save = f_asm.tell()
        lines_behind = []
        frames = FrameSet(split_conf_file)
        mode = 1
        oam_file = os.path.join(os.path.dirname(script_file), name + '_oam.inc')
        parsed_images = {}
        with open(oam_file, 'w') as f_oam:
            f_oam.write('@This file is made by BattleAnimation.py automatically. Don\'t edit it.\n')
            while mode <= 12:
                print('---Mode %d---' % mode)
                lines_behind.append('\n%s_mode_%d:\n' % (name, mode))
                s = next(f_text)
                print(s)
                lines = []
                lines_b = []
                while s[0] != '~':
                    s = next(f_text)
                    if len(s) > 0:
                        print(s)
                        s_out = parse_line(s)
                        s_out_b = s_out
                        if 'p-' in s:
                            # process image
                            [duration, image_file] = s.split('p-', 1)
                            duration = duration.strip()
                            image_file = image_file.strip()
                            if image_file in parsed_images:
                                frame_id = parsed_images[image_file]['frame_id']
                                sheet_id = parsed_images[image_file]['sheet_id']
                                is_pierce = parsed_images[image_file]['is_pierce']
                                if(is_pierce):
                                    frame_id_p = parsed_images[image_file]['frame_id_p']
                                    sheet_id_p = parsed_images[image_file]['sheet_id_p']
                            else:
                                if script_file is not None and not os.path.isabs(image_file):
                                    image_file = os.path.join(os.path.dirname(script_file), image_file)
                                im = Image.open(image_file)
                                is_pierce = False
                                if im.width >= 480:
                                    is_pierce = True
                                    im_p = im.crop((240, 0, 480, 160))
                                    im = im.crop((0, 0, 240, 160))
                                frame_id = frames.add(im)
                                sheet_id = frames.frame_list[frame_id].sheet_index
                                parsed_images[image_file] = {'frame_id': frame_id, 'sheet_id': sheet_id, 'is_pierce': is_pierce}
                                if is_pierce:
                                    frame_id_p = frames.add(im_p)
                                    sheet_id_p = frames.frame_list[frame_id_p].sheet_index
                                    parsed_images[image_file]['frame_id_p'] = frame_id_p
                                    parsed_images[image_file]['sheet_id_p'] = sheet_id_p
                            # frame 0 is empty (for mode 2 and mode 4)
                            s_out += '\tShow %d, %s_sheet_%d, %s_frame_r_%d - %s_oam_r, %s' % (
                                frame_id + 1, name, sheet_id, name, frame_id + 1, name, duration)
                            if mode in [1, 3]:
                                if is_pierce:
                                    s_out_b += '\tShow %d, %s_sheet_%d, %s_frame_r_%d - %s_oam_r, %s' % (
                                        frame_id_p + 1, name, sheet_id_p, name, frame_id_p + 1, name, duration)
                                else:
                                    s_out_b += '\tShow 0, %s_sheet_0, %s_frame_r_0 - %s_oam_r, %s' % (name, name, name, duration)
                        if len(s_out) > 0:
                            lines.append('\t' + s_out + '\n')
                        if len(s_out_b) > 0:
                            lines_b.append('\t' + s_out_b + '\n')
                else:
                    while '\t@Loop begin\n' in lines:
                        index_loop = lines.index('\t@Loop begin\n')
                        if '\tCmd 0x01\n' in lines[index_loop:]:
                            index_c01 = index_loop + lines[index_loop:].index('\tCmd 0x01\n')
                            if '\t@Loop begin\n' in lines[index_loop:index_c01]:
                                lines[index_loop] = '\t@Invalid Loop\n'
                            else:
                                loop_count = 0
                                for i in lines[index_loop:index_c01]:
                                    if 'p-' in i:
                                        loop_count += 1
                                lines[index_c01] = '\tLoop %d\n' % loop_count
                                lines[index_loop] = '\t@Loop start\n'
                        else:
                            lines[index_loop] = '\t@Invalid Loop\n'
                    pass
                    lines.append('\tEndMode\n')
                    lines_behind += lines
                    if mode in [1, 3]:
                        mode += 1
                        lines_behind.append('\n%s_mode_%d:\n' % (name, mode))
                        lines_behind += lines_b + ['\tEndMode\n']
                    mode += 1
            f_oam.writelines(frames.tostring_r(name))
            f_oam.write('\t.section .rodata\n')
            f_oam.writelines(frames.tostring_l(name))
        if script_file is not None:
            path = os.path.dirname(script_file)
        else:
            path = ''
        output_animation_c_file(name, frames.frame_list[0].sheets.palette, path, abbr)
        output_animation_header_file(name, path)
        frames.frame_list[0].sheets.save_as_images(os.path.join(path, name + '_sheet_'))
        frames.frame_list[0].sheets.save_to_c_file(name=name, path=path)
##        f_asm.seek(pos_save, 0)
        lines_extern_sheets = []
##        lines_behind = f_asm.readlines()
        for i in range(len(frames.frame_list[0].sheets.sheet_list)):
            lines_extern_sheets.append('\n\t.extern %s_sheet_%d' % (name, i))
        lines_extern_sheets.append('\n')
        f_asm.writelines(lines_extern_sheets + lines_behind)


def parse_script(script_file: str='script.txt', output_file: str=None, name: str=None, split_conf_file=None, abbr=''):
    if output_file is None and name is not None:
        output_file = name + '_script.s'
    if name is None and output_file is not None:
        name = os.path.basename(output_file)
        name, _ = os.path.splitext(name)
        name = name.replace('_script', '')
    if output_file is None and name is None:
        output_file, _ = os.path.splitext(script_file)
        output_file += '.s'
        name = os.path.basename(script_file)
        name, _ = os.path.splitext(name)
        name = name.replace('_script', '')
##    with open(output_file, 'w+') as f_asm:
    with open(output_file, 'w') as f_asm:
        f_asm.write('@This file is made by BattleAnimation.py automatically. You can edit it.\n')
        f_asm.write('\t.include "BattleAnimationEventDef.inc"\n')
        f_asm.write('\t.section .rodata\n\t.align 4\n')
        f_asm.write('\t.global %s_modes\n' % name)
        f_asm.write('\t.global %s_script\n' % name)
        f_asm.write('\t.global %s_oam_r\n' % name)
        f_asm.write('\t.global %s_oam_l\n' % name)
        f_asm.write('\t.include "../include/%s_oam.inc"\n' % name)
        f_asm.write('\n%s_script:\n' % name)
        with open(script_file, 'r') as f_text:
            parse_modes(name, f_text, f_asm, script_file, split_conf_file, abbr)
        f_asm.write('\n%s_modes:\n' % name)
        for i in range(12):
            f_asm.write('\t.word %s_mode_%d - %s_script\n' % (name, i + 1, name))
        f_asm.write('\t.word 0,0,0,0,0,0,0,0,0,0,0,0\n')
        f_asm.write('\t.end\n')


def main(argv):
    script_file = None
    output_file = None
    name = None
    split_conf_file = None
    abbr = ''
    try:
        opts, args = getopt.getopt(argv, 'i:o:n:c:a:h', ['in=', 'out=', 'name=', 'conf=', 'abbr=', 'help'])
    except getopt.GetoptError:
        print('Commandline Parameter Error. -h/--help.')
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-h', '--help'):
            print('Handle battle animation script and make source files to include in project.\n')
            print('Commandline Parameter:\n')
            print('\t-h,--help\tshow help\n')
            print('\t-i,--in\tinput animation script file\n')
            print('\t-o,--out\toutput assembly script file\n')
            print('\t-n,--name\tanimation name\n')
            print('\t-a,--abbr\tanimation name abbr (less than 12 characters)\n')
            print('\t-c,--conf\tsplit algorithm configure file\n')
            sys.exit()
        elif opt in ('-i', '--in'):
            script_file = arg
        elif opt in ('-o', '--out'):
            output_file = arg
        elif opt in ('-n', '--name'):
            name = arg
        elif opt in ('-a', '--abbr'):
            abbr = arg
        elif opt in ('-c', '--conf'):
            split_conf_file = arg
    parse_script(script_file=script_file, output_file=output_file, name=name, split_conf_file=split_conf_file, abbr=abbr)


if __name__ == "__main__":
    main(sys.argv[1:])
