#include "cic.h"
#include <utility>
using namespace std;

uint8_t CIC::hl()
{
	return 0;
}

void CIC::op00() // nop - no operation
{
}

void CIC::op41() // xchg - exchange A <--> RAM[HL]
{
	swap(a, ram[hl()]);
}

void CIC::op42() // xchgsk - exchange A <--> RAM[HL]
{
	swap(a, ram[hl()]);
	++l;
	if ( /* result > 0Fh */ true) skip();
}

void CIC::op43() // xchgsk - exchange A <--> RAM[HL]
{
	swap(a, ram[hl()]);
	--l;
	if ( /* result < 00h */ true) skip();
}

void CIC::op44() // neg - negate A
{
	a = -a;
}

void CIC::op46() // out - output
{
	ports[l] = a;
}

void CIC::op47() // out - output
{
	ports[l] = 0;
}

void CIC::op48() // set - set carry
{
	c = true;
}

void CIC::op49() // clr - clear carry
{
	c = false;
}

void CIC::op4C() // ret - return
{
	// return
	// pop pc from stack
}

void CIC::op4D() // retsk
{
	// return
	// pop pc from stack
	skip();
}

void CIC::op54() // not - complement
{
	a ^= 0x0F;
}

void CIC::op55()
{
	a = ports[l];
}

void CIC::op57() // xchg - exchange A <--> L
{ 
	swap(a, l);
}

void CIC::op5C() // mov - set X=A
{ 
	x = a;
}

void CIC::op5D() // xchg - exchange X <--> A
{
	swap(x, a);
}

void CIC::op5E() // ???
{
	// special mystery instruction	
}

void CIC::op70() // add
{
	a += ram[hl()];
} 

void CIC::op71() // addsk 
{
}

void CIC::op72() // adc - add with carry
{
	a += ram[hl()] + c;
}

void CIC::op73() // adcsk - add with carry
{
}

void CIC::op78() // jmp - long jump
{ 
}

void CIC::op7C() // call - long call
{
	// push pc+2
	// pc=nmm
}

void CIC::op80() // jmp - short jump
{
	pc = pc & 0x380; // + nn
}

void CIC::reset()
{
	bank = 0;
	pc   = 0x00;
}

void CIC::skip()
{
	++pc;
}

void CIC::poly_inc()
{
	bool bit0 = pc & 0x01;
	bool bit1 = pc & 0x02;
	bool bits01_comb = bit0 ^ bit1;
	bits01_comb = !bits01_comb;

	pc = (pc & 0x380) + (bits01_comb * 0x40) + (pc & 0x7E) / 2;
}
