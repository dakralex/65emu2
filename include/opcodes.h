/**
 * opcodes.h
 *
 * Definition of the instructions of a MOS 6502 CPU with their respective op codes.
 */

#ifndef INC_65EMU2_OPCODES_H
#define INC_65EMU2_OPCODES_H

typedef enum AddressMode {
    UNDEFINED_MODE,
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

} OpCode;

typedef struct opcode_t {
    OpCode code;
    AddressMode mode;
    const char name[3];
} opcode_t;

#define UNDEF_OPCODE {UNDEFINED_OP, UNDEFINED_MODE, ""}

#define ADC_NAME "adc"
#define AND_NAME "and"
#define ASL_NAME "asl"
#define BCC_NAME "bcc"
#define BCS_NAME "bcs"
#define BEQ_NAME "beq"
#define BIT_NAME "bit"
#define BMI_NAME "bmi"
#define BNE_NAME "bne"
#define BPL_NAME "bpl"
#define BRK_NAME "brk"
#define BVC_NAME "bvc"
#define BVS_NAME "bvs"
#define CLC_NAME "clc"
#define CLD_NAME "cld"
#define CLI_NAME "cli"
#define CLV_NAME "clv"
#define CMP_NAME "cmp"
#define CPX_NAME "cpx"
#define CPY_NAME "cpy"
#define DEC_NAME "dec"
#define DEX_NAME "dex"
#define DEY_NAME "dey"
#define EOR_NAME "eor"
#define INC_NAME "inc"
#define INX_NAME "inx"
#define INY_NAME "iny"
#define JMP_NAME "jmp"
#define JSR_NAME "jsr"
#define LDA_NAME "lda"
#define LDX_NAME "ldx"
#define LDY_NAME "ldy"
#define LSR_NAME "lsr"
#define NOP_NAME "nop"
#define ORA_NAME "ora"
#define PHA_NAME "pha"
#define PHP_NAME "php"
#define PLA_NAME "pla"
#define PLP_NAME "plp"
#define ROL_NAME "rol"
#define ROR_NAME "ror"
#define RTI_NAME "rti"
#define RTS_NAME "rts"
#define SBC_NAME "sbc"
#define SEC_NAME "sec"
#define SED_NAME "sed"
#define SEI_NAME "sei"
#define STA_NAME "sta"
#define STX_NAME "stx"
#define STY_NAME "sty"
#define TAX_NAME "tax"
#define TAY_NAME "tay"
#define TSX_NAME "tsx"
#define TXA_NAME "txa"
#define TXS_NAME "txs"
#define TYA_NAME "tya"

static opcode_t opcodes[UINT8_MAX] = {
    /* 0x0X instructions */
    {BRK, IMPLICIT, BRK_NAME},
    {ORA, INDEXED_INDIRECT, ORA_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {ORA, ZERO_PAGE, ORA_NAME},
    {ASL, ZERO_PAGE, ASL_NAME},
    UNDEF_OPCODE,
    {PHP, IMPLICIT, PHP_NAME},
    {ORA, IMMEDIATE, ORA_NAME},
    {ASL, ACCUMULATOR, ASL_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {ORA, ABSOLUTE, ORA_NAME},
    {ASL, ABSOLUTE, ASL_NAME},
    UNDEF_OPCODE,

    /* 0x1X instructions */
    {BPL, RELATIVE, BPL_NAME},
    {ORA, INDIRECT_INDEXED, ORA_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {ORA, ZERO_PAGE_X, ORA_NAME},
    {ASL, ZERO_PAGE_X, ASL_NAME},
    UNDEF_OPCODE,
    {CLC, IMPLICIT, CLC_NAME},
    {ORA, ABSOLUTE_Y, ORA_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {ORA, ABSOLUTE_X, ORA_NAME},
    {ASL, ABSOLUTE_X, ASL_NAME},
    UNDEF_OPCODE,

    /* 0x2X instructions */
    {JSR, ABSOLUTE, JSR_NAME},
    {AND, INDEXED_INDIRECT, AND_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {BIT, ZERO_PAGE, BIT_NAME},
    {AND, ZERO_PAGE, AND_NAME},
    {ROL, ZERO_PAGE, ROL_NAME},
    UNDEF_OPCODE,
    {PLP, IMPLICIT, PLP_NAME},
    {AND, IMMEDIATE, AND_NAME},
    {ROL, ACCUMULATOR, ROL_NAME},
    UNDEF_OPCODE,
    {BIT, ABSOLUTE, BIT_NAME},
    {AND, ABSOLUTE, AND_NAME},
    {ROL, ABSOLUTE, ROL_NAME},
    UNDEF_OPCODE,

    /* 0x3X instructions */
    {BMI, RELATIVE, BMI_NAME},
    {AND, INDIRECT_INDEXED, AND_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {AND, ZERO_PAGE_X, AND_NAME},
    {ROL, ZERO_PAGE_X, ROL_NAME},
    UNDEF_OPCODE,
    {SEC, IMPLICIT, SEC_NAME},
    {AND, ABSOLUTE_Y, AND_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {AND, ABSOLUTE_X, AND_NAME},
    {ROL, ABSOLUTE_X, ROL_NAME},
    UNDEF_OPCODE,

    /* 0x4X instructions */
    {RTI, IMPLICIT, RTI_NAME},
    {EOR, INDEXED_INDIRECT, EOR_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {EOR, ZERO_PAGE, EOR_NAME},
    {LSR, ZERO_PAGE, LSR_NAME},
    UNDEF_OPCODE,
    {PHA, IMPLICIT, PHA_NAME},
    {EOR, IMMEDIATE, EOR_NAME},
    {LSR, ACCUMULATOR, LSR_NAME},
    UNDEF_OPCODE,
    {JMP, ABSOLUTE, JMP_NAME},
    {EOR, ABSOLUTE, EOR_NAME},
    {LSR, ABSOLUTE, LSR_NAME},
    UNDEF_OPCODE,

    /* 0x5X instructions */
    {BVC, RELATIVE, BVC_NAME},
    {EOR, INDIRECT_INDEXED, EOR_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {EOR, ZERO_PAGE_X, EOR_NAME},
    {LSR, ZERO_PAGE_X, LSR_NAME},
    UNDEF_OPCODE,
    {CLI, IMPLICIT, CLI_NAME},
    {EOR, ABSOLUTE_Y, EOR_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {EOR, ABSOLUTE_X, EOR_NAME},
    {LSR, ABSOLUTE_X, LSR_NAME},
    UNDEF_OPCODE,

    /* 0x6X instructions */
    {RTS, IMPLICIT, RTS_NAME},
    {ADC, INDEXED_INDIRECT, ADC_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {ADC, ZERO_PAGE, ADC_NAME},
    {ROR, ZERO_PAGE, ROR_NAME},
    UNDEF_OPCODE,
    {PLA, IMPLICIT, PLA_NAME},
    {ADC, IMMEDIATE, ADC_NAME},
    {ROR, ACCUMULATOR, ROR_NAME},
    UNDEF_OPCODE,
    {JMP, INDIRECT, JMP_NAME},
    {ADC, ABSOLUTE, ADC_NAME},
    {ROR, ABSOLUTE, ROR_NAME},
    UNDEF_OPCODE,

    /* 0x7X instructions */
    {BVS, RELATIVE, BVS_NAME},
    {ADC, INDIRECT_INDEXED, ADC_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {ADC, ZERO_PAGE_X, ADC_NAME},
    {ROR, ZERO_PAGE_X, ROR_NAME},
    UNDEF_OPCODE,
    {SEI, IMPLICIT, SEI_NAME},
    {ADC, ABSOLUTE_Y, ADC_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {ADC, ABSOLUTE_X, ADC_NAME},
    {ROR, ABSOLUTE_X, ROR_NAME},
    UNDEF_OPCODE,

    /* 0x8A instructions */
    UNDEF_OPCODE,
    {STA, INDEXED_INDIRECT, STA_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {STY, ZERO_PAGE, STY_NAME},
    {STA, ZERO_PAGE, STA_NAME},
    {STX, ZERO_PAGE, STX_NAME},
    UNDEF_OPCODE,
    {DEY, IMPLICIT, DEY_NAME},
    UNDEF_OPCODE,
    {TXA, IMPLICIT, TXA_NAME},
    UNDEF_OPCODE,
    {STY, ABSOLUTE, STY_NAME},
    {STA, ABSOLUTE, STA_NAME},
    {STX, ABSOLUTE, STX_NAME},
    UNDEF_OPCODE,

    /* 0x9A instructions */
    {BCC, RELATIVE, BCC_NAME},
    {STA, INDIRECT_INDEXED, STA_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {STY, ZERO_PAGE_X, STY_NAME},
    {STA, ZERO_PAGE_X, STA_NAME},
    {STX, ZERO_PAGE_Y, STX_NAME},
    UNDEF_OPCODE,
    {TYA, IMPLICIT, TYA_NAME},
    {STA, ABSOLUTE_Y, STA_NAME},
    {TXS, IMPLICIT, TXS_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {STA, ABSOLUTE_X, STA_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,

    /* 0xAX instructions */
    {LDY, IMMEDIATE, LDY_NAME},
    {LDA, INDEXED_INDIRECT, LDA_NAME},
    {LDX, IMMEDIATE, LDX_NAME},
    UNDEF_OPCODE,
    {LDY, ZERO_PAGE, LDY_NAME},
    {LDA, ZERO_PAGE, LDA_NAME},
    {LDX, ZERO_PAGE, LDX_NAME},
    UNDEF_OPCODE,
    {TAY, IMPLICIT, TAY_NAME},
    {LDA, IMMEDIATE, LDA_NAME},
    {TAX, IMPLICIT, TAX_NAME},
    UNDEF_OPCODE,
    {LDY, ABSOLUTE, LDY_NAME},
    {LDA, ABSOLUTE, LDA_NAME},
    {LDX, ABSOLUTE, LDX_NAME},
    UNDEF_OPCODE,

    /* 0xBX instructions */
    {BCS, RELATIVE, BCS_NAME},
    {LDA, INDIRECT_INDEXED, LDA_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {LDY, ZERO_PAGE_X, LDY_NAME},
    {LDA, ZERO_PAGE_X, LDA_NAME},
    {LDX, ZERO_PAGE_Y, LDX_NAME},
    UNDEF_OPCODE,
    {CLV, IMPLICIT, CLV_NAME},
    {LDA, ABSOLUTE_Y, LDA_NAME},
    {TSX, IMPLICIT, TSX_NAME},
    UNDEF_OPCODE,
    {LDY, ABSOLUTE_X, LDY_NAME},
    {LDA, ABSOLUTE_X, LDA_NAME},
    {LDX, ABSOLUTE_Y, LDX_NAME},
    UNDEF_OPCODE,

    /* 0xCX instructions */
    {CPY, IMMEDIATE, CPY_NAME},
    {CMP, INDEXED_INDIRECT, CMP_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {CPY, ZERO_PAGE, CPY_NAME},
    {CMP, ZERO_PAGE, CMP_NAME},
    {DEC, ZERO_PAGE, DEC_NAME},
    UNDEF_OPCODE,
    {INY, IMPLICIT, INY_NAME},
    {CMP, IMMEDIATE, CMP_NAME},
    {DEX, IMPLICIT, DEX_NAME},
    UNDEF_OPCODE,
    {CPY, ABSOLUTE, CPY_NAME},
    {CMP, ABSOLUTE, CMP_NAME},
    {DEC, ABSOLUTE, DEC_NAME},
    UNDEF_OPCODE,

    /* 0xDX instructions */
    {BNE, RELATIVE, BNE_NAME},
    {CMP, INDIRECT_INDEXED, CMP_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {CMP, ZERO_PAGE_X, CMP_NAME},
    {DEC, ZERO_PAGE_X, DEC_NAME},
    UNDEF_OPCODE,
    {CLD, IMPLICIT, CLD_NAME},
    {CMP, ABSOLUTE_Y, CMP_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {CMP, ABSOLUTE_X, CMP_NAME},
    {DEC, ABSOLUTE_X, DEC_NAME},
    UNDEF_OPCODE,

    /* 0xEX instructions */
    {CPX, IMMEDIATE, CPX_NAME},
    {SBC, INDEXED_INDIRECT, SBC_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {CPX, ZERO_PAGE, CPX_NAME},
    {SBC, ZERO_PAGE, SBC_NAME},
    {INC, ZERO_PAGE, INC_NAME},
    UNDEF_OPCODE,
    {INX, IMPLICIT, INX_NAME},
    {SBC, IMMEDIATE, SBC_NAME},
    {NOP, IMPLICIT, NOP_NAME},
    UNDEF_OPCODE,
    {CPX, ABSOLUTE, CPX_NAME},
    {SBC, ABSOLUTE, SBC_NAME},
    {INC, ABSOLUTE, INC_NAME},
    UNDEF_OPCODE,

    /* 0xFX instructions */
    {BEQ, RELATIVE, BEQ_NAME},
    {SBC, INDIRECT_INDEXED, SBC_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {SBC, ZERO_PAGE_X, SBC_NAME},
    {INC, ZERO_PAGE_X, INC_NAME},
    UNDEF_OPCODE,
    {SED, IMPLICIT, SED_NAME},
    {SBC, ABSOLUTE_Y, SBC_NAME},
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    UNDEF_OPCODE,
    {SBC, ABSOLUTE_X, SBC_NAME},
    {INC, ABSOLUTE_X, INC_NAME},
};

#endif //INC_65EMU2_OPCODES_H
