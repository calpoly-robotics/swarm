#include "irTest.h"
#include "../Drivers/ir.h"
#include "../Drivers/serial.h"

#define TRANSMIT

Task* testTask;
Message msg;

void initIRTestTask() {
	testTask = addTask(runIRTest);
#ifdef TRANSMIT
 	(*testTask).interval = 20000;
#else
 	(*testTask).interval = 19000;
#endif
}

void runIRTest() {
	// uartPrintDebug(4);
#ifdef TRANSMIT
	sendMessage(0,WHOS_THERE,69);
	sbi(PINA,1);
#else
	if (!readMessage(&msg));
		// uartPrintf("Type:%.3u\tData:%u\n",msg.msg,msg.data);
#endif
	// else
		// uartPrintf(BYTETOBINARYPATTERN"\tTCNT1:%.6u\tOCR1A:%.6u\r",BYTETOBINARY(TIMSK1), TCNT1,OCR1A);
		// uartPrintf(BYTETOBINARYPATTERN "\r", BYTETOBINARY(TIMSK1));
	// 	uartPrintf("%d\r",getRecvBufCount());
}