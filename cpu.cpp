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
		
		//ADC Instructions
		case 0x69: {
			
		}

	}
};

void CPU::testFunction() {
	mem[0x0000] = 0x01;
	mem[0x0001] = 0x02;
	mem[0x0002] = 0xFF;

	std::cout << "0x0000 using absolute indexing adressing mode:\n" << 
	(int) AddrABSidx(0x0100, 0x0001);
}




/*void CPU::updateST(uint8_t reg, uint8_t flags) {  

	if (flags&0x01)
		ST.negative = reg&0x80;

	//Can't implement overflow flag
	//if (flags&0x02)

	if (flags&0x10)

}*/
//INSTRUCTIONS
