# Battle Animation with 31 colors and customized command.
# by laqieer
# 2019-4-15

from PIL import Image, ImageMath
import imagehash
import tkinter as tk
import tkinter.messagebox
import math


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
    palette_1 = palette[: 3 * 16] + [0] * 3 * 16 * 15
    palette_2 = palette[3 * 16: 3 * 16 * 2] + [0] * 3 * 16 * 15
    palette_1s = palette[: 3 * 16] + palette[: 3] * 16 + [0] * 3 * 16 * 14
    palette_2s = palette[: 3] * 16 + palette[3 * 16: 3 * 16 * 2] + [0] * 3 * 16 * 14
    image_1s = image.copy()
    image_1s.putpalette(palette_1s)
    image_2s = image.copy()
    image_2s.putpalette(palette_2s)
    image_1 = set_palette(image_1s, palette_1)
    image_2 = set_palette(image_2s, palette_2)
    return image_1, image_2


def is_transparent(image: Image):
    """
    Check if an image is totally transparent.
    :param image:
    :return: bool.
    """
    return ImageMath.eval('not a', a=image)


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
    im_palette = Image.new("P", (8, 8))
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
                dest_map[8 * i + j] = list(image.getpixel((image.width - j - 1, i)))
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
    def __init__(self, palette: list):
        self.image = Image.new("P", (256, 64))
        self.image.putpalette(palette)
        self.occupied_matrix = [([0] * 32) for i in range(8)]
        self.occupied_tiles = 0

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
        w = max(image.width, width)
        w = min(w, 64)
        h = max(image.height, height)
        h = min(h, 64)
        for i in range(math.ceil(h / 8)):
            for j in range(math.ceil(w / 8)):
                self.occupied_matrix[y0 // 8 + i][x0 // 8 + j] = 1
        self.occupied_tiles += math.ceil(h / 8) * math.ceil(w / 8)

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

    def try_to_add(self, image: Image, priority='col', width=0, height=0):
        """
        Try to add image to the sheet.
        :param image: image to add.
        :param priority: 'col' (default) or 'row'
        :param width: OBJ width
        :param height: OBJ height
        :return: x0, y0 if succeeds, -1, -1 if fails.
        """
        w = max(image.width, width)
        w = min(w, 64)
        h = max(image.height, height)
        h = min(h, 64)
        if priority == 'row':
            x0, y0 = self.find_blank_area_row_first(w, h)
        else:
            x0, y0 = self.find_blank_area_col_first(w, h)
        if x0 >= 0 and y0 >= 0:
            self.add(image, x0, y0, w, h)
        return x0, y0

    def save_as_image(self, fp):
        self.image.save(fp)


class SheetSet:
    """
    All sheets.
    """
    def __init__(self, palette: list):
        self.sheet_list = []
        self.palette = palette

    def append(self):
        self.sheet_list.append(Sheet(self.palette))

    def add(self, image: Image, width=0, height=0):
        for i, sheet in enumerate(self.sheet_list):
            x0, y0 = sheet.try_to_add(image, width, height)
            if x0 >= 0 and y0 >= 0:
                return i, x0, y0
        self.append()
        self.sheet_list[-1].add(image=image, x0=0, y0=0, width=width, height=height)
        return len(self.sheet_list) - 1, 0, 0

    def save_as_images(self, prefix='sheet_'):
        for i, sheet in enumerate(self.sheet_list):
            sheet.save_as_image(prefix + str(i) + '.png')


class Frame:
    """
    One frame.
    """
    sheets = SheetSet([0] * 3 * 256)

    def __init__(self, image: Image):
        self.image = standardize_image(image)
        self.im_p1, self.im_p2 = split_palette(self.image)
        self.im_p1 = self.im_p1.crop(self.im_p1.getbbox())
        self.im_p2 = self.im_p2.crop(self.im_p2.getbbox())
        self.part_list_right = []
        self.part_list_left = []
        if self.sheets.palette == [0] * 3 * 256:
            self.sheets.palette = self.image.getpalette()
        w_obj, h_obj = get_obj_size(self.im_p1)
        self.sheet_index, x0, y0 = self.sheets.add(self.im_p1, w_obj, h_obj)
        self.part_list_right.append(FramePart(w_obj, h_obj, x0, y0, 0, 0))
        self.part_list_left.append(FramePart(w_obj, h_obj, x0, y0, -w_obj, 0, side='left'))
        w_obj, h_obj = get_obj_size(self.im_p2)
        self.sheet_index, x0, y0 = self.sheets.add(self.im_p2, w_obj, h_obj)
        self.part_list_right.append(FramePart(w_obj, h_obj, x0, y0, 0, 0, palette_number=1))
        self.part_list_left.append(FramePart(w_obj, h_obj, x0, y0, -w_obj, 0, side='left', palette_number=1))

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
    def __init__(self):
        self.frame_list = []

    def index(self, image: Image):
        image = standardize_image(image)
        for i, frame in enumerate(self.frame_list):
            if hash_image(image) == hash_image(frame.image):
                return i
        return None

    def add(self, image: Image):
        index = self.index(image)
        if index is None:
            self.frame_list.append(Frame(image))
            index = len(self.frame_list) - 1
        return index


if __name__ == "__main__":
    im_f0 = Image.open('../trash/普莉希拉30色/001.png')
    im_f1 = Image.open('../trash/普莉希拉30色/002.png')
    im_f2 = Image.open('../trash/普莉希拉30色/003.png')
    im_f3 = Image.open('../trash/普莉希拉30色/004.png')
    im_f4 = Image.open('../trash/普莉希拉30色/005.png')
    im_f5 = Image.open('../trash/普莉希拉30色/006.png')
    im_f6 = Image.open('../trash/普莉希拉30色/007.png')
    frames = FrameSet()
    print(frames.add(im_f0))
    print(frames.add(im_f1))
    print(frames.add(im_f2))
    print(frames.add(im_f3))
    print(frames.add(im_f4))
    print(frames.add(im_f5))
    print(frames.add(im_f6))
    frames.frame_list[0].sheets.save_as_images('../trash/普莉希拉30色/sheet_')
