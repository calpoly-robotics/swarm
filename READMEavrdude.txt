For setting up avrdude to program the SWARM bots

Make sure you have all the stuff for the Xiphos board installed & setup.
Install most recent version of avrdude, ie WinAVR-20100110-install.exe.
COPY, don't drag, the "pocketprog-driver" somewhere onto your computer.
COPY, don't drag, "avrdude.conf" and "avrdude.exe" into your avr bin folder, default it would be somewhere
 like C:\WinAVR-20100110\bin by default.
Open up command prompt, go to where the Makefile is, currently in Dropbox/swarm/Code/ as of 8-27-12.
Type "make program"

Should be able to program board.