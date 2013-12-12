#ifndef ADC_H_
#define ADC_H_

#include "../globals.h"

void initADC();

// in millivolts
u16 readADC(u08 pin);

#endif /* ADC_H_ */