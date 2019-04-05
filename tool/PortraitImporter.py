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


def create_tileset_image(dest_image, template, tileset_width=256, tileset_height=32):
    """
    Create tileset image.
    :param dest_image: image display on GBA screen. Image object.
    :param template: includes width, height and oam data. Dictionary.
    :param tileset_width: width of the tileset image. Unit: pixel.
    :param tileset_height: height of the tileset image. Unit: pixel.
    :return: tileset image. Image object.
    """
    if dest_image.width != template["width"] or dest_image.height != template["height"]:
        raise ImageSizeError(dest_image.width, dest_image.height)
    image = Image.new("P", (tileset_width, tileset_height))
    image.putpalette(dest_image.getpalette())
    for i in template["OBJ"]:
        obj_image = dest_image.crop((i["x"], i["y"],
                                     i["x"] + i["width"], i["y"] + i["height"]))
        image.paste(obj_image, (i["tile_x"] * 8, i["tile_y"] * 8))
    return image


def main(argv):
    try:
        opts, args = getopt.getopt(argv[1:], "hcbt:n:s:m:e:p:",
                                   ["help", "source", "binary", "transparent=", "name=", "status_screen=",
                                    "mouth_x=", "mouth_y=", "mouth_frame=", "tileset=", "template=", "mini=",
                                    "eye_frame=", "eye_w=", "eye_h=", "eye_map=", "eye_x=", "eye_y=",
                                    "eye_mode=", "wink_w=", "wink_h=", "save_dialogue_portrait=", "save_tileset=",
                                    "load_dialogue_portrait=", "save_mouth_animation_sheet=",
                                    "save_eye_animation_sheet=", "x_offset=", "x0="])
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
    mini_portrait_file = None
    eye_frame_file = None
    eye_map_file = None
    save_dialogue_portrait_file = None
    save_tileset_file = None
    dialogue_portrait_file = None
    save_mouth_animation_sheet_file = None
    save_eye_animation_sheet_file = None
    mouth_x = -32
    mouth_y = -16
    eye_width = -8
    eye_height = -8
    wink_width = -4
    wink_height = -8
    x_offset = 0
    x0 = "middle"
    eye_x = None
    eye_y = None
    eye_mode = 4
    for opt, arg in opts:
        if opt in ["-h", "--help"]:
            print("Import customized size portrait.")
            print("%s [-h] [-c] [-b] [-t #rrggbb] [-n name] [-s <image_file>]" % argv[0])
            print("\t[-m <image_file>] [--mouth_x mx] [--mouth_y my] [-e <image_file>] [--eye_w ew] [--eye_h eh] "
                  "[--wink_w ww] [--wink_h wh] [-p <image_file>]")
            print("\t[--eye_map <eye_map_file>] [--eye_x ex] [--eye_y ey] [--eye_mode em]")
            print("\t[--tileset <tileset_file>] [--template <template_file>] [--mini <image_file>]")
            print("\t[--save_dialogue_portrait <image_file>] [--save_tileset <image_file>]")
            print("\t[--load_dialogue_portrait <image_file>] [--save_mouth_animation_sheet <image_file>]")
            print("\t[--save_eye_animation_sheet <image_file>] [--x_offset pixel_number] [--x0 type/pixel_number]")
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
            print("--mini: mini portrait displayed on the map. 32x32 image.")
            print("-e,--eye_frame: eye animation frame. Customized size image.")
            print("\tFrame0: open\n\tFrame1: half open half closed\n\tFrame2: closed")
            print("--eye_w: eye width, (Unit: pixel) Must be a multiple of 8.")
            print("--eye_h: eye height, (Unit: pixel) Must be a multiple of 8.")
            print("--wink_w: wink animation width (right eye). (Unit: pixel) Must be a multiple of 8.")
            print("--wink_h: wink animation height (right eye). (Unit: pixel) Must be a multiple of 8.")
            print("--eye_map: json file for eye frame tile map")
            print("--eye_x: X coordinate of eye frame. (Unit: pixel). Needn't be a multiple of 8.")
            print("--eye_y: Y coordinate of eye frame. (Unit: pixel). Needn't be a multiple of 8.")
            print("--eye_mode: mode of eye frame. 1-vanilla, 2-object(32x16), 3-tilemap(recommended),"
                  " 4-no eye animation, 6-always closed.")
            print("--save_dialogue_portrait: save dialogue portrait to an image file")
            print("-p,--load_dialogue_portrait: load the dialogue portrait image")
            print("--save_tileset: save tileset to an image file")
            print("--save_mouth_animation_sheet: save mouth animation to a sheet")
            print("--save_eye_animation_sheet: save eye animation to a sheet")
            print("--x0: the position of x-coordinate 0. middle(default)/left/right/pixel_number_from_left")
            print("--x_offset: the x offset of the whole portrait. pixel_number_from_x0")
            sys.exit(1)
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
        #            file_base = os.path.join(os.path.split(tileset_file)[0], portrait_name)
        elif opt in ["-s", "--status_screen"]:
            portrait_in_status_screen_file = arg
        elif opt == "--mouth_x":
            mouth_x = int(arg)
        elif opt == "--mouth_y":
            mouth_y = int(arg)
        elif opt in ["-m", "--mouth_frame"]:
            mouth_frame_file = arg
        elif opt == "--mini":
            mini_portrait_file = arg
        elif opt in ["-e", "--eye_frame"]:
            eye_frame_file = arg
            eye_mode = 3
        elif opt == "--eye_x":
            eye_x = int(arg)
            eye_mode = 2
        elif opt == "--eye_y":
            eye_y = int(arg)
            eye_mode = 2
        elif opt == "--eye_w":
            eye_width = int(arg)
            eye_mode = 3
        elif opt == "--eye_h":
            eye_height = int(arg)
            eye_mode = 3
        elif opt == "--wink_w":
            wink_width = int(arg)
            eye_mode = 3
        elif opt == "--wink_h":
            wink_height = int(arg)
            eye_mode = 3
        elif opt == "--eye_map":
            eye_map_file = arg
            eye_mode = 3
        elif opt == "--eye_mode":
            eye_mode = int(arg)
        elif opt == "--save_dialogue_portrait":
            save_dialogue_portrait_file = arg
        elif opt == "--save_tileset":
            save_tileset_file = arg
        elif opt in ["-p", "--load_dialogue_portrait"]:
            dialogue_portrait_file = arg
        elif opt == "--save_mouth_animation_sheet":
            save_mouth_animation_sheet_file = arg
        elif opt == "--save_eye_animation_sheet":
            save_eye_animation_sheet_file = arg
        elif opt == "--x0":
            x0 = arg
        elif opt == "--x_offset":
            x_offset = int(arg)
    if eye_frame_file is None:
        eye_mode = 4
    if portrait_name is not None:
        if dialogue_portrait_file is not None:
            file_base = os.path.join(os.path.split(dialogue_portrait_file)[0], portrait_name)
        elif tileset_file is not None:
            file_base = os.path.join(os.path.split(tileset_file)[0], portrait_name)
    if dialogue_portrait_file is not None:
        im_dialogue_portrait = Image.open(dialogue_portrait_file)
        if file_base is None:
            file_base = os.path.splitext(dialogue_portrait_file)[0]
        if im_dialogue_portrait.mode != "P":
            im_dialogue_portrait = im_dialogue_portrait.convert("P", palette=Image.ADAPTIVE, colors=16)
        if len(im_dialogue_portrait.getpalette()) > 16 * 3:
            im_dialogue_portrait = im_dialogue_portrait.quantize(16)
        if (not no_check_transparent_color) and (
                not operator.eq(transparent_color, tuple(im_dialogue_portrait.getpalette()[:3]))):
            for i in range(16):
                if operator.eq(transparent_color, tuple(im_dialogue_portrait.getpalette()[3 * i: 3 * i + 3])):
                    dest_map = [i]
                    for j in range(i):
                        dest_map.append(j)
                    for j in range(i + 1, 16):
                        dest_map.append(j)
                    im_dialogue_portrait = im_dialogue_portrait.remap_palette(dest_map)
                    break
    if tileset_file is not None:
        im_tileset = Image.open(tileset_file)
        if file_base is None:
            file_base = os.path.splitext(tileset_file)[0]
    if portrait_name is None:
        portrait_name = os.path.split(file_base)[1]
    # create tileset with dialogue portrait and template
    if template_file is not None:
        with open(template_file, 'r') as f:
            template = json.load(f)
    if dialogue_portrait_file is not None and tileset_file is None and template_file is not None:
        im_tileset = create_tileset_image(im_dialogue_portrait, template)
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
    if mini_portrait_file is not None:
        im_mini = Image.open(mini_portrait_file)
        if im_mini.width != 32 or im_mini.height != 32:
            raise ImageSizeError(im_mini.width, im_mini.height)
        im_mini = GBAImage.reset_palette(im_mini, im_tileset.getpalette())
        mini_portrait = GBAImage.TileSet(im_mini)
    if eye_frame_file is not None:
        im_eye = Image.open(eye_frame_file)
        if im_eye.width % 8 != 0 or im_eye.height % 24 != 0:
            raise ImageSizeError(im_eye.width, im_eye.height)
        eye_tilemap = None
        if eye_map_file is not None:
            with open(eye_map_file, 'r') as f:
                eye_template = json.load(f)
                if "mode" in eye_template:
                    eye_mode = eye_template["mode"]
                if "width" in eye_template:
                    eye_width = eye_template["width"]
                if "height" in eye_template:
                    eye_height = eye_template["height"]
                if "wink_width" in eye_template:
                    wink_width = eye_template["wink_width"]
                if "wink_height" in eye_template:
                    wink_height = eye_template["wink_height"]
                if "map" in eye_template:
                    eye_tilemap = [([0] * (eye_width // 8)) for i in range(eye_height // 8)]
                    for y in range(eye_height // 8):
                        for x in range(eye_width // 8):
                            eye_tilemap[y][x] = eye_template["map"][(eye_width // 8) * y + x][0] \
                                                + (256 // 8) * eye_template["map"][(eye_width // 8) * y + x][1]
        if eye_width == -8:
            eye_width = im_eye.width
        if eye_height == -8:
            eye_height = im_eye.height // 3
        if wink_width == -4:
            wink_width = eye_width // 2
            wink_width -= wink_width % 8
        if wink_height == -8:
            wink_height = eye_height
        eye_animation = GBAImage.AnimationFrames(eye_frame_file, eye_width, eye_height, 3, im_tileset.getpalette())
        if eye_tilemap is None:
            # fixme the tilemap generated automatically seems to lose some tiles
            eye_tilemap_auto = GBAImage.BGMap(eye_animation.image_list[0], im_tileset.getpalette(), tileset)
    # parse template
    portrait_width = template["width"]
    portrait_height = template["height"]
    oam_right = []
    oam_left = []
    if x0 == "middle":
        x0 = portrait_width // 2
    elif x0 == "left":
        x0 = 0
    elif x0 == "right":
        x0 = portrait_width
    else:
        x0 = int(x0)
    for obj in template["OBJ"]:
        width = obj["width"]
        height = obj["height"]
        x_coordinate = obj["x"] - x0 + x_offset
        y_coordinate = obj["y"] - portrait_height + 80
        tile_number = 32 * obj["tile_y"] + obj["tile_x"]
        oam_right.append(GBAImage.OBJAttribute(tile_number, x_coordinate, y_coordinate, width, height))
        x_coordinate = - (x_coordinate + width)
        oam_left.append(GBAImage.OBJAttribute(
            tile_number, x_coordinate, y_coordinate, width, height, horizontal_flip=1))
    # save the dialogue portrait to image
    if save_dialogue_portrait_file is not None:
        GBAImage.OBJSet(tileset, oam_right, portrait_width, portrait_height,
                        GBAImage.OBJAttribute(0, x_coordinate=portrait_width // 2,
                                              y_coordinate=portrait_height - 80)
                        ).save(save_dialogue_portrait_file)
    # save the tileset to image
    if save_tileset_file is not None:
        # tileset.image.save(save_tileset_file)
        im_tileset.save(save_tileset_file)
    # save mouth and eye animation sheet
    if save_mouth_animation_sheet_file is not None or save_eye_animation_sheet_file is not None:
        if dialogue_portrait_file is not None:
            im_base = im_dialogue_portrait
        else:
            im_base = GBAImage.OBJSet(
                tileset, oam_right, portrait_width, portrait_height,
                GBAImage.OBJAttribute(0, x_coordinate=portrait_width // 2, y_coordinate=portrait_height - 80)).image
        if save_mouth_animation_sheet_file is not None:
            # 2 rows 3 columns
            if mouth_frame_file is None:
                print("Mouth animation doesn't exist.")
            im_save_mouth_animation_sheet = Image.new("P", (im_base.width * 3, im_base.height * 2))
            im_save_mouth_animation_sheet.putpalette(im_base.getpalette())
            for y in range(2):
                for x in range(3):
                    im_save_mouth_animation_sheet.paste(im_base, (im_base.width * x, im_base.height * y))
                    im_save_mouth_animation_sheet.paste(
                        mouth_animation.image_list[3 * y + 2],
                        (im_base.width * x + mouth_x, im_base.height * y + mouth_y))
            im_save_mouth_animation_sheet.save(save_mouth_animation_sheet_file)
        if save_eye_animation_sheet_file is not None:
            # 1 row 3 columns
            if eye_frame_file is None:
                print("Eye animation doesn't exist.")
            if eye_mode == 4:
                print("Eye animation is disabled (eye_mode = 4).")
            im_save_eye_animation_sheet = Image.new("P", (im_base.width * 3, im_base.height))
            im_save_eye_animation_sheet.putpalette(im_base.getpalette())
            for i in range(3):
                im_save_eye_animation_sheet.paste(im_base, (im_base.width * i, 0))
                if eye_x is not None and eye_y is not None:
                    im_save_eye_animation_sheet.paste(
                        eye_animation.image_list[i], (im_base.width * i + eye_x, eye_y))
                elif eye_tilemap is not None:
                    im_tileset_eye_tiles_changed = im_tileset.copy()
                    im_tileset_eye_tiles_changed.paste(
                        eye_animation.image_list[i],
                        ((eye_tilemap[0][0] % 32) * 8, (eye_tilemap[0][0] // 32) * 8))
                    tileset_eye_tiles_changed = GBAImage.TileSet(im_tileset_eye_tiles_changed)
                    im_base_eye_tiles_changed = GBAImage.OBJSet(
                        tileset_eye_tiles_changed, oam_right, portrait_width, portrait_height,
                        GBAImage.OBJAttribute(0, x_coordinate=portrait_width // 2, y_coordinate=portrait_height - 80)
                    ).image
                    im_base_eye_tiles_changed = GBAImage.reset_palette(im_base_eye_tiles_changed, im_base.getpalette())
                    im_save_eye_animation_sheet.paste(im_base_eye_tiles_changed, (im_base.width * i, 0))
                elif eye_tilemap_auto is not None:
                    im_tileset_eye_tiles_changed = im_tileset.copy()
                    im_tileset_eye_tiles_changed.paste(
                        eye_animation.image_list[i],
                        (((eye_tilemap_auto.map[0][0] & 1023) % 32) * 8,
                         ((eye_tilemap_auto.map[0][0] & 1023) // 32) * 8))
                    tileset_eye_tiles_changed = GBAImage.TileSet(im_tileset_eye_tiles_changed)
                    im_base_eye_tiles_changed = GBAImage.OBJSet(
                        tileset_eye_tiles_changed, oam_right, portrait_width, portrait_height,
                        GBAImage.OBJAttribute(0, x_coordinate=portrait_width // 2, y_coordinate=portrait_height - 80)
                    ).image
                    im_base_eye_tiles_changed = GBAImage.reset_palette(im_base_eye_tiles_changed, im_base.getpalette())
                    im_save_eye_animation_sheet.paste(im_base_eye_tiles_changed, (im_base.width * i, 0))
            im_save_eye_animation_sheet.save(save_eye_animation_sheet_file)
    # output C source
    if output_c:
        comment = "// This file is generated by " + os.path.split(argv[0])[1] + " automatically. Don't edit it.\n"
        portrait = "// {%s_portrait_tileset, " % portrait_name
        if mini_portrait_file is None:
            portrait += "0, "
        else:
            portrait += "%s_portrait_mini, " % portrait_name
        portrait += "%s_portrait_palette, " % portrait_name
        portrait += "%s_portrait_mouth_frame, " % portrait_name
        if eye_frame_file is None:
            portrait += "0, "
        else:
            portrait += "{&%s_eye_frame_info}, " % portrait_name
        # fixme the x coordinate calculation may be wrong
        # portrait += "%d, %d, " % (mouth_x - (portrait_width - 96) // 2 - 28, mouth_y - (portrait_height - 80))
        portrait += "%d, " % (mouth_x - (x0 - 48) - 28)
        portrait += "%d, " % (mouth_y - (portrait_height - 80))
        if eye_x is None:
            eye_x_coordinate = 0
        else:
            # eye_x_coordinate = eye_x - (portrait_width - 96) // 2 - 28
            eye_x_coordinate = eye_x - (x0 - 48) - 28
        if eye_y is None:
            eye_y_coordinate = 0
        else:
            eye_y_coordinate = eye_y - (portrait_height - 80)
        portrait += "%d, %d, " % (eye_x_coordinate, eye_y_coordinate)
        portrait += "%d, oam_id, tsa_id, mask_id, 1}, // %s\n" % (eye_mode, portrait_name)

        header_file = file_base + ".h"
        with open(header_file, 'w') as f:
            f.write(comment)
            f.write(portrait)
            f.write("""
#pragma once

#include "FE7JPortrait.h"
#include "FE7JStructDef.h"

""")
            f.write("extern const unsigned short %s_portrait_palette[];\n" % portrait_name)
            f.write("extern const unsigned char %s_portrait_tileset[];\n" % portrait_name)
            f.write("extern const unsigned short %s_portrait_oam_right[];\n" % portrait_name)
            f.write("extern const unsigned short %s_portrait_oam_left[];\n" % portrait_name)
            if portrait_in_status_screen_file is not None:
                f.write("extern const unsigned short %s_portrait_in_status_screen_tsa[];\n" % portrait_name)
                f.write("extern const unsigned short %s_portrait_in_status_screen_mask[][10];\n" % portrait_name)
            f.write("extern const unsigned char %s_portrait_mouth_frame[][32 * 16 / 2];\n" % portrait_name)
            if mini_portrait_file is not None:
                f.write("extern const unsigned char %s_portrait_mini[];\n" % portrait_name)
            if eye_frame_file is not None:
                f.write("extern const struct EyeFrameInfo %s_eye_frame_info;\n" % portrait_name)
        source_file = file_base + ".c"
        with open(source_file, 'w') as f:
            f.write(comment)
            f.write("\n#include \"%s.h\"\n" % portrait_name)
            f.write("\nconst unsigned short %s_portrait_palette[] __attribute__((aligned(4)))= " % portrait_name)
            f.write(palette.tostring() + ";\n")
            f.write("\nconst unsigned char %s_portrait_tileset[] __attribute__((aligned(4)))= " % portrait_name)
            f.write(tileset.tostring().replace("{", "{0x0,0x4,0x10,0x0,", 1) + ";\n")
            f.write("\nconst unsigned short %s_portrait_oam_left[] __attribute__((aligned(4)))= {%d, "
                    % (portrait_name, len(oam_right)))
            for i in oam_right:
                f.write(i.tostring() + ", ")
            f.write("};\n")
            f.write("\nconst unsigned short %s_portrait_oam_right[] __attribute__((aligned(4)))= {%d, "
                    % (portrait_name, len(oam_left)))
            for i in oam_left:
                f.write(i.tostring() + ", ")
            f.write("};\n")
            if portrait_in_status_screen_file is not None:
                f.write("\nconst unsigned short %s_portrait_in_status_screen_tsa[] __attribute__((aligned(4)))= "
                        % portrait_name)
                f.write(status_screen_portrait_map.tostring_reverse() + ";\n")
                f.write("\nconst unsigned short %s_portrait_in_status_screen_mask[9][10] = " % portrait_name)
                f.write(status_screen_portrait_map.tostring_mask() + ";\n")
            f.write("\nconst unsigned char %s_portrait_mouth_frame[6][32 * 16 / 2] __attribute__((aligned(4)))= "
                    % portrait_name)
            if mouth_frame_file is None:
                f.write("{")
                for i in range(6):
                    f.write(mouth_frame.tostring() + ",\n")
                f.write("};\n")
            else:
                f.write(mouth_animation.tostring() + ";\n")
            if mini_portrait_file is not None:
                f.write("\nconst unsigned char %s_portrait_mini[] __attribute__((aligned(4)))= " % portrait_name)
                f.write(mini_portrait.tostring().replace("{", "{0x0,0x0,0x2,0x0,", 1) + ";\n")
            if eye_frame_file is not None:
                f.write("\nconst unsigned char %s_eye_frame[3][%d * %d / 2] __attribute__((aligned(4)))= "
                        % (portrait_name, eye_width, eye_height))
                f.write(eye_animation.tostring() + ";\n")
                f.write("\nconst short %s_eye_frame_map[] = " % portrait_name)
                if eye_tilemap is not None:
                    f.write("{")
                    for y in range(eye_height // 8):
                        for x in range(eye_width // 8):
                            f.write("0x%X," % eye_tilemap[y][x])
                    f.write("};\n")
                else:
                    f.write(eye_tilemap_auto.tostring() + ";\n")
                f.write("\nconst struct EyeFrameInfo %s_eye_frame_info = {%d,%d,%d,%d,"
                        % (portrait_name, eye_width // 8, eye_height // 8, wink_width // 8, wink_height // 8))
                f.write("{%s_eye_frame," % portrait_name)
                f.write("&%s_eye_frame[1]," % portrait_name)
                f.write("&%s_eye_frame[2]}," % portrait_name)
                f.write("%s_eye_frame_map};\n" % portrait_name)
    # todo output binary
    if output_bin:
        pass


if __name__ == "__main__":
    main(sys.argv)
