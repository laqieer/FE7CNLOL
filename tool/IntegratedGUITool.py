# Integrated GUI Tool. Not a ROM editor. 集成图形界面工具, 只输出C/汇编源文件, 不是修改器, 不修改游戏ROM.
# by laqieer
# 2019/4/8

import sys
import os
import math
import json
import getopt
import tkinter as tk
import tkinter.messagebox
import tkinter.colorchooser
from tkinter import filedialog
from PIL import Image, ImageTk, ImageDraw, PaletteFile, GimpPaletteFile, ImageColor
import GBAImage
from codecs import encode


def act_to_list(act_file):
    # fixme Important sidenote: Adobe sometimes does weird stuff, like filling the last bits with 00ff ffff ffff,
    # which totally ruins color amount recognition. I haven't found the documentation for the fileformat,
    # so I don't really know what's going on there. It seems the total_colors_count is the most reliable bit of
    # information we have, as it is least likely to get filled with fff even if we make color tables 2 or 4 colors long,
    #  where as color_count has the tendency to be broken on less than 128 colors palette tables.
    with open(act_file, 'rb') as act:
        raw_data = act.read()  # Read binary data
    hex_data = encode(raw_data, 'hex')  # Convert it to hexadecimal values
    total_colors_count = (int(hex_data[-7:-4], 16))  # Get last 3 digits to get number of colors total
    misterious_count = (int(hex_data[-4:-3], 16))  # I have no idea what does it do
    colors_count = (int(hex_data[-3:], 16))  # Get last 3 digits to get number of nontransparent colors

    # Decode colors from hex to string and split it by 6 (because colors are #1c1c1c)
    colors = [hex_data[i:i + 6].decode() for i in range(0, total_colors_count * 6, 6)]

    # Add # to each item and filter empty items if there is a corrupted total_colors_count bit
    colors = ['#' + i for i in colors if len(i)]

    return colors, total_colors_count


def show_palette(palette, size=4):
    """
    Show palette.
    :param palette: RGB list
    :return: Image
    """
    colors = len(palette) // 3
    rows = math.ceil(colors / 16)
    width = size * 16
    height = size * rows
    image = Image.new("P", (width, height))
    draw = ImageDraw.Draw(image)
    for row in range(rows):
        for col in range(16):
            draw.rectangle((size * col, size * row, size * (col + 1), size * (row + 1),),
                           fill=tuple(palette[3 * (16 * row + col): 3 * (16 * row + col + 1)]))
    return image


def read_palette(palette_file):
    """
    Read palette file.
    :param palette_file: filename
    :return: palette. RGB list.
    """
    _, ext = os.path.splitext(palette_file)
    rgb_list = []
    if ext in [".act", ".ACT"]:
        palette, _ = act_to_list(palette_file)
        for i, color in enumerate(palette):
            color = ImageColor.getrgb(color)
            rgb_list += list(color)
    elif ext in [".gpl", ".GPL"]:
        with open(palette_file, 'rb') as f:
            palette = GimpPaletteFile.GimpPaletteFile(f)
            for i in palette.getpalette():
                for j in i:
                    rgb_list.append(j)
    else:
        with open(palette_file, 'rb') as f:
            palette = PaletteFile.PaletteFile(f)
            for i in palette.getpalette():
                for j in i:
                    rgb_list.append(j)
    return rgb_list


def convert_palette_to_image(image: Image, color_number=256, pixel_size=4):
    """
    Convert palette in an image to an image for display.
    :param image: Image object.
    :param color_number: Color number.
    :param pixel_size: Each color is shown as a pixel_size x pixel_size square.
    :return: 16xN image. Image object.
    """
    palette = image.getpalette()
    colors = len(palette) // 3
    if color_number < colors:
        colors = color_number
    row_number = math.ceil(colors / 16)
    img_palette = Image.new("RGB", (pixel_size * 16, pixel_size * row_number))
    draw = ImageDraw.Draw(img_palette)
    for i in range(row_number):
        for j in range(16):
            draw.rectangle([(pixel_size * j, pixel_size * i), (pixel_size * (j + 1), pixel_size * (i + 1))],
                           fill=tuple(palette[3 * (16 * i + j): 3 * (16 * i + j + 1)]))
    return img_palette


def show_about_info():
    """
    Show about information.
    :return: None
    """
    tk.messagebox.showinfo(title='about', message='''
    Integrated GUI Tool only for FE7CNLOL Project.
    This program is to generate C/Assembly source files.
    This is not a ROM Editor.
    Licensed under GPLv3.
    Author: https://github.com/laqieer.
    ''')


def ask_and_open_image(width=0, height=0, color_number=0, palette: Image = None):
    """
    ask users and open an image.
    :param width: image width.
    :param height: image height.
    :param color_number: color number limit.
    :param palette: Quantize to the palette of given Image.
    :return: Image object. None if fails.
    """
    image_file = filedialog.askopenfilename(title='Open Image', filetypes=[('PNG', '*.png'), ('All Files', '*')])
    if image_file is not None:
        image = Image.open(image_file)
        if width != 0 and image.width != width:
            tk.messagebox.showerror(title='Error',
                                    message='The image width is %d pixel. Required: %d pixel.' % (image.width, width))
            return
        if height != 0 and image.height != height:
            tk.messagebox.showerror(title='Error', message='The image height is %d pixel. Required: %d pixel.'
                                                           % (image.height, height))
            return
        if palette is not None:
            image = image.convert(mode='RGB')
            image = image.quantize(palette=palette)
            return image
        if color_number != 0:
            color_list = image.getcolors(color_number)
            if color_list is None:
                is_quantize = tk.messagebox.askyesno(
                    title='Error', message='The image has more than %d colors. '
                                           'Are you going to quantize it or do it by yourself?' % color_number)
                if is_quantize:
                    image = image.convert(mode='RGB')
                    image = image.quantize(colors=color_number)
                else:
                    return
        return image


def ask_and_open_json():
    """
    Ask users for a json file and read from it
    :return: Dictionary
    """
    json_file = filedialog.askopenfilename(title='Open Template', filetypes=[('JSON', '*.json'), ('All Files', '*')])
    if json_file is not None:
        with open(json_file, 'r') as f:
            return json.load(f)


def ask_and_open_palette():
    """
    Ask user for a palette file.
    :return: palette. RGB list.
    """
    palette_file = filedialog.askopenfilename(title='Open Palette', filetypes=[
        ('PhotoShop Palette', '*.ACT'), ('GIMP Palette', '*.gpl'), ('Teragon-style Palette', '*')])
    if palette_file is not None:
        palette = read_palette(palette_file)
    return palette


def ask_and_save_image(image):
    """
    Ask user and save image.
    :return:None 
    """
    if image is None:
        tk.messagebox.showerror(title='Error', message='Nothing to save.')
    else:
        image_file = filedialog.asksaveasfilename(title='Save Image',
                                                  filetypes=[('PNG', '*.png'), ('All Files', '*')])
        if image is not None:
            image.save(image_file)


def show_main_window(argv):
    """
    Show main window.
    :return: process finished with exit code
    """
    window = tk.Tk()
    window.title("Integrated GUI Tool")

    # welcome image
    cv = tk.Canvas(window, width=445, height=127)
    cv.pack()
    img_welcome_file = tk.PhotoImage(file="welcome.gif")
    cv.create_image(0, 0, anchor='nw', image=img_welcome_file)

    # menu bar
    menu_bar = tk.Menu(window)
    menu_file = tk.Menu(menu_bar, tearoff=0)
    menu_bar.add_cascade(label='File', menu=menu_file)
    menu_file.add_command(label='About', command=show_about_info)
    menu_file.add_command(label='Quit', command=window.quit)
    window.config(menu=menu_bar)

    def show_portrait_window():
        """
        Open portrait tool.
        :return: None
        """
        window_portrait = tk.Toplevel(window)
        window_portrait.title('Portrait')

        img_palette: Image = None
        img_dialogue: Image = None
        img_tileset: Image = None
        img_status_screen: Image = None
        img_mini: Image = None
        img_eye_animation: Image = None
        img_mouth_animation: Image = None
        dict_dialogue_template: dict = None
        img_dialogue_template: Image = None
        img_dialogue_template_tileset: Image = None

        offset_x = tk.IntVar()
        offset_x.set(0)
        offset_y = tk.IntVar()
        offset_y.set(0)

        wink_width = tk.IntVar()
        wink_width.set(0)
        wink_height = tk.IntVar()
        wink_height.set(0)

        def load_portrait_dialogue():
            """
            Load dialogue portrait.
            :return:None.
            """
            nonlocal img_dialogue
            img_dialogue = ask_and_open_image(color_number=16, palette=img_tileset)
            if img_dialogue is not None:
                ph_dialogue = ImageTk.PhotoImage(img_dialogue)
                l_dialogue.config(text="Dialogue: %d x %d" % (img_dialogue.width, img_dialogue.height),
                                  image=ph_dialogue)
                l_dialogue.image = ph_dialogue  # keep a reference!

        def load_portrait_tileset():
            """
            Load portrait tileset.
            :return:None.
            """
            nonlocal img_tileset
            img_tileset = ask_and_open_image(width=256, height=32, color_number=16)
            if img_tileset is not None:
                ph_tileset = ImageTk.PhotoImage(img_tileset)
                l_tileset.config(image=ph_tileset)
                l_tileset.image = ph_tileset  # keep a reference!
                nonlocal img_palette
                img_palette = convert_palette_to_image(img_tileset, color_number=16, pixel_size=8)
                ph_palette = ImageTk.PhotoImage(img_palette)
                l_palette.config(image=ph_palette)
                l_palette.image = ph_palette  # keep a reference!

        def load_portrait_status_screen():
            """
            Load status screen portrait.
            :return:None.
            """
            nonlocal img_status_screen
            img_status_screen = ask_and_open_image(width=80, height=72, color_number=16, palette=img_tileset)
            if img_status_screen is not None:
                ph_status_screen = ImageTk.PhotoImage(img_status_screen)
                l_status_screen.config(image=ph_status_screen)
                l_status_screen.image = ph_status_screen  # keep a reference!

        def load_portrait_mini():
            """
            Load mini portrait.
            :return:None.
            """
            nonlocal img_mini
            img_mini = ask_and_open_image(width=32, height=32, color_number=16, palette=img_tileset)
            if img_mini is not None:
                ph_mini = ImageTk.PhotoImage(img_mini)
                l_mini.config(image=ph_mini)
                l_mini.image = ph_mini  # keep a reference!

        def load_eye_animation():
            """
            Load eye animation.
            :return:None.
            """
            nonlocal img_eye_animation
            img_eye_animation = ask_and_open_image(color_number=16, palette=img_tileset)
            if img_eye_animation is not None:
                ph_eye_animation = ImageTk.PhotoImage(img_eye_animation)
                l_eye_animation.config(text="Eye: %d x %d" % (img_eye_animation.width, img_eye_animation.height // 3),
                                       image=ph_eye_animation)
                l_eye_animation.image = ph_eye_animation  # keep a reference!
                wink_width.set(math.ceil(img_eye_animation.width / 2))
                wink_height.set(img_eye_animation.height // 3)

        def load_mouth_animation():
            """
            Load mouth animation.
            :return:None.
            """
            nonlocal img_mouth_animation
            img_mouth_animation = ask_and_open_image(color_number=16, palette=img_tileset)
            if img_mouth_animation is not None:
                ph_mouth_animation = ImageTk.PhotoImage(img_mouth_animation)
                l_mouth_animation.config(text="Mouth: %d x %d" %
                                              (img_mouth_animation.width, img_mouth_animation.height // 6),
                                         image=ph_mouth_animation)
                l_mouth_animation.image = ph_mouth_animation  # keep a reference!

        def load_dialogue_template():
            """
            Load dialogue portrait template.
            :return: None
            """
            nonlocal dict_dialogue_template
            nonlocal img_dialogue_template
            nonlocal img_dialogue_template_tileset
            dict_dialogue_template = ask_and_open_json()
            if dict_dialogue_template is not None:
                img_dialogue_template = Image.new("RGBA",
                                                  (dict_dialogue_template['width'], dict_dialogue_template['height']))
                img_dialogue_template_tileset = Image.new("RGBA", (256, 32))
                draw_template = ImageDraw.Draw(img_dialogue_template)
                draw_template_tileset = ImageDraw.Draw(img_dialogue_template_tileset)
                palette_template = ['aliceblue', 'antiquewhite', 'aqua', 'aquamarine', 'azure', 'beige', 'bisque',
                                    'blanchedalmond', 'blue', 'blueviolet', 'brown', 'burlywood', 'cadetblue',
                                    'chartreuse', 'chocolate', 'coral', 'cornflowerblue', 'cornsilk', 'crimson',
                                    'cyan', 'darkblue', 'darkcyan', 'darkgoldenrod', 'darkgray', 'darkgreen',
                                    'darkkhaki', 'darkmagenta', 'darkolivegreen', 'darkorange', 'darkorchid', 'darkred']
                for i, obj in enumerate(dict_dialogue_template['OBJ']):
                    x = obj['x']
                    y = obj['y']
                    w = obj['width']
                    h = obj['height']
                    tx = 8 * obj['tile_x']
                    ty = 8 * obj['tile_y']
                    color = palette_template[i]
                    draw_template.rectangle([(x, y), (x + w, y + h)], fill=color)
                    draw_template_tileset.rectangle([(tx, ty), (tx + w, ty + h)], fill=color)
                ph_dialogue_template = ImageTk.PhotoImage(img_dialogue_template)
                l_dialogue_template.config(image=ph_dialogue_template)
                l_dialogue_template.image = ph_dialogue_template  # keep a reference!
                ph_dialogue_template_tileset = ImageTk.PhotoImage(img_dialogue_template_tileset)
                l_dialogue_template_tileset.config(image=ph_dialogue_template_tileset)
                l_dialogue_template_tileset.image = ph_dialogue_template_tileset  # keep a reference!

        def make_portrait_tileset():
            """
            Make tileset from dialogue portrait and template.
            :return: None
            """
            nonlocal img_tileset
            nonlocal img_dialogue
            nonlocal dict_dialogue_template
            if img_dialogue is None:
                tk.messagebox.showerror(title='Error', message='No dialogue portrait.')
            elif img_dialogue_template is None:
                tk.messagebox.showerror(title='Error', message='No portrait template.')
            else:
                img_tileset = Image.new("P", (256, 32))
                img_tileset.putpalette(img_dialogue.getpalette())
                for obj in dict_dialogue_template['OBJ']:
                    x = obj['x']
                    y = obj['y']
                    w = obj['width']
                    h = obj['height']
                    tx = 8 * obj['tile_x']
                    ty = 8 * obj['tile_y']
                    obj_image = img_dialogue.crop((x, y, x + w, y + h))
                    img_tileset.paste(obj_image, (tx, ty, tx + w, ty + h))
            ph_tileset = ImageTk.PhotoImage(img_tileset)
            l_tileset.config(image=ph_tileset)
            l_tileset.image = ph_tileset
            nonlocal img_palette
            img_palette = convert_palette_to_image(img_tileset, color_number=16, pixel_size=8)
            ph_palette = ImageTk.PhotoImage(img_palette)
            l_palette.config(image=ph_palette)
            l_palette.image = ph_palette  # keep a reference!

        def make_portrait_dialogue():
            """
            Make dialogue portrait from tileset and template.
            :return: None
            """
            nonlocal img_dialogue
            nonlocal img_tileset
            nonlocal dict_dialogue_template
            if img_tileset is None:
                tk.messagebox.showerror(title='Error', message='No portrait tileset.')
            elif img_dialogue_template is None:
                tk.messagebox.showerror(title='Error', message='No portrait template.')
            else:
                img_dialogue = Image.new("P", (dict_dialogue_template['width'], dict_dialogue_template['height']))
                img_dialogue.putpalette(img_tileset.getpalette())
                for obj in dict_dialogue_template['OBJ']:
                    x = obj['x']
                    y = obj['y']
                    w = obj['width']
                    h = obj['height']
                    tx = 8 * obj['tile_x']
                    ty = 8 * obj['tile_y']
                    obj_image = img_tileset.crop((tx, ty, tx + w, ty + h))
                    img_dialogue.paste(obj_image, (x, y, x + w, y + h))
            ph_dialogue = ImageTk.PhotoImage(img_dialogue)
            l_dialogue.config(image=ph_dialogue)
            l_dialogue.image = ph_dialogue

        def make_portrait_status_screen():
            """
            Make status screen portrait from dialogue portrait.
            :return: None
            """
            nonlocal img_dialogue
            nonlocal img_status_screen
            if img_dialogue is None:
                tk.messagebox.showerror(title='Error', message='No dialogue portrait.')
            else:
                window_portrait_status_screen = tk.Toplevel(window_portrait)
                window_portrait_status_screen.title('Status Screen Portrait')

                cv_status_screen = tk.Canvas(window_portrait_status_screen,
                                             width=img_dialogue.width, height=img_dialogue.height)
                cv_status_screen.focus_set()
                cv_status_screen.pack()
                ph_dialogue = ImageTk.PhotoImage(img_dialogue)
                cv_status_screen.create_image(0, 0, anchor='nw', image=ph_dialogue)
                cv_status_screen.image = ph_dialogue

                rect_status_screen = cv_status_screen.create_rectangle(0, 0, 80, 72, outline='red')

                def move_left(event):
                    """
                    Move one tile left.
                    :param event:
                    :return:
                    """
                    cv_status_screen.move(rect_status_screen, -8, 0)

                def move_right(event):
                    """
                    Move one tile right.
                    :param event:
                    :return:
                    """
                    cv_status_screen.move(rect_status_screen, 8, 0)

                def move_up(event):
                    """
                    Move one tile up.
                    :param event:
                    :return:
                    """
                    cv_status_screen.move(rect_status_screen, 0, -8)

                def move_down(event):
                    """
                    Move one tile down.
                    :param event:
                    :return:
                    """
                    cv_status_screen.move(rect_status_screen, 0, 8)

                cv_status_screen.bind(sequence="<Left>", func=move_left)
                cv_status_screen.bind(sequence="<Right>", func=move_right)
                cv_status_screen.bind(sequence="<Up>", func=move_up)
                cv_status_screen.bind(sequence="<Down>", func=move_down)

                def confirm_portrait_status_screen():
                    """
                    Convert the part in the red rectangle to status screen portrait.
                    :return:
                    """
                    nonlocal img_status_screen
                    nonlocal img_dialogue
                    img_status_screen = img_dialogue.crop(tuple(cv_status_screen.coords(rect_status_screen)))
                    hf_status_screen = ImageTk.PhotoImage(img_status_screen)
                    l_status_screen.config(image=hf_status_screen)
                    l_status_screen.image = hf_status_screen
                    window_portrait_status_screen.destroy()

                btn_ok = tk.Button(window_portrait_status_screen, text='OK', command=confirm_portrait_status_screen)
                btn_ok.pack()
            pass

        def make_portrait_mini():
            """
            Make mini portrait from dialogue portrait.
            :return:
            """
            nonlocal img_dialogue
            nonlocal img_mini
            if img_dialogue is None:
                tk.messagebox.showerror(title='Error', message='No dialogue portrait.')
            else:
                window_portrait_mini = tk.Toplevel(window_portrait)
                window_portrait_mini.title('Mini Portrait')

                cv_mini = tk.Canvas(window_portrait_mini, width=img_dialogue.width, height=img_dialogue.height)
                cv_mini.focus_set()
                cv_mini.pack()
                ph_dialogue = ImageTk.PhotoImage(img_dialogue)
                cv_mini.create_image(0, 0, anchor='nw', image=ph_dialogue)
                cv_mini.image = ph_dialogue

                rect_mini = cv_mini.create_rectangle(0, 0, 64, 64, outline='red')

                x = tk.IntVar()
                y = tk.IntVar()
                size = tk.IntVar()

                def mouse_press(event):
                    """
                    Handler to press the mouse.
                    :param event:
                    :return:
                    """
                    cv_mini.delete(rect_mini)
                    x.set(event.x)
                    y.set(event.y)

                def mouse_release(event):
                    """
                    Handler to release the mouse.
                    :param event:
                    :return:
                    """
                    x1 = x.get()
                    x2 = event.x
                    y1 = y.get()
                    y2 = event.y
                    if x1 > x2:
                        x1, x2 = x2, x1
                        x.set(x2)
                    if y1 > y2:
                        y1, y2 = y2, y1
                        y.set(y2)
                    if x2 - x1 > y2 - y1:
                        size.set(x2 - x1)
                        y2 = y1 + x2 - x1
                    else:
                        size.set(y2 - y1)
                        x2 = x1 + y2 - y1
                    rect_mini = cv_mini.create_rectangle(x1, y1, x2, y2, outline='red')

                cv_mini.bind(sequence="<ButtonPress-1>", func=mouse_press)
                cv_mini.bind(sequence="<ButtonRelease-1>", func=mouse_release)

                def confirm_portrait_mini():
                    """
                    Confirm and make mini portrait.
                    :return:
                    """
                    nonlocal img_dialogue
                    nonlocal img_mini
                    img_mini = img_dialogue.resize(size=(32, 32),
                                                   box=(x.get(), y.get(), x.get() + size.get(), y.get() + size.get()))
                    ph_mini = ImageTk.PhotoImage(img_mini)
                    l_mini.config(image=ph_mini)
                    l_mini.image = ph_mini
                    window_portrait_mini.destroy()

                btn_ok = tk.Button(window_portrait_mini, text='OK', command=confirm_portrait_mini)
                btn_ok.pack()

        def save_portrait_tileset():
            """
            Save portrait tileset to image.
            :return: None.
            """
            nonlocal img_tileset
            ask_and_save_image(img_tileset)

        def save_portrait_dialogue():
            """
            Save dialogue portrait to image.
            :return: None.
            """
            nonlocal img_dialogue
            ask_and_save_image(img_dialogue)

        def save_portrait_status_screen():
            """
            Save status screen portrait to image.
            :return: None.
            """
            nonlocal img_status_screen
            ask_and_save_image(img_status_screen)

        def save_portrait_mini():
            """
            Save mini portrait to image.
            :return: None.
            """
            nonlocal img_mini
            ask_and_save_image(img_mini)

        def save_eye_animation():
            """
            Save portrait eye animation to image.
            :return: None.
            """
            nonlocal img_eye_animation
            ask_and_save_image(img_eye_animation)

        def save_mouth_animation():
            """
            Save portrait mouth animation to image.
            :return: None.
            """
            nonlocal img_mouth_animation
            ask_and_save_image(img_mouth_animation)

        def save_dialogue_template():
            """
            Save dialogue portrait template to JSON or image
            :return: None
            """
            nonlocal dict_dialogue_template
            nonlocal img_dialogue_template
            nonlocal img_dialogue_template_tileset
            save_file = tk.filedialog.asksaveasfilename(title='Save Template',
                                                        filetypes=[('JSON', '*.json'), ('PNG', '*.png'),
                                                                   ('All Files', '*')])
            if os.path.splitext(save_file) in ['json', 'JSON']:
                if dict_dialogue_template is None:
                    tk.messagebox.showerror(title='Error', message='Nothing to save.')
                else:
                    with open(save_file, 'w') as f:
                        json.dump(dict_dialogue_template, f)
            else:
                if img_dialogue_template is None or img_dialogue_template_tileset is None:
                    tk.messagebox.showerror(title='Error', message='Nothing to save.')
                else:
                    img_dialogue_template_merge = Image.new("RGBA", (256, 32 + img_dialogue_template.height))
                    img_dialogue_template_merge.paste(img_dialogue_template, (0, 0))
                    img_dialogue_template_merge.paste(img_dialogue_template_tileset, (0, img_dialogue_template.height))
                    img_dialogue_template_merge.save(save_file)

        def save_c_source():
            """
            Save to C source file and header.
            :return:
            """
            if img_tileset is None:
                tk.messagebox.showerror(title='Error', message='No portrait tileset.')
            else:
                c_file = tk.filedialog.asksaveasfilename(title='Save to C Source',
                                                         filetypes=(("C source", "*.c"), ("all files", "*.*")))
                if c_file is not None:
                    header_file, _ = os.path.splitext(c_file)
                    _, name = os.path.split(header_file)
                    header_file += '.h'
                    with open(header_file, 'w') as f:
                        f.write('// Exported from' + os.path.basename(argv[0]) + '\n')
                        f.write('''
#pragma once
#include "FE7JPortrait.h"
#include "FE7JStructDef.h"                        
                        ''')
                        f.write('\nextern const PortraitNew portrait_%s;' % name)
                    with open(c_file, 'w') as f:
                        f.write('// Exported from' + os.path.basename(argv[0]) + '\n')
                        f.write('#include \"portrait_%s.h\"\n' % name)
                        palette = GBAImage.Palette(img_tileset.getpalette()[:3 * 16])
                        f.write('\nconst unsigned short portrait_%s_palette[] __attribute__((aligned(4)))= ' % name)
                        f.write(palette.tostring() + ';\n')
                        f.write('\nconst unsigned char portrait_%s_tileset[] __attribute__((aligned(4)))= ' % name)
                        tileset = GBAImage.TileSet(img_tileset)
                        f.write(tileset.tostring().replace('{', '{0x0,0x4,0x10,0x0, ', 1) + ';\n')
                        if dict_dialogue_template is not None:
                            f.write('\nconst unsigned short portrait_%s_oam_left[] __attribute__((aligned(4)))=' % name)
                            f.write('{%d, ' % len(dict_dialogue_template['OBJ']))
                            for obj in dict_dialogue_template['OBJ']:
                                w = obj['width']
                                h = obj['height']
                                x = obj['x']
                                x = x - w // 2 + offset_x.get()
                                y = obj['y']
                                y = y - h + 80 + offset_y.get()
                                tile_number = 32 * obj['tile_y'] + obj['tile_x']
                                obj_attribute = GBAImage.OBJAttribute(tile_number,
                                                                      width=w, height=h, x_coordinate=x, y_coordinate=y)
                                f.write(obj_attribute.tostring())
                            f.write('};\n')
                            f.write('\nconst unsigned short portrait_%s_oam_right[] __attribute__((aligned(4)))=' 
                                    % name)
                            f.write('{%d, ' % len(dict_dialogue_template['OBJ']))
                            for obj in dict_dialogue_template['OBJ']:
                                w = obj['width']
                                h = obj['height']
                                x = obj['x']
                                x = x - w // 2 + offset_x.get()
                                x = - (x + w)
                                y = obj['y']
                                y = y - h + 80 + offset_y.get()
                                tile_number = 32 * obj['tile_y'] + obj['tile_x']
                                obj_attribute = GBAImage.OBJAttribute(
                                    tile_number, width=w, height=h, x_coordinate=x, y_coordinate=y, horizontal_flip=1)
                                f.write(obj_attribute.tostring())
                            f.write('};\n')
                        if img_status_screen is not None:
                            map_status_sceen = GBAImage.BGMap(img_status_screen, img_tileset.getpalette(), tileset)
                            f.write('\nconst unsigned short portrait_%s_tsa[] __attribute__((aligned(4)))=' % name)
                            f.write(map_status_sceen.tostring_reverse() + ';\n')
                            f.write('\nconst unsigned char portrait_%s_status_screen_mask[9][10] =' % name)
                            f.write(map_status_sceen.tostring_mask() + ';\n')
                        nonlocal img_mini
                        if img_mini is not None:
                            img_mini = GBAImage.reset_palette(img_mini, img_tileset.getpalette())
                            f.write('\nconst unsigned char portrait_%s_mini[] __attribute__((aligned(4)))=' % name)
                            tileset_mini = GBAImage.TileSet(img_mini)
                            f.write(tileset_mini.tostring().replace('{', '{0x0,0x0,0x2,0x0, ', 1) + ';\n')
                        nonlocal img_eye_animation
                        if img_eye_animation is not None:
                            img_eye_animation = GBAImage.reset_palette(img_eye_animation, img_tileset.getpalette())
                            f.write('\nconst unsigned char portrait_%s_eye_animation[] __attribute__((aligned(4)))='
                                    % name)
                            tileset_eye_animation = GBAImage.TileSet(img_eye_animation)
                            f.write(tileset_eye_animation.tostring() + ';\n')
                        nonlocal img_mouth_animation
                        if img_mouth_animation is not None:
                            img_mouth_animation = GBAImage.reset_palette(img_mouth_animation, img_tileset.getpalette())
                            f.write('\nconst unsigned char portrait_%s_mouth_animation[] __attribute__((aligned(4)))='
                                    % name)
                            tileset_mouth_animation = GBAImage.TileSet(img_mouth_animation)
                            f.write(tileset_mouth_animation.tostring() + ';\n')
                        if dict_dialogue_template is not None:
                            f.write('\nconst PortraitOBJ portrait_%s_obj = {%d, %d, 0, 0, '
                                    '&portrait_%s_oam_left, &portrait_%s_oam_right};\n' %
                                    (name, dict_dialogue_template['width'],
                                     dict_dialogue_template['height'], name, name))
                        if img_status_screen is not None:
                            f.write('\nconst PortraitBG portrait_%s_bg = '
                                    '{&portrait_%s_tsa, &portrait_%s_status_screen_mask};\n' % (name, name, name))
                        # else:
                            # f.write('\nconst PortraitBG portrait_%s_bg = {NULL, NULL};\n' % name)
                        # todo calculate start tile number of eye automatically
                        if img_eye_animation is not None:
                            w = img_eye_animation.width
                            h = img_eye_animation.height // 3
                            img_eye_frame = img_mouth_animation.crop((0, h * 2, w, h * 3))
                            tileset_eye_frame = GBAImage.TileSet(img_eye_frame)                            
                            tile_number_eye = tileset.find_subset(tileset_eye_frame)
                            if tile_number_eye is None:
                                tk.messagebox.showwarning(title='Warning', 
                                                          message='Cannot locate eye frame automatically.')
                                f.write('\nconst EyeAnimation portrait_%s_eye = '
                                        '{%d, %d, %d, %d, 0, &portrait_%s_eye_animation};\n'
                                        % (name, w, h, wink_width.get(), wink_height.get(), name))
                            else:
                                f.write('\nconst EyeAnimation portrait_%s_eye = '
                                        '{%d, %d, %d, %d, %d, &portrait_%s_eye_animation};\n'
                                        % (name, w, h, wink_width.get(), wink_height.get(), tile_number_eye, name))
                        # else:
                            # f.write('\nconst EyeAnimation portrait_%s_eye = {0, 0, 0, 0, 0, NULL};\n' % name)
                        # todo calculate start tile number of mouth automatically
                        if img_mouth_animation is not None:
                            w = img_mouth_animation.width
                            h = img_mouth_animation.height // 6
                            img_mouth_frame = img_mouth_animation.crop((0, h * 5, w, h * 6))
                            tileset_mouth_frame = GBAImage.TileSet(img_mouth_frame)                            
                            tile_number_mouth = tileset.find_subset(tileset_mouth_frame)
                            if tile_number_mouth is None:
                                tk.messagebox.showwarning(title='Warning', 
                                                          message='Cannot locate mouth frame automatically.')
                                f.write('\nconst MouthAnimation portrait_%s_mouth = '
                                        '{%d, %d, 0, &portrait_%s_mouth_animation};\n' % (name, w, h, name))
                            else:
                                f.write('\nconst MouthAnimation portrait_%s_mouth = '
                                        '{%d, %d, %d, &portrait_%s_mouth_animation};\n'
                                        % (name, w, h, tile_number_mouth, name))
                        # else:
                            # f.write('\nconst MouthAnimation portrait_%s_mouth = {0, 0, 0, NULL};\n' % name)
                        f.write('\nconst char portrait_%s_name[] = \"%s\";\n' % (name, name))
                        f.write('\nconst PortraitExtra portrait_%s_extra_info = {' % name)
                        if dict_dialogue_template is None:
                            f.write('NULL, ')
                        else:
                            f.write('&portrait_%s_obj, ' % name)
                        if img_status_screen is None:
                            f.write('NULL, ')
                        else:
                            f.write('&portrait_%s_bg, ' % name)
                        if img_eye_animation is None:
                            f.write('NULL, ')
                        else:
                            f.write('&portrait_%s_eye, ' % name)
                        if img_mouth_animation is None:
                            f.write('NULL, ')
                        else:
                            f.write('&portrait_%s_mouth, ' % name)
                        f.write('&portrait_%s_name};\n' % name)
                        # f.write('&portrait_%s_bg, &portrait_%s_eye, &portrait_%s_mouth, &portrait_%s_name};\n'
                        #     % (name, name, name, name))
                        f.write('const PortraitNew portrait_%s = {&portrait_%s_tileset, ' % (name, name))
                        if img_mini is None:
                            f.write('NULL, ')
                        else:
                            f.write('&portrait_%s_mini, ' % name)
                        f.write('&portrait_%s_palette, ' % name)
                        f.write('&portrait_%s_extra_info, NULL, NULL, 1, -1, 0};\n' % name)
                        
        def make_portrait_wink():
            """
            Set wink width and height.
            :return: 
            """
            if img_eye_animation is None:
                tk.messagebox.showerror(title='Error', message='No eye animation.')
            else:
                window_wink = tk.Toplevel(window_portrait)
                window_wink.title('Wink')
                eye_width = img_eye_animation.width
                eye_height = img_eye_animation.height // 3
                cv_wink = tk.Canvas(window_wink, width=eye_width, height=eye_height, bd=0)
                cv_wink.pack()
                cv_wink.focus_set()
                ph_eye = ImageTk.PhotoImage(img_eye_animation.crop((0, 0, eye_width, eye_height)))
                cv_wink.create_image(0, 0, anchor='nw', image=ph_eye)
                # invisible label to keep reference to ph_eye
                l_eye = tk.Label(window_wink, image=ph_eye)
                # l_eye.pack()
                l_eye.image = ph_eye
                line_vertical = cv_wink.create_line(eye_width - wink_width.get(), 0,
                                               eye_width - wink_width.get(), eye_height, fill='red')
                line_horizontal = cv_wink.create_line(
                    0, eye_height - wink_height.get(), eye_width, eye_height - wink_height.get(),
                    fill='red')

                def set_wink_area():
                    """
                    Set wink width and height.
                    :return:
                    """
                    wink_width.set(eye_width - cv_wink.coords(line_vertical)[0])
                    wink_height.set(eye_height - cv_wink.coords(line_horizontal)[1])
                    window_wink.destroy()

                def move_left(event):
                    cv_wink.move(line_vertical, -8, 0)

                def move_right(event):
                    cv_wink.move(line_vertical, 8, 0)

                def move_up(event):
                    cv_wink.move(line_horizontal, 0, -8)

                def move_down(event):
                    cv_wink.move(line_horizontal, 0, 8)

                cv_wink.bind(sequence='<Left>', func=move_left)
                cv_wink.bind(sequence='<Right>', func=move_right)
                cv_wink.bind(sequence='<Up>', func=move_up)
                cv_wink.bind(sequence='<Down>', func=move_down)

                btn_ok = tk.Button(window_wink, text='OK', command=set_wink_area)
                btn_ok.pack()

        menu_bar_portrait = tk.Menu(window_portrait)
        menu_load = tk.Menu(menu_bar_portrait, tearoff=0)
        menu_make = tk.Menu(menu_bar_portrait, tearoff=0)
        menu_save = tk.Menu(menu_bar_portrait, tearoff=0)
        menu_bar_portrait.add_cascade(label='Load', menu=menu_load)
        menu_bar_portrait.add_cascade(label='Make', menu=menu_make)
        menu_bar_portrait.add_cascade(label='Save', menu=menu_save)
        menu_load.add_command(label='Tileset', command=load_portrait_tileset)
        menu_load.add_command(label='Dialogue', command=load_portrait_dialogue)
        menu_load.add_command(label='Template', command=load_dialogue_template)
        menu_load.add_command(label='Status Screen', command=load_portrait_status_screen)
        menu_load.add_command(label='Mini', command=load_portrait_mini)
        menu_load.add_command(label='Eye Animation', command=load_eye_animation)
        menu_load.add_command(label='Mouth Animation', command=load_mouth_animation)
        menu_make.add_command(label='Tileset', command=make_portrait_tileset)
        menu_make.add_command(label='Dialogue', command=make_portrait_dialogue)
        menu_make.add_command(label='Status Screen', command=make_portrait_status_screen)
        menu_make.add_command(label='Mini', command=make_portrait_mini)
        menu_make.add_command(label='Wink', command=make_portrait_wink)
        menu_save.add_command(label='Tileset', command=save_portrait_tileset)
        menu_save.add_command(label='Dialogue', command=save_portrait_dialogue)
        menu_save.add_command(label='Template', command=save_dialogue_template)
        menu_save.add_command(label='Status Screen', command=save_portrait_status_screen)
        menu_save.add_command(label='Mini', command=save_portrait_mini)
        menu_save.add_command(label='Eye Animation', command=save_eye_animation)
        menu_save.add_command(label='Mouth Animation', command=save_mouth_animation)
        menu_save.add_command(label='C Source', command=save_c_source)

        window_portrait.config(menu=menu_bar_portrait)

        l_palette = tk.Label(window_portrait, text='Palette', compound='bottom')
        l_palette.pack()

        l_tileset = tk.Label(window_portrait, text='Tileset', compound='bottom')
        l_tileset.pack()

        l_dialogue = tk.Label(window_portrait, text='Dialogue', compound='bottom')
        l_dialogue.pack()

        l_dialogue_template_tileset = tk.Label(window_portrait, text='Template', compound='bottom')
        l_dialogue_template_tileset.pack()

        l_dialogue_template = tk.Label(window_portrait, compound='bottom')
        l_dialogue_template.pack()

        l_status_screen = tk.Label(window_portrait, text='Status Screen', compound='bottom')
        l_status_screen.pack()

        l_mini = tk.Label(window_portrait, text='Mini', compound='bottom')
        l_mini.pack()

        l_eye_animation = tk.Label(window_portrait, text='Eye Animation', compound='bottom')
        l_eye_animation.pack()

        l_mouth_animation = tk.Label(window_portrait, text='Mouth Animation', compound='bottom')
        l_mouth_animation.pack()

    def show_image_window():
        """
        Open image tool.
        :return: None
        """
        window_image = tk.Toplevel(window)
        window_image.title('Image')

        palette = [0] * 3 * 256
        img_init: Image = None
        img_palette: Image = None
        img_edit: Image = None
        img_last: Image = None

        size = tk.StringVar(window_image, name='Image Size')
        tile_number = tk.StringVar(window_image, name='Tile Number')
        major_tile_number = tk.StringVar(window_image, name='Important Tile Number')

        def count_major_tile_number(threshold):
            """
            Count tiles with more than threshold pixels.
            :param threshold: pixel number
            :return:None
            """
            nonlocal img_edit
            if type(threshold) is not int:
                threshold = int(threshold)
            tileset = GBAImage.TileSet(img_edit)
            major_tile_number.set("%d tiles have over %d pixels." %
                                  (tileset.get_major_tile_number(threshold), threshold))

        def count_tile_number():
            """
            Count tiles.
            :return: None.
            """
            nonlocal img_edit
            tileset = GBAImage.TileSet(img_edit)
            tile_number.set("%d tiles." % tileset.get_non_blank_tile_number())

        def refresh():
            """
            Refresh image and palette.
            :return: None.
            """
            nonlocal img_edit
            nonlocal img_palette
            nonlocal palette
            if img_edit is not None:
                palette = img_edit.getpalette()
                ph_edit = ImageTk.PhotoImage(img_edit)
                l_image.config(image=ph_edit)
                l_image.image = ph_edit  # keep a reference!
                img_palette = convert_palette_to_image(img_edit)
                ph_palette = ImageTk.PhotoImage(img_palette)
                l_palette.config(image=ph_palette)
                l_palette.image = ph_palette  # keep a reference!
                size.set('Size: %d x %d' % (img_edit.width, img_edit.height))
                count_tile_number()
                count_major_tile_number(scale_threshold.get())

        def undo():
            """
            Undo.
            :return: None
            """
            nonlocal img_last
            nonlocal img_edit
            if img_last is not None:
                img_last, img_edit = img_edit, img_last
            refresh()

        def undo_all():
            """
            Undo.
            :return: None
            """
            nonlocal img_edit
            nonlocal img_init
            if img_init is not None:
                img_edit = img_init
            refresh()

        def load_image():
            """
            Load image.
            :return: Image object
            """
            nonlocal img_init
            nonlocal img_edit
            nonlocal img_last
            nonlocal palette
            img_init = ask_and_open_image()
            if img_init.mode != "P":
                img_init = img_init.convert("P", palette=Image.ADAPTIVE, colors=256)
            if img_init is not None:
                ph_load = ImageTk.PhotoImage(img_init)
                l_image.config(image=ph_load)
                l_image.image = ph_load  # keep a reference!
                nonlocal img_palette
                img_palette = convert_palette_to_image(img_init)
                ph_palette = ImageTk.PhotoImage(img_palette)
                l_palette.config(image=ph_palette)
                l_palette.image = ph_palette  # keep a reference!
            img_last = img_init.copy()
            img_edit = img_init.copy()
            size.set('Size: %d x %d' % (img_edit.width, img_edit.height))
            # tileset = GBAImage.TileSet(img_edit)
            # tile_number.set("%d Tiles" % tileset.get_non_blank_tile_number())
            count_tile_number()
            count_major_tile_number(scale_threshold.get())
            palette = img_edit.getpalette()

        def load_palette():
            """
            Load palette and requantize image.
            :return: None.
            """
            nonlocal palette
            nonlocal img_edit
            nonlocal img_last
            palette = ask_and_open_palette()
            if palette is not None:
                img_palette = show_palette(palette)
                ph_palette = ImageTk.PhotoImage(img_palette)
                l_palette.config(image=ph_palette)
                l_palette.image = ph_palette
                # requantize the image
                if img_edit is not None:
                    img_last = img_edit
                    img_edit = img_edit.convert("RGB")
                    img_edit = img_edit.quantize(palette=img_palette)
                    img_edit = GBAImage.reset_palette(img_edit, palette)

        def save_image():
            """
            Save image.
            :return: None.
            """
            nonlocal img_edit
            ask_and_save_image(img_edit)

        def edit_palette():
            """
            Edit palette.
            :return:
            """
            window_palette = tk.Toplevel(window_image)
            window_palette.title('Palette')

            '''def slider_update(something):
                red = round(red_slider.get() * 255 / 31)
                green = round(green_slider.get() * 255 / 31)
                blue = round(blue_slider.get() * 255 / 31)
                colour = "#%02X%02X%02X" % (red, green, blue)
                canvas.config(bg=colour)
                hex_text.delete(0, tk.END)
                hex_text.insert(0, colour)

            def color_set():
                colour = hex_text.get()
                canvas.config(bg=colour)
                red_slider.set(round(int(colour[1:3], 16) * 31 / 255))
                green_slider.set(round(int(colour[3:5], 16) * 31 / 255))
                blue_slider.set(round(int(colour[5:7], 16) * 31 / 255))

            color_size = 16
            canvas = tk.Canvas(window_palette, width=color_size * 16, height=color_size * 16)
            for i in range(16):
                for j in range(16):
                    canvas.create_rectangle(color_size * j, color_size * i, color_size * (j + 1), color_size * (i + 1),
                                            fill="#%02X%02X%02X"
                                                 % (palette[3 * (16 * i + j)], palette[3 * (16 * i + j) + 1],
                                                    palette[3 * (16 * i + j) + 2]))
            red_slider = tk.Scale(window_palette, from_=0, to=31, command=slider_update)
            green_slider = tk.Scale(window_palette, from_=0, to=31, command=slider_update)
            blue_slider = tk.Scale(window_palette, from_=0, to=31, command=slider_update)
            hex_text = tk.Entry(window_palette, text="#000000")
            button = tk.Button(window_palette, text="Set", command=color_set)
            l_red = tk.Label(window_palette, text='R')
            l_green = tk.Label(window_palette, text='G')
            l_blue = tk.Label(window_palette, text='B')

            l_red.grid(row=1, column=1)
            l_green.grid(row=1, column=2)
            l_blue.grid(row=1, column=3)
            red_slider.grid(row=2, column=1)
            green_slider.grid(row=2, column=2)
            blue_slider.grid(row=2, column=3)
            canvas.grid(row=3, column=1, columnspan=3)
            hex_text.grid(row=4, column=1, columnspan=3)
            button.grid(row=5, column=1, columnspan=3)'''

        def set_transparent_color_index():
            """
            Resort palette to make transparent color in the first slot of each row.
            :return: None
            """
            window_transparent_index = tk.Toplevel(window_image)
            window_transparent_index.title('Index')

            color_size = 32

            def show_color():
                """
                Show color from index in palette.
                :return: None.
                """
                nonlocal palette
                if int(e_index_row.get()) in range(16) and int(e_index_column.get()) in range(16):
                    color_index = 16 * int(e_index_row.get()) + int(e_index_column.get())
                    r = palette[3 * color_index]
                    g = palette[3 * color_index + 1]
                    b = palette[3 * color_index + 2]
                    canvas.config(bg='#%02X%02X%02X' % (r, g, b))

            def callback(e):
                """
                Refresh shown color.
                :param e: useless.
                :return: None.
                """
                show_color()

            def sort_palette():
                """
                Sort palette to make transparent color in the 1st slot of each row.
                :return: None
                """
                nonlocal palette
                nonlocal img_last
                nonlocal img_edit
                palette = img_edit.getpalette()
                transparent_index = 16 * int(e_index_row.get()) + int(e_index_column.get())
                '''r = palette[3 * transparent_index]
                g = palette[3 * transparent_index + 1]
                b = palette[3 * transparent_index + 2]
                for i in range(3):
                    palette.pop(3 * transparent_index)
                for i in range(16):
                    palette.insert(3 * i, r)
                    palette.insert(3 * i + 1, g)
                    palette.insert(3 * i + 2, b)'''
                dest_map = list(range(256))
                dest_map.pop(transparent_index)
                # for i in range(16):
                #   dest_map.insert(16 * i, transparent_index)
                dest_map.insert(0, transparent_index)
                for i in range(1, 16):
                    dest_map.insert(16 * i, 255)
                img_last = img_edit
                img_edit = img_edit.remap_palette(dest_map[:256])
                palette = img_edit.getpalette()
                for i in range(1, 16):
                    palette[16 * 3 * i] = palette[0]
                    palette[16 * 3 * i + 1] = palette[1]
                    palette[16 * 3 * i + 2] = palette[2]
                img_edit.putpalette(palette)
                refresh()
                window_transparent_index.destroy()

            index_row = tk.StringVar(window_transparent_index)
            index_row.set('0')
            l_index_row = tk.Label(window_transparent_index, text='row')
            e_index_row = tk.Entry(window_transparent_index, textvariable=index_row, width=2)
            e_index_row.bind('<Return>', (lambda _: callback(e_index_row)))
            l_index_row.grid(row=1, column=1)
            e_index_row.grid(row=1, column=2)

            index_column = tk.StringVar(window_transparent_index)
            index_column.set('0')
            l_index_column = tk.Label(window_transparent_index, text='column')
            e_index_column = tk.Entry(window_transparent_index, textvariable=index_column, width=2)
            e_index_column.bind('<Return>', (lambda _: callback(e_index_column)))
            l_index_column.grid(row=2, column=1)
            e_index_column.grid(row=2, column=2)

            canvas = tk.Canvas(window_transparent_index, width=color_size, height=color_size)
            canvas.grid(row=1, column=3)
            show_color()

            btn_sort_palette = tk.Button(window_transparent_index, text='Set', command=sort_palette)
            btn_sort_palette.grid(row=3, column=2)

        def change_transparent_color():
            """
            Change tranparent color.
            :return: None
            """
            nonlocal palette
            nonlocal img_last
            nonlocal img_edit
            palette = img_edit.getpalette()
            color = tk.colorchooser.askcolor()
            if color is not None:
                for i in range(16):
                    palette[16 * 3 * i] = math.floor(color[0][0])
                    palette[16 * 3 * i + 1] = math.floor(color[0][1])
                    palette[16 * 3 * i + 2] = math.floor(color[0][2])
            img_last = img_edit
            img_edit.putpalette(palette)
            refresh()

        def slim():
            """
            Slim the image by removing blank border.
            :return:
            """
            nonlocal img_last
            nonlocal img_edit
            box = img_edit.getbbox()
            if box is None:
                tk.messagebox.showwarning("The image is empty.")
            else:
                img_last = img_edit
                img_edit = img_edit.crop(box)
            refresh()

        def scale(scaling):
            """
            Scale the image.
            :param scaling:
            :return: None.
            """
            if type(scaling) is str:
                scaling = float(scaling)
            nonlocal img_last
            nonlocal img_edit
            nonlocal img_init
            width = round(img_init.width * scaling)
            height = round(img_init.height * scaling)
            img_last = img_edit
            img_edit = img_init.resize((width, height))
            refresh()

        def requantize():
            """
            Reduce the color number.
            :return: None
            """
            nonlocal img_last
            nonlocal img_edit
            window_requantize = tk.Toplevel(window_image)

            img_reference = None

            def load_palette():
                """
                Load palette from image.
                :return: None.
                """
                nonlocal img_reference
                img_reference = ask_and_open_image()
                if img_reference is not None:
                    img_palette_ref = convert_palette_to_image(img_reference)
                    ph_palette_ref = ImageTk.PhotoImage(img_palette_ref)
                    l_palette_ref.config(image=ph_palette_ref)
                    l_palette_ref.image = ph_palette_ref

            btn_load_palette = tk.Button(window_requantize, text='Load palette from image', command=load_palette)
            btn_load_palette.pack()
            l_palette_ref = tk.Label(window_requantize)
            l_palette_ref.pack()
            l_color_number = tk.Label(window_requantize, text='Color Number')
            l_color_number.pack()
            e_color_number = tk.Entry(window_requantize)
            e_color_number.pack()
            e_color_number.insert('end', '16')
            l_kmeans = tk.Label(window_requantize, text='Kmeans')
            l_kmeans.pack()
            e_kmeans = tk.Entry(window_requantize)
            e_kmeans.pack()
            e_kmeans.insert('end', '0')
            l_method = tk.Label(window_requantize, text='Method')
            l_method.pack()

            method = tk.IntVar()
            method.set(0)

            dither = tk.IntVar()
            dither.set(1)

            img_temp: Image = None

            def quantize_and_preview():
                """
                Quantize image for preview.
                :return: None
                """
                nonlocal img_temp
                nonlocal img_edit
                img_temp = img_edit.convert("RGB", palette=Image.ADAPTIVE)
                img_temp = img_temp.quantize(colors=int(e_color_number.get()), method=method.get(),
                                             kmeans=int(e_kmeans.get()), palette=img_reference, dither=dither.get())
                if img_temp is not None:
                    ph_preview = ImageTk.PhotoImage(img_temp)
                    l_preview.config(image=ph_preview)
                    l_preview.image = ph_preview

            def requantize_and_save():
                """
                Quantize image and save.
                :return:
                """
                nonlocal img_temp
                nonlocal img_edit
                nonlocal img_last
                img_temp = img_edit.convert("RGB", palette=Image.ADAPTIVE)
                img_temp = img_temp.quantize(colors=int(e_color_number.get()), method=method.get(),
                                             kmeans=int(e_kmeans.get()), palette=img_reference, dither=dither.get())
                if img_temp is not None:
                    img_last = img_edit
                    img_edit = img_temp
                    refresh()
                    window_requantize.destroy()

            r1_method = tk.Radiobutton(window_requantize, text='median cut', variable=method, value=0,
                                       command=quantize_and_preview)
            r1_method.pack()
            r2_method = tk.Radiobutton(window_requantize, text='maximum coverage ', variable=method, value=1,
                                       command=quantize_and_preview)
            r2_method.pack()
            r3_method = tk.Radiobutton(window_requantize, text='fast octree', variable=method, value=2,
                                       command=quantize_and_preview)
            r3_method.pack()
            # dependency required by this method was not enabled at compile time
            # r4_method = tk.Radiobutton(window_requantize, text='libimagequant', variable=method, value=3,
            #                           command=quantize_and_preview)
            # r4_method.pack()

            c_dither = tk.Checkbutton(window_requantize, text='FLOYDSTEINBERG', variable=dither, onvalue=1, offvalue=0)
            c_dither.pack()

            l_preview = tk.Label(window_requantize, text='Preview', compound='bottom')
            l_preview.pack()
            if img_temp is not None:
                ph_preview = ImageTk.PhotoImage(img_temp)
                l_preview.config(image=ph_preview)
                l_preview.image = ph_preview

            btn_ok = tk.Button(window_requantize, text='OK', command=requantize_and_save)
            btn_ok.pack()

            pass

        menu_bar_image = tk.Menu(window_image)
        menu_load = tk.Menu(menu_bar_image, tearoff=0)
        menu_edit = tk.Menu(menu_bar_image, tearoff=0)
        menu_save = tk.Menu(menu_bar_image, tearoff=0)
        menu_bar_image.add_cascade(label='Load', menu=menu_load)
        menu_bar_image.add_cascade(label='Edit', menu=menu_edit)
        menu_bar_image.add_cascade(label='Save', menu=menu_save)
        menu_load.add_command(label='Image', command=load_image)
        menu_load.add_command(label='Palette', command=load_palette)
        menu_save.add_command(label='Image', command=save_image)
        submenu_transparent = tk.Menu(menu_edit, tearoff=0)
        menu_edit.add_cascade(label='Tranparent Color', menu=submenu_transparent, underline=0)
        submenu_transparent.add_command(label="Index", command=set_transparent_color_index)
        submenu_transparent.add_command(label="Change", command=change_transparent_color)
        menu_edit.add_command(label="Requantize", command=requantize)
        menu_edit.add_command(label="Slim", command=slim)
        menu_edit.add_separator()
        menu_edit.add_command(label="Undo", command=undo)
        menu_edit.add_command(label="Undo All", command=undo_all)

        window_image.config(menu=menu_bar_image)

        l_palette = tk.Label(window_image, text='Palette', compound='bottom')
        l_palette.pack()

        l_image = tk.Label(window_image, text='Image', compound='bottom')
        l_image.pack()

        l_size = tk.Label(window_image, textvariable=size)
        l_size.pack()

        l_tile_number = tk.Label(window_image, textvariable=tile_number)
        l_tile_number.pack()

        l_major_tile_number = tk.Label(window_image, textvariable=major_tile_number)
        l_major_tile_number.pack()

        scale_threshold = tk.Scale(window_image, label='Threshold', from_=0, to=64, orient=tk.HORIZONTAL, length=320,
                                   showvalue=1, tickinterval=8, resolution=1, command=count_major_tile_number)
        scale_threshold.pack()

        scale_scaling = tk.Scale(window_image, label='Scaling', from_=0.1, to=1, orient=tk.HORIZONTAL, length=320,
                                 showvalue=1, tickinterval=0.1, resolution=0.01, command=scale)
        scale_scaling.pack()

    def show_battle_animation_window():
        """
        Open battle animation tool.
        :return: None
        """
        window_battle_animation = tk.Toplevel(window)
        window_battle_animation.title('Battle Animation')

    # function buttons
    btn_portrait = tk.Button(window, text='Portrait', command=show_portrait_window)
    btn_portrait.pack(side='left', padx=10, pady=5)
    btn_battle_animation = tk.Button(window, text='Battle Animation', command=show_battle_animation_window)
    btn_battle_animation.pack(side='left', padx=10, pady=5)
    btn_image = tk.Button(window, text='Image', command=show_image_window)
    btn_image.pack(side='left', padx=10, pady=5)

    # main window message loop
    window.mainloop()


if __name__ == "__main__":
    if len(sys.argv) == 1:
        show_main_window(sys.argv)
    else:
        try:
            opts, args = getopt.getopt(sys.argv[1:], "", ["palette="])
        except getopt.GetoptError:
            print("Commandline is for debugging. Use GUI instead.")
            sys.exit(-1)
        pass
        for opt, arg in opts:
            if opt in ["--palette"]:
                palette_file = arg
                palette = read_palette(palette_file)
                print(palette)
