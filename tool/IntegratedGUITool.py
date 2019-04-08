# Integrated GUI Tool. Not a ROM editor. 集成图形界面工具, 只输出C/汇编源文件, 不是修改器, 不修改游戏ROM.
# by laqieer
# 2019/4/8

import tkinter as tk
import tkinter.messagebox
import sys


def show_about_info():
    """
    Show about information.
    :return: nothing
    """
    tk.messagebox.showinfo(title='about', message='''
    Integrated GUI Tool only for FE7CNLOL Project.
    This program is to generate C/Assembly source files.
    This is not a ROM Editor.
    Licensed under GPLv3.
    Author: https://github.com/laqieer.
    ''')


def show_portrait_window():
    """
    Open portrait tool.
    :return: nothing
    """
    pass


def show_battle_animation_window():
    """
    Open battle animation tool.
    :return: nothing
    """
    pass


def show_main_window(argv):
    """
    Show main window.
    :param argv: commandline arguments
    :return: process finished with exit code
    """
    window = tk.Tk()
    window.title("Integrated GUI Tool")

    # welcome image
    cv = tk.Canvas(window, width=445, height=127)
    cv.pack()
    img_welcome_file = tk.PhotoImage(file="welcome.gif")
    img = cv.create_image(0, 0, anchor='nw', image=img_welcome_file)

    # menubar
    menubar = tk.Menu(window)
    menu_file = tk.Menu(menubar, tearoff=0)
    menubar.add_cascade(label='File', menu=menu_file)
    menu_file.add_command(label='About', command=show_about_info)
    menu_file.add_command(label='Quit', command=window.quit)
    window.config(menu=menubar)

    # function buttons
    btn_portrait = tk.Button(window, text='Portrait', command=show_portrait_window)
    btn_portrait.pack(side='left', padx=10, pady=5)
    btn_battle_animation = tk.Button(window, text='Battle Animation', command=show_battle_animation_window)
    btn_battle_animation.pack(side='left', padx=10, pady=5)

    # main window message loop
    window.mainloop()


if __name__ == "__main__":
    show_main_window(sys.argv)
