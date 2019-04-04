# Import customized size portrait
# by laqieer
# 2019-4-3

import GBAImage
import os
import sys
import getopt
import operator
from PIL import Image, ImageColor
import json


class ImageSizeError(Exception):
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def __str__(self):
        return "Wrong image size: %dx%d" % (self.width, self.height)


def main(argv):
    try:
        opts, args = getopt.getopt(argv[1:], "hcbt:n:s:m:",
                                   ["help", "source", "binary", "transparent=", "name=", "status_screen=",
                                    "mouth_x=", "mouth_y=", "mouth_frame=", "tileset=", "template="])
    except getopt.GetoptError:
        print("%s -h" % argv[0])
        sys.exit(2)
    transparent_color = ImageColor.getrgb("#a0c898")
    no_check_transparent_color = False
    output_c = False
    output_bin = False
    file_base = None
    portrait_name = None
    portrait_in_status_screen_file = None
    mouth_frame_file = None
    tileset_file = None
    template_file = None
    mouth_x = -32
    mouth_y = -16
    for opt, arg in opts:
        if opt in ["-h", "--help"]:
            print("Import customized size portrait.")
            print("%s [-h] [-c] [-b] [-t #rrggbb] [-n name] [-s <image_file>]" % argv[0])
            print("\t[-m <image_sequence>] [--mouth_x mx] [--mouth_y my]")
            print("[--tileset <tileset_file>] [--template <template_file>]")
            print("--tileset: 256x32 image")
            print("--template: json file to config template")
            print("-h,--help: show help information")
            print("-c,--source: output C source file")
            print("-b,--binary: output binary file")
            print("-t,--transparent: transparent color (default: #a0c898)."
                  "Set to nocheck if you have placed the transparent color to the first slot in the palette")
            print("-n,--name: portrait name")
            print("-s,--status_screen: portrait in status screen. 80x72 image")
            print("-m,--mouth_frame: mouth animation frame. Each frame is 32x16. Support 32x96 image or 32x16 image",
                  "sequence (6 frames).\n\tFrame0: smile open\n\tFrame1: smile half open\n\tFrame2: smile closed\n"
                  "\tFrame3: open\n\tFrame4: half open\n\tFrame5: closed")
            print("--mouth_x: x coordinate of mouth frame (base: top-left of the portrait)")
            print("--mouth_y: y coordinate of mouth frame (base: top-left of the portrait)")
        elif opt in ["-c", "--source"]:
            output_c = True
        elif opt in ["-b", "--binary"]:
            output_bin = True
        elif opt == "--tileset":
            tileset_file = arg
        elif opt == "--template":
            template_file = arg
        elif opt in ["-t", "--transparent"]:
            if arg == "nocheck":
                no_check_transparent_color = True
            else:
                transparent_color = ImageColor.getrgb(arg)
        elif opt in ["-n", "--name"]:
            portrait_name = arg
            file_base = os.path.join(os.path.split(tileset_file)[0], portrait_name)
        elif opt in ["-s", "--status_screen"]:
            portrait_in_status_screen_file = arg
        elif opt == "--mouth_x":
            mouth_x = int(arg)
        elif opt == "--mouth_y":
            mouth_y = int(arg)
        elif opt in ["-m", "--mouth_frame"]:
            mouth_frame_file = arg
    if tileset_file is not None:
        im_tileset = Image.open(tileset_file)
        if file_base is None:
            file_base = os.path.splitext(tileset_file)[0]
        if portrait_name is None:
            portrait_name = os.path.split(file_base)[1]
    if not operator.eq(im_tileset.size, (256, 32)):
        raise ImageSizeError(im_tileset.width, im_tileset.height)
    if im_tileset.mode != "P":
        im_tileset = im_tileset.convert("P", palette=Image.ADAPTIVE, colors=16)
    if len(im_tileset.getpalette()) > 16 * 3:
        im_tileset = im_tileset.quantize(16)
    if (not no_check_transparent_color) and (not operator.eq(transparent_color, tuple(im_tileset.getpalette()[:3]))):
        for i in range(16):
            if operator.eq(transparent_color, tuple(im_tileset.getpalette()[3 * i: 3 * i + 3])):
                dest_map = [i]
                for j in range(i):
                    dest_map.append(j)
                for j in range(i + 1, 16):
                    dest_map.append(j)
                im_tileset = im_tileset.remap_palette(dest_map)
                break
    palette = GBAImage.Palette(im_tileset.getpalette())
    palette.resize(16)
    tileset = GBAImage.TileSet(im_tileset)
    if template_file is not None:
        with open(template_file, 'r') as f:
            template = json.load(f)
    if portrait_in_status_screen_file is not None:
        im_ss = Image.open(portrait_in_status_screen_file)
        if not operator.eq(im_ss.size, (80, 72)):
            raise ImageSizeError(im_ss.width, im_ss.height)
        status_screen_portrait_map = GBAImage.BGMap(im_ss, im_tileset.getpalette(), tileset)
    if mouth_frame_file is None:
        #        mouth_frame_sheet = Image.new("P", (32, 16 * 6), transparent_color)
        #        for i in range(6):
        #            mouth_frame_sheet.paste(im.crop((256 - 32, 0, 256, 16)), (0, 16 * i))
        #        mouth_animation = GBAImage.TileSet(mouth_frame_sheet)
        mouth_frame = GBAImage.TileSet(im_tileset.crop((256 - 32, 0, 256, 16)))
    else:
        mouth_animation = GBAImage.AnimationFrames(mouth_frame_file, 32, 16, 6, im_tileset.getpalette())
        im_tileset.paste(mouth_animation.image_list[5], (256 - 32, 0, 256, 16))
        tileset = GBAImage.TileSet(im_tileset)
    # parse template
    portrait_width = template["width"]
    portrait_height = template["height"]
    oam_right = []
    oam_left = []
    for obj in template["OBJ"]:
        width = obj["width"]
        height = obj["height"]
        x_coordinate = obj["x"] - portrait_width // 2
        y_coordinate = obj["y"] - portrait_height + 80
        tile_number = 32 * obj["tile_y"] + obj["tile_x"]
        oam_right.append(GBAImage.OBJAttribute(tile_number, x_coordinate, y_coordinate, width, height))
        x_coordinate = - (x_coordinate + width)
        oam_left.append(GBAImage.OBJAttribute(
            tile_number, x_coordinate, y_coordinate, width, height, horizontal_flip=1))
    # output C source
    if output_c:
        comment = "// This file is generated by " + os.path.split(argv[0])[1] + " automatically. Don't edit it.\n"
        header_file = file_base + ".h"
        with open(header_file, 'w') as f:
            f.write(comment)
            f.write("""
#pragma once

#include "FE7JPortrait.h"
#include "FE7JStructDef.h"
#include "Gba_video.h"

""")
            f.write("extern const unsigned short %s_portrait_palette[];\n" % portrait_name)
            f.write("extern const unsigned char %s_portrait_tileset[];\n" % portrait_name)
            f.write("extern const unsigned short %s_portrait_oam_right[];\n" % portrait_name)
            f.write("extern const unsigned short %s_portrait_oam_left[];\n" % portrait_name)
            if portrait_in_status_screen_file is not None:
                f.write("extern const unsigned short %s_portrait_in_status_screen_tsa[];\n" % portrait_name)
                f.write("extern const unsigned short %s_portrait_in_status_screen_mask[][10];\n" % portrait_name)
            f.write("extern const unsigned char %s_portrait_mouth_frame[][32 * 16 / 2];\n" % portrait_name)
        source_file = file_base + ".c"
        with open(source_file, 'w') as f:
            f.write(comment)
            f.write("\n#include \"%s.h\"\n" % portrait_name)
            f.write("\nconst unsigned short %s_portrait_palette[] = " % portrait_name)
            f.write(palette.tostring() + ";\n")
            f.write("\nconst unsigned char %s_portrait_tileset[] = " % portrait_name)
            f.write(tileset.tostring().replace("{", "{0x0,0x4,0x10,0x0,", 1) + ";\n")
            f.write("\nconst unsigned short %s_portrait_oam_right[] = {%d, " % (portrait_name, len(oam_right)))
            for i in oam_right:
                f.write(i.tostring() + ", ")
            f.write("};\n")
            f.write("\nconst unsigned short %s_portrait_oam_left[] = {%d, " % (portrait_name, len(oam_left)))
            for i in oam_left:
                f.write(i.tostring() + ", ")
            f.write("};\n")
            if portrait_in_status_screen_file is not None:
                f.write("\nconst unsigned short %s_portrait_in_status_screen_tsa[] = " % portrait_name)
                f.write(status_screen_portrait_map.tostring_reverse() + ";\n")
                f.write("\nconst unsigned short %s_portrait_in_status_screen_mask[9][10] = " % portrait_name)
                f.write(status_screen_portrait_map.tostring_mask() + ";\n")
            f.write("extern const unsigned char %s_portrait_mouth_frame[6][32 * 16 / 2] = " % portrait_name)
            if mouth_frame_file is None:
                f.write("{")
                for i in range(6):
                    f.write(mouth_frame.tostring() + ",\n")
                f.write("};\n")
            else:
                f.write(mouth_animation.tostring() + ";\n")
    # todo output binary
    if output_bin:
        pass


if __name__ == "__main__":
    main(sys.argv)
