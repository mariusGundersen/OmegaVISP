# OmegaVISP

[![](https://raw.githubusercontent.com/mariusGundersen/OmegaVISP/master/docs/OmegaVISP-thumb.jpg)](https://github.com/mariusGundersen/OmegaVISP/blob/master/docs/OmegaVISP.jpg)

## Features

The OmegaVISP has the following features:

 * Connect to AVRstudio 4
 * Enter and leave programming mode
 * Read signature
 * Read fuses
 * Write fuses
 * Read flash
 * Write flash
 * Read lockbits
 * Write lockbits
 * Read eeprom
 * Write eeprom
 * Erase chip
 * Calibrate RC-Oscillator
 * Set ISP-frequency

### Unsupported Features

The following features have yet to be implemented:

 * Connect to AVRDude
 * Firmware upgrade via bootloader

### Supported Devices

Theoretically, it should work on all ATtiny and ATmega AVR devices. It has been tested on the following devices:

 * ATmega168, ATmega88, ATmega48
 * ATmega128
 * ATmega32

## Bill of Materials
The following list contains the bill of materials for the OmegaVISP. Each component has a link to the product page at [Farnell](http://no.farnell.com). 

 * U1: [CP2102](http://no.farnell.com/silicon-laboratories/cp2102-gm/usb-to-uart-bridge-3-6v-mlp-28/dp/9282130) USB - UART
 * U2: [Atmega168](http://no.farnell.com/atmel/atmega168-20au/8bit-16k-flash-mcu-tqfp32-168/dp/9171193) Microcontroller
 * J1: [MC32604](http://no.farnell.com/multicomp/mc32604/plug-usb-r-a-type-a-smt/dp/1696545) USB plug
 * ISP + Uart: [Header 2 row](http://no.farnell.com/harwin/m20-9980546/header-2row-5way/dp/1022236) 3x2 + 2x2 Header
 * X1: [3.6864Mhz](http://no.farnell.com/abracon/abls-3-6864mhz-b2-t/crystal-3-6864mhz-18pf-smd/dp/7940609) Crystal
 * Power, Status: [1206 LED](http://no.farnell.com/kingbright/kp-3216ec/led-smd-1206-red/dp/8530025) LED
 * R1: [10k 0805](http://no.farnell.com/bourns/cr0805-fx-1002elf/resistor-0805-10kr-1/dp/1612522) Resistor
 * R2, R3: [330R 0805](http://no.farnell.com/vishay-draloric/crcw0805330rfkea/resistor-0805-330r-1/dp/1469918) Resistor
 * C1: [0.1uF 0805](http://no.farnell.com/avx/08053c104kat2a/capacitor-mlcc-0805-25v-100nf/dp/1740665) Capacitor
 * C2: [1uF 0805](http://no.farnell.com/kemet/c0805c105z4vactu/capacitor-0805-1uf-16v/dp/9227806) Capacitor
 * C3, C4: [18pF 1206](http://no.farnell.com/kemet/c1206c180j5gactu/capacitor-ceramic-multilayer/dp/1650895) Capacitor
 * RX, TX: [2.54mm 2 pin](http://no.farnell.com/fischer-elektronik/cab-4-gs/jumper-2-54mm-black/dp/9728970) Jumper
 * 
Total cost for 1 is '''NOK 94.65''', 10 is '''NOK 63.84''' (not including shipping and VAT)

## PCB
The PCB can be bought from [batchPCB](http://batchpcb.com/index.php/Products/46076). The price per board is '''USD 2.72''' (not including shipping).

## Firmware
The latest compiled firmware can be downloaded from [firmware/default/OmegaVISP.hex](https://raw.githubusercontent.com/mariusGundersen/OmegaVISP/master/firmware/default/OmegaVISP.hex). 

## Drivers
The USB - UART controller requires a driver to be installed on MIcrosoft Windows computers, which can be found in the software folder of the repository or downloaded from the [Silicon Labs homepage](http://www.silabs.com/products/mcu/pages/usbtouartbridgevcpdrivers.aspx). Linux systems seem to recognize the device without drivers.
