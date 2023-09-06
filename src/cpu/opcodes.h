/**
 * @file opcodes.h
 *
 * CHIP8 Core OpCodes
 * @author Caglar Kantarcioglu
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "cpu.h"

#ifndef OPCODES_H
#define OPCODES_H

/**
 * OpCode 00E0: 0x0000 -> 0x00E0
 * Clears the screen.
 */
void OP_00E0(struct CPU *cpu, struct RAM *ram);

/**
 * OpCode: 00EE: 0x000 -> 0x00EE
 * Returns from subroutine
 */
void OP_00EE(struct CPU *cpu);

/**
 * OpCode: 1NNN -> 0x1000
 * Jumps to address NNN
 */
void OP_1NNN(struct CPU *cpu, uint16_t nnn);

/**
 * OpCode: 2NNN: 0x2000
 * Calls subroutine at NNN
 */
void OP_2NNN(struct CPU *cpu, uint16_t nnn);

/**
 * OpCode: 3XNN: 0x3000
 * Skips the next instruction if VX equals NN
 */
void OP_3XNN(struct CPU *cpu, uint8_t x, uint8_t nn);

/**
 * OpCode: 4XNN: 0x4000
 * Skips the next instruction if VX does not equal NN
 */
void OP_4XNN(struct CPU *cpu, uint8_t x, uint8_t nn);

/**
 * OpCode: 5XY0: 0x5000
 * Skips the next instruction if VX equals VY
 */
void OP_5XY0(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: 6XNN: 0x6000
 * Sets VX to NN
 */
void OP_6XNN(struct CPU *cpu, uint8_t x, uint8_t nn);

/**
 * OpCode 0x7000
 * Adds NN to VX (carry flag is not changed)
 */
void OP_7XNN(struct CPU *cpu, uint8_t x, uint8_t nn);

/**
 * OpCode: 8XYO: 0x8000 -> 0x0
 * Sets VX to the value of VY
 */
void OP_8XY0(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: 8XY1: 0x8000 -> 0x1
 * Sets VX to VX or VY
 */
void OP_8XY1(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: 8XY2: 0x8000 -> 0x2
 * Sets VX to VX and VY
 */
void OP_8XY2(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: 8XY3: 0x8000 -> 0x3
 * Sets VX to VX xor VY
 */
void OP_8XY3(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: 8XY4: 0x8000 -> 0x4
 * Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there is not
 */
void OP_8XY4(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: 8XY5: 0x8000 -> 0x5
 * VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there is not
 */
void OP_8XY5(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: 8XY6: 0x8000 -> 0x6
 * Stores the least significant bit of VX in VF and then shifts VX to the right by 1
 */
void OP_8XY6(struct CPU *cpu, uint8_t x);

/**
 * OpCode: 8XY7: 0x8000 -> 0x7
 * Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there is not
 */
void OP_8XY7(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: 8XYE: 0x8000 -> 0xE
 * Stores the most significant bit of VX in VF and then shifts VX to the left by 1
 */
void OP_8XYE(struct CPU *cpu, uint8_t x);

/**
 * OpCode: 9XY0: 0x9000
 * Skips the next instruction if VX does not equal VY
 */
void OP_9XY0(struct CPU *cpu, uint8_t x, uint8_t y);

/**
 * OpCode: ANNN: 0xA000
 * Sets I to the address NNN
 */
void OP_ANNN(struct CPU *cpu, uint16_t nnn);

/**
 * OpCode: BNNN: 0xB000
 * Sets I to the address NNN
 */
void OP_BNNN(struct CPU *cpu, uint16_t nnn);

/**
 * OpCode: CXNN: 0xC000
 * Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN
 */
void OP_CXNN(struct CPU *cpu, uint8_t x, uint8_t nn);

/**
 * OpCode: DXYN: 0xD000
 * Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels.
 */
void OP_DXYN(struct CPU *cpu, struct RAM *ram, uint8_t x, uint8_t y, uint8_t n);

/**
 * OpCode FX07: 0xF000 -> 0x07
 * Sets VX to the value of the delay timer
 */
void OP_FX07(struct CPU *cpu, uint8_t x);

/**
 * OpCode FX0A: 0xF000 -> 0x0A
 * A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key event).
 */
void OP_FX0A(struct CPU *cpu, uint8_t x);


/**
 * OpCode: FX15: 0xF000 -> 0x15
 * Sets the delay timer to VX
 */
void OP_FX15(struct CPU *cpu, uint8_t x);

/**
 * OpCode: FX18: 0xF000 -> 0x18
 * Sets the sound timer to VX
 */
void OP_FX18(struct CPU *cpu, uint8_t x);

/**
 * OpCode FX1E: 0xF000 -> 0x1E
 * Adds VX to I. VF is not affected
 */
void OP_FX1E(struct CPU *cpu, uint8_t x);

/**
 * OpCode: FX29: 0xF000 -> 0x29
 * Sets I to the location of the sprite for the character in VX
 */
void OP_FX29(struct CPU *cpu, uint8_t x);

/**
 * OpCode: FX33: 0xF000 -> 0x33
 * Stores the binary-coded decimal representation of VX, with the hundred's digit in memory at location in I
 */
void OP_FX33(struct CPU *cpu, struct RAM *ram, uint8_t x);

/**
 * OpCode: FX55: 0xF000 -> 0x55
 * Stores from V0 to VX (including VX) in memory, starting at address I
 */
void OP_FX55(struct CPU *cpu, struct RAM *ram, uint8_t x);

/**
 * OpCode: FX65: 0xF000 -> 0x65
 * Fills from V0 to VX (including VX) with values from memory, starting at address I
 */
void OP_FX65(struct CPU *cpu, struct RAM *ram, uint8_t x);

/**
 * OpCode: EX95: 0xE0000 -> 0x9E
 * Skips the next instruction if the key stored in VX is pressed
 */
void OP_EX9E(struct CPU *cpu, uint8_t x);

/**
 * OpCode: EXA1: 0xE0000 -> 0xA1
 * Skips the next instruction if the key stored in VX is not pressed
 */
void OP_EXA1(struct CPU *cpu, uint8_t x);

#endif