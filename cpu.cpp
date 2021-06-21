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
			PC += 2;
			LDA(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}
		case 0xB9: {
			PC += 2;
			LDA(AddrABSY(mem[PC-1]<<8 | mem[PC]));
		}
		case 0xA1: {
			PC++;
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
			PC += 2;
			LDX(AddrABSY(mem[PC-1]<<8 | mem[PC]));
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
			PC += 2;
			LDY(AddrABSX(mem[PC-1]<<8 | mem[PC]));
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
			PC += 2;
			STA(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x99: {
			PC += 2;
			STA(AddrABSY(mem[PC-1]<<8 | mem[PC]));
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

		//TXA
		case 0x8A: {
			TXA(AddrIMP());
		}

		//TYA
		case 0x98: {
			TYA(AddrIMP());
		}


	//STACK OPERATION INSTRUCTIONS
		//TSX
		case 0xBA: {
			TSX(AddrIMP());
		}

		//TXS
		case 0x9A: {
			TXS(AddrIMP());
		}

		//PHA
		case 0x48: {
			PHA(AddrIMP());
		}

		//PHP
		case 0x08: {
			PHP(AddrIMP());
		}

		//PLA
		case 0x68: {
			PLA(AddrIMP());
		}

		//PLP
		case 0x28: {
			PLP(AddrIMP());
		}


	//LOGCAL INSTRUCTIONS
		//AND
		case 0x29: {
			PC++;
			AND(AddrIMD(mem[PC]));
		}
		case 0x25: {
			PC++;
			AND(AddrZPG(mem[PC]));
		}
		case 0x35: {
			PC++;
			AND(AddrZPGX(mem[PC]));
		}
		case 0x2D: {
			PC += 2;
			AND(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x3D: {
			PC += 2;
			AND(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x39: {
			PC += 2;
			AND(AddrABSY(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x21: {
			PC++;
			AND(AddrXIND(mem[PC]));
		}
		case 0x31: {
			AND(AddrINDY(mem[PC]));
		}
		
		//EOR
		case 0x49: {
			PC++;
			EOR(AddrIMD(mem[PC]));
		}
		case 0x45: {
			PC++;
			EOR(AddrZPG(mem[PC]));
		}
		case 0x55: {
			PC++;
			EOR(AddrZPGX(mem[PC]));
		}
		case 0x4D: {
			PC += 2;
			EOR(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x5D: {
			PC += 2;
			EOR(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x59: {
			PC += 2;
			EOR(AddrABSY(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x41: {
			PC++;
			EOR(AddrXIND(mem[PC]));
		}
		case 0x51: {
			PC++;
			EOR(AddrINDY(mem[PC]));
		}

		//ORA
		case 0x09: {
			PC++;
			ORA(AddrIMD(mem[PC]));
		}
		case 0x05: {
			PC++;
			ORA(AddrZPG(mem[PC]));
		}
		case 0x15: {
			PC++;
			ORA(AddrZPGX(mem[PC]));
		}
		case 0x0D: {
			PC += 2;
			ORA(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x1D: {
			PC += 2;
			ORA(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x19: {
			PC += 2;
			ORA(AddrABSY(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x01: {
			PC++;
			ORA(AddrXIND(mem[PC]));
		}
		case 0x11: {
			PC++;
			ORA(AddrINDY(mem[PC]));
		}

		//BIT
		case 0x24: {
			PC++;
			BIT(AddrZPG(mem[PC]));
		}
		case 0x2C: {
			PC += 2;
			BIT(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}


	//ARITHMETIC INSTRUCTIONS
		//ADC

		//69... NIIICCEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE!!!
		case 0x69: {
			PC++;
			ADC(AddrIMD(mem[PC]));
		}
		case 0x65: {
			PC++;
			ADC(AddrZPG(mem[PC]));
		}
		case 0x75: {
			PC++;
			ADC(AddrZPGX(mem[PC]));
		}
		case 0x6D: {
			PC += 2;
			ADC(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}


	//INCREMENT AND DECREMENT INSTRUCTIONS
		//INC
		case 0xE6: {
			PC++;
			INC(AddrZPG(mem[PC]));
		} 
		case 0xF6: {
			PC++;
			INC(AddrZPG(mem[PC]));
		}
		case 0xEE: {
			PC += 2;
			INC(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0xFE: {
			PC += 2;
			INC(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}

		//INX
		case 0xE8: {
			INY(AddrIMP());
		}

		//INY
		case 0xC8: {
			INY(AddrIMP());
		}

		//DEC
		case 0xC6: {
			PC++;
			DEC(AddrZPG(mem[PC]));
		}
		case 0xD6: {
			PC++;
			DEC(AddrZPGX(mem[PC]));
		}
		case 0xCE: {
			PC += 2;
			DEC(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0xDE: {
			PC += 2;
			DEC(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}

		//DEX
		case 0xCA: {
			PC++;
			DEX(AddrIMP());
		}

		//DEY
		case 0x88: {
			PC++;
			DEY(AddrIMP());
		}


	//SHIFT INSTRUCTIONS
		//ASL
		case 0x0A: {
			ASL(AddrACC());
		}
		case 0x06: {
			PC++;
			ASL(AddrZPG(mem[PC]));
		}
		case 0x16: {
			PC++;
			ASL(AddrZPGX(mem[PC]));
		}
		case 0x0E: {
			PC++;
			ASL(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x1E: {
			PC++;
			ASL(AddrABSX(mem[PC-1] | mem[PC]));
		}

		//LSR
		case 0x4A: {
			LSR(AddrACC());
		}
		case 0x46: {
			PC++;
			LSR(AddrZPG(mem[PC]));
		}
		case 0x56: {
			PC++;
			LSR(AdddrZPGX(mem[PC]));
		}
		case 0x4E: {
			PC++;
			LSR(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x5E: {
			PC++;
			LSR(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}

		//ROL
		case 0x2A: {
			ROL(AdrACC());
		}
		case 0x26: {
			PC++;
			ROL(AddrZPG(mem[PC]));
		}
		case 0x2E: {
			PC++;
			ROL(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x3E: {
			ROL(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}

		//ROL
		case 0x6A: {
			ROL(AdrACC());
		}
		case 0x66: {
			PC++;
			ROL(AddrZPG(mem[PC]));
		}
		case 0x76: {
			PC++;
			ROL(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x7E: {
			ROL(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}

		//Fuck caffeine withdrawal
	}
}

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
