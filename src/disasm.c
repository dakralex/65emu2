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
print_implicit (FILE* dest, const char name[])
{
  fprintf (dest, "%s", name);
}

void
print_accumulator (FILE* dest, const char name[])
{
  fprintf (dest, "%s A", name);
}

void
print_immediate (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s #$%02x", name, code[1]);
}

void
print_zero_page (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s $%02x", name, code[1]);
}

void
print_zero_page_x (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s $%02x,X", name, code[1]);
}

void
print_zero_page_y (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s $%02x,Y", name, code[1]);
}

void
print_relative (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s $%02x", name, code[1]);
}

void
print_absolute (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s $%02x%02x", name, code[1], code[2]);
}

void
print_absolute_x (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s $%02x%02x,X", name, code[1], code[2]);
}

void
print_absolute_y (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s $%02x%02x,Y", name, code[1], code[2]);
}

void
print_indirect (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s $%02x", name, code[1]);
}

void
print_indexed_indirect (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s ($%02x,X)", name, code[1]);
}

void
print_indirect_indexed (FILE* dest, const unsigned char* code, const char name[])
{
  fprintf (dest, "%s ($%02x),Y", name, code[1]);
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
        print_implicit (dest, "brk");
        break;
      case ORA_INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, "ora");
        op_len = 2;
        break;
      case ORA_ZERO_PAGE:
        print_zero_page (dest, code, "ora");
        op_len = 2;
        break;
      case ASL_ZERO_PAGE:
        print_zero_page (dest, code, "asl");
        op_len = 2;
        break;
      case PHP_IMPLICIT:
        print_implicit (dest, "php");
        break;
      case ORA_IMMEDIATE:
        print_immediate (dest, code, "ora");
        op_len = 2;
        break;
      case ASL_ACCUMULATOR:
        print_accumulator (dest, "acc");
        break;
      case ORA_ABSOLUTE:
        print_absolute (dest, code, "ora");
        op_len = 3;
        break;
      case ASL_ABSOLUTE:
        print_absolute (dest, code, "asl");
        op_len = 3;
        break;
      case BPL_RELATIVE:
        print_relative (dest, code, "bpl");
        op_len = 2;
        break;
      case ORA_INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, "ora");
        op_len = 2;
        break;
      case ORA_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "ora");
        op_len = 2;
        break;
      case ASL_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "asl");
        op_len = 2;
        break;
      case CLC_IMPLICIT:
        print_implicit (dest, "clc");
        break;
      case ORA_ABSOLUTE_Y:
        print_absolute_y (dest, code, "ora");
        op_len = 3;
        break;
      case ORA_ABSOLUTE_X:
        print_absolute_x (dest, code, "ora");
        op_len = 3;
        break;
      case ASL_ABSOLUTE_X:
        print_absolute_x (dest, code, "asl");
        op_len = 3;
        break;
      case JSR_ABSOLUTE:
        print_absolute (dest, code, "jsr");
        op_len = 3;
        break;
      case AND_INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, "and");
        op_len = 2;
        break;
      case BIT_ZERO_PAGE:
        print_zero_page (dest, code, "bit");
        op_len = 2;
        break;
      case AND_ZERO_PAGE:
        print_zero_page (dest, code, "and");
        op_len = 2;
        break;
      case ROL_ZERO_PAGE:
        print_zero_page (dest, code, "rol");
        op_len = 2;
        break;
      case PLP_IMPLICIT:
        print_implicit (dest, "plp");
        break;
      case AND_IMMEDIATE:
        print_immediate (dest, code, "and");
        op_len = 2;
        break;
      case ROL_ACCUMULATOR:
        print_accumulator (dest, "rol");
        break;
      case BIT_ABSOLUTE:
        print_absolute (dest, code, "bit");
        op_len = 3;
        break;
      case AND_ABSOLUTE:
        print_absolute (dest, code, "and");
        op_len = 3;
        break;
      case ROL_ABSOLUTE:
        print_absolute (dest, code, "rol");
        op_len = 3;
        break;
      case BMI_RELATIVE:
        print_relative (dest, code, "bmi");
        op_len = 2;
        break;
      case AND_INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, "and");
        op_len = 2;
        break;
      case AND_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "and");
        op_len = 2;
        break;
      case ROL_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "rol");
        op_len = 2;
        break;
      case SEC_IMPLICIT:
        print_implicit (dest, "sec");
        op_len = 2;
        break;
      case AND_ABSOLUTE_Y:
        print_absolute_y (dest, code, "and");
        op_len = 3;
        break;
      case AND_ABSOLUTE_X:
        print_absolute_x (dest, code, "and");
        op_len = 3;
        break;
      case ROL_ABSOLUTE_X:
        print_absolute_x (dest, code, "rol");
        op_len = 3;
        break;
      case RTI_IMPLICIT:
        print_implicit (dest, "rti");
        break;
      case EOR_INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, "eor");
        op_len = 2;
        break;
      case EOR_ZERO_PAGE:
        print_zero_page (dest, code, "eor");
        op_len = 2;
        break;
      case LSR_ZERO_PAGE:
        print_zero_page (dest, code, "lsr");
        op_len = 2;
        break;
      case PHA_IMPLICIT:
        print_implicit (dest, "pha");
        break;
      case EOR_IMMEDIATE:
        print_immediate (dest, code, "eor");
        op_len = 2;
        break;
      case LSR_ACCUMULATOR:
        print_accumulator (dest, "lsr");
        break;
      case JMP_ABSOLUTE:
        print_absolute (dest, code, "jmp");
        op_len = 3;
        break;
      case EOR_ABSOLUTE:
        print_absolute (dest, code, "eor");
        op_len = 3;
        break;
      case LSR_ABSOLUTE:
        print_absolute (dest, code, "lsr");
        op_len = 3;
        break;
      case BVC_RELATIVE:
        print_relative (dest, code, "bvc");
        op_len = 2;
        break;
      case EOR_INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, "eor");
        op_len = 2;
        break;
      case EOR_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "eor");
        op_len = 2;
        break;
      case LSR_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "lsr");
        op_len = 2;
        break;
      case CLI_IMPLICIT:
        print_implicit (dest, "cli");
        break;
      case EOR_ABSOLUTE_Y:
        print_absolute_y (dest, code, "eor");
        op_len = 3;
        break;
      case EOR_ABSOLUTE_X:
        print_absolute_x (dest, code, "eor");
        op_len = 3;
        break;
      case LSR_ABSOLUTE_X:
        print_absolute_x (dest, code, "lsr");
        op_len = 3;
        break;
      case RTS_IMPLICIT:
        print_implicit (dest, "rts");
        break;
      case ADC_INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, "adc");
        op_len = 2;
        break;
      case ADC_ZERO_PAGE:
        print_zero_page (dest, code, "adc");
        op_len = 2;
        break;
      case ROR_ZERO_PAGE:
        print_zero_page (dest, code, "ror");
        op_len = 2;
        break;
      case PLA_IMPLICIT:
        print_implicit (dest, "pla");
        break;
      case ADC_IMMEDIATE:
        print_immediate (dest, code, "adc");
        op_len = 2;
        break;
      case ROR_ACCUMULATOR:
        print_accumulator (dest, "ror");
        break;
      case JMP_INDIRECT:
        print_indirect (dest, code, "jmp");
        op_len = 2;
        break;
      case ADC_ABSOLUTE:
        print_absolute (dest, code, "adc");
        op_len = 3;
        break;
      case ROR_ABSOLUTE_X:
        print_absolute_x (dest, code, "ror");
        op_len = 3;
        break;
      case BVS_RELATIVE:
        print_relative (dest, code, "bvs");
        op_len = 2;
        break;
      case ADC_INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, "adc");
        op_len = 2;
        break;
      case ADC_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "adc");
        op_len = 2;
        break;
      case ROR_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "ror");
        op_len = 2;
        break;
      case SEI_IMPLICIT:
        print_implicit (dest, "sei");
        break;
      case ADC_ABSOLUTE_Y:
        print_absolute_y (dest, code, "adc");
        op_len = 3;
        break;
      case ADC_ABSOLUTE_X:
        print_absolute_x (dest, code, "adc");
        op_len = 3;
        break;
      case ROR_ABSOLUTE:
        print_absolute (dest, code, "ror");
        op_len = 3;
        break;
      case STA_INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, "sta");
        op_len = 2;
        break;
      case STY_ZERO_PAGE:
        print_zero_page (dest, code, "sty");
        op_len = 2;
        break;
      case STA_ZERO_PAGE:
        print_zero_page (dest, code, "sta");
        op_len = 2;
        break;
      case STX_ZERO_PAGE:
        print_zero_page (dest, code, "stx");
        op_len = 2;
        break;
      case DEY_IMPLICIT:
        print_implicit (dest, "dey");
        break;
      case TXA_IMPLICIT:
        print_implicit (dest, "txa");
        break;
      case STY_ABSOLUTE:
        print_absolute (dest, code, "sty");
        op_len = 3;
        break;
      case STA_ABSOLUTE:
        print_absolute (dest, code, "sta");
        op_len = 3;
        break;
      case STX_ABSOLUTE:
        print_absolute (dest, code, "stx");
        op_len = 3;
        break;
      case BCC_RELATIVE:
        print_relative (dest, code, "bcc");
        op_len = 2;
        break;
      case STA_INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, "sta");
        op_len = 2;
        break;
      case STY_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "sty");
        op_len = 2;
        break;
      case STA_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "sta");
        op_len = 2;
        break;
      case STX_ZERO_PAGE_Y:
        print_zero_page_y (dest, code, "stx");
        op_len = 2;
        break;
      case TYA_IMPLICIT:
        print_implicit (dest, "tya");
        break;
      case STA_ABSOLUTE_Y:
        print_absolute_y (dest, code, "sta");
        op_len = 3;
        break;
      case TXS_IMPLICIT:
        print_implicit (dest, "txs");
        break;
      case STA_ABSOLUTE_X:
        print_absolute_x (dest, code, "sta");
        op_len = 3;
        break;
      case LDY_IMMEDIATE:
        print_immediate (dest, code, "ldy");
        op_len = 2;
        break;
      case LDA_INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, "lda");
        op_len = 2;
        break;
      case LDX_IMMEDIATE:
        print_immediate (dest, code, "ldx");
        op_len = 2;
        break;
      case LDY_ZERO_PAGE:
        print_zero_page (dest, code, "ldy");
        op_len = 2;
        break;
      case LDA_ZERO_PAGE:
        print_zero_page (dest, code, "lda");
        op_len = 2;
        break;
      case LDX_ZERO_PAGE:
        print_zero_page (dest, code, "ldx");
        op_len = 2;
        break;
      case TAY_IMPLICIT:
        print_implicit (dest, "tay");
        break;
      case LDA_IMMEDIATE:
        print_immediate (dest, code, "lda");
        op_len = 2;
        break;
      case TAX_IMPLICIT:
        print_implicit (dest, "tax");
        break;
      case LDY_ABSOLUTE:
        print_absolute (dest, code, "ldy");
        op_len = 3;
        break;
      case LDA_ABSOLUTE:
        print_absolute (dest, code, "lda");
        op_len = 3;
        break;
      case LDX_ABSOLUTE:
        print_absolute (dest, code, "ldx");
        op_len = 3;
        break;
      case BCS_RELATIVE:
        print_relative (dest, code, "bcs");
        op_len = 2;
        break;
      case LDA_INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, "lda");
        op_len = 2;
        break;
      case LDY_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "ldy");
        op_len = 2;
        break;
      case LDA_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "lda");
        op_len = 2;
        break;
      case LDX_ZERO_PAGE_Y:
        print_zero_page_y (dest, code, "ldx");
        op_len = 2;
        break;
      case CLV_IMPLICIT:
        print_implicit (dest, "clv");
        break;
      case LDA_ABSOLUTE_Y:
        print_absolute_y (dest, code, "lda");
        op_len = 3;
        break;
      case TSX_IMPLICIT:
        print_implicit (dest, "tsx");
        break;
      case LDY_ABSOLUTE_X:
        print_absolute_x (dest, code, "ldy");
        op_len = 3;
        break;
      case LDA_ABSOLUTE_X:
        print_absolute_x (dest, code, "lda");
        op_len = 3;
        break;
      case LDX_ABSOLUTE_Y:
        print_absolute_y (dest, code, "ldx");
        op_len = 3;
        break;
      case CPY_IMMEDIATE:
        print_immediate (dest, code, "cpy");
        op_len = 2;
        break;
      case CMP_INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, "cmp");
        op_len = 2;
        break;
      case CPY_ZERO_PAGE:
        print_zero_page (dest, code, "cpy");
        op_len = 2;
        break;
      case CMP_ZERO_PAGE:
        print_zero_page (dest, code, "cmp");
        op_len = 2;
        break;
      case DEC_ZERO_PAGE:
        print_zero_page (dest, code, "dec");
        op_len = 2;
        break;
      case INY_IMPLICIT:
        print_implicit (dest, "iny");
        break;
      case CMP_IMMEDIATE:
        print_immediate (dest, code, "cmp");
        op_len = 2;
        break;
      case DEX_IMPLICIT:
        print_implicit (dest, "dex");
        break;
      case CPY_ABSOLUTE:
        print_absolute (dest, code, "cpy");
        op_len = 3;
        break;
      case CMP_ABSOLUTE:
        print_absolute (dest, code, "cmp");
        op_len = 3;
        break;
      case DEC_ABSOLUTE:
        print_absolute (dest, code, "dec");
        op_len = 3;
        break;
      case BNE_RELATIVE:
        print_relative (dest, code, "bne");
        op_len = 2;
        break;
      case CMP_INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, "cmp");
        op_len = 2;
        break;
      case CMP_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "cmp");
        op_len = 2;
        break;
      case DEC_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "dec");
        op_len = 2;
        break;
      case CLD_IMPLICIT:
        print_implicit (dest, "cld");
        break;
      case CMP_ABSOLUTE_Y:
        print_absolute_y (dest, code, "cmp");
        op_len = 3;
        break;
      case CMP_ABSOLUTE_X:
        print_absolute_x (dest, code, "cmp");
        op_len = 3;
        break;
      case DEC_ABSOLUTE_X:
        print_absolute_x (dest, code, "dec");
        op_len = 3;
        break;
      case CPX_IMMEDIATE:
        print_immediate (dest, code, "cpx");
        op_len = 2;
        break;
      case SBC_INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, "sbc");
        op_len = 2;
        break;
      case CPX_ZERO_PAGE:
        print_zero_page (dest, code, "cpx");
        op_len = 2;
        break;
      case SBC_ZERO_PAGE:
        print_zero_page (dest, code, "sbc");
        op_len = 2;
        break;
      case INC_ZERO_PAGE:
        print_zero_page (dest, code, "inc");
        op_len = 2;
        break;
      case INX_IMPLICIT:
        print_implicit (dest, "inx");
        break;
      case SBC_IMMEDIATE:
        print_immediate (dest, code, "sbc");
        op_len = 2;
        break;
      case NOP_IMPLICIT:
        print_implicit (dest, "nop");
        break;
      case CPX_ABSOLUTE:
        print_absolute (dest, code, "cpx");
        op_len = 3;
        break;
      case SBC_ABSOLUTE:
        print_absolute (dest, code, "sbc");
        op_len = 3;
        break;
      case INC_ABSOLUTE:
        print_absolute (dest, code, "inc");
        op_len = 3;
        break;
      case BEQ_RELATIVE:
        print_relative (dest, code, "beq");
        op_len = 2;
        break;
      case SBC_INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, "sbc");
        op_len = 2;
        break;
      case SBC_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "sbc");
        op_len = 2;
        break;
      case INC_ZERO_PAGE_X:
        print_zero_page_x (dest, code, "inc");
        op_len = 2;
        break;
      case SED_IMPLICIT:
        print_implicit (dest, "sed");
        break;
      case SBC_ABSOLUTE_Y:
        print_absolute_y (dest, code, "sbc");
        op_len = 3;
        break;
      case SBC_ABSOLUTE_X:
        print_absolute_x (dest, code, "sbc");
        op_len = 3;
        break;
      case INC_ABSOLUTE_X:
        print_absolute_x (dest, code, "inc");
        op_len = 3;
        break;
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