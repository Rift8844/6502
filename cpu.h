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
		struct {
			bool carry;
			bool zero;
			bool interrupt;
			bool decimal;
			bool brk;
			//Reserved does nothing lmfao
			bool reserved;
			bool overflow;
			bool negative;
		} statusVals;

		uint8_t status;
	} ST;

	Memory mem;

	//Wipe all registers and memory
	void initialize();

	//Addressing modes
public:
	CPU();

	void loadProgram(std::string const& name);
	void executeCycle();
};