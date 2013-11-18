swarm
=====

The base will, every so often, poll every address on the bus to see who is there.
We may have it restrict to a smaller number of addresses for increased efficiency
The base will then, device by device, ask them if they have any data to offload.

TODO:
	MX25L25635EZNI-12G
	UART with base station
	base station test code
	Buzzer
	Ledtask
		blink specific led
		on for duration
	Battery task
		when voltage is <3.4V full sleep. wake every few minutes
		when voltage is <3.6V sleep. Wake every minute and be annoying
	Just ensure all hardware has code