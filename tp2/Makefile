CC=gcc
CFLAGS=-Wall
EXEC=Natural_Join

all: $(EXEC)

Natural_Join: Natural_Join.o
	$(CC) -o $@ $^

Natural_Join.o: Natural_Join.c
	$(CC) -o $@ -c $< $(CFLAGS)

run:
	./$(EXEC)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
