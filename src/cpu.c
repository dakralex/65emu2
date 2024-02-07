/**
 * cpu.c
 */

#include <stddef.h>
#include "cpu.h"
#include "opcode.h"

void
tick (cpu_t* state, mem_t* mem)
{
  uint8_t const* curr = mem[state->pc];
  opcode_t const* op = decode_opcode (curr);
  uint8_t const* operand = NULL;
  uint8_t temp = 0;

  switch (op->mode) {
    case UNDEFINED_MODE:
      return;
    case IMPLICIT:
      break;
    case ACCUMULATOR:
      operand = &state->acc;
      break;
    case IMMEDIATE:
      temp = *(curr + 1);
      operand = &temp;
      break;
    case ZERO_PAGE:
      operand = mem[*(curr + 1)];
      break;
    case ZERO_PAGE_X:
      operand = mem[*(curr + 1) + state->idx_x % 0xFF];
      break;
    case ZERO_PAGE_Y:
      operand = mem[*(curr + 1) + state->idx_y % 0xFF];
      break;
    case RELATIVE:
      operand = *(mem + (int8_t) * (curr + 1));
      break;
    case ABSOLUTE:
      operand = mem[*(curr + 1) << 8 | *(curr + 2)];
      break;
    case ABSOLUTE_X:
      operand = mem[*(curr + 1) << 8 | *(curr + 2) + state->idx_x];
      break;
    case ABSOLUTE_Y:
      operand = mem[*(curr + 1) << 8 | *(curr + 2) + state->idx_y];
      break;
    case INDIRECT:
      operand = mem[*mem[*(curr + 1)]];
      break;
    case INDEXED_INDIRECT:
      break;
    case INDIRECT_INDEXED:
      break;
  }
}
