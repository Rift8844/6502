
#I'm not sure if my new makefile is made properly and
#reasonably, but it fucking works lmao so whatever lol

all: 6502

6502: cpu.o addressing_modes.o instructions.o memory.o main.o
	g++ -C memory.o cpu.o addressing_modes.o instructions.o main.o -o 6502
	echo BUILD COMPLETE

cpu.o: addressing_modes.o instructions.o cpu.h cpu.cpp
	g++ -c cpu.h cpu.cpp
addressing_modes.o: addressing_modes.cpp
	g++ -c addressing_modes.cpp
instructions.o: instructions.cpp
	g++ -c instructions.cpp

memory.o: memory.h memory.cpp
	g++ -c memory.h memory.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm 6502

clean_objects:
	rm $(wildcard *.o)
	rm $(wildcard *.h.gch)

clean_all: clean clean_objects

#g++ -o 6502 cpu.h instructions.cpp addressing_modes.cpp cpu.cpp memory.h memory.cpp main.cpp -ICPU -I.

