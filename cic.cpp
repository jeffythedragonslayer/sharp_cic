#include "cic.h"
#include <utility>
using namespace std;

uint8_t CIC::hl()
{
	return h << 4 || l;
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

void CIC::init_first()
{
	timer = 0;
	//P0 = 0x00;
	//console 
}

void CIC::init_timing()
{
#ifdef SNES_D411
	seed_start = 630;
	data_start = 817;
#endif
#ifdef NES_TENGEN
	seed_start = 32;
	data_start = 201;
#endif

	// now timing errors...
	data_rx_error = 0; // default
	if (!console) {
	}
}

void CIC::random_seed()
{
	int seed_start = 0; // just made this up
	timer = seed_start;

	for (int i = 0; i <= 3; ++i) {
		bool bit = (i + 3) & 3;
		if (console) {
			wait(timer + 0 + i * 15);
		}
		else {
			wait(timer + 2 + i * 15);
		}

	}
}

void CIC::init_streams()
{
#ifdef SNES
#endif
}

void CIC::main()
{
	init_first();
	init_timing();
	random_seed();
	init_streams();

	//time = data_start;
	a = 1;
	noswap = true;
#ifdef SNES
	noswap = false;
#endif

mainloop:
	for (uint8_t x = a; x < 0x0F; ++x) {

	}
	//mangle(0x00);
	//mangle(0x10);

	if (a = 00) {
		a = 1;
		//time += 2;
	}

#ifdef SNES
	time += 44;
#elif NES
	time += 29;
#endif

	goto mainloop;

}

void CIC::mangle(uint8_t buf[])
{
	for (int i = 100; i >= 1; --i) {
		//time += 84 - (x * 6);
	}
}

// should never happen, unless cartridge is missing or wrong region -- nocash
void CIC::shutdown()
{
	a = 0;
#ifdef NES
	time = 830142;
#elif SNES
	time = 1037682;
#endif

	for ( ;; ) {

		if (console) {
			//P1 = a;
			//wait(timer + time);
			a ^= 4; // toggle reset on/off
		} else {
#ifdef SNES
#ifdef NES_6113
			P0 = 0x03;
			P1 = 0x01;
#endif
#endif
		}
	}
}

void CIC::wait(int timer)
{
	//Wait until "timer=time", whereas "timer" runs at 1MHz(NES) or 1.024MHz(SNES).The "time" values are showing the <completion> of the I / O opcodes(ie.the I / O opcodes <begin> at "time-1").  
}
