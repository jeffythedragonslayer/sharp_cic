#pragma once
#include <cstdint>

struct CIC
{ 
	uint8_t a; // 4-bit accumulator
	uint8_t x; // 4-bit general purpose register

	// 6-bit HL
	uint8_t l; // 4-bit pointer register
	uint8_t h; // 2-bit pointer register

	uint8_t hl();
	
	bool c;	// carry flag

	// 10-bit program counter
	uint8_t bank; // 3-bit program counter bank
	uint8_t pc;   // 7-bit polynomial counter

	uint8_t rom[512];
	uint8_t ram[32]; // 32x4bit
	uint16_t stack[4]; // 4x10bit
	uint16_t ports[4]; // 4x4bit

	uint32_t timer;
	bool console; // true when this is the console CIC, false when this is the cart CIC

	bool noswap;

	int data_rx_error;

	bool nes_6113_in_console;
	int P0;
	int P1;

	int seed_start, data_start;

	// opcodes
	void op00(); // nop
	void op40(); // mov
	void op41(); // xchg
	void op42(); // xchgsk
	void op43(); // xchgsk
	void op44(); // neg
	void op45(); // ???
	void op46(); // out
	void op47(); // out
	void op48(); // set
	void op49(); // clr
	void op4B(); // ?
	void op4C(); // ret
	void op4D(); // retsk
	void op54(); // not
	void op55(); // in
	void op56(); // ?
	void op57(); // xchg
	void op5C(); // mov
	void op5D(); // xchg
	void op5E(); // ???
	void op5F();
	void op70(); // add
	void op71(); // addsk
	void op72(); // adc
	void op73(); // adcsk
	void op74(); // mov
	void op75(); // mov
	void op76(); // mov
	void op77(); // mov 
	void op78(); // jmp
	void op7C(); // call
	void op80(); // jmp

	void reset();
	void skip();
	void poly_inc();

	void push();
	void pop();

	void main();
	void shutdown();

	void init_first();
	void init_timing();
	void random_seed();
	void init_streams();

	void mangle(uint8_t buf[]);

	void wait(int timer);
};
