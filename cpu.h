#include <cstdint>
#include "memory.h"
#include <string>

#pragma once

//One day a girl will be impressed by this
class CPU {
	static constexpr uint16_t stackStart = 0x0100;
	static constexpr uint16_t stackEnd =   0x01FF;

	uint16_t PC;
	/*SP is an offset from 0x0100, not an
	absolute address, since the SP is only 8 bit*/
	uint8_t SP;

	uint8_t AC;
	uint8_t X;
	uint8_t Y;

	/*ST meaning StaTus register. Apparently
	this is bad programming practice, because
	this is endian dependent, and it's
	technically UB.*/
	union {
		bool carry;
		bool zero;
		bool interrupt;
		bool decimal;
		bool brk;
		//Reserved does nothing lmfao
		bool reserved;
		bool overflow;
		bool negative;

		uint8_t status;
	} ST;

	Memory mem = Memory(65536);

	//Wipe all registers and memory
	void initialize();

	/*Fetch two bytes of data, which are needed
	in some cases*/
	uint16_t  fetchTwoByte(uint16_t addr) const { return (mem[addr] << 8) | mem[addr+1]; }
	//Decode an address as little endian
	uint16_t decodeLE(uint16_t addr) { return (addr << 8)|(addr >> 8); }


	//Addressing mode implementations

	uint8_t& AddrABS(uint16_t arg);
	//ABSX and ABY
	uint8_t& AddrABSidx(uint16_t arg, uint8_t idx);
	uint8_t  AddrIMD(uint8_t arg);
	/*Look into later, I don't think anything is needed
	for this one though*/
	uint8_t  AddrIMP(uint8_t arg);
	uint16_t AddrIND(uint16_t arg);
	uint8_t& AddrXIND(uint8_t idx, uint8_t arg);
	uint8_t& AddrINDY(uint8_t arg, uint8_t idx);
	uint16_t AddrREL(uint8_t arg);
	uint8_t& AddrZPG(uint8_t arg);
	//ZPGX and ZPGY
	uint8_t& AddrZPGIDX(uint8_t arg, uint8_t idx);

	//Instructions
	/*Implemented in order, as listed on 
	www.obelisk.me.uk/6502/instructions.html*/

	


public:
	CPU() { initialize(); }

	void testFunction();

	void loadProgram(std::string const& name);
	void executeCycle();
};