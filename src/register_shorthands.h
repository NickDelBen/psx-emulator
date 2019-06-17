/******************************************************
 * Contains useful shorthand macros for the registers
 *
 * Created by: Nick DelBen
 * Created on: June 16, 2019
 ******************************************************/

#ifndef PSX_EMU_REGISTER_SHORTHANDS_H
#define PSX_EMU_REGISTER_SHORTHANDS_H

#define $pc pc /* Program counter register */

#define $zero 0x0 /* Zero Register. Always zero */

#define $at   registers[1]  /* Assembler Temporary */
#define $v0   registers[2]  /* Function return value 1 */
#define $v1   registers[3]  /* Function return value 2 */
#define $a0   registers[4]  /* Function argument 0 */
#define $a1   registers[5]  /* Function argument 1 */
#define $a2   registers[6]  /* Function argument 2 */
#define $a3   registers[7]  /* Function argument 3 */
#define $t0   registers[8]  /* Temporary register 0 */
#define $t1   registers[9]  /* Temporary register 1 */
#define $t2   registers[10] /* Temporary register 2 */
#define $t3   registers[11] /* Temporary register 3 */
#define $t4   registers[12] /* Temporary register 4 */
#define $t5   registers[13] /* Temporary register 5 */
#define $t6   registers[14] /* Temporary register 6 */
#define $t7   registers[15] /* Temporary register 7 */
#define $s0   registers[16] /* Saved Register 0 */
#define $s1   registers[17] /* Saved Register 1 */
#define $s2   registers[18] /* Saved Register 2 */
#define $s3   registers[19] /* Saved Register 3 */
#define $s4   registers[20] /* Saved Register 4 */
#define $s5   registers[21] /* Saved Register 5 */
#define $s6   registers[22] /* Saved Register 6 */
#define $s7   registers[23] /* Saved Register 7 */
#define $t8   registers[24] /* Temporary register 8 */
#define $t9   registers[25] /* Temporary register 9 */
#define $k0   registers[26] /* Kernel reserved register 0 */
#define $k1   registers[27] /* Kernel reserved register 1 */
#define $gp   registers[28] /* Global pointer */
#define $sp   registers[29] /* Stack pointer */
#define $dp   registers[30] /* Frame Pointer */
#define $ra   registers[31] /* Function return address */

#endif //PSX_EMU_REGISTER_SHORTHANDS_H
