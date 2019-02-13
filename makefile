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
# 章节事件的目录
EVENTS	:=	event
# 源文件的目录
SOURCES	:=	src sound $(EVENTS)
# 二进制数据的目录
DATA	:=	data
# 头文件
HEADERS	:=	include
# Create a gfx library variable
GFXLIBS     ?= libgfx.a
# 函数库路径
LIBRARIES	:=	lib/libfe lib/libmy lib/libagb lib/libtonc
# 链接的函数库
# LIBS        := -nostdlib -lgfx -ltonc
LIBS        := -lgfx -ltonc
# LIBS        := -lgfx -
# makefile本身(修改了makefile就应该先make clean再重新make)
# MAKEFILES	:= makefile gbamake

# Event Assembler Core
EA	:=	Core
# Event Assembler选项
EAFLAGS	:=	C FE7J

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
EVENTFILES	:=	$(foreach dir,$(EVENTS),$(wildcard $(dir)/*.event))
SFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S))) \
			$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
ASMFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.asm))) \
				$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.ASM)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))

# export OFILES	:=	$(CFILES:.c=.o) $(subst .s,.o,$(SFILES:.S=.o)) $(BINFILES:.bin=.o) $(EVENTFILES:.event=.o)
export OFILES	:=	$(CFILES:.c=.o) $(subst .s,.o,$(SFILES:.S=.o)) $(subst .asm,.o,$(ASMFILES:.ASM=.o)) $(BINFILES:.bin=.o)
# export OFILES	:=	$(CFILES:.c=.o) $(subst .s,.o,$(SFILES:.S=.o))
# export LIBPATHS	:=	$(foreach dir,$(LIBRARIES),-L$(dir)/lib)
export LIBPATHS	:=	$(foreach dir,$(LIBRARIES),-L../$(dir)/lib) -L$(CURDIR)
export INCLUDES	:=	$(foreach dir,$(HEADERS),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBRARIES),-I$(CURDIR)/$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

# 伪目标
.PHONY: all $(BUILD) clean event gtags

all	: event $(BUILD)

# 切换到build目录下make
$(BUILD):
	[ -d $@ ] || mkdir -p $@
#	$(MAKE) --no-print-directory -f $(CURDIR)/gfxmake
#	$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	
event : $(notdir $(EVENTFILES:.event=.s))

%.s: %.event
	$(EA) $(EAFLAGS) -input:$(EVENTS)/$(notdir $<) -output:src/$(notdir $@)

clean:
	rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba
	
gtags:
	gtags
	
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
	@-sed -n '/INCLUDE\s\+$*\.lds/ q 1' ../$(BUILD)/auto.lds; if [ $$? -eq 0 ]; then echo -e "\nINCLUDE $*.lds" >> ../$(BUILD)/auto.lds; fi
	@sed '/^\/\/SECTION\s\+\S\+\s\+0x\S\+/ s/^\/\/SECTION\s\+\(\S\+\)\s\+0x\(\S\+\)/\. = 0x\2; \.\1 : {\*\.o(\.\1)}/w ../$(BUILD)/$*.lds' $< >/dev/null
	@sed -i -n '/^\/\/SECTION\s\+\S\+\s\+0x\S\+/ s/^\/\/SECTION\s\+\(\S\+\)\s\+0x\S\+/__attribute__((section(\"\.\1\")))/; p' $<
	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d $(CFLAGS) $(INCLUDES) -c $< -o $@

.S.o:
	@-sed -n '/INCLUDE\s\+$*\.lds/ q 1' ../$(BUILD)/auto.lds; if [ $$? -eq 0 ]; then echo -e "\nINCLUDE $*.lds" >> ../$(BUILD)/auto.lds; fi
	@sed '/^\@section\s\+\S\+\s\+0x\S\+/ s/^\@section\s\+\(\S\+\)\s\+0x\(\S\+\)/\. = 0x\2; \.\1 : {\*\.o(\.\1)}/w ../$(BUILD)/$*.lds' $< >/dev/null
	@sed -i -n '/^\@section\s\+\S\+\s\+0x\S\+/ s/^\@section\s\+\(\S\+\)\s\+0x\S\+/\.section \.\1,"ax",%progbits/; p' $<
#	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(AS) --MD $(DEPSDIR)/$*.d $(ASFLAGS) $(INCLUDES) -o $@ $<
	
.s.o:
#	从注释自动生成段配置
#	格式: @section <段名> <地址>
#	https://sourceware.org/binutils/docs-2.22/as/Section.html#Section
	@-sed -n '/INCLUDE\s\+$*\.lds/ q 1' ../$(BUILD)/auto.lds; if [ $$? -eq 0 ]; then echo -e "\nINCLUDE $*.lds" >> ../$(BUILD)/auto.lds; fi
	@sed '/^\@section\s\+\S\+\s\+0x\S\+/ s/^\@section\s\+\(\S\+\)\s\+0x\(\S\+\)/\. = 0x\2; \.\1 : {\*\.o(\.\1)}/w ../$(BUILD)/$*.lds' $< >/dev/null
	@sed -i -n '/^\@section\s\+\S\+\s\+0x\S\+/ s/^\@section\s\+\(\S\+\)\s\+0x\S\+/\.section \.\1,"ax",%progbits/; p' $<
#	$(CC) -MMD -MP -MF $(DEPSDIR)/$*.d -x assembler-with-cpp $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(AS) --MD $(DEPSDIR)/$*.d $(ASFLAGS) $(INCLUDES) -o $@ $<
	
%.o: %.asm
	armasm --MD --li -g --cpu=ARM7TDMI --thumb --apcs=interwork -o $@ $<
	
%.o: %.ASM
	armasm --cpreproc --MD --li -g --cpu=ARM7TDMI --thumb --apcs=interwork -o $@ $<
	
%.s: %.bin
	bin2s $< >$@
	@echo "extern const u8" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" > `(echo $(<F) | tr . _)`.h
	@echo "extern const u32" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(<F) | tr . _)`.h

#%.s: %.event
#	$(EA) $(EAFLAGS) -input:../src/$(notdir $<) -output:../src/$(notdir $@)
#	$(EA) $(EAFLAGS) -input:$< -output:$@
	
%.elf:
	$(CC) $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -o $@
#	去掉调试信息，可以载入VBAM
	$(STRIP) -g -o $*-stripped.elf $@

%.gba: %.elf
#	$(OBJCOPY) $(OBJCOPYFLAGS) $<
	$(OBJCOPY) -O binary $< $@
	
# 若使用ld链接,则有两种方式处理.rom段:
#	(1) 链接的时候设置.rom段不加载,这样就不会出现段重叠的问题影响链接过程,生成elf;
#		完成链接(已经生成elf)之后再用objcopy修改.rom段的属性让它输出占空间;
#		objcopy从修改后的elf中dump出最后的二进制游戏卡带,包含了.rom段的内容。
#		特点是.rom不在elf的section(段)中，却不在segment(程序节)中。
#	(2) 链接的时候给链接器ld传递--no-check-sections选项,不检查段重叠;
#		完成链接后直接用objcopy从elf中dump出游戏卡带内容即可。
#		特点是生成的elf中包含完整的.rom,既在section中又在segment中。
# 若使用armlink链接，则可以通过命令行选项将segment overlap的error降级为warning完成链接;
#		完成链接后直接用objcopy从elf中dump出游戏卡带内容即可。
#		特点是生成的elf中包含完整的.rom,既在section中又在segment中。
# 详见: http://feuniverse.us/t/guide-doc-asm-hacking-in-c/3351

# 对二进制数据的封装命令
# define bin2o
#	bin2s $< | $(CC) -o $@
#	echo "extern const u8" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" > `(echo $(<F) | tr . _)`.h
#	echo "extern const u32" `(echo $(<F) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(<F) | tr . _)`.h
# endef

-include $(DEPENDS)

endif