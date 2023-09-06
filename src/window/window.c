#include "window.h"

struct EmulatorWindow *createWindow(int argc, char *args[]) {
    SDL_Window *instance = NULL;
    SDL_Surface *surface = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Error: %s\n", SDL_GetError());
        exit(0);
    }

    instance = SDL_CreateWindow(
            "CHIP8 Emulator",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN);

    if (instance == NULL) {
        printf("SDL_Error: %s\n", SDL_GetError());
        exit(0);
    }

    renderer = SDL_CreateRenderer(instance, -1, SDL_RENDERER_ACCELERATED);

    struct EmulatorWindow *window = (struct EmulatorWindow *) malloc(sizeof(struct EmulatorWindow));

    window->instance = instance;
    window->surface = surface;
    window->renderer = renderer;
    window->quit = 0;

    return window;
}

void Window_RenderDisplay(struct EmulatorWindow *window, struct RAM *ram) {
    for (int i = 0; i < 64 * 32; i++) {
        if (ram->display[i]) {
            SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
        } else {
            SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
        }

        int x = i % 64;
        int y = i / 64;

        SDL_Rect rect;
        rect.x = x * 10;
        rect.y = y * 10;
        rect.w = 10;
        rect.h = 10;

        SDL_RenderFillRect(window->renderer, &rect);
    }

    SDL_RenderPresent(window->renderer);
}

void Window_ListenEvents(struct EmulatorWindow *window, struct CPU *cpu) {
    SDL_Event event;

    uint8_t keyPad;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                window->quit = 1;
                break;
            case SDL_KEYUP:
                keyPad = Window_DecodeKeyPad(event.key.keysym.scancode);
                if (keyPad != 0xFF) {
                    cpu->keypad[keyPad] = 1;
                }
                break;
            case SDL_KEYDOWN:
                keyPad = Window_DecodeKeyPad(event.key.keysym.scancode);
                if (keyPad != 0xFF) {
                    cpu->keypad[keyPad] = 0;
                }
                break;
        }
    }
}

uint8_t Window_DecodeKeyPad(uint16_t scancode) {
    switch (scancode) {
        case 0x1E: // 1
            return 0x1;
        case 0x1F: // 2
            return 0x2;
        case 0x20: // 3
            return 0x3;
        case 0x21: // 4
            return 0xC;
        case 0x14: // q
            return 0x4;
        case 0x1A: // w
            return 0x5;
        case 0x15: // r
            return 0xD;
        case 0x08: // e
            return 0x6;
        case 0x09: // f
            return 0xE;
        case 0x04: // a
            return 0x7;
        case 0x16: // s
            return 0x8;
        case 0x07: // d
            return 0x9;
        case 0x1D: // z
            return 0xA;
        case 0x1B: // x
            return 0x0;
        case 0x06: // c
            return 0xB;
        case 0x19: // v
            return 0xF;
    }

    return 0xFF;
}

void Window_Close(struct EmulatorWindow *window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->instance);
    SDL_Quit();
}