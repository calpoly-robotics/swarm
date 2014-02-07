#include "irTest.h"
#include "../Drivers/ir.h"
#include "../Drivers/serial.h"

// #define TRANSMIT

Task* testTask;

void initIRTestTask() {
	testTask = addTask(runIRTest);
 	(*testTask).interval = 1000;
}

void runIRTest() {
#ifdef TRANSMIT
	sendMessage(0,WHOS_THERE,69);
#else
	Message msg;
	if (!readMessage(&msg))
		uartPrintf("Type:%u\tData:%u\n",msg.msg,msg.data);
#endif
	// else
		// uartPrintf(BYTETOBINARYPATTERN"\tTCNT1:%.6u\tOCR1A:%.6u\r",BYTETOBINARY(TIMSK1), TCNT1,OCR1A);
		// uartPrintf(BYTETOBINARYPATTERN "\r", BYTETOBINARY(TIMSK1));
	// 	uartPrintf("%d\r",getRecvBufCount());
}