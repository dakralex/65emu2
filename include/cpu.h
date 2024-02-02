/**
 * cpu.h
 *
 * CPU state management and interface for emulated MOS 6502.
 */

#ifndef SFEMU2_CPU_H
#define SFEMU2_CPU_H

#include <inttypes.h>

struct CPU {
    int8_t acc;                           /* Accumulator register A */

    int8_t idx_x;                         /* Index register X */
    int8_t idx_y;                         /* Index register Y */
    int8_t sp;                            /* Stack pointer */

    int16_t pc;                           /* Program counter */

    unsigned int s_negative  : 1;         /* Negative flag */
    unsigned int s_overflow  : 1;         /* Overflow flag */
    unsigned int             : 1;         /* Reserved flag */
    unsigned int s_break     : 1;         /* Break flag */
    unsigned int s_decimal   : 1;         /* Decimal flag */
    unsigned int s_interrupt : 1;         /* Interrupt flag */
    unsigned int s_zero      : 1;         /* Zero flag */
    unsigned int s_carry     : 1;         /* Carry flag */
};

#endif //SFEMU2_CPU_H
