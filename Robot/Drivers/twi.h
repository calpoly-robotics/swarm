#ifndef TWI_H_
#define TWI_H_

void twiInit();

void twiStart();
void twiStop();

void twiWrite(u08 data);
u08 twiRead(u08 ack=0);

#endif