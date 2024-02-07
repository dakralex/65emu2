/**
 * opcodes.h
 *
 * Definition of the instructions of a MOS 6502 CPU with their respective op codes.
 */

#ifndef INC_65EMU2_OPCODE_H
#define INC_65EMU2_OPCODE_H

typedef enum AddressMode {
    UNDEFINED_MODE,

    /**
     * Implicit mode
     *
     * Instructions in implicit addressing mode do not have any operand as they
     * work on a specific location that is implied by the instruction itself,
     * e.g. CLC clears the carry flag in the processor status register.
     */
    IMPLICIT,

    /**
     * Accumulator mode
     *
     * Instructions in accumulator addressing mode do not have any operand as
     * they work on the accumulator register.
     */
    ACCUMULATOR,

    /**
     * Immediate value mode
     *
     * Instructions in immediate addressing mode have a single byte constant
     * operand, which is used as a value for the instruction itself instead of
     * fetching a specific memory location.
     */
    IMMEDIATE,

    /**
     * Zero paging
     *
     * Instructions in zero page addressing mode work with a single byte
     * operand, which is used to fetch a memory location in the first 256 bytes
     * of memory (as that is the limit on what can be addressed with a single
     * byte).
     */
    ZERO_PAGE,

    /**
     * Zero paging + X index register
     *
     * Instructions in zero page X addressing mode work with a single byte
     * operand, which the current value of the X index register is added to and
     * then used to calculate a zero page address, that is the resulting memory
     * address is byte-sized and therefore cannot exceed 0xFF.
     */
    ZERO_PAGE_X,

    /**
     * Zero Paging + Y index register
     *
     * Instructions in zero page Y addressing mode work with a single byte
     * operand, which the current value of the Y index register is added to and
     * then used to calculate a zero page address, that is the resulting memory
     * address is byte-sized and therefore cannot exceed 0xFF.
     */
    ZERO_PAGE_Y,

    /**
     * Relative addressing
     *
     * Instructions in relative addressing mode (which are only branch
     * instructions) work with a single byte operand, which is a signed byte
     * integer to calculate the relative memory location for the program
     * counter if the condition is true.
     */
    RELATIVE,

    /**
     * Absolute addressing
     *
     * Instructions in absolute addressing mode work with a double byte
     * operand, which is used for fetching any specified memory location.
     */
    ABSOLUTE,

    /**
     * Absolute addressing + X index register
     *
     * Instructions in absolute X addressing mode work with a double byte
     * operand, which the current value of the X index register is added to and
     * then used to calculate any memory location, which will be used for the
     * instruction.
     */
    ABSOLUTE_X,

    /**
     * Absolute addressing + Y index register
     *
     * Instructions in absolute Y addressing mode work with a double byte
     * operand, which the current value of the Y index register is added to and
     * then used to calculate any memory location, which will be used for the
     * instruction.
     */
    ABSOLUTE_Y,

    /**
     * Indirection addressing
     *
     * Instructions in indirect addressing mode work with a double byte operand,
     * which is used to fetch a memory location whose value is used as the
     * actual target value. This addressing mode is only available for the JMP
     * instruction.
     */
    INDIRECT,
    INDEXED_INDIRECT,
    INDIRECT_INDEXED,
} AddressMode;

typedef enum OpCode {
    UNDEFINED_OP,

    /**
     * ADC - ADd with Carry instruction
     */
    ADC,

    /**
     * AND - logical AND instruction
     */
    AND,

    /**
     * ASL - Arithmetic Shift Left instruction
     */
    ASL,

    /**
     * BCC - Branch if Carry Clear instruction
     */
    BCC,

    /**
     * BCS - Branch if Carry Set instruction
     */
    BCS,

    /**
     * BEQ - Branch if EQual instruction
     */
    BEQ,

    /**
     * BIT - BIt test instruction
     */
    BIT,

    /**
     * BMI - Branch if MInus instruction
     */
    BMI,

    /**
     * BNE - Branch if Not Equal instruction
     */
    BNE,

    /**
     * BPL - Branch if Positive instruction
     */
    BPL,

    /**
     * BRK - force interrupt (BReaK) instruction
     */
    BRK,

    /**
     * BVC - Branch if Overflow Clear instruction
     */
    BVC,

    /**
     * BVS - Branch if Overflow Set instruction
     */
    BVS,

    /**
     * CLC - CLear Carry flag instruction
     */
    CLC,

    /**
     * CLD - CLear Decimal mode instruction
     */
    CLD,

    /**
     * CLI - CLear Interrupt disable instruction
     */
    CLI,

    /**
     * CLV - CLear oVerflow flag instruction
     */
    CLV,

    /**
     * CMP - CoMPare instruction
     */
    CMP,

    /**
     * CPX - ComPare X register instruction
     */
    CPX,

    /**
     * CPY - ComPare Y register instruction
     */
    CPY,

    /**
     * DEC - DECrement memory instruction
     */
    DEC,

    /**
     * DEX - DEcrement X register instruction
     */
    DEX,

    /**
     * DEY - DEcrement Y register instruction
     */
    DEY,

    /**
     * EOR - logical Exclusive OR instruction
     */
    EOR,

    /**
     * INC - INCrement memory instruction
     */
    INC,

    /**
     * INX - INcrement X register instruction
     */
    INX,

    /**
     * INY - INcrement Y register instruction
     */
    INY,

    /**
     * JMP - JuMP instruction
     */
    JMP,

    /**
     * JSR - Jump to SubRoutine instruction
     */
    JSR,

    /**
     * LDA - LoaD Accumulator instruction
     */
    LDA,

    /**
     * LDX - LoaD X register instruction
     */
    LDX,

    /**
     * LDY - LoaD Y register instruction
     */
    LDY,

    /**
     * LSR - Logical Shift Right instruction
     */
    LSR,

    /**
     * NOP - No OPeration instruction
     */
    NOP,

    /**
     * ORA - logical inclusive OR on Accumulator instruction
     */
    ORA,

    /**
     * PHA - PusH Accumulator instruction
     */
    PHA,

    /**
     * PHP - PusH Processor status instruction
     */
    PHP,

    /**
     * PLA - PuLl Accumulator instruction
     */
    PLA,

    /**
     * PLP - PuLl Processor status instruction
     */
    PLP,

    /**
     * ROL - ROtate Left instruction
     */
    ROL,

    /**
     * ROR - ROtate Right instruction
     */
    ROR,

    /**
     * RTI - ReTurn from Interrupt instruction
     */
    RTI,

    /**
     * RTS - ReTurn from Subroutine instruction
     */
    RTS,

    /**
     * SBC - SuBtract with Carry instruction
     */
    SBC,

    /**
     * SEC - SEt Carry flag instruction
     */
    SEC,

    /**
     * SED - SEt Decimal mode instruction
     */
    SED,

    /**
     * SEI - SEt Interrupt disable flag instruction
     */
    SEI,

    /**
     * STA - STore Accumulator instruction
     */
    STA,

    /**
     * STX - STore X register instruction
     */
    STX,

    /**
     * STY - STore Y register instruction
     */
    STY,

    /**
     * TAX - Transfer Accumulator to X register instruction
     */
    TAX,

    /**
     * TAY - Transfer Accumulator to Y register instruction
     */
    TAY,

    /**
     * TSX - Transfer Stack pointer to X register instruction
     */
    TSX,

    /**
     * TXA - Transfer X register to Accumulator instruction
     */
    TXA,

    /**
     * TXS - Transfer X register to Stack pointer instruction
     */
    TXS,

    /**
     * TYA - Transfer Y register to Accumulator instruction
     */
    TYA,

    /**
     * Size of the opcode enumeration
     */
    OPCODE_SIZE,

} OpCode;

typedef struct opcode_t {
    OpCode code;
    AddressMode mode;
} opcode_t;

/**
 * Returns the corresponding opcode for the specified byte.
 *
 * @param byte byte to be decoded
 * @return opcode decoded from byte
 */
const opcode_t*
decode_opcode (const uint8_t* byte);

/**
 * Returns the corresponding three letter name for the specified op code.
 *
 * @param opcode opcode to get the name for
 * @return name string for the op code.
 */
const char*
get_opcode_name (const opcode_t* opcode);

#endif //INC_65EMU2_OPCODE_H
