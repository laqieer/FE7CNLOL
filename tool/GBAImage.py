# GBA Image Utility
# by laqieer
# 2019/4/1

from PIL import Image
import struct


class Error(Exception):
    """Base class for exceptions in GBAImage module."""
    pass


class OBJSizeError(Error):
    """Exception raised for errors in the OBJ size.

    Attributes:
        width -- OBJ width
        height -- OBJ height
        message -- explanation of the error
    """

    def __init__(self, width, height, message="wrong OBJ size"):
        self.width = width
        self.height = height
        self.message = message


class Color:
    """
    RGB5 Color
    """
    '''
    def __init__(self, v):
        self.red = v and 31
        self.green = v >> 5 and 31
        self.blue = v >> 10 and 31
    '''

    def __init__(self, r=0, g=0, b=0):
        self.red = round(r * 31 / 255)
        self.green = round(g * 31 / 255)
        self.blue = round(b * 31 / 255)

    def to_short(self):
        return self.red | self.green << 5 | self.blue << 10

    def tostring(self):
        return "RGB5(%d,%d,%d)" % (self.red, self.green, self.blue)

    def __cmp__(self, other):
        if self.to_short() < other.to_short():
            return -1
        elif self.to_short() > other.to_short():
            return 1
        else:
            return 0

    def __eq__(self, other):
        return self.red == other.red and self.green == other.green and self.blue == other.blue


class Palette:
    """
    RGB5 Palette
    """

    def __init__(self, rgb_list):
        self.color_list = []
        self.color_number = len(rgb_list) // 3
        for i in range(self.color_number):
            self.color_list.append(Color(rgb_list[3 * i], rgb_list[3 * i + 1], rgb_list[3 * i + 2]))

    def resize(self, color_number):
        self.color_number = color_number
        self.color_list = self.color_list[:color_number]

    def to_bytes(self):
        s = bytes()
        for i in range(self.color_number):
            s += struct.pack('H', self.color_list[i].to_short())
        return s

    def tostring(self):
        s = '{'
        for i in range(self.color_number):
            s += self.color_list[i].tostring() + ','
        s += '}'
        return s


class Tile:
    """
    8x8 4bit depth Tile
    """

    def __init__(self, image):
        self.pixel_list = list(image.getdata())
        self.byte_list = []
        self.palette_number = 0
        for i in range(8 * 8 // 2):
            # Each tile occupies 32 bytes of memory. Each byte representing two dots.
            # the lower 4 bits define the color for the left (!) dot, the upper 4 bits the color for the right dot.
            if self.pixel_list[2 * i] > 15:
                self.palette_number = self.pixel_list[2 * i] // 16
            if self.pixel_list[2 * i + 1] > 15:
                self.palette_number = self.pixel_list[2 * i + 1] // 16
            self.byte_list.append(self.pixel_list[2 * i] & 15 | (self.pixel_list[2 * i + 1] & 15) << 4)
        self.bytes = bytes()
        for i in self.byte_list:
            self.bytes += struct.pack('B', i)
        self.hash = hash(self.bytes)

    def to_bytes(self):
        return self.bytes

    def tostring(self):
        s = '\t'
        for i in self.byte_list:
            s += "0x%X," % i
        s += '\n'
        return s

    def __cmp__(self, other):
        if self.hash < other.hash:
            return -1
        elif self.hash > other.hash:
            return 1
        else:
            return 0

    def is_transparent(self):
        transparent = True
        for i in self.byte_list:
            if i != 0:
                transparent = False
                break
        return transparent

    def __eq__(self, other):
        return self.hash == other.hash


class TileSet:
    """
    8x8 4bit depth TileSet
    """

    def __init__(self, image):
        self.image = image
        if image.getpalette() is None:
            print("Warning: the image is not indexed. Try to index it to 256 colors automatically.")
            self.image = image.convert(mode="P", palette=Image.ADAPTIVE, colors=256)
        # todo split a 256 color palette to several 16 color palette
        # the first slot of each palette is transparent
        self.palette = Palette(image.getpalette())
        self.width = self.image.width // 8  # tile
        self.height = self.image.height // 8  # tile
        self.tile_matrix = [([0] * self.width) for i in range(self.height)]  # no flip
        self.tile_matrix_horizontal_flip = [([0] * self.width) for i in range(self.height)]
        self.tile_matrix_vertical_flip = [([0] * self.width) for i in range(self.height)]
        self.tile_matrix_horizontal_vertical_flip = [([0] * self.width) for i in range(self.height)]
        for y in range(self.height):
            for x in range(self.width):
                self.tile_matrix[y][x] = Tile(self.image.crop((8 * x, 8 * y, 8 * x + 8, 8 * y + 8)))
                self.tile_matrix_horizontal_flip[y][x] = Tile(self.image.crop(
                    (8 * x, 8 * y, 8 * x + 8, 8 * y + 8)).transpose(Image.FLIP_LEFT_RIGHT))
                self.tile_matrix_vertical_flip[y][x] = Tile(self.image.crop(
                    (8 * x, 8 * y, 8 * x + 8, 8 * y + 8)).transpose(
                    Image.FLIP_LEFT_RIGHT).transpose(Image.FLIP_TOP_BOTTOM))
                self.tile_matrix_horizontal_vertical_flip[y][x] = Tile(self.image.crop(
                    (8 * x, 8 * y, 8 * x + 8, 8 * y + 8)))

    def to_bytes(self):
        s = bytes()
        for y in range(self.height):
            for x in range(self.width):
                s += self.tile_matrix[y][x].to_bytes()
        return s

    def tostring(self):
        s = "{\n"
        for y in range(self.height):
            for x in range(self.width):
                s += self.tile_matrix[y][x].tostring()
            s += '\n'
        s += '}'
        return s

    def find_tile(self, tile):
        for y in range(self.height):
            for x in range(self.width):
                tile_number = self.width * y + x
                palette_number = self.tile_matrix[y][x].palette_number
                if tile == self.tile_matrix[y][x]:
                    return BGTile(tile_number, palette_number)
                elif tile == self.tile_matrix_horizontal_flip[y][x]:
                    return BGTile(tile_number, palette_number, horizontal_flip=1)
                elif tile == self.tile_matrix_vertical_flip[y][x]:
                    return BGTile(tile_number, palette_number, vertical_flip=1)
                elif tile == self.tile_matrix_horizontal_vertical_flip[y][x]:
                    return BGTile(tile_number, palette_number, horizontal_flip=1, vertical_flip=1)
        return None


class BGTile:
    """
    BG Screen Data Format (BG Map) (2 bytes per entry)
    """

    def __init__(self, tile_number, palette_number=0, horizontal_flip=0, vertical_flip=0):
        self.tile_number = tile_number & 1023
        self.palette_number = palette_number & 15
        self.horizontal_flip = horizontal_flip & 1
        self.vertical_flip = vertical_flip & 1

    def to_short(self):
        return self.tile_number | (self.horizontal_flip << 10) | (self.vertical_flip << 11) | (
                self.palette_number << 12)

    def tostring(self):
        return "BGTile(%d,%d,%d,%d)" % (self.tile_number, self.palette_number, self.horizontal_flip, self.vertical_flip)


class BGMap:
    """
    BG Map. It is also called TSA.
    """
    def __init__(self, image, palette, tileset):
        source_palette = Palette(image.getpalette())
        dest_palette = Palette(palette)
        dest_map = [0] * dest_palette.color_number
        for j in range(dest_palette.color_number):
            for i in range(source_palette.color_number):
                if source_palette.color_list[i] == dest_palette.color_list[j]:
                    dest_map[j] = i
                    break
        self.image = image.remap_palette(dest_map)
        self.tiles = TileSet(self.image)
        self.alpha = [([0] * self.tiles.width) for i in range(self.tiles.height)]
        self.map = [([0] * self.tiles.width) for i in range(self.tiles.height)]
        for y in range(self.tiles.height):
            for x in range(self.tiles.width):
                if self.tiles.tile_matrix[y][x].is_transparent() or tileset.find_tile(
                        self.tiles.tile_matrix[y][x]) is None:
                    self.alpha[y][x] = 0
                    self.map[y][x] = BGTile(0)
                else:
                    self.alpha[y][x] = 1
                    self.map[y][x] = tileset.find_tile(self.tiles.tile_matrix[y][x])

    def tostring(self):
        s = "{\n"
        for y in range(self.tiles.height):
            for x in range(self.tiles.width):
                s += self.map[y][x].tostring() + ","
            s += '\n'
        s += '}'
        return s

    def tostring_reverse(self):
        """
        Reverse rows. Add width and height at the begin.
        :return: C source
        """
        s = "{\n"
        s += "\t0x%X,\n" % (((self.tiles.width - 1) | (self.tiles.height - 1) << 8) & 0xFFFF)
        for y in range(self.tiles.height):
            s += "\t"
            for x in range(self.tiles.width):
                s += self.map[self.tiles.height - 1 - y][x].tostring() + ","
            s += '\n'
        s += '}'
        return s

    def to_bytes_reverse(self):
        """
        Reverse rows. Add width and height at the begin.
        :return: binary bytes
        """
        s = bytes()
        s += struct.pack('BB', self.tiles.width - 1, self.tiles.height - 1)
        for y in range(self.tiles.height):
            for x in range(self.tiles.width):
                s += struct.pack('H', self.map[self.tiles.height - 1 - y][x].to_short())
        return s

    def to_bytes(self):
        s = bytes()
        for y in range(self.tiles.height):
            for x in range(self.tiles.width):
                s += struct.pack('H', self.map[y][x].to_short())
        return s

    def tostring_alpha(self):
        s = "{\n"
        for y in range(self.tiles.height):
            s += "\t{"
            for x in range(self.tiles.width):
                s += "%d," % self.alpha[y][x]
            s += '},\n'
        s += '}'
        return s

    def to_bytes_alpha(self):
        s = bytes()
        for y in range(self.tiles.height):
            for x in range(self.tiles.width):
                s += struct.pack('H', self.alpha[y][x])
        return s


# OBJ Shape
Square = 0
Horizontal = 1
Vertical = 2

# OBJ Mode
Normal = 0
SemiTransparent = 1
OBJWindow = 2


class OBJAttribute:
    """
    OBJ - OAM Attributes
    """

    def __init__(self, tile_number, x_coordinate=0, y_coordinate=0, width=8, height=8, horizontal_flip=0,
                 vertical_flip=0, palette_number=0, priority=0, mode=Normal, mosaic=0, rotation_scaling=0,
                 rotation_scaling_parameter_number=0, double_size=0, disable=0, palette256=0):
        self.tile_number = tile_number & 1023
        self.palette_number = palette_number & 15
        self.x_coordinate = x_coordinate & 255
        self.y_coordinate = y_coordinate & 511
        self.width = width
        self.height = height
        try:
            if width not in [8, 16, 32, 64] or height not in [8, 16, 32, 64]:
                raise OBJSizeError(width, height)
        except OBJSizeError as err:
            print("%s: %dx%d" % (err.message, err.width, err.height))
        if width == height:
            self.shape = Square
        elif width > height:
            self.shape = Horizontal
        else:
            self.shape = Vertical
        try:
            if width == 64 or height == 64:
                self.size = 3
            elif width == 32:
                if height == 8:
                    self.size = 1
                else:
                    self.size = 2
            elif width == 8:
                if height == 32:
                    self.size = 1
                else:
                    self.size = 0
            elif width == 16:
                if height == 8:
                    self.size = 0
                elif height == 16:
                    self.size = 1
                elif height == 32:
                    self.size = 2
                else:
                    raise OBJSizeError(width, height)
            else:
                raise OBJSizeError(width, height)
        except OBJSizeError as err:
            print("%s: %dx%d" % (err.message, err.width, err.height))
        self.horizontal_flip = horizontal_flip & 1
        self.vertical_flip = vertical_flip & 1
        self.priority = priority & 3
        self.mode = mode & 3
        self.mosaic = mosaic & 1
        self.rotation_scaling = rotation_scaling & 1
        self.rotation_scaling_parameter_number = rotation_scaling_parameter_number & 31
        self.double_size = double_size & 1
        self.disable = disable & 1
        self.palette256 = palette256 & 1
        self.OBJAttribute0 = (y_coordinate | rotation_scaling << 8 | mode << 10 | mosaic << 12 | palette256 << 13
                              | self.shape << 14) & 0xFFFF
        self.OBJAttribute1 = x_coordinate | self.size << 14
        if rotation_scaling == 1:
            self.OBJAttribute1 = self.OBJAttribute1 | rotation_scaling_parameter_number << 9
        else:
            self.OBJAttribute1 = self.OBJAttribute1 | horizontal_flip << 12
            self.OBJAttribute1 = self.OBJAttribute1 | vertical_flip << 13
        self.OBJAttribute1 = self.OBJAttribute1 & 0xFFFF
        self.OBJAttribute2 = (tile_number | priority << 10 | palette_number << 12) & 0xFFFF

    def to_bytes(self):
        return struct.pack('HHH', self.OBJAttribute0, self.OBJAttribute1, self.OBJAttribute2)

    def tostring(self):
        return "0x%X,0x%X,0x%X" % (self.OBJAttribute0, self.OBJAttribute1, self.OBJAttribute2)
