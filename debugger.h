#include "cpu.h"
#include "memory.h"
#include <iostream>

#pragma once

class CPUDebugger : public CPU {

public:
	//FACE MELTER HOW TO DO IMPOSSIBLE THINGS
	uint16_t getPC() const { return PC; };
	uint8_t& getSP()  { return SP; };
	uint8_t& getA()   { return A;  };
	uint8_t& getX()   { return X;  };
	uint8_t& getY()   { return Y;  };

	uint8_t  getSP() const { return SP; };
	uint8_t  getA()  const { return A;  };
	uint8_t  getX()  const { return X;  };
	uint8_t  getY()  const { return Y;  };

	uint16_t getInstr() const { return (mem[PC]<<8 | mem[PC+1]); };

	//uint8_t union& ST()   { return ST; };
	Memory& getMem()  { return mem; };

	void jump(uint16_t loc) { JMP(loc); };
};

std::ostream& operator<<(std::ostream& os, CPUDebugger& cpu);