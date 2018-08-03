# by laqieer
# 2017/1/26

# 添加工具路径
# PATH	:=	$(DEVKITARM)/bin;$(PATH)
# error: make: make: Command not found
# I was inadvertently overriding my PATH so none of my commands were being found.

# 指定各种目录和文件

# 生成的目标文件以工程目录名命名
TARGET	:=	$(shell basename $(CURDIR))
# 生成文件的目录
BUILD	:=	build
# 源文件的目录
SOURCES	:=	src sound
# 二进制数据的目录
DATA	:=	data
# 头文件
HEADERS	:=	include
# Create a gfx library variable
GFXLIBS     ?= libgfx.a
# 函数库路径
LIBRARIES	:=	lib/libfe lib/libmy lib/libagb lib/libtonc
# 链接的函数库
LIBS        := -nostdlib -lgfx -ltonc
# LIBS        := -lgfx -
# makefile本身(修改了makefile就应该先make clean再重新make)
# MAKEFILES	:= makefile gbamake

# 若在顶层目录
ifeq (0,$(MAKELEVEL))

# 向下层传递变量
export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/$(BUILD)
# 链接脚本
export LDS	=	$(OUTPUT).ld					

# 要编译的文件类型清单

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

# 伪目标
.PHONY: $(BUILD) clean

# 切换到build目录下make
$(BUILD):
	[ -d $@ ] || mkdir -p $@
	$(MAKE) --no-print-directory -f $(CURDIR)/gfxmake
	$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

all	: $(BUILD)

clean:
	rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba
	
# 若已经进入到build目录
else

include ../gbamake

# 依赖性
DEPENDS	:=	$(OFILES:.o=.d)

# 真正的编译目标
$(OUTPUT).gba: $(OUTPUT).elf

$(OUTPUT).elf: $(OFILES) $(LDS) $(GFXLIBS)

# 通用规则

%.a:
	rm -f $@
	$(AR) -rc $@ $^

.c.o:
#	从注释自动生成段配置
#	格式: //SECTION <段名> <地址>
	-sed -n '/INCLUDE\s\+$*\.lds/ q 1' ../$(BUILD)/auto.lds; if [ $$? -eq 0 ]; then echo -e "\nINCLUDE $*.lds" >> ../$(BUILD)/auto.lds; fi
	sed '/^\/\/SECTION\s\+\S\+\s\+0x\S\+/ s/^\/\/SECTION\s\+\(\S\+\)\s\+0x\(\S\+\)/\. = 0x\2; \.\1 : {\*\.o(\.\1)}/w ../$(BUILD)/$*.lds' $<
	sed -i -n '/^\/\/SECTION\s\+\S\+\s\+0x\S\+/ s/^\/\/SECTION\s\+\(\S\+\)\s\+0x\S\+/__attribute__((section(\"\.\1\")))/; p' $<
	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) $(INCLUDES) -c $< -o $@

.S.o:
#	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(AS) --MD $(DEPSDIR)/$*.d $(ASFLAGS) $(INCLUDES) -o $@ $<
	
.s.o:
#	从注释自动生成段配置
#	格式: @section <段名> <地址>
#	定义的汇编段最后找不到了。。。
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

# 对二进制数据的封装命令
# define bin2o
#	bin2s $< | $(CC) -o $@
#	echo "extern const u8" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" > `(echo $(<F) | tr . _)`.h
#	echo "extern const u32" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(<F) | tr . _)`.h
# endef

-include $(DEPENDS)

endif