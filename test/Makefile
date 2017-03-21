EXE = tgp

CC      = gcc
LD      = gcc
CP      = objcopy
OD      = objdump
AS      = as


SOURCES_PROJECT = test_generic_packet.c generic_packet.c gp_receive.c gp_proj_universal.c

SOURCES = $(SOURCES_PROJECT)
OBJECTS = $(SOURCES:.c=.o)

#Where to find sources
LOCAL_SRC_DIR = src
VPATH = ../src


CFLAGS  =  -I. -I../include \
	-c -fno-common -O2 -g  \
	$(LOCAL_CFLAGS)
LFLAGS  =
LFLAGS_END =
CPFLAGS = -Obinary
ODFLAGS = -S

all: $(EXE)
	@ echo ""
	@ echo ""

debug:
	@ echo "Sources:"  $(SOURCES)
	@ echo "Objects:"  $(OBJECTS)

clean:
	-rm -f $(EXE) $(OBJECTS)

main.bin: main.elf
	@ echo "/* ***************************************************** */"
	@ echo "/* ...copying                                             */"
	@ echo "/* ***************************************************** */"
	$(CP) $(CPFLAGS) main.elf main.bin
	$(OD) $(ODFLAGS) main.elf > main.lst

$(EXE): $(OBJECTS)
	@ echo "/* ***************************************************** */"
	@ echo "/* ...linking " $(EXE) " */"
	@ echo "/* ***************************************************** */"
	$(LD) $(LFLAGS) -o $(EXE) $(OBJECTS) $(LFLAGS_END)
	@ echo ""
	@ echo ""

%.o: %.c
	@ echo "/* ***************************************************** */"
	@ echo "/* ...compiling " $(notdir $<) " */"
	@ echo "/* ***************************************************** */"
	$(CC) $(CFLAGS) $< -o $@
	@ echo ""

run: $(EXE)
	$(EXE)

gdb: $(EXE)
	gdb $(EXE)

valgrind: $(EXE)
	valgrind $(EXE)
