6502: cpu.h cpu.cpp memory.h memory.cpp main.cpp 
	g++ -o 6502 cpu.h cpu.cpp instructions.cpp addressing_modes.cpp memory.h memory.cpp main.cpp -ICPU -I.