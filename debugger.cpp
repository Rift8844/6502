#include <iostream>
#include <ios>
#include <iomanip>
#include "debugger.h"

//WARNING: VERRRY SLOW
std::ostream& operator<<(std::ostream& os, CPUDebugger& cpu) {
	return os << "\nRegs:\n" << 
	"\tPC: " << std::hex << std::setw(4) << std::setfill('0') << (int) cpu.getPC() <<
	"\tA:  " << std::hex << std::setw(4) << std::setfill('0') << (int) cpu.getA() << 
	"\tX:  " << std::hex << std::setw(4) <<  std::setfill('0') << (int) cpu.getX() <<
	"\tY:  " << std::hex << std::setw(4) <<  std::setfill('0') << (int) cpu.getY() <<
	"\nInstruction: " << std::hex << std::setw(4) << 
	cpu.getInstr() << std::endl;
}