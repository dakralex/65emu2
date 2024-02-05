/**
 * disasm.h
 *
 * Disassembler for MOS 6502 binaries.
 */

#ifndef INC_65EMU2_DIS_ASM_H
#define INC_65EMU2_DIS_ASM_H

void
disassemble (const unsigned char* buf, size_t fsize, FILE* dest);

int
main (int argc, char* argv[]);

#endif //INC_65EMU2_DIS_ASM_H
