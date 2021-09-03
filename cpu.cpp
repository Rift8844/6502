#include <iostream>
#include <fstream>
#include "cpu.h"
 
void CPU::initialize() {
	constexpr std::size_t memSize = 65536;

	//PC = stackEnd+1;
	/*I'm nto sure of this, but apparently NES
	uses a "reset vector", which sets the PC to
	the value at address 0XFFFC*/
	SP = 0x00;
	A =  0x00;
	X =  0x00;
	Y =  0x00;
	ST.status = 0x00;

	//Fix this shit later lol
	mem = Memory(memSize);
}

void CPU::executeCycle() {
	oldPC = PC;
	
	switch(mem[oldPC]) {
		/*Try optimizing this by making
		the accumulator in a union with the
		carry bit, so you only have to do one
		instruction!*/
		

	//LOAD OPCODES
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


	//STORE OPCODES
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


	//REGISTER TRANSFER OPCODES
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


	//STACK OPERATION OPCODES
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


	//LOGCAL OPCODES
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


	//ARITHMETIC OPCODES
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


	//INCREMENT AND DECREMENT OPCODES
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


	//SHIFT OPCODES
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
			PC += 2;
			ASL(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x1E: {
			PC += 2;
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
			LSR(AddrZPGX(mem[PC]));
		}
		case 0x4E: {
			PC += 2;
			LSR(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x5E: {
			PC += 2;
			LSR(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}

		//ROL
		case 0x2A: {
			ROL(AddrACC());
		}
		case 0x26: {
			PC++;
			ROL(AddrZPG(mem[PC]));
		}
		case 0x2E: {
			PC += 2;
			ROL(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x3E: {
			PC += 2;
			ROL(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}

		//ROL
		case 0x6A: {
			ROL(AddrACC());
		}
		case 0x66: {
			PC++;
			ROL(AddrZPG(mem[PC]));
		}
		case 0x76: {
			PC += 2;
			ROL(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x7E: {
			PC += 2;
			ROL(AddrABSX(mem[PC-1]<<8 | mem[PC]));
		}


	//JUMP AND CALL OPCODES
		//JMP
		case 0x4C: {
			PC += 2;
			JMP(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}
		case 0x6C: {
			PC += 2;
			JMP(AddrIND(mem[PC-1]<<8 | mem[PC]));
		}

		//JSR
		case 0x20: {
			PC += 2;
			JSR(AddrABS(mem[PC-1]<<8 | mem[PC]));
		}

		//RTS
		case 0x60: {
			RTS(AddrIMP());
		}


	//BRANCH OPCODES
		//BCC
		case 0x90: {
			PC++;
			BCC(AddrREL(mem[PC]));
		}

		//BCS
		case 0xB0: {
			PC++;
			BCS(AddrREL(mem[PC]));
		}

		//BEQ
		case 0xF0: {
			PC++;
			BEQ(AddrREL(mem[PC]));
		}

		//BMI
		case 0x30: {
			PC++;
			BMI(AddrREL(mem[PC]));
		}

		//BNE
		case 0xD0: {
			PC++;
			BNE(AddrREL(mem[PC]));
		}

		//BPL
		case 0x10: {
			PC++;
			BCS(AddrREL(mem[PC]));
		}

		//BVC
		case 0x50: {
			PC++;
			BCS(AddrREL(mem[PC]));
		}

		//BVS
		case 0x70: {
			PC++;
			BVS(AddrREL(mem[PC]));
		}

	//STATUS FLAG OPCODES
		//CLC
		case 0x18: {
			CLC(AddrIMP());
		}

		//CLD
		case 0xD8: {
			CLD(AddrIMP());
		}

		//CLI
		case 0x58: {
			CLI(AddrIMP());
		}

		//CLV
		case 0xB8: {
			CLV(AddrIMP());
		}

		//SEC
		case 0x38: {
			SEC(AddrIMP());
		}

		//SED
		case 0xF8: {
			SED(AddrIMP());
		}

		//SEI
		case 0x78: {
			SEI(AddrIMP());
		}


	//SYSTEM FUNCTION OPCODES
		//BRK
		case 0x00: {
			BRK(AddrIMP());
		}

		//NOP
		case 0xEA: {
			NOP(AddrIMP());
		}

		//RTI
		case 0x40: {
			RTI(AddrIMP());
		}
	}

	PC++;
}





/*void CPU::updateST(uint8_t reg, uint8_t flags) {  

	if (flags&0x01)
		ST.negative = reg&0x80;

	//Can't implement overflow flag
	//if (flags&0x02)

	if (flags&0x10)

}*/
