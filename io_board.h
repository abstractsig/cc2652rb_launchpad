/*
 *
 * Ti cc2652rb launchpad
 *
 * Has:
 *
 *		MX25R8035FZUILO 8Mbit SPI flash
 *
 */
#ifndef io_board_H_
#define io_board_H_
#include <io_cpu.h>

// red LED
#define LED_1_BOARD_PIN def_cc2652_io_output_pin (\
		IOID_6,\
		IO_PIN_ACTIVE_LEVEL_HIGH,\
		IO_PIN_LEVEL_INACTIVE\
	)
#define LED_1	LED_1_BOARD_PIN.io

// green LED
#define LED_2_BOARD_PIN def_cc2652_io_output_pin (\
		IOID_7,\
		IO_PIN_ACTIVE_LEVEL_HIGH,\
		IO_PIN_LEVEL_INACTIVE\
	)
#define LED_2	LED_2_BOARD_PIN.io

// XDS110 UART
#define XDS110_UART_TX_DIO		IOID_3
#define XDS110_UART_RX_DIO		IOID_2


#ifdef IMPLEMENT_IO_BOARD
void
add_io_implementation_board_methods (io_implementation_t *io_i) {
	add_io_implementation_cpu_methods (io_i);
}
#endif /* IMPLEMENT_IO_BOARD */
#endif
