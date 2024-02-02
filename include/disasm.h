/**
 * disasm.h
 *
 * Disassembler for MOS 6502 binaries.
 */

#ifndef SFEMU2_CPU_H
#define SFEMU2_CPU_H

void
disassemble (const unsigned char* buf, size_t fsize, FILE* dest);

int
main (int argc, char* argv[]);

#endif //SFEMU2_CPU_H
