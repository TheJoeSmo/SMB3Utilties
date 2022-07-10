

all: compile

compile: bin/NoDice

# Generate the main file to run
bin/NoDice: o/M6502/M6502.o o/NoDice/gui_overlay.o o/NoDice/gui_property_box.o o/NoDice/edit.o o/NoDice/gui_combobox_simple.o o/NoDiceLib/stristr.o o/NoDiceLib/ram.o o/NoDiceLib/exec.o o/NoDiceLib/config.o o/NoDice/ppu.o o/NoDice/gui_popups.o o/NoDice/gui.o o/NoDiceLib/NoDiceLib.o o/NoDiceLib/ezxml.o o/NoDice/guictls.o o/NoDice/NoDice.o o/NoDice/main.o
	gcc -std=c11 -g -o $@ o/M6502/M6502.o o/NoDice/gui_overlay.o o/NoDice/gui_property_box.o o/NoDice/edit.o o/NoDice/gui_combobox_simple.o o/NoDiceLib/stristr.o o/NoDiceLib/ram.o o/NoDiceLib/exec.o o/NoDiceLib/config.o o/NoDice/ppu.o o/NoDice/gui_popups.o o/NoDice/gui.o o/NoDiceLib/NoDiceLib.o o/NoDiceLib/ezxml.o o/NoDice/guictls.o o/NoDice/NoDice.o o/NoDice/main.o `pkg-config --cflags gtk+-2.0`  `pkg-config --libs gtk+-2.0`

o/NoDice/main.o: src/NoDice/main.c
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/NoDice.o: src/NoDice/NoDice.c src/NoDice/NoDice.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/ppu.o: src/NoDice/ppu.c src/NoDice/ppu.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/edit.o: src/NoDice/edit.c src/NoDice/edit.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/gui_popups.o: src/NoDice/gui_popups.c src/NoDice/gui_popups.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/gui_overlay.o: src/NoDice/gui_overlay.c src/NoDice/gui_overlay.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/gui_property_box.o: src/NoDice/gui_property_box.c src/NoDice/gui_property_box.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/gui.o: src/NoDice/gui.c src/NoDice/gui.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/gui_combobox_simple.o: src/NoDice/gui_combobox_simple.c src/NoDice/gui_combobox_simple.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDice/guictls.o: src/NoDice/gui_listbox.c src/NoDice/guictls.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDiceLib/NoDiceLib.o: src/NoDiceLib/nodice.c src/NoDiceLib/NoDiceLib.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDiceLib/exec.o: src/NoDiceLib/exec.c src/NoDiceLib/exec.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDiceLib/internal.o: src/NoDiceLib/internal.c src/NoDiceLib/internal.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDiceLib/config.o: src/NoDiceLib/config.c src/NoDiceLib/config.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDiceLib/stristr.o: src/NoDiceLib/stristr.c src/NoDiceLib/stristr.h
	gcc -std=c11 -g -c $< -o $@

o/NoDiceLib/ram.o: src/NoDiceLib/ram.c src/NoDiceLib/ram.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/NoDiceLib/ezxml.o: src/NoDiceLib/ezxml.c src/NoDiceLib/ezxml.h
	gcc -std=c11 -g -c $< -o $@ `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

o/M6502/M6502.o: src/NoDiceLib/rom.c $(wildcard src/M6502/*.c) $(wildcard src/M6502/*.h)
	gcc -std=c11 -g -c $< -o $@

tidy:
	clang-tidy -fix src/NoDice/*.c -checks=readability-else-after-return,readability-isolate-declaration,readability-braces-around-statements -- `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` 
	clang-tidy -fix src/NoDiceLib/*.c -checks=readability-else-after-return,readability-isolate-declaration,readability-braces-around-statements -- `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` 
	clang-tidy -fix src/NoDice/*.h -checks=readability-else-after-return,readability-isolate-declaration,readability-braces-around-statements -- `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` 
	clang-tidy -fix src/NoDiceLib/*.h -checks=readability-else-after-return,readability-isolate-declaration,readability-braces-around-statements -- `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` 
	clang-tidy -fix src/M6502/M6502.h -checks=readability-else-after-return,readability-isolate-declaration,readability-braces-around-statements -- `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` 
	clang-format -i --style=file ./src/NoDice/*.c
	clang-format -i --style=file ./src/NoDiceLib/*.c
	clang-format -i --style=file ./src/NoDice/*.h
	clang-format -i --style=file ./src/NoDiceLib/*.h
	clang-format -i --style=file ./src/M6502/M6502.h

clear: clean
	@clear

clean:
	@rm -rf o/*.o
	@rm -rf o/M6502/*.o
	@rm -rf o/NoDiceLib/*.o
	@rm -rf o/NoDice/*.o
