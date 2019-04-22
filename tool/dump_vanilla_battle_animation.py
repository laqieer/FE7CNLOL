# A simple tool to dump vanilla battle animation to a single assembly source file
# by laqieer
# 2019/4/22

import os, sys, getopt
from GBAGame import *

battle_animation_table = {'AFEJ': 0x6A0008, 'AE7J': 0xE00008, 'AE7E': 0xE00008, 'BE8J': 0xC00008, 'BE8E': 0xC00008}

def get_battle_animation_table(f_rom):
    game_code = get_game_code(f_rom)
    if game_code not in battle_animation_table:
        print('Unknown game.\n')
        sys.exit(-1)
    return battle_animation_table[game_code]

def get_battle_animation(f_rom, index):
    return get_battle_animation_table(f_rom) + 32 * index

def write_head(f_asm, name):
    f_asm.write('@This file is dumped by dump_vanilla_battle_animation.py automatically. Don\'t edit it.\n')
    f_asm.write('\t.global %s_animation\n' % name)
    f_asm.write('\t.section .rodata\n')

def dump_battle_animation(f_rom, f_asm, index, name):
    base_addr = get_battle_animation(f_rom, index)
    f_rom.seek(base_addr)
    abbr = str(f_rom.read(12))[2:-1]
    modes_addr = read_rom_offset(f_rom, base_addr + 12)
    script_addr = read_rom_offset(f_rom, base_addr + 16)
    oam_r_addr = read_rom_offset(f_rom, base_addr + 20)
    oam_l_addr = read_rom_offset(f_rom, base_addr + 24)
    palette_addr = read_rom_offset(f_rom, base_addr + 28)
    palette_addr_len = get_lz77_src_data_length(f_rom, palette_addr)
    palette_data = read_data(f_rom, palette_addr, palette_addr_len)
    f_asm.write(output_asm(palette_data, name + '_pal'))
    oam_r_addr_len = get_lz77_src_data_length(f_rom, oam_r_addr)
    oam_r_data = read_data(f_rom, oam_r_addr, oam_r_addr_len)
    f_asm.write(output_asm(oam_r_data, name + '_oam_r'))
    oam_l_addr_len = get_lz77_src_data_length(f_rom, oam_l_addr)
    oam_l_data = read_data(f_rom, oam_l_addr, oam_l_addr_len)
    f_asm.write(output_asm(oam_l_data, name + '_oam_l'))
    # todo handle script
    f_asm.write('\n\t.align 2\n')
    f_asm.write(name + '_script:\n')
    modes_data = read_data(f_rom, modes_addr, 96)
    f_asm.write(output_asm(modes_data, name + '_modes'))
    f_asm.write('\n\t.align 2\n')
    f_asm.write(name + '_animation:\n')
    f_asm.write('\t.string "%s"\n' % abbr)
    f_asm.write('\t.word %s_modes\n' % name)
    f_asm.write('\t.word %s_script\n' % name)
    f_asm.write('\t.word %s_oam_r\n' % name)
    f_asm.write('\t.word %s_oam_l\n' % name)
    f_asm.write('\t.word %s_pal\n' % name)

def main(argv):
    rom_file = None
    index = 0
    out_file = None
    name = ''
    try:
        opts, args = getopt.getopt(argv, 'r:i:o:n:', ['rom=', 'index=', 'out=', 'name='])
    except getopt.GetoptError:
        print('-r/--rom <rom_file> -o/--out <output_file>',
              '-i/--index <animation_id> -n/--name <base_name>\n')
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-r', '--rom'):
            rom_file = arg
        elif opt in ('-i', '--index'):
            if arg in ('all', 'ALL'):
                index = 'all'
            else:
                index = int(arg, 16)
        elif opt in ('-o', '--out'):
            out_file = arg
        elif opt in ('-n', '--name'):
            name = arg
    if out_file is None:
        out_file = 'banim_%s.s' % name
    with open(rom_file, 'rb') as f_rom, open(out_file, 'w') as f_asm:
        write_head(f_asm, name)
        dump_battle_animation(f_rom, f_asm, index, name)

if __name__ == "__main__":
    main(sys.argv[1:])
