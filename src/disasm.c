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
read_file (FILE* fp, unsigned char* dest)
{
  fseek (fp, 0L, SEEK_END);
  long fsize = ftell (fp);
  fseek (fp, 0L, SEEK_SET);

  dest = malloc (fsize + 1);
  fread (dest, fsize, 1, fp);

  dest[fsize] = 0;

  return fsize;
}

void
dis_asm_bin (FILE* fp)
{
  unsigned char* buf = {0};
  size_t fsize = read_file (fp, buf);

  unsigned int pc = 0;
  unsigned int op_len = 1;
  unsigned char const* code = &buf[pc];

  while (pc < fsize) {
    printf ("%04x ", pc);

    switch (*code) {
      case BRK_IMPLICIT: printf ("brk"); break;
      default:
        fprintf (stderr, "Could not decode op code at %04x with value %02x", pc, code[0]);
        exit(1);
    }

    pc += op_len;
    code = &buf[pc];
    op_len = 1;
  }
}

int
main (int argc, char* argv[])
{
  if (argc == 2) {
    FILE* fp = fopen (argv[1], "r");

    if (fp == NULL) {
      fprintf (stderr, "%s: Could not open file %s for reading\n", argv[0], argv[1]);
      exit (1);
    }

    dis_asm_bin (fp);

    fclose (fp);
  } else {
    fprintf (stderr, "Usage: ./%s [FILE]\n", argv[0]);
    exit (1);
  }

  return 0;
}