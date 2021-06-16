#include <cstdint>
#include "memory.h"
#include <string>

#pragma once

/*I think women are special creatures. They seem to follow
certain observable patterns, more extreme then the ones
exhibited by male neurotypicals.*/
class CPU {
	static constexpr uint16_t stackStart = 0x0100;
	static constexpr uint16_t stackEnd =   0x01FF;

	uint16_t PC;
	/*SP is an offset from 0x0100, not an
	absolute address, since the SP is only 8 bit*/
	uint8_t SP;

	uint8_t A;
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
	in some cases. Fetchtwobyte uses little endian, and preserves
	the page number.*/
	uint16_t fetchTwoByte(uint16_t addr) const { 
		uint16_t val = mem[addr];
		addr++;

		if (addr&0x00FF == 0x00)
			addr -= 0x0100;

		val |= mem[addr]<<8;
		return val; 
	}

	/*uint16_t old_fetchTwoByte(uint16_t addr) const { 
		return mem[addr] | (mem[addr&0xFF00 & ((addr+1)&0x00FF)] << 8); 
	}*/



	//Decode an address as little endian
	uint16_t decodeLE(uint16_t addr) const { return (addr << 8)|(addr >> 8); }


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
	uint16_t AddrREL(int8_t arg);
	uint8_t& AddrZPG(uint8_t arg);
	//ZPGX and ZPGY
	uint8_t& AddrZPGidx(uint8_t arg, uint8_t idx);

	//Instructions
	/*Implemented in order, as listed on 
	www.obelisk.me.uk/6502/instructions.html*/



	void LD(uint8_t& reg, uint8_t val);
	void LDA(uint8_t val);
	void LDX(uint8_t val);
	void LDY(uint8_t val);


	void STA(uint8_t& loc);
	void STX(uint8_t& loc);
	void STY(uint8_t& loc);


	void TR(uint8_t& lval, uint8_t rval);
	void TAX();
	void TAY();
	void TXA();
	void TYA();


	void TSX();
	void TXS();
	void PHA();
	void PHP();
	void PLA();
	void PLP();


	void AND(uint8_t m);
	void EOR(uint8_t m);
	void ORA(uint8_t m);
	void BIT(uint8_t m);

public:
	CPU() { initialize(); }

	void testFunction();

	void loadProgram(std::string const& name);
	void executeCycle();
};