#include <iostream>
#include "cpu.h"
 
void CPU::initialize() {
	constexpr std::size_t memSize = 65536;

	PC = stackEnd+1;
	SP = 0x00;
	A =  0x00;
	X =  0x00;
	Y =  0x00;
	ST.status = 0x00;

	//Fix this shit later lol
	mem = Memory(memSize);
}

//Implement later
void CPU::loadProgram(std::string const& name) {};


void CPU::executeCycle() {
	switch(mem[PC]) {
		/*Try optimizing this by making
		the accumulator in a union with the
		carry bit, so you only have to do one
		instruction!*/


	}
};

void CPU::testFunction() {}




/*void CPU::updateST(uint8_t reg, uint8_t flags) {  

	if (flags&0x01)
		ST.negative = reg&0x80;

	//Can't implement overflow flag
	//if (flags&0x02)

	if (flags&0x10)

}*/
//INSTRUCTIONS
