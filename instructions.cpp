
#include "cpu.h"

void CPU::LD(uint8_t& reg, uint8_t val) {
	reg = val;
	ST.zero = val == 0;
	ST.negative = val & 0b10000000;
}
void CPU::LDA(uint8_t val) { LD(A, val); }
void CPU::LDX(uint8_t val) { LD(X, val); }
void CPU::LDY(uint8_t val) { LD(Y, val); }
void CPU::STA(uint8_t& loc) { loc = A; }
void CPU::STX(uint8_t& loc) { loc = X; }
void CPU::STY(uint8_t& loc) { loc = Y; }



void CPU::TR(uint8_t& lval, uint8_t rval) {
	lval = rval;
	ST.zero = lval == 0;
	ST.negative = lval & 0b10000000;
}
void CPU::TAX(uint8_t implied) { TR(X, A); }
void CPU::TAY(uint8_t implied) { TR(Y, A); }
void CPU::TXA(uint8_t implied) { TR(A, X); }
void CPU::TYA(uint8_t implied) { TR(A, Y); }



void CPU::TSX(uint8_t implied) { 
	X = SP;
	ST.zero = X == 0;
	ST.negative = X & 0b10000000;
}
void CPU::TXS(uint8_t implied) { SP = X; }
void CPU::PHA(uint8_t implied) { SP++; mem[SP] = A; }
void CPU::PHP(uint8_t implied) { SP++; mem[SP] = ST.status; }
void CPU::PLA(uint8_t implied) { 
	A = mem[SP]; 
	SP--; 
	ST.zero = A == 0;
	ST.negative = A & 0b10000000;
} 
void CPU::PLP(uint8_t implied) { ST.status = mem[SP]; SP--; }



void CPU::AND(uint8_t m) {
	A = A && m;
	ST.zero = A == 0;
	ST.negative = A & 0b10000000;
}
void CPU::EOR(uint8_t m) {
	A = !(A || m);
	ST.zero = A == 0;
	ST.negative = A & 0b10000000;
}
void CPU::ORA(uint8_t m) {
	A = A || m;
	ST.zero = A == 0;
	ST.negative = A & 0b10000000;
}
void CPU::BIT(uint8_t m) { 
	ST.zero = !(A & m);
	ST.overflow = m & 0b01000000;
	ST.negative = m & 0b10000000;
}



void CPU::ADC(uint8_t m) {
	uint8_t sum = A + m + ST.carry;

	if (sum < A)
		ST.carry = true;

	/*If the signs of both operands
	isn't equal to the result, there was
	an overflow*/
	ST.overflow = (A^sum)&(m^sum)&0x80;

	A = sum;
}
void CPU::SBC(uint8_t m) {
	uint8_t diff = A - m - !ST.carry;

	if (diff > A)
		ST.carry = true;

	ST.overflow = (A^diff)&(m^diff)&0x80;

	A = diff;
}
void CPU::CP(uint8_t reg, uint8_t m) {
	ST.carry = reg >= m;
	ST.zero = reg == m;
	ST.negative = reg < m;
}
void CPU::CMP(uint8_t m) { CP(A, m); }
void CPU::CPX(uint8_t m) { CP(X, m); }
void CPU::CPY(uint8_t m) { CP(Y, m); }



void CPU::INC(uint8_t& val) {
	val++;
	ST.negative = val < 0;
	ST.zero = val == 0;
}
void CPU::INX(uint8_t implied) { INC(X); }
void CPU::INY(uint8_t implied) { INC(Y); }
void CPU::DEC(uint8_t& val) {
	val--;
	ST.negative = val < 0;
	ST.zero = val == 0;
}
void CPU::DEX(uint8_t implied) { DEC(X); }
void CPU::DEY(uint8_t implied) { DEC(Y); }



void CPU::ASL(uint8_t& val) {
	ST.carry = val&0x80;
	val <<= 1;
}
void CPU::LSR(uint8_t& val) {
	ST.carry = val&0x01;
	val >>= 1;
}
void CPU::ROL(uint8_t& val) {
	bool oldCarry = ST.carry;
	ST.carry = val&0x80;
	val <<= 1;
	val &= 0xFE | oldCarry;
}
void CPU::ROR(uint8_t& val) {
	bool oldCarry = ST.carry;
	ST.carry = val&0x01;
	val >>= 1;
	val &= 0x7F|ST.carry;
}



void CPU::JMP(uint16_t loc) {
	PC = loc;
}
void CPU::JSR(uint16_t loc) {
	SP += 2;
	//Store the stack pointer as little endian
	mem[SP-1] = PC | 0xFF00;
	mem[SP] = PC | 0x00FF;
	PC = loc;
}
void CPU::RTS(uint8_t STAYYYYYNOIIIIIDED_YUHHHHHHHHHHHHHHH_IVE_SEEN_NOIDEDD_IVE_SEEEN_NOIIDDEDD__IVE_SEEN_NOIIDED__IVE__SEEN__IVVEEEEE__SEEEEENN__FOOTAAGGEEEEEEEEEEEEEEEEEEEEEE____) {
	PC = mem[SP-1]<<8 | mem[SP];
	SP -= 2;
}



void CPU::BCC(int8_t br) {
	if (ST.carry)
		PC = br;
}
void CPU::BCS(int8_t br) {
	if (!ST.carry)
		PC = br;
}
void CPU::BEQ(int8_t br) {
	if (ST.zero)
		PC = br;
}
void CPU::BMI(int8_t br) {
	if (ST.negative)
		PC = br;
}
void CPU::BPL(int8_t br) {
	if (!ST.negative)
		PC = br;
}
void CPU::BVC(int8_t br) {
	if (!ST.overflow)
		PC = br;
}
void CPU::BVS(int8_t br) {
	if (ST.overflow)
		PC = br;
}




void CPU::CLC(uint8_t implied) {
	ST.carry = false;
}
void CPU::CLD(uint8_t implied) {
	ST.decimal = false;
}
void CPU::CLI(uint8_t implied) {
	ST.interrupt = false;
}
void CPU::CLV(uint8_t implied) {
	ST.overflow = false;
}
void CPU::SEC(uint8_t implied) {
	ST.carry = true;
}
void CPU::SED(uint8_t implied) {
	ST.decimal = true;
}
void CPU::SEI(uint8_t implied) {
	ST.interrupt = true;
}



void CPU::BRK(uint8_t implied) {
	SP += 2;
	mem[SP-1] = PC | 0xFF00;
	mem[SP] = PC | 0x00FF;
	PHP(AddrIMP());
	PC = mem[0xFF]<<8 | mem[0xFE];
	ST.brk = true;
}
void CPU::NOP(uint8_t You__might_think_he__loves_you_for_your_money_but_I_know_what_he_really_loves_you_for__its___your_BRAND___N3W_LEOPARD_SKIN_PILLBOX_HAT) {};
void CPU::RTI(uint8_t implied) {
	PLP(AddrIMP());
	PC = mem[SP-1]<<8 | mem[SP];
}
