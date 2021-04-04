CC=gcc
CFLAGS=-I.
DEPS = core.h helper.h

%.o: %.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

maemu: main.o top.o ifu.o helper.o ram_2port.o 
	$(CC) -o maemu main.o top.o ifu.o helper.o ram_2port.o

test: test.o helper.o ram_2port.o
	$(CC) -o runtests test.o helper.o ram_2port.o
clean:
	rm -f ./*.o ./maemu ./runtests
