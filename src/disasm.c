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

    switch (*code) {
      case BRK_IMPLICIT:
        fprintf (dest, "brk");
        break;
      default:
        fprintf (stderr, "Could not decode op code at %04x with value %02x", pc, code[0]);
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