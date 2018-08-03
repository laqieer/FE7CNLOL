# by laqieer
# 2017/1/26

# ��ӹ���·��
# PATH	:=	$(DEVKITARM)/bin;$(PATH)
# error: make: make: Command not found
# I was inadvertently overriding my PATH so none of my commands were being found.

# ָ������Ŀ¼���ļ�

# ���ɵ�Ŀ���ļ��Թ���Ŀ¼������
TARGET	:=	$(shell basename $(CURDIR))
# �����ļ���Ŀ¼
BUILD	:=	build
# Դ�ļ���Ŀ¼
SOURCES	:=	src sound
# ���������ݵ�Ŀ¼
DATA	:=	data
# ͷ�ļ�
HEADERS	:=	include
# Create a gfx library variable
GFXLIBS     ?= libgfx.a
# ������·��
LIBRARIES	:=	lib/libfe lib/libmy lib/libagb lib/libtonc
# ���ӵĺ�����
LIBS        := -nostdlib -lgfx -ltonc
# LIBS        := -lgfx -
# makefile����(�޸���makefile��Ӧ����make clean������make)
# MAKEFILES	:= makefile gbamake

# ���ڶ���Ŀ¼
ifeq (0,$(MAKELEVEL))

# ���²㴫�ݱ���
export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/$(BUILD)
# ���ӽű�
export LDS	=	$(OUTPUT).ld					

# Ҫ������ļ������嵥

CFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S))) \
			$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))

export OFILES	:=	$(CFILES:.c=.o) $(subst .s,.o,$(SFILES:.S=.o)) $(BINFILES:.bin=.o)
# export OFILES	:=	$(CFILES:.c=.o) $(subst .s,.o,$(SFILES:.S=.o))
# export LIBPATHS	:=	$(foreach dir,$(LIBRARIES),-L$(dir)/lib)
export LIBPATHS	:=	$(foreach dir,$(LIBRARIES),-L../$(dir)/lib) -L$(CURDIR)
export INCLUDES	:=	$(foreach dir,$(HEADERS),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBRARIES),-I$(CURDIR)/$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

# αĿ��
.PHONY: $(BUILD) clean

# �л���buildĿ¼��make
$(BUILD):
	[ -d $@ ] || mkdir -p $@
	$(MAKE) --no-print-directory -f $(CURDIR)/gfxmake
	$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

all	: $(BUILD)

clean:
	rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba
	
# ���Ѿ����뵽buildĿ¼
else

include ../gbamake

# ������
DEPENDS	:=	$(OFILES:.o=.d)

# �����ı���Ŀ��
$(OUTPUT).gba: $(OUTPUT).elf

$(OUTPUT).elf: $(OFILES) $(LDS) $(GFXLIBS)

# ͨ�ù���

%.a:
	rm -f $@
	$(AR) -rc $@ $^

.c.o:
#	��ע���Զ����ɶ�����
#	��ʽ: //SECTION <����> <��ַ>
	-sed -n '/INCLUDE\s\+$*\.lds/ q 1' ../$(BUILD)/auto.lds; if [ $$? -eq 0 ]; then echo -e "\nINCLUDE $*.lds" >> ../$(BUILD)/auto.lds; fi
	sed '/^\/\/SECTION\s\+\S\+\s\+0x\S\+/ s/^\/\/SECTION\s\+\(\S\+\)\s\+0x\(\S\+\)/\. = 0x\2; \.\1 : {\*\.o(\.\1)}/w ../$(BUILD)/$*.lds' $<
	sed -i -n '/^\/\/SECTION\s\+\S\+\s\+0x\S\+/ s/^\/\/SECTION\s\+\(\S\+\)\s\+0x\S\+/__attribute__((section(\"\.\1\")))/; p' $<
	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) $(INCLUDES) -c $< -o $@

.S.o:
#	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(AS) --MD $(DEPSDIR)/$*.d $(ASFLAGS) $(INCLUDES) -o $@ $<
	
.s.o:
#	��ע���Զ����ɶ�����
#	��ʽ: @section <����> <��ַ>
#	����Ļ�������Ҳ����ˡ�����
#	-sed -n '/INCLUDE\s\+$*\.lds/ q 1' ../$(BUILD)/auto.lds; if [ $$? -eq 0 ]; then echo -e "\nINCLUDE $*.lds" >> ../$(BUILD)/auto.lds; fi
#	sed '/^\@section\s\+\S\+\s\+0x\S\+/ s/^\@section\s\+\(\S\+\)\s\+0x\(\S\+\)/\. = 0x\2; \.\1 : {\*\.o(\.\1)}/w ../$(BUILD)/$*.lds' $<
#	sed -i -n '/^\@section\s\+\S\+\s\+0x\S\+/ s/^\@section\s\+\(\S\+\)\s\+0x\S\+/\.section \.\1,"x"/; p' $<
#	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(AS) --MD $(DEPSDIR)/$*.d $(ASFLAGS) $(INCLUDES) -o $@ $<
	
%.s: %.bin
	bin2s $< >$@
	@echo "extern const u8" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" > `(echo $(<F) | tr . _)`.h
	@echo "extern const u32" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(<F) | tr . _)`.h

%.elf:
	$(CC) $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -o $@

%.gba: %.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $<
	$(OBJCOPY) -O binary $< $@

# �Զ��������ݵķ�װ����
# define bin2o
#	bin2s $< | $(CC) -o $@
#	echo "extern const u8" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" > `(echo $(<F) | tr . _)`.h
#	echo "extern const u32" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(<F) | tr . _)`.h
# endef

-include $(DEPENDS)

endif