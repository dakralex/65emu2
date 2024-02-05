/**
 * disasm.c
 *
 * Implementation of MOS 6502 disassembler.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "disasm.h"
#include "opcodes.h"

size_t
read_file (const char* filename, uint8_t** dest)
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
print_immediate (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s #$%02x", name, code[1]);
}

void
print_zero_page (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s $%02x", name, code[1]);
}

void
print_zero_page_x (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s $%02x,X", name, code[1]);
}

void
print_zero_page_y (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s $%02x,Y", name, code[1]);
}

void
print_relative (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s $%02x", name, code[1]);
}

void
print_absolute (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s $%02x%02x", name, code[1], code[2]);
}

void
print_absolute_x (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s $%02x%02x,X", name, code[1], code[2]);
}

void
print_absolute_y (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s $%02x%02x,Y", name, code[1], code[2]);
}

void
print_indirect (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s $%02x", name, code[1]);
}

void
print_indexed_indirect (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s ($%02x,X)", name, code[1]);
}

void
print_indirect_indexed (FILE* dest, const uint8_t* code, const char name[])
{
  fprintf (dest, "%s ($%02x),Y", name, code[1]);
}

void
disassemble (const uint8_t* buf, size_t fsize, FILE* dest)
{
  unsigned int pc = 0;
  uint8_t const* code;
  opcode_t const* opcode;

  while (pc < fsize) {
    code = &buf[pc];
    printf ("%04x:  ", pc);
    opcode = &opcodes[*code];

    switch (opcode->mode) {
      case IMMEDIATE:
        print_immediate (dest, code, opcode->name);
        pc += 2;
        break;
      case ZERO_PAGE:
        print_zero_page (dest, code, opcode->name);
        pc += 2;
        break;
      case ZERO_PAGE_X:
        print_zero_page_x (dest, code, opcode->name);
        pc += 2;
        break;
      case ZERO_PAGE_Y:
        print_zero_page_y (dest, code, opcode->name);
        pc += 2;
        break;
      case RELATIVE:
        print_relative (dest, code, opcode->name);
        pc += 2;
        break;
      case INDIRECT:
        print_indirect (dest, code, opcode->name);
        pc += 2;
        break;
      case INDEXED_INDIRECT:
        print_indexed_indirect (dest, code, opcode->name);
        pc += 2;
        break;
      case INDIRECT_INDEXED:
        print_indirect_indexed (dest, code, opcode->name);
        pc += 2;
        break;
      case ABSOLUTE:
        print_absolute (dest, code, opcode->name);
        pc += 3;
        break;
      case ABSOLUTE_X:
        print_absolute_x (dest, code, opcode->name);
        pc += 3;
        break;
      case ABSOLUTE_Y:
        print_absolute_y (dest, code, opcode->name);
        pc += 3;
        break;
      case IMPLICIT:
        print_implicit (dest, opcode->name);
        pc += 1;
        break;
      case ACCUMULATOR:
        print_accumulator (dest, opcode->name);
      default:
        pc += 1;
    }

    fprintf (dest, "\n");
  }
}

int
main (int argc, char* argv[])
{
  if (argc == 2) {
    uint8_t* buf;
    size_t fsize = read_file (argv[1], &buf);
    disassemble (buf, fsize, stdout);
    free (buf);
  } else {
    fprintf (stderr, "Usage: %s [FILE]\n", argv[0]);
    exit (EXIT_FAILURE);
  }

  exit (EXIT_SUCCESS);
}