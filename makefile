CC=gcc
CFLAGS=-I.
DEPS = core.h helper.h

%.o: %.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

maemu: main.o top.o ifu.o helper.o ram_2port.o rf.o
	$(CC) -o maemu main.o top.o ifu.o helper.o ram_2port.o rf.o

test: test.o helper.o ram_2port.o rf.o
	$(CC) -o runtests test.o helper.o ram_2port.o rf.o
clean:
	rm -f ./*.o ./maemu ./runtests
