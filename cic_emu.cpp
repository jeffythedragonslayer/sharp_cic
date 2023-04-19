#include <iostream>
#include "cic.h"
using namespace std;

int main()
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