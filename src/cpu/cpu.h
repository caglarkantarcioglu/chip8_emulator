/**
 * @file cpu.h
 *
 * Central Processing Unit (CPU) of the CHIP8 Emulator
 * @author Caglar Kantarcioglu
 */

#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define REGISTER_SIZE 16
#define STACK_SIZE 16
#define KEYPAD_SIZE 16

struct CPU {
    /**
     * Program Counter
     * Points to the current instruction in memory
     */
    uint16_t pc;

    /**
     * Registers (V0, V1, ..., VF)
     * For carry, borrow and pixel collision
     */
    uint8_t V[REGISTER_SIZE];

    /**
     * Index
     * Used to point at locations in memory
     */
    uint16_t I;

    /**
     * Stack
     * Store return addresses when subroutines are called
     */
    uint16_t stack[STACK_SIZE];
    uint8_t sp;

    /**
     * Timers
     * Delay Timer: Used for timing the events
     * Sound Timer: Used for sound effects
     */
    uint8_t delayTimer;
    uint8_t soundTimer;

    // Keypad
    uint8_t keypad[16];
};

struct CPU *createCPU();

void CPU_Step(struct CPU *cpu, struct RAM *ram);

uint16_t CPU_FetchOpCode(struct CPU *cpu, struct RAM *ram);

void CPU_DecodeAndExecOpCode(struct CPU *cpu, struct RAM *ram, uint16_t opcode);

#endif