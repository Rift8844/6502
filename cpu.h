#pragma once
#include <cstdint>
#include "memory.h"

//One day a girl will be impressed by this
class CPU {
	static constexpr uint16_t stackStart = 0x0100;
	static constexpr uint16_t stackEnd =   0x01FF;

	uint16_t PC = stackEnd+1;
	/*SP is an offset from 0x0100, not an
	absolute address, since the SP is only 8 bit*/
	uint8_t SP =  0x00;

	uint8_t AC =  0;
	uint8_t X =   0;
	uint8_t Y =   0;

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

	//Don't use a separate memory class for now
	std::vector<uint8_t> memory;

	//Wipe all registers and memory
	void initialize();

public:
	CPU();

	void loadProgram(std::string const& name);
	void executeCycle();
};
