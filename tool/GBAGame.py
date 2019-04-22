# GBA Game Utility
# by laqieer
# 2019/4/22

def get_game_code(f_rom):
    """
    0ACh - Game Code, Uppercase Ascii, 4 characters
    This is the same code as the AGB-UTTD code which is printed on the package and sticker on (commercial) cartridges (excluding the leading "AGB-" part).
      U  Unique Code          (usually "A" or "B" or special meaning)
      TT Short Title          (eg. "PM" for Pac Man)
      D  Destination/Language (usually "J" or "E" or "P" or specific language)
    """
    f_rom.seek(0xAC)
    return f_rom.read(4).decode()

def read_pointer(f_rom, offset=None):
    if offset is not None:
        f_rom.seek(offset)
    s = f_rom.read(4)
    ptr = int.from_bytes(s, byteorder='little', signed=False)
    return ptr

def is_valid_pointer(ptr, type='ROM'):
    if type in ('ROM', 'rom'):
        return ptr >= 0x8000000 and ptr <= 0x9FFFFFF
    else:
        return True

def convert_pointer_to_offset(ptr):
    if is_valid_pointer(ptr, type='ROM'):
        return ptr - 0x8000000
    else:
        return None

def read_rom_offset(f_rom, offset=None):
    ptr = read_pointer(f_rom, offset)
    return convert_pointer_to_offset(ptr)

def read_data(f_rom, offset, length):
    f_rom.seek(offset)
    return f_rom.read(length)

def get_lz77_src_data_length(f_rom, offset):
    f_rom.seek(offset + 1)
    return int.from_bytes(f_rom.read(3), byteorder='little', signed=False)

def output_c(data: bytes, name):
    return '\nconst unsigned char %s[] __attribute__((aligned(4)))= {%s};\n' % (name, ','.join(['0x%X' % i for i in list(data)]))

def output_asm(data: bytes, name):
    return '\n\t.align 2\n%s:\n\t.byte %s\n' % (name, ','.join(['0x%X' % i for i in list(data)]))
