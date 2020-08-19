# Arduino_MEGA_Tester
This project started out as a way to learn about vintage DRAM chips by building an Arduino based tester. Yes, similar projects exist but part of the fun comes from learning to do it yourself.

After getting the testing of 4164 and 41256 DRAMs working someone asked about testing 4116 DRAMs which require three supply voltages and have the nasty tendency to short the rails together when they fail. This required adding some TVS diode arrays to clamp the I/O to 5V/GND and using some small encapsulated DC-DC converters also made sense.

I started with an Arduino Mega as I had one handy, adn also ported it to the Uno, Micro, and Nano. I designed a PCB around the Micro as well. After using the Mega to build an RCA 1802 tester it ocurred to me that by going back to the Mega with its numerous I/O and larger code space, that I could build a more universal tester.

So, after a 6 month hiatus on the project I picked it up again, moved back to the Mega 2560 and designed a 'Mega Tester' shield for it. The shield accepts 'PODs' which is a daughter board customized for a particular range of ICs. For example the 'DRAM Tester POD' which is for 4116, 4164, 41256 and 41464 DRAMs.
