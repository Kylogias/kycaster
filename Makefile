CC := gcc
LD := gcc
DB := gdb

SRCFOLDER := src
OBJFOLDER := obj
BINFOLDER := bin
INCFOLDER := inc
LIBFOLDER := lib
DYNFOLDER := dyn

SRCEXT := .c
OBJEXT := .o
EXEEXT := .exe
DLLEXT := .dll

PROJNAME := Kycaster

LIBPATH := ./$(LIBFOLDER)
INCPATH := ./$(INCFOLDER)

CCFLAGS := -I$(INCPATH) -std=c2x
LDFLAGS := -L$(LIBPATH) -lumka -lraylibdll -std=c2x

# ----------------------------------------
#         NO EDITS PAST THIS POINT
# ----------------------------------------

CFILES := $(wildcard ./$(SRCFOLDER)/*$(SRCEXT))
CFILES+=$(wildcard ./$(SRCFOLDER)/**/*$(SRCEXT))
OFILES := $(patsubst ./$(SRCFOLDER)/%,./$(OBJFOLDER)/%,$(CFILES:$(SRCEXT)=$(OBJEXT)))
EXEFILE := ./$(BINFOLDER)/$(PROJNAME)$(EXEEXT)
DFILES := $(wildcard ./$(DYNFOLDER)/*$(DLLEXT))
DLLTO := $(patsubst ./$(DYNFOLDER)/%,./$(BINFOLDER)/%,$(DFILES))

ifneq ($(OS),Windows_NT)
	CLEAN=clean_posix
else
	CLEAN=clean_win
endif

all: clean copy_dll build custom

$(OFILES): $(OBJFOLDER)/%$(OBJEXT): $(SRCFOLDER)/%$(SRCEXT)
	$(CC) -o $(OBJFOLDER)/$(@F) -c $< $(CCFLAGS)

$(BINFOLDER)/%$(DLLEXT): $(DYNFOLDER)/%$(DLLEXT)
	cp -f $< $@

clean: $(CLEAN)

clean_posix: clean_custom_posix
	rm -rf ./$(OBJFOLDER)/*
	rm -rf ./$(BINFOLDER)/*

clean_win: clean_custom_win
	del /S /Q *$(OBJEXT)
	del /S /Q *$(EXEEXT)

copy_dll: $(DLLTO)

build: $(OFILES)
	$(LD) -o $(EXEFILE) $(patsubst %,./$(OBJFOLDER)/%,$(^F)) $(LDFLAGS)

# ----------------------------------------
#           CUSTOM RULES GO HERE
#-----------------------------------------

UMKAEXT := .um
UMFILES := $(wildcard ./$(SRCFOLDER)/*$(UMKAEXT))
UMTO := $(patsubst ./$(SRCFOLDER)/%,./$(BINFOLDER)/%,$(UMFILES))

custom: $(UMTO)

$(BINFOLDER)/%$(UMKAEXT): $(SRCFOLDER)/%$(UMKAEXT)
	cp -f $< $@

clean_custom_win:

clean_custom_posix: