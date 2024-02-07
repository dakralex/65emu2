/**
 * cpu.h
 *
 * CPU state management and interface for emulated MOS 6502.
 */

#ifndef INC_65EMU2_CPU_H
#define INC_65EMU2_CPU_H

#include <inttypes.h>
#include "memory.h"

typedef struct cpu_t {
    uint8_t acc;                          /* Accumulator register A */

    uint8_t idx_x;                        /* Index register X */
    uint8_t idx_y;                        /* Index register Y */
    uint8_t sp;                           /* Stack pointer */

    uint16_t pc;                          /* Program counter */

    unsigned int s_negative  : 1;         /* Negative flag */
    unsigned int s_overflow  : 1;         /* Overflow flag */
    unsigned int             : 1;         /* Reserved flag */
    unsigned int s_break     : 1;         /* Break flag */
    unsigned int s_decimal   : 1;         /* Decimal flag */
    unsigned int s_interrupt : 1;         /* Interrupt flag */
    unsigned int s_zero      : 1;         /* Zero flag */
    unsigned int s_carry     : 1;         /* Carry flag */
} cpu_t;

void
tick (cpu_t* state, mem_t* mem);

#endif //INC_65EMU2_CPU_H
