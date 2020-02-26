/*
 *
 * Ti cc2652rb launchpad
 *
 */
#ifndef io_board_H_
#define io_board_H_
#include <io_cpu.h>

#ifdef IMPLEMENT_IO_BOARD
void
add_io_implementation_board_methods (io_implementation_t *io_i) {
	add_io_implementation_cpu_methods (io_i);
}
#endif /* IMPLEMENT_IO_BOARD */
#endif
