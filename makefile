CC=gcc
CFLAGS=-I.
DEPS = core.h helper.h

%.o: %.c $(DEPS)
	$(CC) -c -g -Wall -o $@ $< $(CFLAGS)

maemu: main.o top.o ifu.o helper.o ram_2port.o rf.o decode.o
	$(CC) -o maemu main.o top.o ifu.o helper.o ram_2port.o rf.o decode.o

test: test.o helper.o ram_2port.o rf.o decode.o
	$(CC) -o runtests test.o helper.o ram_2port.o rf.o decode.o
clean:
	rm -f ./*.o ./maemu ./runtests
