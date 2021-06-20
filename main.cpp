
#include <iostream>
#include <fstream>
#include "cpu.h"

int main() {
	CPU cpu;
	std::ifstream testRom("test.rom");
	cpu.mem.loadState(testRom);

	
	for (int i = 0; i < 26; i++)
		std::cout << cpu.mem[i];
}