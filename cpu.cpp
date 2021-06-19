#include <iostream>
#include "cpu.h"
 
void CPU::initialize() {
	constexpr std::size_t memSize = 65536;

	PC = stackEnd+1;
	SP = 0x00;
	A =  0x00;
	X =  0x00;
	Y =  0x00;
	ST.status = 0x00;

	//Fix this shit later lol
	mem = Memory(memSize);
}

//Implement later
void CPU::loadProgram(std::string const& name) {};


void CPU::executeCycle() {
	switch(mem[PC]) {
		/*Try optimizing this by making
		the accumulator in a union with the
		carry bit, so you only have to do one
		instruction!*/
		

	//LOAD INSTRUCTIONS
		//LDA
		case 0xA9: {
			PC++;
			LDA(AddrIMD(mem[PC]));
		}
		case 0xA5: {
			PC++;
			LDA(AddrZPG(mem[PC]));
		}
		case 0xB5: {
			PC++;
			LDA(AddrZPGX(mem[PC]));
		}
		case 0xAD: {
			PC += 2;
			//Endianness is handled by addressing modes
			LDA(AddrABS((mem[PC]-1)<<8 | mem[PC]));
		}
		case 0xBD: {
			LDA(AddrABSX(mem[PC]));
		}
		case 0xB9: {
			LDA(AddrABSY(mem[PC]));
		}
		case 0xA1: {
			LDA(AddrXIND(mem[PC]));
		}
		case 0xB1: {
			PC++;
			LDA(AddrINDY(mem[PC]));
		}


		//LDX
		case 0xA2: {
			PC++;
			LDX(AddrIMD(mem[PC]));
		}
		case 0xA6: {
			PC++;
			LDX(AddrZPG(mem[PC]));
		}
		case 0xB6: {
			PC++;
			LDX(AddrZPGY(mem[PC]));
		}
		case 0xAE: {
			PC += 2;
			//Endianness is handled by addressing modes
			LDX(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0xBE: {
			PC++;
			LDX(AddrABSY(mem[PC]));
		}

		//LDY
		case 0xA0: {
			PC++;
			LDY(AddrIMD(mem[PC]));
		}
		case 0xA4: {
			PC++;
			LDY(AddrZPG(mem[PC]));
		}
		case 0xB4: {
			PC++;
			LDY(AddrZPGX(mem[PC]));
		}
		case 0xAC: {
			PC += 2;
			//Endianness is handled by addressing modes
			LDY(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0xBC: {
			PC++;
			LDY(AddrABSX(mem[PC]));
		}


	//STORE INSTRUCTIONS
		//STA
		case 0x85: {
			PC++;
			STA(AddrZPG(mem[PC]));
		}
		case 0x95: {
			PC++;
			STA(AddrZPGX(mem[PC]));
		}
		case 0x8D: {
			PC += 2;
			STA(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x9D: {
			PC++;
			STA(AddrABSX(mem[PC]));
		}
		case 0x99: {
			PC++;
			STA(AddrABSY(mem[PC]));
		}
		case 0x81: {
			PC++;
			STA(AddrXIND(mem[PC]));
		}
		case 0x91: {
			PC++;
			STA(AddrINDY(mem[PC]));
		}

		//STX
		case 0x86: {
			PC++;
			STX(AddrZPG(mem[PC]));
		}
		case 0x96: {
			PC++;
			STX(AddrZPGY(mem[PC]));
		}
		case 0x8E: {
			PC += 2;
			STX(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}

		//STY
		case 0x84: {
			PC++;
			STX(AddrZPG(mem[PC]));
		}
		case 0x94: {
			PC++;
			STX(AddrZPGX(mem[PC]));
		}
		case 0x8C: {
			PC += 2;
			STX(AddrABS(mem[PC-1]<<8 |  mem[PC]));
		}


	//REGISTER TRANSFER INSTRUCTIONS
		//TAX
		case 0xAA: {
			TAX(AddrIMP());
		}

		//TAY
		case 0xA8: {
			TAY(AddrIMP());
		}

		//TSX
		case 0xBA: {
			TSX(AddrIMP());
		}

		//TXA
		case 0x8A: {
			TXA(AddrIMP());
		}

		//TXS
		case 0x9A: {
			TXS(AddrIMP());
		}

		//TYA
		case 0x98: {
			TYA(AddrIMP());
		}
	}
};

void CPU::testFunction() {

}




/*void CPU::updateST(uint8_t reg, uint8_t flags) {  

	if (flags&0x01)
		ST.negative = reg&0x80;

	//Can't implement overflow flag
	//if (flags&0x02)

	if (flags&0x10)

}*/
//INSTRUCTIONS
