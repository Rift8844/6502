
#include "cpu.h"

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
uint8_t CPU::AddrIMP() { return 0; }

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