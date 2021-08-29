#include "cpu.h"
#pragma once

class CPUDebugger {
	CPU& cpu;

public:
	//FACE MELTER HOW TO DO IMPOSSIBLE THINGS
	uint16_t PC ()  { return cpu.PC; }
	uint8_t& SP ()  { return cpu.SP; }
	uint8_t& A()    { return cpu.A; }
	uint8_t& X()  	{ return cpu.X; }
	uint8_t& Y() 	{ return cpu.Y; }
	uint8_t& ST()   { return cpu.ST; }
	uint8_t& mem()  { return cpu.mem; }

	uint16_t getInstr { return mem[PC-1]<<8 | mem[PC]; }

	void jump(uint16_t loc) { cpu.JMP(loc); }

	CPUDebugger(CPU& cpu_) : cpu {cpu_} {};
}