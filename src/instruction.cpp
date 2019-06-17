//
// Created by nickd on 6/17/2019.
//

#include "instruction.h"

#include <iostream>
#include <bitset>

namespace PSX {
    // Construct new instance of an instruction
    Instruction::Instruction(uint32_t operation) :
        operation(operation){
    }

    // Return the function of the instruction [31:26]
    uint32_t Instruction::function() {
        return operation >> CPU_OP_OFF_FN;
    }

    // Return the sub-function for this operation
    uint32_t Instruction::subfunction() {
        return operation & CPU_OP_MASK_SUBFN;
    }

    // Returns the register index [20:16]
    uint32_t Instruction::rt() {
        return (operation >> CPU_OP_OFF_IDX_RT) & CPU_OP_MASK_REG_IDX;
    }

    // Returns the register index [25:21]
    uint32_t Instruction::rs() {
        return (operation >> CPU_OP_OFF_IDX_RS) & CPU_OP_MASK_REG_IDX;
    }

    // Returns the immediate value [16:0]
    uint32_t Instruction::immediate() {
        return operation & CPU_OP_MASK_IMM;
    }

    // Returns the immediate value as a sign-extended 32 bit value
    //TODO: Ensure sign extending works
    uint32_t Instruction::immediate_se() {
        uint32_t temp = operation & CPU_OP_MASK_IMM;
        return (temp >> 15 == 0) ? temp : (temp | 0xFFFF0000);
    }

    // Returns the register index bits [15:11]
    uint32_t Instruction::rd() {
        return (operation >> 11) & CPU_OP_MASK_REG_IDX;
    }

    // Returns the shift amount immediate value [10:6]
    uint32_t Instruction::shift() {
        return (operation >> CPU_OP_OFF_SHIFT_IM) * CPU_OP_MASK_SHFT_IMM;
    }

    // Returns the imm jump value
    uint32_t Instruction::immediate_jump() {
        return operation & CPU_OP_MASK_JMP_IMM;
    }


}