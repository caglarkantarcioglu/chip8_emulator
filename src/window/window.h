/**
 * @file window.h
 *
 * SDL window manager of the CHIP8 Emulator
 * @author Caglar Kantarcioglu
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

struct EmulatorWindow {
    SDL_Window *instance;

    SDL_Surface *surface;

    SDL_Renderer *renderer;

    int quit;
};

struct EmulatorWindow *createWindow(int argc, char *args[]);

void Window_RenderDisplay(struct EmulatorWindow *window, struct RAM *ram);

void Window_ListenEvents(struct EmulatorWindow *window, struct CPU *cpu);

void Window_Close(struct EmulatorWindow *window);

uint8_t Window_DecodeKeyPad(uint16_t scancode);

#endif