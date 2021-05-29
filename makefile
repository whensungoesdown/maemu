CC=gcc
CFLAGS=-I.
DEPS = core.h helper.h

%.o: %.c $(DEPS)
	$(CC) -c -g -Wall -o $@ $< $(CFLAGS)

maemu: main.o top.o ifu.o helper.o ram_2port.o rf.o decode.o latdff.o adder.o exu.o reservation_station.o rob.o register_stat.o
	$(CC) -o maemu main.o top.o ifu.o helper.o ram_2port.o rf.o decode.o latdff.o adder.o exu.o reservation_station.o rob.o register_stat.o

test: test.o helper.o ram_2port.o rf.o decode.o latdff.o adder.o exu.o reservation_station.o rob.o register_stat.o
	$(CC) -o runtests test.o helper.o ram_2port.o rf.o decode.o latdff.o adder.o exu.o reservation_station.o rob.o register_stat.o
clean:
	rm -f ./*.o ./maemu ./runtests
