#include "globals.h"
#include "Drivers/drivers.h"


void init() {
	initDrivers();
}

int main() {
	init();

	return 0;
}