#include <iostream>
#include <ios>
#include <iomanip>
#include "debugger.h"

//WARNING: VERRRY SLOW
std::ostream& operator<<(std::ostream& os, CPUDebugger& cpu) {
	return os << "Regs:\n" << 
	"\tPC: " << std::hex << std::setw(4) << std::setfill('0') << cpu.getPC() <<
	"\tA:  " << std::hex << std::setw(4) << std::setfill('0') << cpu.getA() << 
	"\tX:  " << std::hex << std::setw(4) <<  std::setfill('0') << cpu.getX() <<
	"\tY:  " << std::hex << std::setw(4) <<  std::setfill('0') << cpu.getY() <<
	"\n\nInstruction: " << std::hex << std::setw(4) << 
	cpu.getInstr() << std::endl;
}