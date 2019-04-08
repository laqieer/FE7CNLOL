# Integrated GUI Tool. Not a ROM editor. 集成图形界面工具, 只输出C/汇编源文件, 不是修改器, 不修改游戏ROM.
# by laqieer
# 2019/4/8

import sys
import os
import json
import tkinter as tk
import tkinter.messagebox
from tkinter import filedialog
from PIL import Image, ImageTk, ImageDraw
import math


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


def ask_and_open_image(width=0, height=0, color_number=0, palette: Image=None):
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


def show_main_window():
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

        img_palette = None
        img_dialogue = None
        img_tileset = None
        img_status_screen = None
        img_mini = None
        img_eye_animation = None
        img_mouth_animation = None
        dict_dialogue_template = None
        img_dialogue_template = None
        img_dialogue_template_tileset = None

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
        menu_save.add_command(label='Tileset', command=save_portrait_tileset)
        menu_save.add_command(label='Dialogue', command=save_portrait_dialogue)
        menu_save.add_command(label='Template', command=save_dialogue_template)
        menu_save.add_command(label='Status Screen', command=save_portrait_status_screen)
        menu_save.add_command(label='Mini', command=save_portrait_mini)
        menu_save.add_command(label='Eye Animation', command=save_eye_animation)
        menu_save.add_command(label='Mouth Animation', command=save_mouth_animation)
        
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
        show_main_window()
