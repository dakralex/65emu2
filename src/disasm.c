/**
 * disasm.c
 *
 * Implementation of MOS 6502 disassembler.
 */

#include <stdio.h>
#include <stdlib.h>
#include "disasm.h"
#include "opcodes.h"

size_t
read_file (const char* filename, unsigned char** dest)
{
  FILE* fp = fopen (filename, "rb");

  if (fp == NULL) {
    fprintf (stderr, "Could not open file %s for reading.\n", filename);
    exit (EXIT_FAILURE);
  }

  fseek (fp, 0L, SEEK_END);
  long fsize = ftell (fp);
  fseek (fp, 0L, SEEK_SET);

  long nsize = fsize + 1;
  if (nsize == 0) {
    fprintf (stderr, "Could not allocate buffer while seeking file %s.\n", filename);
    fclose (fp);
    exit (EXIT_FAILURE);
  }

  *dest = malloc (nsize);
  fread (*dest, fsize, 1, fp);
  fclose (fp);

  return fsize;
}

void
disassemble (const unsigned char* buf, size_t fsize, FILE* dest)
{
  unsigned int pc = 0;
  unsigned int op_len;
  unsigned char const* code;

  while (pc < fsize) {
    op_len = 1;
    code = &buf[pc];
    printf ("%04x ", pc);

    // TODO Refactor this to a decoder (e.g. derived from schematics and bit checks)
    switch (*code) {
      case BRK_IMPLICIT:
        fprintf (dest, "brk");
        break;
      case ORA_INDEXED_INDIRECT:
        fprintf (dest, "ora ($%02x,X)", code[1]);
        op_len = 2;
        break;
      case ORA_ZERO_PAGE:
        fprintf (dest, "ora $%02x", code[1]);
        op_len = 2;
        break;
      case ASL_ZERO_PAGE:
        fprintf (dest, "asl $%02x", code[1]);
        op_len = 2;
        break;
      case PHP_IMPLICIT:
        fprintf (dest, "php");
        break;
      case ORA_IMMEDIATE:
        fprintf (dest, "ora #$%02x", code[1]);
        op_len = 2;
        break;
      case ASL_ACCUMULATOR:
        fprintf (dest, "asl A");
        break;
      case ORA_ABSOLUTE:
        fprintf (dest, "ora $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case ASL_ABSOLUTE:
        fprintf (dest, "asl $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case BPL_RELATIVE:
        fprintf (dest, "bpl $%02x", code[1]);
        op_len = 2;
        break;
      case ORA_INDIRECT_INDEXED:
        fprintf (dest, "ora ($%02x),Y", code[1]);
        op_len = 2;
        break;
      case ORA_ZERO_PAGE_X:
        fprintf (dest, "ora $%02x,X", code[1]);
        op_len = 2;
        break;
      case ASL_ZERO_PAGE_X:
        fprintf (dest, "asl $%02x,X", code[1]);
        op_len = 2;
        break;
      case CLC_IMPLICIT:
        fprintf (dest, "clc");
        break;
      case ORA_ABSOLUTE_Y:
        fprintf (dest, "ora $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;
      case ORA_ABSOLUTE_X:
        fprintf (dest, "ora $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case ASL_ABSOLUTE_X:
        fprintf (dest, "asl $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case JSR_ABSOLUTE:
        fprintf (dest, "jsr $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case AND_INDEXED_INDIRECT:
        fprintf (dest, "and ($%02x,X)", code[1]);
        op_len = 2;
        break;
      case BIT_ZERO_PAGE:
        fprintf (dest, "bit $%02x", code[1]);
        op_len = 2;
        break;
      case AND_ZERO_PAGE:
        fprintf (dest, "and $%02x", code[1]);
        op_len = 2;
        break;
      case ROL_ZERO_PAGE:
        fprintf (dest, "rol $%02x", code[1]);
        op_len = 2;
        break;
      case PLP_IMPLICIT:
        fprintf (dest, "plp");
        break;
      case AND_IMMEDIATE:
        fprintf (dest, "and #$%02x", code[1]);
        op_len = 2;
        break;
      case ROL_ACCUMULATOR:
        fprintf (dest, "rol A");
        break;
      case BIT_ABSOLUTE:
        fprintf (dest, "bit $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case AND_ABSOLUTE:
        fprintf (dest, "and $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case ROL_ABSOLUTE:
        fprintf (dest, "rol $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case BMI_RELATIVE:
        fprintf (dest, "bmi $%02x", code[1]);
        op_len = 2;
        break;
      case AND_INDIRECT_INDEXED:
        fprintf (dest, "and ($%02x),Y", code[1]);
        op_len = 2;
        break;
      case AND_ZERO_PAGE_X:
        fprintf (dest, "and $%02x,X", code[1]);
        op_len = 2;
        break;
      case ROL_ZERO_PAGE_X:
        fprintf (dest, "rol $%02x,X", code[1]);
        op_len = 2;
        break;
      case SEC_IMPLICIT:
        fprintf (dest, "sec", code[1]);
        op_len = 2;
        break;
      case AND_ABSOLUTE_Y:
        fprintf (dest, "and $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;
      case AND_ABSOLUTE_X:
        fprintf (dest, "and $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case ROL_ABSOLUTE_X:
        fprintf (dest, "rol $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case RTI_IMPLICIT:
        fprintf (dest, "rti");
        break;
      case EOR_INDEXED_INDIRECT:
        fprintf (dest, "eor ($%02x,X)", code[1]);
        op_len = 2;
        break;
      case EOR_ZERO_PAGE:
        fprintf (dest, "eor $%02x", code[1]);
        op_len = 2;
        break;
      case LSR_ZERO_PAGE:
        fprintf (dest, "lsr $%02x", code[1]);
        op_len = 2;
        break;
      case PHA_IMPLICIT:
        fprintf (dest, "pha");
        break;
      case EOR_IMMEDIATE:
        fprintf (dest, "eor #$%02x", code[1]);
        op_len = 2;
        break;
      case LSR_ACCUMULATOR:
        fprintf (dest, "lsr A");
        break;
      case JMP_ABSOLUTE:
        fprintf (dest, "jmp $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case EOR_ABSOLUTE:
        fprintf (dest, "eor $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case LSR_ABSOLUTE:
        fprintf (dest, "lsr $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case BVC_RELATIVE:
        fprintf (dest, "bvc $%02x", code[1]);
        op_len = 2;
        break;
      case EOR_INDIRECT_INDEXED:
        fprintf (dest, "eor ($%02x),Y", code[1]);
        op_len = 2;
        break;
      case EOR_ZERO_PAGE_X:
        fprintf (dest, "eor $%02x,X", code[1]);
        op_len = 2;
        break;
      case LSR_ZERO_PAGE_X:
        fprintf (dest, "lsr $%02x,X", code[1]);
        op_len = 2;
        break;
      case CLI_IMPLICIT:
        fprintf (dest, "cli");
        break;
      case EOR_ABSOLUTE_Y:
        fprintf (dest, "eor $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;
      case EOR_ABSOLUTE_X:
        fprintf (dest, "eor $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case LSR_ABSOLUTE_X:
        fprintf (dest, "lsr $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case RTS_IMPLICIT:
        fprintf (dest, "rts");
        break;
      case ADC_INDEXED_INDIRECT:
        fprintf (dest, "adc ($%02x,X)", code[1]);
        op_len = 2;
        break;
      case ADC_ZERO_PAGE:
        fprintf (dest, "adc $%02x", code[1]);
        op_len = 2;
        break;
      case ROR_ZERO_PAGE:
        fprintf (dest, "ror $%02x", code[1]);
        op_len = 2;
        break;
      case PLA_IMPLICIT:
        fprintf (dest, "pla");
        break;
      case ADC_IMMEDIATE:
        fprintf (dest, "adc #$%02x", code[1]);
        op_len = 2;
        break;
      case ROR_ACCUMULATOR:
        fprintf (dest, "ror A");
        break;
      case JMP_INDIRECT:
        fprintf (dest, "jmp $%02x", code[1]);
        op_len = 2;
        break;
      case ADC_ABSOLUTE:
        fprintf (dest, "adc $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case ROR_ABSOLUTE_X:
        fprintf (dest, "ror $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case BVS_RELATIVE:
        fprintf (dest, "bvs $%02x", code[1]);
        op_len = 2;
        break;
      case ADC_INDIRECT_INDEXED:
        fprintf (dest, "adc ($%02x),Y", code[1]);
        op_len = 2;
        break;
      case ADC_ZERO_PAGE_X:
        fprintf (dest, "adc $%02x,X", code[1]);
        op_len = 2;
        break;
      case ROR_ZERO_PAGE_X:
        fprintf (dest, "ror $%02x,X", code[1]);
        op_len = 2;
        break;
      case SEI_IMPLICIT:
        fprintf (dest, "sei");
        break;
      case ADC_ABSOLUTE_Y:
        fprintf (dest, "adc $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;
      case ADC_ABSOLUTE_X:
        fprintf (dest, "adc $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case ROR_ABSOLUTE:
        fprintf (dest, "ror $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case STA_INDEXED_INDIRECT:
        fprintf (dest, "sta ($%02x,X)", code[1]);
        op_len = 2;
        break;
      case STY_ZERO_PAGE:
        fprintf (dest, "sty $%02x", code[1]);
        op_len = 2;
        break;
      case STA_ZERO_PAGE:
        fprintf (dest, "sta $%02x", code[1]);
        op_len = 2;
        break;
      case STX_ZERO_PAGE:
        fprintf (dest, "stx $%02x", code[1]);
        op_len = 2;
        break;
      case DEY_IMPLICIT:
        fprintf (dest, "dey");
        break;
      case TXA_IMPLICIT:
        fprintf (dest, "txa");
        break;
      case STY_ABSOLUTE:
        fprintf (dest, "sty $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case STA_ABSOLUTE:
        fprintf (dest, "sta $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case STX_ABSOLUTE:
        fprintf (dest, "stx $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case BCC_RELATIVE:
        fprintf (dest, "bcc $%02x", code[1]);
        op_len = 2;
        break;
      case STA_INDIRECT_INDEXED:
        fprintf (dest, "sta ($%02x),Y", code[1]);
        op_len = 2;
        break;
      case STY_ZERO_PAGE_X:
        fprintf (dest, "sty $%02x,X", code[1]);
        op_len = 2;
        break;
      case STA_ZERO_PAGE_X:
        fprintf (dest, "sta $%02x,X", code[1]);
        op_len = 2;
        break;
      case STX_ZERO_PAGE_Y:
        fprintf (dest, "stx $%02x,Y", code[1]);
        op_len = 2;
        break;
      case TYA_IMPLICIT:
        fprintf (dest, "tya");
        break;
      case STA_ABSOLUTE_Y:
        fprintf (dest, "sta $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;
      case TXS_IMPLICIT:
        fprintf (dest, "txs");
        break;
      case STA_ABSOLUTE_X:
        fprintf (dest, "sta $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case LDY_IMMEDIATE:
        fprintf (dest, "ldy $#%02x", code[1]);
        op_len = 2;
        break;
      case LDA_INDEXED_INDIRECT:
        fprintf (dest, "lda ($%02x,X)", code[1]);
        op_len = 2;
        break;
      case LDX_IMMEDIATE:
        fprintf (dest, "ldx #$%02x", code[1]);
        op_len = 2;
        break;
      case LDY_ZERO_PAGE:
        fprintf (dest, "ldy $%02x", code[1]);
        op_len = 2;
        break;
      case LDA_ZERO_PAGE:
        fprintf (dest, "lda $%02x", code[1]);
        op_len = 2;
        break;
      case LDX_ZERO_PAGE:
        fprintf (dest, "ldx $%02x", code[1]);
        op_len = 2;
        break;
      case TAY_IMPLICIT:
        fprintf (dest, "tay");
        break;
      case LDA_IMMEDIATE:
        fprintf (dest, "lda #$%02x", code[1]);
        op_len = 2;
        break;
      case TAX_IMPLICIT:
        fprintf (dest, "tax");
        break;
      case LDY_ABSOLUTE:
        fprintf (dest, "ldy $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case LDA_ABSOLUTE:
        fprintf (dest, "lda $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case LDX_ABSOLUTE:
        fprintf (dest, "ldx $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case BCS_RELATIVE:
        fprintf (dest, "bcs $%02x", code[1]);
        op_len = 2;
        break;
      case LDA_INDIRECT_INDEXED:
        fprintf (dest, "lda ($%02x),Y", code[1]);
        op_len = 2;
        break;
      case LDY_ZERO_PAGE_X:
        fprintf (dest, "ldy $%02x,X", code[1]);
        op_len = 2;
        break;
      case LDA_ZERO_PAGE_X:
        fprintf (dest, "lda $%02x,X", code[1]);
        op_len = 2;
        break;
      case LDX_ZERO_PAGE_Y:
        fprintf (dest, "ldx $%02x,Y", code[1]);
        op_len = 2;
        break;
      case CLV_IMPLICIT:
        fprintf (dest, "clv");
        break;
      case LDA_ABSOLUTE_Y:
        fprintf (dest, "lda $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;
      case TSX_IMPLICIT:
        fprintf (dest, "tsx");
        break;
      case LDY_ABSOLUTE_X:
        fprintf (dest, "ldy $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case LDA_ABSOLUTE_X:
        fprintf (dest, "lda $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case LDX_ABSOLUTE_Y:
        fprintf (dest, "ldx $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;
      case CPY_IMMEDIATE:
        fprintf (dest, "cpy #$%02x", code[1]);
        op_len = 2;
        break;
      case CMP_INDEXED_INDIRECT:
        fprintf (dest, "cmp ($%02x,X)", code[1]);
        op_len = 2;
        break;
      case CPY_ZERO_PAGE:
        fprintf (dest, "cpy $%02x", code[1]);
        op_len = 2;
        break;
      case CMP_ZERO_PAGE:
        fprintf (dest, "cmp $%02x", code[1]);
        op_len = 2;
        break;
      case DEC_ZERO_PAGE:
        fprintf (dest, "dec $%02x", code[1]);
        op_len = 2;
        break;
      case INY_IMPLICIT:
        fprintf (dest, "iny");
        break;
      case CMP_IMMEDIATE:
        fprintf (dest, "cmp #$%02x", code[1]);
        op_len = 2;
        break;
      case DEX_IMPLICIT:
        fprintf (dest, "dex");
        break;
      case CPY_ABSOLUTE:
        fprintf (dest, "cpy $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;

      case BNE_RELATIVE:
        fprintf (dest, "bne $%02x", code[1]);
        op_len = 2;
        break;
      case CMP_INDIRECT_INDEXED:
        fprintf (dest, "cmp ($%02x),Y", code[1]);
        op_len = 2;
        break;
      case CMP_ZERO_PAGE_X:
        fprintf (dest, "cmp $%02x,X", code[1]);
        op_len = 2;
        break;
      case DEC_ZERO_PAGE_X:
        fprintf (dest, "dec $%02x,X", code[1]);
        op_len = 2;
        break;
      case CLD_IMPLICIT:
        fprintf (dest, "cld");
        break;
      case CMP_ABSOLUTE_Y:
        fprintf (dest, "cmp $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;

      case CPX_IMMEDIATE:
        fprintf (dest, "cpx #$%02x", code[1]);
        op_len = 2;
        break;
      case SBC_INDEXED_INDIRECT:
        fprintf (dest, "sbc ($%02x,X)", code[1]);
        op_len = 2;
        break;
      case CPX_ZERO_PAGE:
        fprintf (dest, "cpx $%02x", code[1]);
        op_len = 2;
        break;
      case SBC_ZERO_PAGE:
        fprintf (dest, "sbc $%02x", code[1]);
        op_len = 2;
        break;
      case INC_ZERO_PAGE:
        fprintf (dest, "inc $%02x", code[1]);
        op_len = 2;
        break;
      case INX_IMPLICIT:
        fprintf (dest, "inx");
        break;
      case SBC_IMMEDIATE:
        fprintf (dest, "sbc #$%02x", code[1]);
        op_len = 2;
        break;
      case NOP_IMPLICIT:
        fprintf (dest, "nop");
        break;
      case CPX_ABSOLUTE:
        fprintf (dest, "cpx $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case SBC_ABSOLUTE:
        fprintf (dest, "sbc $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case INC_ABSOLUTE:
        fprintf (dest, "inc $%02x%02x", code[1], code[2]);
        op_len = 3;
        break;
      case BEQ_RELATIVE:
        fprintf (dest, "beq $%02x", code[1]);
        op_len = 2;
        break;
      case SBC_INDIRECT_INDEXED:
        fprintf (dest, "sbc ($%02x),Y", code[1]);
        op_len = 2;
        break;
      case SBC_ZERO_PAGE_X:
        fprintf (dest, "sbc $%02x,X", code[1]);
        op_len = 2;
        break;
      case INC_ZERO_PAGE_X:
        fprintf (dest, "inc $%02x,X", code[1]);
        op_len = 2;
        break;
      case SED_IMPLICIT:
        fprintf (dest, "sed");
        break;
      case SBC_ABSOLUTE_Y:
        fprintf (dest, "sbc $%02x%02x,Y", code[1], code[2]);
        op_len = 3;
        break;
      case SBC_ABSOLUTE_X:
        fprintf (dest, "sbc $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      case INC_ABSOLUTE_X:
        fprintf (dest, "inc $%02x%02x,X", code[1], code[2]);
        op_len = 3;
        break;
      default:
        fprintf (stderr, "Could not decode op code at %04x with value %02x.", pc, code[0]);
        exit (1);
    }

    fprintf (dest, "\n");
    pc += op_len;
  }
}

int
main (int argc, char* argv[])
{
  if (argc == 2) {
    unsigned char* buf;
    size_t fsize = read_file (argv[1], &buf);
    disassemble (buf, fsize, stdout);
  } else {
    fprintf (stderr, "Usage: %s [FILE]\n", argv[0]);
    exit (EXIT_FAILURE);
  }

  exit (EXIT_SUCCESS);
}