#include <iostream>
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
	
}



//Address modes
uint8_t& CPU::AddrABS(uint16_t arg) { return mem.getLE(arg); }
//ABSX and ABY
uint8_t& CPU::AddrABSidx(uint16_t arg, uint8_t idx) { 
	uint16_t addr = arg+idx;
	//Way to check if a carry occured
	if (addr < arg)
		ST.carry = true;

	return mem.getLE(addr); 
}

/*This is completely fucking useless, and literally
does nothing except return the same byte you passed to
it lmfao*/
uint8_t CPU::AddrIMD(uint8_t arg) { return arg; }
/*Look into later, I don't think anything is needed
for this one though*/
uint8_t CPU::AddrIMP(uint8_t arg) { return 0; }

uint8_t& CPU::AddrIND(uint16_t arg) { return mem[mem.getLE(arg)]; }
uint8_t& CPU::AddrXIND(uint8_t idx, uint8_t arg) {
	uint8_t addr = arg+idx;
	if (addr < arg)
		ST.carry = true;

	return mem[mem[addr]];
}

uint8_t& CPU::AddrINDY(uint8_t arg, uint8_t idx) {
	uint8_t addr = mem[arg];
	uint8_t offsetAdr = addr+idx;

	if (offsetAdr < addr)
		ST.carry = true;

	return mem[offsetAddr];
}

//I think this is right..? INCOMPLETE
uint16_t CPU::AddrREL(uint8_t arg) {
	union {
		int8_t signedOff;
		uint8_t unsignedOff;
	} offset;
	offset.unsignedOff = arg;

	return PC+offset.signedOff;
}

uint8_t& CPU::AddrZPG(uint8_t arg) {
	return mem[arg];
}

//ZPGX and ZPGY
uint8_t& CPU::AddrZPGIDX(uint8_t arg, uint8_t idx) {
	//Cast to one byte
	return mem[(uint8_t) (arg+idx)];
}





//Now the instructions