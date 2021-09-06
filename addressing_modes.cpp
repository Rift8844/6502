
#include "cpu.h"

uint8_t& CPU::AddrABS(uint16_t arg) { return mem[arg]; }
//ABSX and ABSY
uint8_t& CPU::AddrABSidx(uint16_t arg, uint8_t idx) {
	//Wrap around while preserving the page
	uint16_t addr = (arg&0xFF00 | (arg+idx+ST.carry)&0x00FF);
	ST.carry = addr < arg+idx;

	return mem[addr];
}
uint8_t& CPU::AddrABSX(uint16_t arg) { return AddrABSidx(arg, X); }
uint8_t& CPU::AddrABSY(uint16_t arg) { return AddrABSidx(arg, Y); }


/*This is completely fucking useless, and literally
does nothing except return the same byte you passed to
it lmfao*/
uint8_t CPU::AddrIMD(uint8_t arg) { return arg; }
/*Look into later, I don't think anything is needed
for this one though*/
uint8_t CPU::AddrIMP() { return 0; }
/*Apparently there's an accumulator
addressing mode*/
uint8_t& CPU::AddrACC() { return A; }

uint16_t CPU::AddrIND(uint16_t arg) { 
	return fetchTwoByte(arg);
}

uint8_t& CPU::AddrXIND(uint8_t arg) {
	return mem[fetchTwoByte((uint8_t) arg+X)];
}

uint8_t& CPU::AddrINDY(uint8_t arg) {
	uint16_t baseAddr = fetchTwoByte(arg);

	return mem[baseAddr+Y];
}

//I think this is right..? INCOMPLETE
/*Why did I say this was incomplete before
Was there a reason? I think I pulled an
all nighter before I wrote this thing. I
really hope there's not some deadly bug in
this that is just waiting to be discovered...*/
uint16_t CPU::AddrREL(int8_t arg) {
	return PC + 1 + arg;
}

uint8_t& CPU::AddrZPG(uint8_t arg) {
	return mem[arg];
}

//ZPGX and ZPGY
inline uint8_t& CPU::AddrZPGidx(uint8_t arg, uint8_t idx) {
	//Cast to one byte
	return mem[(uint8_t) (arg+idx)];
}
uint8_t& CPU::AddrZPGX(uint8_t arg) { return AddrZPGidx(arg, X); }
uint8_t& CPU::AddrZPGY(uint8_t arg) { return AddrZPGidx(arg, Y); }