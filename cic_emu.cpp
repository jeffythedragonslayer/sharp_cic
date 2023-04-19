#include <iostream>
#include "cic.h"
using namespace std;

void test_poly()
{
	cout << hex;
	CIC cic;

	cic.pc = 0;

	while (true) {
		cic.poly_inc();
		int pc = cic.pc;
		cout << pc << '\n'; 
	}
}

int main()
{
	CIC lock, key;

	lock.console = true;
	key.console = false;
}
