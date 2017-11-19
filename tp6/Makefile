.PHONY: clean doc rapport rm-rs

CC=gcc
CFLAGS= -g -Wall --std=gnu99
RS_TXT := res/RS.txt
RS_DISK_TXT := res/disk/RS.txt
# Repertoire global
SRCDIR     := src
OBJDIR     := obj
BINDIR     := bin

# Zone source de bdd
BDD_DIR      := bdd
SRCDIR_BDD   := $(SRCDIR)/$(BDD_DIR)
OBJDIR_BDD   := $(OBJDIR)/$(BDD_DIR)
SOURCES_BDD  := $(wildcard $(SRCDIR_BDD)/*.c)
HEADERS_BDD  := $(wildcard $(SRCDIR_BDD)/*.h)
OBJECTS_BDD  := $(SOURCES_BDD:$(SRCDIR_BDD)/%.c=$(OBJDIR_BDD)/%.o)

# Zone source de démo
DEMO_DIR      := demo
SRCDIR_DEMO   := $(SRCDIR)/$(DEMO_DIR)
OBJDIR_DEMO   := $(OBJDIR)/$(DEMO_DIR)
SOURCES_DEMO  := $(wildcard $(SRCDIR_DEMO)/*.c)
HEADERS_DEMO  := $(wildcard $(SRCDIR_DEMO)/*.h)
OBJECTS_DEMO  := $(SOURCES_DEMO:$(SRCDIR_DEMO)/%.c=$(OBJDIR_DEMO)/%.o)

# Zone source de test
TEST_DIR      := test
SRCDIR_TEST   := $(SRCDIR)/$(TEST_DIR)
OBJDIR_TEST   := $(OBJDIR)/$(TEST_DIR)
SOURCES_TEST  := $(wildcard $(SRCDIR_TEST)/*.c)
HEADERS_TEST  := $(wildcard $(SRCDIR_TEST)/*.h)
OBJECTS_TEST  := $(SOURCES_TEST:$(SRCDIR_TEST)/%.c=$(OBJDIR_TEST)/%.o)

# Zone binaire de démo
BINDIR_DEMO   := $(BINDIR)/$(DEMO_DIR)
BIN_DEMO      := $(patsubst $(SRCDIR_DEMO)/%.c,$(BINDIR_DEMO)/%,$(SOURCES_DEMO))

# Zone binaire de test
BINDIR_TEST   := $(BINDIR)/$(TEST_DIR)
BIN_TEST      := $(patsubst $(SRCDIR_TEST)/%.c,$(BINDIR_TEST)/%,$(SOURCES_TEST))

# Recette pour une compilation complete
all:  $(OBJECTS_BDD) $(OBJECTS_DEMO) $(OBJECTS_TEST) $(BIN_DEMO) $(BIN_TEST)

# Recette de compilatation de objets de démo
$(OBJDIR_DEMO)/%.o : $(SRCDIR_DEMO)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$<" reussite!"

# Recette de compilatation de objets de test
$(OBJDIR_TEST)/%.o : $(SRCDIR_TEST)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$<" reussite!"

# Recette de compilatation de objets de la bibliotheque bdd
$(OBJDIR_BDD)/%.o : $(SRCDIR_BDD)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Compilation "$<" reussite!"

# Recette de compilatation des exécutable de test
$(BINDIR_TEST)/%: $(OBJDIR_TEST)/%.o $(OBJECTS_BDD)
	@mkdir -p $(dir $@)
	@$(CC) $(OBJECTS_BDD) $(subst $(BINDIR_TEST)/,$(OBJDIR_TEST)/,$@).o -o $@
	@echo "Compilation "$<" reussite!"

# Recette de compilatation des exécutable de demo
$(BINDIR_DEMO)/%: $(OBJDIR_DEMO)/%.o $(OBJECTS_BDD)
	@mkdir -p $(dir $@)
	@$(CC) $(OBJECTS_BDD) $(subst $(BINDIR_DEMO)/,$(OBJDIR_DEMO)/,$@).o -o $@
	@echo "Compilation "$<" reussite!"

# Netoyage du projet
clean: rm-rs
	@rm -rf $(RS_TXT)
	@echo "Fichier "$(RS_TXT)" supprimé"
	@rm -rf $(RS_DISK_TXT)
	@echo "Fichier "$(RS_DISK_TXT)" supprimé"
	@rm -rf $(OBJDIR)
	@echo "Répertoire "$(OBJDIR)" supprimé"
	@rm -rf $(BINDIR)
	@echo "Répertoire "$(BINDIR)" supprimé"

# Lancement de script de test
test: $(BIN_TEST)
	@chmod +x script/test.sh
	@./script/test.sh
	@echo "Script de test terminé"

# Lancement du générateur de document
doc:
	@doxygen doc/doxyfile
	@echo "Génération de la doc terminé"

# Lancement du générateur de rapport
rapport:
	@cd rapport && $(MAKE)
	@cp rapport/rapport.pdf rapport.pdf
	@echo "Génération du rapport terminé"

# Lancement de la démo 1
demo-tp1: bin/demo/tp1-natural-join
	./bin/demo/tp1-natural-join
	@echo "Démonstration terminé"

# Lancement de la démo 2
demo-tp2: bin/demo/tp2-merge-join-without-duplicate
	./bin/demo/tp2-merge-join-without-duplicate
	@echo "Démonstration terminé"

# Lancement de la démo 3
demo-tp3: bin/demo/tp3-merge-join-with-duplicate
	./bin/demo/tp3-merge-join-with-duplicate
	@echo "Démonstration terminé"

# Lancement de la démo 4
demo-tp4: bin/demo/tp4-hash-join
	./bin/demo/tp4-hash-join
	@echo "Démonstration terminé"

# Lancement de la démo 4
demo-tp5: bin/demo/tp5-nested-loop-disk
	./bin/demo/tp5-nested-loop-disk
	@echo "Démonstration terminé"

# Supression de RS.txt
rm-rs:
	@find . -path '*/RS/*' -delete
	@find . -type d -name 'RS' -empty -delete
	@find . -path '*/tableR/*' -delete
	@find . -type d -name 'tableR' -empty -delete
	@find . -path '*/tableS/*' -delete
	@find . -type d -name 'tableS' -empty -delete
	@find . -path '*/RS.txt' -delete
	@echo "Supression des fichier généré terminé"

zip: clean
	zip -r ${name}TP${n}.zip Makefile README.md doc/ rapport/ rapport.pdf refman.pdf res/ script/ src/ sujet.pdf
