#pragma once
#include <cstdint>
#include "memory.h"

class CPU {
	uint8_t A;
	uint8_t X;
	uint8_t Y;

	uint16_t PC;
	uint8_t SP;

	union {
		struct {
			bool carry;
			bool zero;
			bool interrupt;
			bool decimal;
			bool brk;
			bool overflow;
			bool negative;
		} statusVals;

		uint8_t status;
	} ST;

	Memory mem;
};