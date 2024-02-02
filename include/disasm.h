/**
 * disasm.h
 *
 * Disassembler for MOS 6502 binaries.
 */

#ifndef SFEMU2_CPU_H
#define SFEMU2_CPU_H

void
dis_asm_bin (FILE* fp);

int
main (int argc, char* argv[]);

#endif //SFEMU2_CPU_H
