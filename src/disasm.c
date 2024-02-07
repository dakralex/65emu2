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
#include "opcode.h"

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
disassemble (const uint8_t* buf, size_t fsize, FILE* dest)
{
  unsigned int pc = 0;
  uint8_t const* code;
  opcode_t const* opcode;
  char const* name;

  while (pc < fsize) {
    code = &buf[pc];
    printf ("%04x:  ", pc);
    opcode = decode_opcode (code);
    name = get_opcode_name (opcode);

    switch (opcode->mode) {
      case IMPLICIT:
        fprintf (dest, "%s", name);
        pc += 1;
        break;
      case ACCUMULATOR:
        fprintf (dest, "%s A", name);
        pc += 1;
        break;
      case IMMEDIATE:
        fprintf (dest, "%s #$%02x", name, code[1]);
        pc += 2;
        break;
      case ZERO_PAGE:
        fprintf (dest, "%s $%02x", name, code[1]);
        pc += 2;
        break;
      case ZERO_PAGE_X:
        fprintf (dest, "%s $%02x,X", name, code[1]);
        pc += 2;
        break;
      case ZERO_PAGE_Y:
        fprintf (dest, "%s $%02x,Y", name, code[1]);
        pc += 2;
        break;
      case RELATIVE:
        fprintf (dest, "%s $%02x", name, code[1]);
        pc += 2;
        break;
      case INDIRECT:
        fprintf (dest, "%s $%02x", name, code[1]);
        pc += 2;
        break;
      case INDEXED_INDIRECT:
        fprintf (dest, "%s ($%02x,X)", name, code[1]);
        pc += 2;
        break;
      case INDIRECT_INDEXED:
        fprintf (dest, "%s ($%02x),Y", name, code[1]);
        pc += 2;
        break;
      case ABSOLUTE:
        fprintf (dest, "%s $%02x%02x", name, code[1], code[2]);
        pc += 3;
        break;
      case ABSOLUTE_X:
        fprintf (dest, "%s $%02x%02x,X", name, code[1], code[2]);
        pc += 3;
        break;
      case ABSOLUTE_Y:
        fprintf (dest, "%s $%02x%02x,Y", name, code[1], code[2]);
        pc += 3;
        break;
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