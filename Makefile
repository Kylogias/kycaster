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

CCFLAGS := -I$(INCPATH) -std=c17
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
	CLEAN=clean_custom_posix
	BACKUP=backup_posix
else
	CLEAN=clean_custom_win
	BACKUP=backup_win
endif

all: backup clean copy_dll build custom

$(OFILES): $(OBJFOLDER)/%$(OBJEXT): $(SRCFOLDER)/%$(SRCEXT)
	$(CC) -o $(OBJFOLDER)/$(@F) -c $< $(CCFLAGS)

$(BINFOLDER)/%$(DLLEXT): $(DYNFOLDER)/%$(DLLEXT)
	cp -f $< $@

clean: $(CLEAN)

backup: $(BACKUP)

backup_win:
	if exist "../$(PROJNAME)_BACKUP" rd /S /Q "../$(PROJNAME)_BACKUP"
	if not exist "../$(PROJNAME)_BACKUP" mkdir "../$(PROJNAME)_BACKUP"
	cp -f -r -t "../$(PROJNAME)_BACKUP" "./"

backup_posix:

clean_posix:
	rm -rf ./$(OBJFOLDER)/*
	rm -rf ./$(BINFOLDER)/*

clean_win:
	if exist "./$(OBJFOLDER)" rd /S /Q "./$(OBJFOLDER)"
	if not exist "./$(OBJFOLDER)" md "./$(OBJFOLDER)"
	if exist "./$(BINFOLDER)" rd /S /Q "./$(BINFOLDER)"
	if not exist "./$(BINFOLDER)" md "./$(BINFOLDER)"

copy_dll: $(DLLTO)

build: $(OFILES)
	$(LD) -o $(EXEFILE) $(patsubst %,./$(OBJFOLDER)/%,$(^F)) $(LDFLAGS)

# ----------------------------------------
#           CUSTOM RULES GO HERE
#-----------------------------------------

UMKAEXT := .um
UMFILES := $(wildcard ./$(SRCFOLDER)/*$(UMKAEXT))
UMFILES += $(wildcard ./$(SRCFOLDER)/**/*$(UMKAEXT))
SCRIPTTO := $(BINFOLDER)/scripts
UMTO := $(patsubst ./$(SCRIPTFROM)/%,./$(SCRIPTTO)/%,$(UMFILES))

custom: $(UMTO)

$(SCRIPTTO)/%$(UMKAEXT): $(SRCFOLDER)/%%/%$(UMKAEXT)
	cp -f $< ./$(SCRIPTTO)/$(@F)

clean_custom_win: clean_win
	if exist "./$(SCRIPTTO)" rd /S /Q "./$(SCRIPTTO)"
	if not exist "./$(SCRIPTTO)" md "./$(SCRIPTTO)"

clean_custom_posix: clean_posix