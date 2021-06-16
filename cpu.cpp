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
	mem[0x0000] = 0x01;
	mem[0x0001] = 0x02;
	mem[0x0002] = 0xFF;

	std::cout << "0x0000 using absolute indexing adressing mode:\n" << 
	(int) AddrABSidx(0x0100, 0x0001);
}


//ADDRESSING MODES

uint8_t& CPU::AddrABS(uint16_t arg) { return mem.getLE(arg); }
//ABSX and ABY
uint8_t& CPU::AddrABSidx(uint16_t arg, uint8_t idx) { 
	uint16_t addr = decodeLE(arg)+idx;

	return mem[addr]; 
}

/*This is completely fucking useless, and literally
does nothing except return the same byte you passed to
it lmfao*/
uint8_t CPU::AddrIMD(uint8_t arg) { return arg; }
/*Look into later, I don't think anything is needed
for this one though*/
uint8_t CPU::AddrIMP(uint8_t arg) { return 0; }

uint16_t CPU::AddrIND(uint16_t arg) { 
	return fetchTwoByte(arg);
}

uint8_t& CPU::AddrXIND(uint8_t idx, uint8_t arg) {
	return mem[fetchTwoByte((uint8_t) arg+idx)];
}

uint8_t& CPU::AddrINDY(uint8_t arg, uint8_t idx) {
	uint16_t baseAddr = fetchTwoByte(arg);

	return mem[baseAddr+idx];
}

//I think this is right..? INCOMPLETE
uint16_t CPU::AddrREL(int8_t arg) {
	return PC+2 + arg;
}

uint8_t& CPU::AddrZPG(uint8_t arg) {
	return mem[arg];
}

//ZPGX and ZPGY
uint8_t& CPU::AddrZPGidx(uint8_t arg, uint8_t idx) {
	//Cast to one byte
	return mem[(uint8_t) (arg+idx)];
}

