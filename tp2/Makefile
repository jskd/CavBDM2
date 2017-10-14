CC=gcc

CFLAGS= -Wall



BDD_SOURCES = $(wildcard src/bdd/*.c)
BDD_HEADERS = $(wildcard src/bdd/*.h)

SRCDIR     := src
OBJDIR     := obj
BINDIR     := bin

BDD_DIR      := bdd
SRCDIR_BDD   := $(SRCDIR)/$(BDD_DIR)
OBJDIR_BDD   := $(OBJDIR)/$(BDD_DIR)
SOURCES_BDD  := $(wildcard $(SRCDIR_BDD)/*.c)
HEADERS_BDD  := $(wildcard $(SRCDIR_BDD)/*.h)
OBJECTS_BDD  := $(SOURCES_BDD:$(SRCDIR_BDD)/%.c=$(OBJDIR_BDD)/%.o)


DEMO_DIR      := demo
SRCDIR_DEMO   := $(SRCDIR)/$(DEMO_DIR)
OBJDIR_DEMO   := $(OBJDIR)/$(DEMO_DIR)
SOURCES_DEMO  := $(wildcard $(SRCDIR_DEMO)/*.c)
HEADERS_DEMO  := $(wildcard $(SRCDIR_DEMO)/*.h)
OBJECTS_DEMO  := $(SOURCES_DEMO:$(SRCDIR_DEMO)/%.c=$(OBJDIR_DEMO)/%.o)

TEST_DIR      := test
SRCDIR_TEST   := $(SRCDIR)/$(TEST_DIR)
OBJDIR_TEST   := $(OBJDIR)/$(TEST_DIR)
SOURCES_TEST  := $(wildcard $(SRCDIR_TEST)/*.c)
HEADERS_TEST  := $(wildcard $(SRCDIR_TEST)/*.h)
OBJECTS_TEST  := $(SOURCES_TEST:$(SRCDIR_TEST)/%.c=$(OBJDIR_TEST)/%.o)



BINDIR_DEMO   := $(BINDIR)/$(DEMO_DIR)
BIN_DEMO      := $(patsubst $(SRCDIR_DEMO)/%.c,$(BINDIR_DEMO)/%,$(SOURCES_DEMO))


BINDIR_TEST   := $(BINDIR)/$(TEST_DIR)
BIN_TEST      := $(patsubst $(SRCDIR_TEST)/%.c,$(BINDIR_TEST)/%,$(SOURCES_TEST))


all: $(OBJECTS_BDD) $(OBJECTS_DEMO) $(OBJECTS_TEST) $(BIN_DEMO) $(BIN_TEST)

$(OBJDIR_DEMO)/%.o : $(SRCDIR_DEMO)/%.c
	echo "1"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	echo "Compiled "$<" successfully!"

$(OBJDIR_TEST)/%.o : $(SRCDIR_TEST)/%.c
	echo "2"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	echo "Compiled "$<" successfully!"

$(OBJDIR_BDD)/%.o : $(SRCDIR_BDD)/%.c
	echo "3"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
	echo "Compiled "$<" successfully!"

$(BINDIR_TEST)/%: $(OBJDIR_TEST)/%.o 
	echo "5"
	mkdir -p $(dir $@)
	$(CC) $(OBJECTS_BDD) $(subst $(BINDIR_TEST)/,$(OBJDIR_TEST)/,$@).o -o $@
	echo "Compiled "$<" successfully!"

$(BINDIR_DEMO)/%: $(OBJDIR_DEMO)/%.o 
	echo "4"
	mkdir -p $(dir $@)
	$(CC) $(OBJECTS_BDD) $(subst $(BINDIR_DEMO)/,$(OBJDIR_DEMO)/,$@).o -o $@
	echo "Compiled "$<" successfully!"


clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

