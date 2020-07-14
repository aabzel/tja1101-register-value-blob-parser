# tja1101-register-value-blob-parser
tja1101 binary register value blob parser (interpreter)

That is a utility tool to interpret the raw binary TJA1101 registers values blob to human readable *.txt configuration report according the TJA1101 datasheet.
As a example there are data-in and data-out for tja1101 *.txt. 
Users all over the world may appreciate that diagnostic tool and such support of TJA1101.

The TJA1101 registers values themselves must be read from TJA1101 chip via 2-wire MDIO bus to MCU RAM. 
Then binary blob must be transfered from MCU RAM to PC disc (in txt file) via UART,RS232, 100-Base-TX, Bluetooth, WiFi, CAN or any other interface.

Finaly on PC that utility can instantly interpret chip settings and reveal honest TJA1101 configuration.

That is a very handy tool for diagnostic and bug search.

