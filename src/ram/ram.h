/**
 * @file ram.h
 *
 * Random Access Memory (RAM) of the CHIP8 Emulator
 * @author Caglar Kantarcioglu
 */

#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MEMORY_SIZE 4096
#define DISPLAY_SIZE (64 * 32)

#define FONTSET_SIZE 80
#define FONTSET_ALLOCATION 0x00
#define ROM_ALLOCATION 0x200

struct RAM {
    uint8_t memory[MEMORY_SIZE];

    uint8_t display[DISPLAY_SIZE];

    int drawFlag;
};

struct RAM *createRAM();

void writeFontset(uint8_t memory[MEMORY_SIZE]);

#endif