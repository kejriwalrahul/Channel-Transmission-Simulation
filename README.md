# Channel-Transmission-Simulation

This project simulates channel transmission by first Huffman coding the I/P file, channel coding the source coded file and transmitting over UDP protocol. At the receiver, it checks CRC and requests retransmission if received incorrectly. We test this using different bit error probabilities. After complete reception, it decodes the message to get back the original I/P file.   

##Usage
1. `make` for running program
2. `make` in include dir for making xmission code
3. `make server` to start receiver
4. `make client` to start client
5. Terminate server after xmission
6. `make decode` to decode received file

Note: `make debug` to go to debug mode
