
#include <iostream>
#include <fstream>
#include <sstream>
#include "cpu.h"
#include "debugger.h"

int main() {
	CPUDebugger cpu;

	std::ifstream rom("official_only.nes");
	/*Skip the NES header, which is 16 bytes long,
	and starts that the beginning of the ROM*/
	cpu.getMem().loadState(rom, 0x8000, 0x0010);
	cpu.jump(0xEA71);
	
	cpu.getMem()[0x6000] = 0x80;
	for (uint64_t i = 0; cpu.getMem()[0x6000] >= 0x80; i++) {
		std::cout << cpu;
		std::cout << "Status code: " << std::hex << (int) cpu.getMem()[0x6000] <<
		"\nInstruction number " << i;

		cpu.executeCycle();
	}
} 