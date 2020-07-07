/*
 *
 * Ti cc2652rb launchpad
 *
 *               .-----------------.                    .-----------------.
 *               |  3V3 10 21 5V   |                    |DIO7  40 20 0V   |
 *               |DIO23  9 22 0V   |                    |DIO6  39 19 DIO12|
 *               |DIO2   8 23 DIO25|                    |DIO20 38 18 DIO11|
 *               |DIO3   7 24 DIO26|                    |DIO19 37 17      |
 *               |DIO22  6 25 DIO27|                    |DIO18 36 16      |
 *               |DIO24  5 26 DIO28|                    |      35 15 DIO9 |
 *               |DIO10  4 27 DIO29|                    |      34 14 DIO8 |
 *               |DIO21  3 28 DIO30|                    |      33 13 DIO13|
 *               |DIO4   2 29 DIO0 |                    |DIO16 32 12 DIO14|
 *               |DIO5   1 30 DIO1 |                    |DIO17 31 11 DIO15|
 *               `-----------------'                    `-----------------'
 *
 * Has:
 *
 *      MX25R8035FZUILO 8Mbit SPI flash
 *
 */
#ifndef io_board_H_
#define io_board_H_
#include <io_cpu.h>

void io_board_panic (io_t*,int);

#define SPECIALISE_IO_BOARD_IMPLEMENTATION(S) \
    SPECIALISE_IO_CPU_IMPLEMENTATION(S) \
	 .panic = io_board_panic,\
    /**/

// red LED
#define LED_1_BOARD_PIN def_cc2652_io_output_pin (\
        IOID_6,\
        IO_PIN_ACTIVE_LEVEL_HIGH,\
        IO_PIN_LEVEL_INACTIVE\
    )
#define LED_1   LED_1_BOARD_PIN.io

// green LED
#define LED_2_BOARD_PIN def_cc2652_io_output_pin (\
        IOID_7,\
        IO_PIN_ACTIVE_LEVEL_HIGH,\
        IO_PIN_LEVEL_INACTIVE\
    )
#define LED_2   LED_2_BOARD_PIN.io

// Button 1
#define BTN1_BOARD_PIN def_cc2652_io_input_pin (\
      IOID_13,\
		IO_PIN_ACTIVE_LEVEL_LOW,\
		IOC_IOPULL_UP\
  )

// Button 2
#define BTN2_BOARD_PIN def_cc2652_io_input_pin (\
      IOID_14,\
      IO_PIN_ACTIVE_LEVEL_LOW,\
		IOC_IOPULL_UP\
  )

// XDS110 UART
#define XDS110_UART_TX_DIO      IOID_3
#define XDS110_UART_RX_DIO      IOID_2

void initialise_io_board (io_t*);

#ifdef IMPLEMENT_IO_BOARD
//-----------------------------------------------------------------------------
//
// Implementation
//
//-----------------------------------------------------------------------------

void
initialise_io_board (io_t *io) {
    initialise_io_cpu (io);
}

void
io_board_panic (io_t *io,int code) {

	// blink LED

	DISABLE_INTERRUPTS;
	while (1);
}

#endif /* IMPLEMENT_IO_BOARD */
#endif
/*
Copyright 2020 Gregor Bruce

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright notice
and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
