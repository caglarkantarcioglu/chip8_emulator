#include "cpu.h"
#include "opcodes.c"

struct CPU *createCPU() {
    struct CPU *cpu = (struct CPU *) malloc(sizeof(struct CPU));

    cpu->pc = ROM_ALLOCATION;
    cpu->sp = 0;
    cpu->delayTimer = 0;
    cpu->soundTimer = 0;

    memset(cpu->V, 0, sizeof(uint8_t) * REGISTER_SIZE);
    memset(cpu->stack, 0, sizeof(uint8_t) * STACK_SIZE);
    memset(cpu->keypad, 0, sizeof(uint8_t) * KEYPAD_SIZE);

    return cpu;
}

void CPU_Step(struct CPU *cpu, struct RAM *ram) {
    if (cpu->delayTimer > 0) cpu->delayTimer -= 1;
    if (cpu->soundTimer > 0) cpu->soundTimer -= 1;

    // Fetch OpCode
    uint16_t opcode = CPU_FetchOpCode(cpu, ram);

    // Decode and execute OpCode
    CPU_DecodeAndExecOpCode(cpu, ram, opcode);
}

uint16_t CPU_FetchOpCode(struct CPU *cpu, struct RAM *ram) {
    return (ram->memory[cpu->pc] << 8) | ram->memory[cpu->pc + 1];
}

void CPU_DecodeAndExecOpCode(struct CPU *cpu, struct RAM *ram, uint16_t opcode) {
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;
    uint8_t n = opcode & 0x000F;
    uint8_t nn = opcode & 0x00FF;
    uint16_t nnn = opcode & 0x0FFF;

    // Decode and execute
    switch (opcode & 0xF000) {
        case 0x0000:
            switch (nn) {
                case 0x00E0:
                    return OP_00E0(cpu, ram);
                case 0x00EE:
                    return OP_00EE(cpu);
                default:
                    break;
            }
            break;
        case 0xF000:
            switch (nn) {
                case 0x07:
                    return OP_FX07(cpu, x);
                case 0x0A:
                    return OP_FX0A(cpu, x);
                case 0x1E:
                    return OP_FX1E(cpu, x);
                case 0x15:
                    return OP_FX15(cpu, x);
                case 0x18:
                    return OP_FX18(cpu, x);
                case 0x29:
                    return OP_FX29(cpu, x);
                case 0x33:
                    return OP_FX33(cpu, ram, x);
                case 0x55:
                    return OP_FX55(cpu, ram, x);
                case 0x65:
                    return OP_FX65(cpu, ram, x);
                default:
                    break;
            }
            break;
        case 0x8000:
            switch (n) {
                case 0x0000:
                    return OP_8XY0(cpu, x, y);
                case 0x0001:
                    return OP_8XY1(cpu, x, y);
                case 0x0002:
                    return OP_8XY2(cpu, x, y);
                case 0x0003:
                    return OP_8XY3(cpu, x, y);
                case 0x0004:
                    return OP_8XY4(cpu, x, y);
                case 0x0005:
                    return OP_8XY5(cpu, x, y);
                case 0x0006:
                    return OP_8XY6(cpu, x);
                case 0x0007:
                    return OP_8XY7(cpu, x, y);
                case 0x000E:
                    return OP_8XYE(cpu, x);
                default:
                    break;
            }
            break;
        case 0xE000:
            switch (nn) {
                case 0x9E:
                    return OP_EX9E(cpu, x);
                case 0xA1:
                    return OP_EXA1(cpu, x);
                default:
                    break;
            }
            break;
        case 0x1000:
            return OP_1NNN(cpu, nnn);
        case 0x2000:
            return OP_2NNN(cpu, nnn);
        case 0x3000:
            return OP_3XNN(cpu, x, nn);
        case 0x4000:
            return OP_4XNN(cpu, x, nn);
        case 0x5000:
            return OP_5XY0(cpu, x, y);
        case 0x6000:
            return OP_6XNN(cpu, x, nn);
        case 0x7000:
            return OP_7XNN(cpu, x, nn);
        case 0x9000:
            return OP_9XY0(cpu, x, y);
        case 0xA000:
            return OP_ANNN(cpu, nnn);
        case 0xB000:
            return OP_BNNN(cpu, nnn);
        case 0xC000:
            return OP_CXNN(cpu, x, nn);
        case 0xD000:
            return OP_DXYN(cpu, ram, x, y, n);
        default:
            break;
    }
}

