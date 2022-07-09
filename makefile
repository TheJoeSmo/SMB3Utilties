


all: compile

compile: bin/nesasm

# Generate the main file to run
bin/nesasm: o/M6502/M6502.o o/NoDiceLib/NoDiceLib.o o/NoDiceLib/ezxml.o o/NoDice/guictls.o o/NoDice/NoDice.o o/NoDice/main.o
	gcc -std=c11 -O -o $@ o/M6502/M6502.o o/NoDiceLib/NoDiceLib.o o/NoDiceLib/ezxml.o o/NoDice/guictls.o o/NoDice/NoDice.o o/NoDice/main.o `pkg-config --cflags gtk+-2.0`

o/NoDice/main.o: src/NoDice/main.c
	gcc -std=c11 -O -c $< -o $@ `pkg-config --cflags gtk+-2.0`

o/NoDice/NoDice.o: $(wildcard src/NoDice/*.c) $(wildcard src/NoDice/*.h)
	gcc -std=c11 -O -c $< -o $@ `pkg-config --cflags gtk+-2.0`

o/NoDice/guictls.o: src/NoDice/gui_combobox_simple.c $(wildcard src/NoDice/*.c) $(wildcard src/NoDice/*.h)
	gcc -std=c11 -O -c $< -o $@ `pkg-config --cflags gtk+-2.0`

o/NoDiceLib/NoDiceLib.o: src/NoDiceLib/nodice.c $(wildcard src/NoDiceLib/*.c) $(wildcard src/NoDiceLib/*.h)
	gcc -std=c11 -O -c $< -o $@ `pkg-config --cflags gtk+-2.0`

o/NoDiceLib/internal.o: src/NoDiceLib/internal.c $(wildcard src/NoDiceLib/*.c) $(wildcard src/NoDiceLib/*.h)
	gcc -std=c11 -O -c $< -o $@ `pkg-config --cflags gtk+-2.0`

o/NoDiceLib/ezxml.o: src/NoDiceLib/ezxml.c $(wildcard src/NoDiceLib/*.c) $(wildcard src/NoDiceLib/*.h)
	gcc -std=c11 -O -c $< -o $@ `pkg-config --cflags gtk+-2.0`

o/M6502/M6502.o: src/NoDiceLib/rom.c $(wildcard src/M6502/*.c) $(wildcard src/M6502/*.h)
	gcc -std=c11 -O -c $< -o $@

clean:
	@rm -rf o/*.o
	@rm -rf o/M6502/*.o
	@rm -rf o/NoDiceLib/*.o
	@rm -rf o/NoDice/*.o
