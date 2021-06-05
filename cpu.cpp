#include "cpu.h"
 
void CPU::initialize() {
	constexpr std::size_t memSize = 65536;

	PC = stackEnd+1;
	SP = 0x00;
	AC = 0x00;
	X =  0x00;
	Y =  0x00;
	ST.status = 0x00;

	//Fix this shit later lol
	//mem = Memory(65536);
}
//Implement later
void CPU::loadProgram(std::string const& name) {};


void CPU::executeCycle() {
	switch(mem[PC]) {
		/*Try optimizing this by making
		the accumulator in a union with the
		carry bit, so you only have to do one
		instruction!*/
		
		//ADC Instructions
		case 0x69: {
			
		}

	}
};

#include <iostream>

void CPU::testFunction() {
	std::cout << (int) AddrIMM(16);
}