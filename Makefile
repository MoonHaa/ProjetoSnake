#define compilador principal
CC := gcc

#seta diretorios, extensoes de arquivos e flags de compilação
SRCDIR := src
BUILDDIR := build
BINDIR := bin
MAINDIR := main
TESTDIR := test
SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -std=c11 -Wall
LIB := -lncurses
INC := -I include

#compila o programa
all: snake

#compila o programa
snake: $(OBJECTS) $(BUILDDIR)/principal.o
	@mkdir -p $(BINDIR)
	@echo " Linkando Snake..."
	@echo " $(CC) $^ -o $(BINDIR)/Snake $(LIB)"; $(CC) $^ -o $(BINDIR)/Snake $(LIB)

#compila o arquivo principal.c
$(BUILDDIR)/principal.o: $(MAINDIR)/principal.c
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

#compila a teste
test: $(OBJECTS) $(BUILDDIR)/teste.o
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $(BINDIR)/teste $(LIB)

#compile a main da teste
$(BUILDDIR)/teste.o: $(TESTDIR)/teste.c
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

#compila os demais arquivos .c
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

#clean
clean:
	@echo " Limpando...";
	@echo " $(RM) -rf $(BUILDDIR) $(BINDIR)"; $(RM) -rf $(BUILDDIR) $(BINDIR)

.PHONY: clean test snake

