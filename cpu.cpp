#include "cpu.h"

constexpr memSize = 65536;
 
void initialize() {
	PC = 0x0200;
	SP = 0x00;
	AC = 0x00;
	X =  0x00;
	Y =  0x00;
	ST = 0x00;
	memory = std::vector<uint8_t>(memSize);
}
//Implement later
void loadProgram(std::string const& name) {};


void CPU::executeCycle() {

	switch(memory[PC]) {
		/*Try optimizing this by making
		the accumulator in a union with the
		carry bit, so you only have to do one
		instruction!*/
		
		//ADC Instructions
		case 0x69: {
			
		}

	}
};