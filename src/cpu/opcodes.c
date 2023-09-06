#include "opcodes.h"

void OP_00E0(struct CPU *cpu, struct RAM *ram) {
    memset(ram->display, 0, sizeof(uint8_t) * DISPLAY_SIZE);

    ram->drawFlag = 1;
    cpu->pc += 2;
}

void OP_00EE(struct CPU *cpu) {
    cpu->sp -= 1;
    cpu->pc = cpu->stack[cpu->sp] + 2;
}

void OP_1NNN(struct CPU *cpu, uint16_t nnn) {
    cpu->pc = nnn;
}

void OP_2NNN(struct CPU *cpu, uint16_t nnn) {
    cpu->stack[cpu->sp] = cpu->pc;
    cpu->sp += 1;
    cpu->pc = nnn;
}

void OP_3XNN(struct CPU *cpu, uint8_t x, uint8_t nn) {
    cpu->pc += (cpu->V[x] == nn) ? 4 : 2;
}

void OP_4XNN(struct CPU *cpu, uint8_t x, uint8_t nn) {
    cpu->pc += (cpu->V[x] != nn) ? 4 : 2;
}

void OP_5XY0(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->pc += (cpu->V[x] == cpu->V[y]) ? 4 : 2;
}

void OP_6XNN(struct CPU *cpu, uint8_t x, uint8_t nn) {
    cpu->V[x] = nn;
    cpu->pc += 2;
}

void OP_7XNN(struct CPU *cpu, uint8_t x, uint8_t nn) {
    cpu->V[x] += nn;
    cpu->pc += 2;
}

void OP_8XY0(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->V[x] = cpu->V[y];
    cpu->pc += 2;
}

void OP_8XY1(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->V[x] = cpu->V[x] | cpu->V[y];
    cpu->pc += 2;
}

void OP_8XY2(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->V[x] = cpu->V[x] & cpu->V[y];
    cpu->pc += 2;
}

void OP_8XY3(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->V[x] = cpu->V[x] ^ cpu->V[y];
    cpu->pc += 2;
}

void OP_8XY4(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->V[0xF] = ((cpu->V[x] + cpu->V[y]) > 0xFF) ? 1 : 0;
    cpu->V[x] = cpu->V[x] + cpu->V[y];
    cpu->pc += 2;
}

void OP_8XY5(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->V[0xF] = (cpu->V[x] > cpu->V[y]) ? 1 : 0;
    cpu->V[x] = cpu->V[x] - cpu->V[y];
    cpu->pc += 2;
}

void OP_8XY6(struct CPU *cpu, uint8_t x) {
    cpu->V[0xF] = cpu->V[x] & 0x1;
    cpu->V[x] = cpu->V[x] >> 1;
    cpu->pc += 2;
}

void OP_8XY7(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->V[0xF] = (cpu->V[y] > cpu->V[x]) ? 1 : 0;
    cpu->V[x] = cpu->V[y] - cpu->V[x];
    cpu->pc += 2;
}

void OP_8XYE(struct CPU *cpu, uint8_t x) {
    cpu->V[0xF] = (cpu->V[x] >> 7) & 0x1;
    cpu->V[x] = (cpu->V[x] << 1);
    cpu->pc += 2;
}

void OP_9XY0(struct CPU *cpu, uint8_t x, uint8_t y) {
    cpu->pc += (cpu->V[x] != cpu->V[y]) ? 4 : 2;
}

void OP_ANNN(struct CPU *cpu, uint16_t nnn) {
    cpu->I = nnn;
    cpu->pc += 2;
}

void OP_BNNN(struct CPU *cpu, uint16_t nnn) {
    cpu->pc = nnn + cpu->V[0];
}

void OP_CXNN(struct CPU *cpu, uint8_t x, uint8_t nn) {
    cpu->V[x] = (rand() % 256) & nn;
    cpu->pc += 2;
}

void OP_DXYN(struct CPU *cpu, struct RAM *ram, uint8_t x, uint8_t y, uint8_t n) {
    cpu->V[0xF] = 0;

    for (int i = 0; i < n; i++) {
        uint8_t byte = ram->memory[cpu->I + i];

        for (int j = 0; j < 8; j++) {
            uint8_t bit = byte & (0x80 >> j);

            if (bit == 0) continue;

            int posX = cpu->V[x] + j;
            int posY = cpu->V[y] + i;

            int index = (posY * 64) + posX;

            if (ram->display[index] != 0) cpu->V[0xF] = 1;

            ram->display[index] = ram->display[index] ^ bit;
        }
    }

    cpu->pc += 2;
    ram->drawFlag = 1;
}

void OP_FX07(struct CPU *cpu, uint8_t x) {
    cpu->V[x] = cpu->delayTimer;
    cpu->pc += 2;
}

void OP_FX0A(struct CPU *cpu, uint8_t x) {
    int keyPress = 0;
    while (keyPress == 0) {
        for (int i = 0; i < KEYPAD_SIZE; i++) {
            if (cpu->keypad[i] == 1) {
                cpu->V[x] = i;
                keyPress = 1;
            }
        }
    }
    cpu->pc += 2;
}

void OP_FX15(struct CPU *cpu, uint8_t x) {
    cpu->delayTimer = cpu->V[x];
    cpu->pc += 2;
}

void OP_FX18(struct CPU *cpu, uint8_t x) {
    cpu->soundTimer = cpu->V[x];
    cpu->pc += 2;
}

void OP_FX1E(struct CPU *cpu, uint8_t x) {
    cpu->V[0xF] = ((cpu->I + cpu->V[x]) > 0xFFF) ? 1 : 0;
    cpu->I += cpu->V[x];
    cpu->pc += 2;
}

void OP_FX29(struct CPU *cpu, uint8_t x) {
    cpu->I = FONTSET_ALLOCATION + (cpu->V[x] * 5);
    cpu->pc += 2;
}

void OP_FX33(struct CPU *cpu, struct RAM *ram, uint8_t x) {
    uint8_t vx = cpu->V[x];

    ram->memory[cpu->I] = (vx % 1000) / 100;
    ram->memory[cpu->I + 1] = (vx % 100) / 10;
    ram->memory[cpu->I + 2] = (vx % 10);

    cpu->pc += 2;
}

void OP_FX55(struct CPU *cpu, struct RAM *ram, uint8_t x) {
    for (int i = 0; i <= x; i++) {
        ram->memory[cpu->I + i] = cpu->V[i];
    }

    cpu->I += x + 1;
    cpu->pc += 2;
}

void OP_FX65(struct CPU *cpu, struct RAM *ram, uint8_t x) {
    for (int i = 0; i < x; i++) {
        cpu->V[i] = ram->memory[cpu->I + i];
    }

    cpu->I += x + 1;
    cpu->pc += 2;
}

void OP_EX9E(struct CPU *cpu, uint8_t x) {
    cpu->pc += (cpu->keypad[cpu->V[x]] == 1) ? 4 : 2;
}

void OP_EXA1(struct CPU *cpu, uint8_t x) {
    cpu->pc += (cpu->keypad[cpu->V[x]] == 0) ? 4 : 2;
}