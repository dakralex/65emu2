/**
 * opcodes.h
 *
 * Definition of the instructions of a MOS 6502 CPU with their respective op codes.
 */

#ifndef SFEMU2_OPCODES_H
#define SFEMU2_OPCODES_H

enum AddressMode {
    IMPLICIT,
    ACCUMULATOR,
    IMMEDIATE,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    RELATIVE,
    ABSOLUTE,
    ABSOLUTE_X,
    ABSOLUTE_Y,
    INDIRECT,
    INDEXED_INDIRECT,
    INDIRECT_INDEXED,
};

struct Instruction {
    unsigned char code;
    char code_name[3];
    enum AddressMode address_mode;
};

enum OpCode {
    /**
     * ADD - ADd with Carry instruction
     */

    ADC_ABSOLUTE = 0x6d,
    ADC_ABSOLUTE_X = 0x7d,
    ADC_ABSOLUTE_Y = 0x79,
    ADC_IMMEDIATE = 0x69,
    ADC_INDEXED_INDIRECT = 0x61,
    ADC_INDIRECT_INDEXED = 0x71,
    ADC_ZERO_PAGE = 0x65,
    ADC_ZERO_PAGE_X = 0x75,

    /**
     * AND - logical AND instruction
     */

    AND_ABSOLUTE = 0x2d,
    AND_ABSOLUTE_X = 0x3d,
    AND_ABSOLUTE_Y = 0x39,
    AND_IMMEDIATE = 0x29,
    AND_INDEXED_INDIRECT = 0x21,
    AND_INDIRECT_INDEXED = 0x31,
    AND_ZERO_PAGE = 0x25,
    AND_ZERO_PAGE_X = 0x35,

    /**
     * ASL - Arithmetic Shift Left instruction
     */

    ASL_ABSOLUTE = 0x0e,
    ASL_ABSOLUTE_X = 0x1e,
    ASL_ACCUMULATOR = 0x0a,
    ASL_ZERO_PAGE = 0x06,
    ASL_ZERO_PAGE_X = 0x16,

    /**
     * BCC - Branch if Carry Clear instruction
     */

    BCC_RELATIVE = 0x90,

    /**
     * BCS - Branch if Carry Set instruction
     */

    BCS_RELATIVE = 0xb0,

    /**
     * BEQ - Branch if EQual instruction
     */
    BEQ_RELATIVE = 0xf0,

    /**
     * BIT - BIt test instruction
     */

    BIT_ABSOLUTE = 0x2c,
    BIT_ZERO_PAGE = 0x24,

    /**
     * BMI - Branch if MInus instruction
     */

    BMI_RELATIVE = 0x30,

    /**
     * BNE - Branch if Not Equal instruction
     */

    BNE_RELATIVE = 0xd0,

    /**
     * BPL - Branch if Positive instruction
     */

    BPL_RELATIVE = 0x10,

    /**
     * BRK - force interrupt (BReaK) instruction
     */

    BRK_IMPLICIT = 0x00,

    /**
     * BVC - Branch if Overflow Clear instruction
     */

    BVC_RELATIVE = 0x50,

    /**
     * BVS - Branch if Overflow Set instruction
     */

    BVS_RELATIVE = 0x70,

    /**
     * CLC - CLear Carry flag instruction
     */

    CLC_IMPLICIT = 0x18,

    /**
     * CLD - CLear Decimal mode instruction
     */

    CLD_IMPLICIT = 0xd8,

    /**
     * CLI - CLear Interrupt disable instruction
     */

    CLI_IMPLICIT = 0x58,

    /**
     * CLV - CLear oVerflow flag instruction
     */

    CLV_IMPLICIT = 0xb8,

    /**
     * CMP - CoMPare instruction
     */

    CMP_ABSOLUTE = 0xcd,
    CMP_ABSOLUTE_X = 0xdd,
    CMP_ABSOLUTE_Y = 0xd9,
    CMP_IMMEDIATE = 0xc9,
    CMP_INDEXED_INDIRECT = 0xc1,
    CMP_INDIRECT_INDEXED = 0xd1,
    CMP_ZERO_PAGE = 0xc5,
    CMP_ZERO_PAGE_X = 0xd5,

    /**
     * CPX - ComPare X register instruction
     */

    CPX_ABSOLUTE = 0xec,
    CPX_IMMEDIATE = 0xe0,
    CPX_ZERO_PAGE = 0xe4,

    /**
     * CPY - ComPare Y register instruction
     */

    CPY_ABSOLUTE = 0xcc,
    CPY_IMMEDIATE = 0xc0,
    CPY_ZERO_PAGE = 0xc4,

    /**
     * DEC - DECrement memory instruction
     */

    DEC_ABSOLUTE = 0xce,
    DEC_ABSOLUTE_X = 0xde,
    DEC_ZERO_PAGE = 0xc6,
    DEC_ZERO_PAGE_X = 0xd6,

    /**
     * DEX - DEcrement X register instruction
     */

    DEX_IMPLICIT = 0xca,

    /**
     * DEY - DEcrement Y register instruction
     */

    DEY_IMPLICIT = 0x88,

    /**
     * EOR - logical Exclusive OR instruction
     */

    EOR_ABSOLUTE = 0x4d,
    EOR_ABSOLUTE_X = 0x5d,
    EOR_ABSOLUTE_Y = 0x59,
    EOR_IMMEDIATE = 0x49,
    EOR_INDEXED_INDIRECT = 0x41,
    EOR_INDIRECT_INDEXED = 0x51,
    EOR_ZERO_PAGE = 0x45,
    EOR_ZERO_PAGE_X = 0x55,

    /**
     * INC - INCrement memory instruction
     */

    INC_ABSOLUTE = 0xee,
    INC_ABSOLUTE_X = 0xfe,
    INC_ZERO_PAGE = 0xe6,
    INC_ZERO_PAGE_X = 0xf6,

    /**
     * INX - INcrement X register instruction
     */

    INX_IMPLICIT = 0xe8,

    /**
     * INY - INcrement Y register instruction
     */

    INY_IMPLICIT = 0xc8,

    /**
     * JMP - JuMP instruction
     */

    JMP_ABSOLUTE = 0x4c,
    JMP_INDIRECT = 0x6c,

    /**
     * JSR - Jump to SubRoutine instruction
     */

    JSR_ABSOLUTE = 0x20,

    /**
     * LDA - LoaD Accumulator instruction
     */

    LDA_ABSOLUTE = 0xad,
    LDA_ABSOLUTE_X = 0xbd,
    LDA_ABSOLUTE_Y = 0xb9,
    LDA_IMMEDIATE = 0xa9,
    LDA_INDEXED_INDIRECT = 0xa1,
    LDA_INDIRECT_INDEXED = 0xb1,
    LDA_ZERO_PAGE = 0xa5,
    LDA_ZERO_PAGE_X = 0xb5,

    /**
     * LDX - LoaD X register instruction
     */

    LDX_ABSOLUTE = 0xae,
    LDX_ABSOLUTE_Y = 0xbe,
    LDX_IMMEDIATE = 0xa2,
    LDX_ZERO_PAGE = 0xa6,
    LDX_ZERO_PAGE_Y = 0xb6,

    /**
     * LDY - LoaD Y register instruction
     */

    LDY_ABSOLUTE = 0xac,
    LDY_ABSOLUTE_X = 0xbc,
    LDY_IMMEDIATE = 0xa0,
    LDY_ZERO_PAGE = 0xa4,
    LDY_ZERO_PAGE_X = 0xb4,

    /**
     * LSR - Logical Shift Right instruction
     */

    LSR_ABSOLUTE = 0x4e,
    LSR_ABSOLUTE_X = 0x5e,
    LSR_ACCUMULATOR = 0x4a,
    LSR_ZERO_PAGE = 0x46,
    LSR_ZERO_PAGE_X = 0x56,

    /**
     * NOP - No OPeration instruction
     */

    NOP_IMPLICIT = 0xea,

    /**
     * ORA - logical inclusive OR on Accumulator instruction
     */

    ORA_ABSOLUTE = 0x0d,
    ORA_ABSOLUTE_X = 0x1d,
    ORA_ABSOLUTE_Y = 0x19,
    ORA_IMMEDIATE = 0x09,
    ORA_INDEXED_INDIRECT = 0x01,
    ORA_INDIRECT_INDEXED = 0x11,
    ORA_ZERO_PAGE = 0x05,
    ORA_ZERO_PAGE_X = 0x15,

    /**
     * PHA - PusH Accumulator instruction
     */

    PHA_IMPLICIT = 0x48,

    /**
     * PHP - PusH Processor status instruction
     */

    PHP_IMPLICIT = 0x08,

    /**
     * PLA - PuLl Accumulator instruction
     */

    PLA_IMPLICIT = 0x68,

    /**
     * PLP - PuLl Processor status instruction
     */

    PLP_IMPLICIT = 0x28,

    /**
     * ROL - ROtate Left instruction
     */

    ROL_ABSOLUTE = 0x2e,
    ROL_ABSOLUTE_X = 0x3e,
    ROL_ACCUMULATOR = 0x2a,
    ROL_ZERO_PAGE = 0x26,
    ROL_ZERO_PAGE_X = 0x36,

    /**
     * ROR - ROtate Right instruction
     */

    ROR_ABSOLUTE = 0x7e,
    ROR_ABSOLUTE_X = 0x6e,
    ROR_ACCUMULATOR = 0x6a,
    ROR_ZERO_PAGE = 0x66,
    ROR_ZERO_PAGE_X = 0x76,

    /**
     * RTI - ReTurn from Interrupt instruction
     */

    RTI_IMPLICIT = 0x40,

    /**
     * RTS - ReTurn from Subroutine instruction
     */

    RTS_IMPLICIT = 0x60,

    /**
     * SBC - SuBtract with Carry instruction
     */

    SBC_ABSOLUTE = 0xed,
    SBC_ABSOLUTE_X = 0xfd,
    SBC_ABSOLUTE_Y = 0xf9,
    SBC_IMMEDIATE = 0xe9,
    SBC_INDEXED_INDIRECT = 0xe1,
    SBC_INDIRECT_INDEXED = 0xf1,
    SBC_ZERO_PAGE = 0xe5,
    SBC_ZERO_PAGE_X = 0xf5,

    /**
     * SEC - SEt Carry flag instruction
     */

    SEC_IMPLICIT = 0x38,

    /**
     * SED - SEt Decimal mode instruction
     */

    SED_IMPLICIT = 0xf8,

    /**
     * SEI - SEt Interrupt disable flag instruction
     */

    SEI_IMPLICIT = 0x78,

    /**
     * STA - STore Accumulator instruction
     */

    STA_ABSOLUTE = 0x8d,
    STA_ABSOLUTE_X = 0x9d,
    STA_ABSOLUTE_Y = 0x99,
    STA_INDEXED_INDIRECT = 0x81,
    STA_INDIRECT_INDEXED = 0x91,
    STA_ZERO_PAGE = 0x85,
    STA_ZERO_PAGE_X = 0x95,

    /**
     * STX - STore X register instruction
     */

    STX_ABSOLUTE = 0x8e,
    STX_ZERO_PAGE = 0x86,
    STX_ZERO_PAGE_Y = 0x96,

    /**
     * STY - STore Y register instruction
     */

    STY_ABSOLUTE = 0x8c,
    STY_ZERO_PAGE = 0x84,
    STY_ZERO_PAGE_X = 0x94,

    /**
     * TAX - Transfer Accumulator to X register instruction
     */

    TAX_IMPLICIT = 0xaa,

    /**
     * TAY - Transfer Accumulator to Y register instruction
     */

    TAY_IMPLICIT = 0xa8,

    /**
     * TSX - Transfer Stack pointer to X register instruction
     */

    TSX_IMPLICIT = 0xba,

    /**
     * TXA - Transfer X register to Accumulator instruction
     */

    TXA_IMPLICIT = 0x8a,

    /**
     * TXS - Transfer X register to Stack pointer instruction
     */

    TXS_IMPLICIT = 0x9a,

    /**
     * TYA - Transfer Y register to Accumulator instruction
     */

    TYA_IMPLICIT = 0x98,
};

#endif //SFEMU2_OPCODES_H
