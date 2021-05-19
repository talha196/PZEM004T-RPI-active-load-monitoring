

# RPi-based-flask-server
This repository is developed for hosting a basic server on Raspberry Pi 3 to interface serial port (UART) data on a basic web application. 
The Serial port, it's baud rate and parity check can be configured at the beginning of the .py script. 

This script parses through the UART (ttyS0) recieved packets and seperates the Voltage, Current and Power information recieved from a remote load monitoring device via Transciever module on 433Mhz band. It then publishes these results on the web application(.html file) which simply can be opened in the broswer once the python script is running and is hosting as a server. The Raspberry Pi hosts a star network topology here with it being a central node and hosting daughter nodes on different channels on the same frequency band. 

Upto 2 devices are being hosted by this proof of concept example.
