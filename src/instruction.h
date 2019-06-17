/******************************************************
 * Contains description of a MIPS instruction
 *
 * Created by: Nick DelBen
 * Created on: June 16, 2019
 ******************************************************/

#ifndef PSX_EMU_INSTRUCTION_H
#define PSX_EMU_INSTRUCTION_H

#include <cstdint>

#define CPU_OP_MASK_SUBFN    0x3F
#define CPU_OP_MASK_REG_IDX  0x1F
#define CPU_OP_MASK_IMM      0xFFFF
#define CPU_OP_MASK_SHFT_IMM 0x1F
#define CPU_OP_MASK_JMP_IMM  0x3FFFFFF

#define CPU_OP_OFF_FN       26
#define CPU_OP_OFF_IDX_RT   16
#define CPU_OP_OFF_IDX_RS   21
#define CPU_OP_OFF_SHIFT_IM 6

namespace PSX {
    class Instruction {
    public:
        uint32_t operation;
        // Creates a new instruction
        Instruction(uint32_t operation);
        // Return the function of the instruction [31:26]
        uint32_t function();
        // Return the sub-function for this operation
        uint32_t subfunction();
        // Returns the register index [20:16]
        uint32_t rt();
        // Returns the register index [25:21]
        uint32_t rs();
        // Returns the immediate value [16:0]
        uint32_t immediate();
        // Returns the register index [15:11]
        uint32_t rd();
        // Returns the immediate value as a sign-extended 32 bit value
        uint32_t immediate_se();
        // Returns the shift amount immediate value [10:6]
        uint32_t shift();
        // Returns the imm jump value
        uint32_t immediate_jump();
    };
}


#endif //PSX_EMU_INSTRUCTION_H
