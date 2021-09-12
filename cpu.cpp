#include <iostream>
#include <fstream>
#include "cpu.h"
 

constexpr uint32_t memSize = 0xFFFF;

void CPU::initialize() {

	//PC = stackEnd+1;
	/*I'm not sure of this, but apparently NES
	uses a "reset vector", which sets the PC to
	the value at address 0XFFFC*/
	SP = 0x00;
	A =  0x00;
	X =  0x00;
	Y =  0x00;
	ST.status = 0x00;
	PC = 0x00;

	//Fix this shit later lol
	//mem = Memory(memSize);
}

CPU::CPU() : mem { Memory(memSize) } {
	initialize();
}

void CPU::executeCycle() {

	switch(mem[PC]) {
		/*Try optimizing this by making
		the accumulator in a union with the
		carry bit, so you only have to do one
		instruction!*/
		
	/*ENDIANNESS NOTE:
	Endianness is handled by the opcode decodeing.
	Every three byte instruction increments the PC
	by two before it is executed, selecting the
	lo-byte. When it is passed to the addressing mode
	function, the lo-byte is shifted mem[PC] is shifted
	<< 8 to the high digit. The hi-byte is then ORd |
	to the low digit.*/

	//LOAD OPCODES
		//LDA
		case 0xA9: {
			PC++;
			LDA(AddrIMD(mem[PC]));
			break;
		}
		case 0xA5: {
			PC++;
			LDA(AddrZPG(mem[PC]));
			break;
		}
		case 0xB5: {
			PC++;
			LDA(AddrZPGX(mem[PC]));
			break;
		}
		case 0xAD: {
			PC += 2;
			LDA(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xBD: {
			PC += 2;
			LDA(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xB9: {
			PC += 2;
			LDA(AddrABSY(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xA1: {
			PC++;
			LDA(AddrXIND(mem[PC]));
			break;
		}
		case 0xB1: {
			PC++;
			LDA(AddrINDY(mem[PC]));
			break;
		}

		//LDX
		case 0xA2: {
			PC++;
			LDX(AddrIMD(mem[PC]));
			break;
		}
		case 0xA6: {
			PC++;
			LDX(AddrZPG(mem[PC]));
			break;
		}
		case 0xB6: {
			PC++;
			LDX(AddrZPGY(mem[PC]));
			break;
		}
		case 0xAE: {
			PC += 2;
			//Endianness is handled by addressing modes
			LDX(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xBE: {
			PC += 2;
			LDX(AddrABSY(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//LDY
		case 0xA0: {
			PC++;
			LDY(AddrIMD(mem[PC]));
			break;
		}
		case 0xA4: {
			PC++;
			LDY(AddrZPG(mem[PC]));
			break;
		}
		case 0xB4: {
			PC++;
			LDY(AddrZPGX(mem[PC]));
			break;
		}
		case 0xAC: {
			PC += 2;
			//Endianness is handled by addressing modes
			LDY(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xBC: {
			PC += 2;
			LDY(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}


	//STORE OPCODES
		//STA
		case 0x85: {
			PC++;
			STA(AddrZPG(mem[PC]));
			break;
		}
		case 0x95: {
			PC++;
			STA(AddrZPGX(mem[PC]));
			break;
		}
		case 0x8D: {
			PC += 2;
			STA(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x9D: {
			PC += 2;
			STA(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x99: {
			PC += 2;
			STA(AddrABSY(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x81: {
			PC++;
			STA(AddrXIND(mem[PC]));
			break;
		}
		case 0x91: {
			PC++;
			STA(AddrINDY(mem[PC]));
			break;
		}

		//STX
		case 0x86: {
			PC++;
			STX(AddrZPG(mem[PC]));
			break;
		}
		case 0x96: {
			PC++;
			STX(AddrZPGY(mem[PC]));
			break;
		}
		case 0x8E: {
			PC += 2;
			STX(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//STY
		case 0x84: {
			PC++;
			STX(AddrZPG(mem[PC]));
			break;
		}
		case 0x94: {
			PC++;
			STX(AddrZPGX(mem[PC]));
			break;
		}
		case 0x8C: {
			PC += 2;
			STX(AddrABS(mem[PC-1]<<8 |  mem[PC]));
			break;
		}


	//REGISTER TRANSFER OPCODES
		//TAX
		case 0xAA: {
			TAX(AddrIMP());
			break;
		}

		//TAY
		case 0xA8: {
			TAY(AddrIMP());
			break;
		}

		//TXA
		case 0x8A: {
			TXA(AddrIMP());
			break;
		}

		//TYA
		case 0x98: {
			TYA(AddrIMP());
			break;
		}


	//STACK OPERATION OPCODES
		//TSX
		case 0xBA: {
			TSX(AddrIMP());
			break;
		}

		//TXS
		case 0x9A: {
			TXS(AddrIMP());
			break;
		}

		//PHA
		case 0x48: {
			PHA(AddrIMP());
			break;
		}

		//PHP
		case 0x08: {
			PHP(AddrIMP());
			break;
		}

		//PLA
		case 0x68: {
			PLA(AddrIMP());
			break;
		}

		//PLP
		case 0x28: {
			PLP(AddrIMP());
			break;
		}


	//LOGCAL OPCODES
		//AND
		case 0x29: {
			PC++;
			AND(AddrIMD(mem[PC]));
			break;
		}
		case 0x25: {
			PC++;
			AND(AddrZPG(mem[PC]));
			break;
		}
		case 0x35: {
			PC++;
			AND(AddrZPGX(mem[PC]));
			break;
		}
		case 0x2D: {
			PC += 2;
			AND(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x3D: {
			PC += 2;
			AND(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x39: {
			PC += 2;
			AND(AddrABSY(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x21: {
			PC++;
			AND(AddrXIND(mem[PC]));
			break;
		}
		case 0x31: {
			AND(AddrINDY(mem[PC]));
			break;
		}
		
		//EOR
		case 0x49: {
			PC++;
			EOR(AddrIMD(mem[PC]));
			break;
		}
		case 0x45: {
			PC++;
			EOR(AddrZPG(mem[PC]));
			break;
		}
		case 0x55: {
			PC++;
			EOR(AddrZPGX(mem[PC]));
			break;
		}
		case 0x4D: {
			PC += 2;
			EOR(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x5D: {
			PC += 2;
			EOR(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x59: {
			PC += 2;
			EOR(AddrABSY(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x41: {
			PC++;
			EOR(AddrXIND(mem[PC]));
			break;
		}
		case 0x51: {
			PC++;
			EOR(AddrINDY(mem[PC]));
			break;
		}

		//ORA
		case 0x09: {
			PC++;
			ORA(AddrIMD(mem[PC]));
			break;
		}
		case 0x05: {
			PC++;
			ORA(AddrZPG(mem[PC]));
			break;
		}
		case 0x15: {
			PC++;
			ORA(AddrZPGX(mem[PC]));
			break;
		}
		case 0x0D: {
			PC += 2;
			ORA(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x1D: {
			PC += 2;
			ORA(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x19: {
			PC += 2;
			ORA(AddrABSY(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x01: {
			PC++;
			ORA(AddrXIND(mem[PC]));
			break;
		}
		case 0x11: {
			PC++;
			ORA(AddrINDY(mem[PC]));
			break;
		}

		//BIT
		case 0x24: {
			PC++;
			BIT(AddrZPG(mem[PC]));
			break;
		}
		case 0x2C: {
			PC += 2;
			BIT(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}


	//ARITHMETIC OPCODES
		//ADC

		//69... NIIICCEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE!!!
		case 0x69: {
			PC++;
			ADC(AddrIMD(mem[PC]));
			break;
		}
		case 0x65: {
			PC++;
			ADC(AddrZPG(mem[PC]));
			break;
		}
		case 0x75: {
			PC++;
			ADC(AddrZPGX(mem[PC]));
			break;
		}
		case 0x6D: {
			PC += 2;
			ADC(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x7D: {
			PC += 2;
			ADC(AddrABSX(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0x79: {
			PC += 2;
			ADC(AddrABSY(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0x61: {
			PC += 2;
			ADC(AddrXIND(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0x71: {
			PC += 2;
			ADC(AddrINDY(mem[PC]<<8 | mem[PC]));
			break;
		}

		//SBC
		case 0xE9: {
			PC++;
			SBC(AddrIMD(mem[PC]));
			break;
		}
		case 0xE5: {
			PC++;
			SBC(AddrZPG(mem[PC]));
			break;
		}
		case 0xF5: {
			PC++;
			SBC(AddrZPGX(mem[PC]));
			break;
		}
		case 0xED: {
			PC += 2;
			SBC(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xFD: {
			PC += 2;
			SBC(AddrABSX(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0xF9: {
			PC += 2;
			SBC(AddrABSY(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0xE1: {
			PC += 2;
			SBC(AddrXIND(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0xF1: {
			PC += 2;
			SBC(AddrINDY(mem[PC]<<8 | mem[PC]));
			break;
		}

		//CMP
		case 0xC9: {
			PC++;
			CMP(AddrIMD(mem[PC]));
			break;
		}
		case 0xC5: {
			PC++;
			CMP(AddrZPG(mem[PC]));
			break;
		}
		case 0xD5: {
			PC++;
			CMP(AddrZPGX(mem[PC]));
			break;
		}
		case 0xCD: {
			PC += 2;
			CMP(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xDD: {
			PC += 2;
			CMP(AddrABSX(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0xD9: {
			PC += 2;
			CMP(AddrABSY(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0xC1: {
			PC += 2;
			CMP(AddrXIND(mem[PC]<<8 | mem[PC]));
			break;
		}
		case 0xD1: {
			PC += 2;
			CMP(AddrINDY(mem[PC]<<8 | mem[PC]));
			break;
		}

		//CPX
		case 0xE0: {
			PC++;
			CPX(AddrIMD(mem[PC]));
			break;
		}
		case 0xE4: {
			PC++;
			CPX(AddrZPG(mem[PC]));
			break;
		}
		case 0xEC: {
			PC++;
			CPX(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//CPY
		case 0xC0: {
			PC++;
			CPY(AddrIMD(mem[PC]));
			break;
		}
		case 0xC4: {
			PC++;
			CPY(AddrZPG(mem[PC]));
			break;
		}
		case 0xCC: {
			PC++;
			CPY(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}



	//INCREMENT AND DECREMENT OPCODES
		//INC
		case 0xE6: {
			PC++;
			INC(AddrZPG(mem[PC]));
			break;
		} 
		case 0xF6: {
			PC++;
			INC(AddrZPG(mem[PC]));
			break;
		}
		case 0xEE: {
			PC += 2;
			INC(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xFE: {
			PC += 2;
			INC(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//INX
		case 0xE8: {
			INX(AddrIMP());
			break;
		}

		//INY
		case 0xC8: {
			INY(AddrIMP());
			break;
		}

		//DEC
		case 0xC6: {
			PC++;
			DEC(AddrZPG(mem[PC]));
			break;
		}
		case 0xD6: {
			PC++;
			DEC(AddrZPGX(mem[PC]));
			break;
		}
		case 0xCE: {
			PC += 2;
			DEC(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0xDE: {
			PC += 2;
			DEC(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//DEX
		case 0xCA: {
			DEX(AddrIMP());
			break;
		}

		//DEY
		case 0x88: {
			DEY(AddrIMP());
			break;
		}


	//SHIFT OPCODES
		//ASL
		case 0x0A: {
			ASL(AddrACC());
			break;
		}
		case 0x06: {
			PC++;
			ASL(AddrZPG(mem[PC]));
			break;
		}
		case 0x16: {
			PC++;
			ASL(AddrZPGX(mem[PC]));
			break;
		}
		case 0x0E: {
			PC += 2;
			ASL(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x1E: {
			PC += 2;
			ASL(AddrABSX(mem[PC-1] | mem[PC]));
			break;
		}

		//LSR
		case 0x4A: {
			LSR(AddrACC());
			break;
		}
		case 0x46: {
			PC++;
			LSR(AddrZPG(mem[PC]));
			break;
		}
		case 0x56: {
			PC++;
			LSR(AddrZPGX(mem[PC]));
			break;
		}
		case 0x4E: {
			PC += 2;
			LSR(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x5E: {
			PC += 2;
			LSR(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//ROL
		case 0x2A: {
			ROL(AddrACC());
			break;
		}
		case 0x26: {
			PC++;
			ROL(AddrZPG(mem[PC]));
			break;
		}
		case 0x2E: {
			PC += 2;
			ROL(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x3E: {
			PC += 2;
			ROL(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//ROL
		case 0x6A: {
			ROL(AddrACC());
			break;
		}
		case 0x66: {
			PC++;
			ROL(AddrZPG(mem[PC]));
			break;
		}
		case 0x76: {
			PC += 2;
			ROL(AddrABS(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x7E: {
			PC += 2;
			ROL(AddrABSX(mem[PC]<<8 | mem[PC-1]));
			break;
		}


	//JUMP AND CALL OPCODES
		//JMP
		case 0x4C: {
			PC += 2;
			JMP(AddrABS_16b(mem[PC]<<8 | mem[PC-1]));
			break;
		}
		case 0x6C: {
			PC += 2;
			JMP(AddrIND(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//JSR
		case 0x20: {
			PC += 2;
			JSR(AddrABS_16b(mem[PC]<<8 | mem[PC-1]));
			break;
		}

		//RTS
		case 0x60: {
			RTS(AddrIMP());
			break;
		}


	//BRANCH OPCODES
		//BCC
		/*OPTIMIZATION NOTE:
		The new branch address is calculated
		before checking if the branch will occur
		in the first place. This will probably
		not be a heavy bottleneck in performance,
		but nevertheless, it is an unnecessary
		calculation in the code. Consider changing,
		if appropriate.*/
		
		case 0x90: {
			PC++;
			BCC(AddrREL(mem[PC]));
			break;
		}

		//BCS
		case 0xB0: {
			PC++;
			BCS(AddrREL(mem[PC]));
			break;
		}

		//BEQ
		case 0xF0: {
			PC++;
			BEQ(AddrREL(mem[PC]));
			break;
		}

		//BMI
		case 0x30: {
			PC++;
			BMI(AddrREL(mem[PC]));
			break;
		}

		//BNE
		case 0xD0: {
			PC++;
			BNE(AddrREL(mem[PC]));
			break;
		}

		//BPL
		case 0x10: {
			PC++;
			BPL(AddrREL(mem[PC]));
			break;
		}

		//BVC
		case 0x50: {
			PC++;
			BCS(AddrREL(mem[PC]));
			break;
		}

		//BVS
		case 0x70: {
			PC++;
			BVS(AddrREL(mem[PC]));
			break;
		}

	//STATUS FLAG OPCODES
		//CLC
		case 0x18: {
			CLC(AddrIMP());
			break;
		}

		//CLD
		case 0xD8: {
			CLD(AddrIMP());
			break;
		}

		//CLI
		case 0x58: {
			CLI(AddrIMP());
			break;
		}

		//CLV
		case 0xB8: {
			CLV(AddrIMP());
			break;
		}

		//SEC
		case 0x38: {
			SEC(AddrIMP());
			break;
		}

		//SED
		case 0xF8: {
			SED(AddrIMP());
			break;
		}

		//SEI
		case 0x78: {
			SEI(AddrIMP());
			break;
		}


	//SYSTEM FUNCTION OPCODES
		//BRK
		case 0x00: {
			BRK(AddrIMP());
			break;
		}

		//NOP
		case 0xEA: {
			NOP(AddrIMP());
			break;
		}

		//RTI
		case 0x40: {
			RTI(AddrIMP());
			break;
		}

		default: {
			std::cerr << "Uknown opcode " << std::hex <<
			(mem[PC+1]<<8 | mem[PC]) << std::endl;
			throw std::exception();
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
