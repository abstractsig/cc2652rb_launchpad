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
 *               |DIO10  4 27      |                    |      34 14 DIO8 |
 *               |DIO21  3 28      |                    |      33 13 DIO13|
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

void    initialise_io_board (io_t*);

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


#if 0
// see drivers
void CC2652RB_LAUNCHXL_sendExtFlashByte(PIN_Handle pinHandle, uint8_t byte)
{
    uint8_t i;

    /* SPI Flash CS */
    PIN_setOutputValue(pinHandle, IOID_20, 0);

    for (i = 0; i < 8; i++) {
        PIN_setOutputValue(pinHandle, IOID_10, 0);  /* SPI Flash CLK */

        /* SPI Flash MOSI */
        PIN_setOutputValue(pinHandle, IOID_9, (byte >> (7 - i)) & 0x01);
        PIN_setOutputValue(pinHandle, IOID_10, 1);  /* SPI Flash CLK */

        /*
         * Waste a few cycles to keep the CLK high for at
         * least 45% of the period.
         * 3 cycles per loop: 8 loops @ 48 Mhz = 0.5 us.
         */
        CPUdelay(8);
    }

    PIN_setOutputValue(pinHandle, IOID_10, 0);  /* CLK */
    PIN_setOutputValue(pinHandle, IOID_20, 1);  /* CS */

    /*
     * Keep CS high at least 40 us
     * 3 cycles per loop: 700 loops @ 48 Mhz ~= 44 us
     */
    CPUdelay(700);
}

void CC2652RB_LAUNCHXL_wakeUpExtFlash(void)
{
    PIN_Config extFlashPinTable[] = {
        /* SPI Flash CS */
        IOID_20 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL |
                PIN_INPUT_DIS | PIN_DRVSTR_MED,
        PIN_TERMINATE
    };
    PIN_State extFlashPinState;
    PIN_Handle extFlashPinHandle = PIN_open(&extFlashPinState, extFlashPinTable);

    /*
     *  To wake up we need to toggle the chip select at
     *  least 20 ns and ten wait at least 35 us.
     */

    /* Toggle chip select for ~20ns to wake ext. flash */
    PIN_setOutputValue(extFlashPinHandle, IOID_20, 0);
    /* 3 cycles per loop: 1 loop @ 48 Mhz ~= 62 ns */
    CPUdelay(1);
    PIN_setOutputValue(extFlashPinHandle, IOID_20, 1);
    /* 3 cycles per loop: 560 loops @ 48 Mhz ~= 35 us */
    CPUdelay(560);

    PIN_close(extFlashPinHandle);
}


void CC2652RB_LAUNCHXL_shutDownExtFlash(void)
{
    /*
     *  To be sure we are putting the flash into sleep and not waking it,
     *  we first have to make a wake up call
     */
    CC2652RB_LAUNCHXL_wakeUpExtFlash();

    PIN_Config extFlashPinTable[] = {
        /* SPI Flash CS*/
        IOID_20 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL |
                PIN_INPUT_DIS | PIN_DRVSTR_MED,
        /* SPI Flash CLK */
        IOID_10 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL |
                PIN_INPUT_DIS | PIN_DRVSTR_MED,
        /* SPI Flash MOSI */
        IOID_9 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL |
                PIN_INPUT_DIS | PIN_DRVSTR_MED,
        /* SPI Flash MISO */
        IOID_8 | PIN_INPUT_EN | PIN_PULLDOWN,
        PIN_TERMINATE
    };
    PIN_State extFlashPinState;
    PIN_Handle extFlashPinHandle = PIN_open(&extFlashPinState, extFlashPinTable);

    uint8_t extFlashShutdown = 0xB9;

    CC2652RB_LAUNCHXL_sendExtFlashByte(extFlashPinHandle, extFlashShutdown);

    PIN_close(extFlashPinHandle);
}
#endif

#endif /* IMPLEMENT_IO_BOARD */
#endif
