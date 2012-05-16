For setting up avrdude to program the SWARM bots

Install most recent version of avrdude.
COPY, don't drag, the "pocketprog-driver" somewhere onto your computer.
COPY, don't drag, "avrdude.conf" and "avrdude.exe" into your avr bin folder, default it would be somewhere
 like C:\WinAVR-20100110\bin by default.
Open up command prompt, go to where the Makefile is, currently in Dropbox/Code/ as of 5-16-12.
Type "make program"

Should be able to program board.