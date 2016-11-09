# stm32f103_locm3

sample source codes for STM32F103VCT6 board.

* board    : STM32F103VCT6 board.
* language : c
* compiler : gcc (arm-none-eabi-gcc)
* lib      : libopencorem3

# connectors

P1 UART (molex PicoBlade compatible connector 1.25mm pitch)

|pin| description  |
|:-:|:--|
| 1 | PA2 UART2 RX |
| 2 | PA3 UART2 TX |
| 3 | 3.3V         |
| 4 | GND          |

P2 SPI (molex PicoBlade compatible connector 1.25mm pitch)

|pin| description  |
|:-:|:--|
| 1 | PA4 SPI CS   |
| 2 | PA5 SPI CLK  |
| 3 | PA6 SPI MISO |
| 4 | PA7 SPI MOSI |

P3 SDCARD (MicroSD)

|pin| description |
|:-:|:--|
| 1 | PC10 DATA2  |
| 2 | PC11 DATA3  |
| 3 | PD2  CMD    |
| 4 | 3.3V        |
| 5 | PC12 CLK    |
| 6 | GND         |
| 7 | PC8  DATA0  |
| 8 | PC9  DATA1  |
| 9 | -           |

P4 LCD (2.54mm pin header)

T.B.D.

P5 SWD  (molex PicoBlade compatible connector 1.25mm pitch)

|pin| description |
|:-:|:--|
| 1 | PA14 SWC    |
| 2 | GND         |
| 3 | PA13 SWD    |
| 4 | 5V          |

