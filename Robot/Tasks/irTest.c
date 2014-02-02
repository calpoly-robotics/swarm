#include "irTest.h"
#include "../Drivers/ir.h"
#include "../Drivers/serial.h"

Task* testTask;

void initIRTestTask() {
	testTask = addTask(runIRTest);
 	(*testTask).interval = 100;
}

void runIRTest() {
	// sendMessage(0,WHOS_THERE,69);
	Message msg;
	if (!readMessage(&msg))
		uartPrintf("Type:%u\tData:%u\n",msg.msg,msg.data);
	// else
	// 	uartPrintf(BYTETOBINARYPATTERN "\n", BYTETOBINARY(PINC));
	// 	uartPrintf("%d\r",getRecvBufCount());
}