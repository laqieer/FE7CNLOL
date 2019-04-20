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
        self.hash_dict[hash_image(image)] = (x0, y0)
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
                (x0, y0) = self.hash_dict[part['hash']]
            else:
                x0, y0 = self.find_blank_area_col_first(part['width'], part['height'])
                if x0 == -1 or y0 == -1:
                    self.occupied_matrix = occupied_matrix
                    return None
                for row in range(y0 // 8, (y0 + part['height']) // 8):
                    for col in range(x0 // 8, (x0 + part['width']) // 8):
                        self.occupied_matrix[row][col] = 1
            space_list.append({'x': part['x'], 'y': part['y'], 'width': part['width'],
                               'height': part['height'], 'x0': x0, 'y0': y0, 'hash': part['hash']})
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
        s = '%s_sheet_%d:\n\t' % (name, self.index)
        s += GBAImage.TileSet(self.image).tostring()[1:-1]
        s += '\n'
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

    def save_to_asmfile(self, name='', path=''):
        asmfile = os.path.join(path, name + '_sheets.inc')
        with open(asmfile, 'w') as f_asm:
            f_asm.write('@This file is made by BattleAnimation.py automatically. Don\'t edit it.\n')
            f_asm.write('\t.section .rodata\n\t.align\n')
            f_asm.write(self.tostring(name) + '\n')


class Frame:
    """
    One frame.
    """
    sheets = SheetSet([0] * 3 * 256)

    def __init__(self, image: Image, split_conf=None):
        if split_conf is None:
            self.split_conf = obj_conf
        else:
            self.split_conf = split_conf
        self.image = standardize_image(image)
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
                obj_cmd = 'OBJR'
                if side == 'left':
                    dx = - dx - space['width']
                    obj_cmd = 'OBJL'
                s += '\t%s %s, %d, %d, %d, %d\n' % (obj_cmd, dimension, x0, y0, dx, dy)
        if len(self.space_list_p2) > 0:
            for space in self.space_list_p2:
                dimension = '_%dx%d' % (space['width'], space['height'])
                x0 = space['x0']
                y0 = space['y0']
                dx = space['x'] + self.bbox_p1[0] - 148
                dy = space['y'] + self.bbox_p1[1] - 88
                obj_cmd = 'OBJR_P2'
                if side == 'left':
                    dx = - dx - space['width']
                    obj_cmd = 'OBJL_P2'
                s += '\t%s %s, %d, %d, %d, %d\n' % (obj_cmd, dimension, x0, y0, dx, dy)
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
    s_out = 'Cmd 0x%s' % s[1:3]
    if s[1:3] == '01':
        s_out = '@Loop end\n\t' + s_out
    return s_out


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


def output_palette_group(name, fp, palette: list):
    palette_bytes = GBAImage.Palette(palette).to_bytes()
    palette_group_bytes = palette_bytes * 4
    with open('palette_group_temp.bin', 'wb') as f_temp:
        f_temp.write(palette_group_bytes)
    nlzss.encode_file('palette_group_temp.bin', 'palette_group_temp_nlzss.bin')
    fp.write('// LZ77 compressed\n')
    fp.write(bin2c.bin2c('palette_group_temp_nlzss.bin', varname=name + '_pal_1') + '\n')
    os.remove('palette_group_temp.bin')
    os.remove('palette_group_temp_nlzss.bin')


def output_palette_2(name, fp, palette: list):
    fp.write('const unsigned short %s_pal_2[] __attribute__((aligned(4)))= {' % name)
    fp.write(GBAImage.Palette(palette).tostring_raw())
    fp.write('};\n')


def output_animation_palette(name: str, palette: list, path=''):
    palette_file = os.path.join(path, name + '_pal.c')
    with open(palette_file, 'w') as f_pal:
        f_pal.write('//This file is made by BattleAnimation.py automatically. Don\'t edit it.\n')
        output_palette_group(name, f_pal, palette[: 3 * 16])
        output_palette_2(name, f_pal, palette[3 * 16: 3 * 16 * 2])


def parse_modes(name, f_text, f_asm, script_file=None):
    if f_text is not None and f_asm is not None:
        frames = FrameSet('SplitConf.json')
        mode = 1
        oam_file = os.path.join(os.path.dirname(script_file), name + '_oam.inc')
        with open(oam_file, 'w') as f_oam:
            f_oam.write('@This file is made by BattleAnimation.py automatically. Don\'t edit it.\n')
            while mode <= 12:
                print('---Mode %d---' % mode)
                f_asm.write('\n%s_mode_%d:\n' % (name, mode))
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
                            if script_file is not None and not os.path.isabs(image_file):
                                image_file = os.path.join(os.path.dirname(script_file), image_file)
                            im = Image.open(image_file)
                            # todo handle pierce frame (width: 480/488)
                            is_pierce = False
                            if im.width >= 480:
                                is_pierce = True
                                im_p = im.crop((240, 0, 480, 160))
                                im = im.crop((0, 0, 240, 160))
                            frame_id = frames.add(im)
                            sheet_id = frames.frame_list[frame_id].sheet_index
                            # frame 0 is empty (for mode 2 and mode 4)
                            s_out += '\tShow %d, %s_sheet_%d, %s_frame_r_%d - %s_oam_r, %s' % (
                                frame_id + 1, name, sheet_id, name, frame_id + 1, name, duration)
                            if is_pierce:
                                frame_id_p = frames.add(im_p)
                                sheet_id_p = frames.frame_list[frame_id_p].sheet_index
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
                    # todo add loop command
                    pass
                    lines.append('\tEndMode\n')
                    f_asm.writelines(lines)
                    if mode in [1, 3]:
                        mode += 1
                        f_asm.write('\n%s_mode_%d:\n' % (name, mode))
                        f_asm.writelines(lines_b)
                    mode += 1
            f_oam.writelines(frames.tostring_r(name))
            f_oam.write('\t.section .rodata\n')
            f_oam.writelines(frames.tostring_l(name))
        if script_file is not None:
            path = os.path.dirname(script_file)
        else:
            path = ''
        output_animation_palette(name, frames.frame_list[0].sheets.palette, path)
        frames.frame_list[0].sheets.save_as_images(os.path.join(path, name + '_sheet_'))
        frames.frame_list[0].sheets.save_to_asmfile(name=name, path=path)


def parse_script(script_file: str='script.txt', output_file: str=None, name: str=None):
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
    with open(output_file, 'w') as f_asm:
        f_asm.write('@This file is made by BattleAnimation.py automatically. You can edit it.\n')
        f_asm.write('\t.include "BattleAnimationEventDef.inc"\n')
        f_asm.write('\t.include "%s_sheet.inc"\n' % name)
        f_asm.write('\t.section .rodata\n\t.align 4\n')
        f_asm.write('\t.global %s_modes\n' % name)
        f_asm.write('\t.global %s_script\n' % name)
        f_asm.write('\t.global %s_oam_r\n' % name)
        f_asm.write('\t.global %s_oam_l\n' % name)
        f_asm.write('\t.include "%s_oam.inc"\n' % name)
        f_asm.write('\n%s_script:\n' % name)
        with open(script_file, 'r') as f_text:
            parse_modes(name, f_text, f_asm, script_file)
        f_asm.write('\n%s_modes:\n' % name)
        for i in range(12):
            f_asm.write('\t.word %s_mode_%d - %s_script\n' % (name, i + 1, name))
        f_asm.write('\t.word 0,0,0,0,0,0,0,0,0,0,0,0\n')
        f_asm.write('\t.end\n')


if __name__ == "__main__":
    # test: split frame and make sheet
    '''im_f0 = Image.open('../trash/普莉希拉30色/001.png')
    im_f1 = Image.open('../trash/普莉希拉30色/002.png')
    im_f2 = Image.open('../trash/普莉希拉30色/003.png')
    im_f3 = Image.open('../trash/普莉希拉30色/004.png')
    im_f4 = Image.open('../trash/普莉希拉30色/005.png')
    im_f5 = Image.open('../trash/普莉希拉30色/006.png')
    im_f6 = Image.open('../trash/普莉希拉30色/007.png')
    frames = FrameSet('SplitConf.json')
    print("pocessing 001.png")
    print("Frame ", frames.add(im_f0))
    print("pocessing 002.png")
    print("Frame ", frames.add(im_f1))
    print("pocessing 003.png")
    print("Frame ", frames.add(im_f2))
    print("pocessing 004.png")
    print("Frame ", frames.add(im_f3))
    print("pocessing 005.png")
    print("Frame ", frames.add(im_f4))
    print("pocessing 006.png")
    print("Frame ", frames.add(im_f5))
    print("pocessing 007.png")
    print("Frame ", frames.add(im_f6))
    frames.frame_list[0].sheets.save_as_images('../trash/普莉希拉30色/sheet_')'''
##    frames = FrameSet('SplitConf.json')
##    im = Image.open('../trash/erlm_sw1/erlm_sw1_000.png')
##    print(frames.add(im))
    # test: parse script
    parse_script('../trash/erlm_sw1/erlm_sw1.txt')
