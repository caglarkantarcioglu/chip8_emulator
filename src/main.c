#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "ram/ram.c"
#include "cpu/cpu.c"
#include "window/window.c"

void launchROMFile(const char *filename, uint8_t memory[MEMORY_SIZE]);

int main(int argc, char *args[]) {
    srand(time(NULL));

    struct CPU *cpu = createCPU();
    struct RAM *ram = createRAM();

    struct EmulatorWindow *window = createWindow(argc, args);

    launchROMFile("chip8.ch8", ram->memory);

    while (!window->quit) {
        Window_ListenEvents(window, cpu);

        CPU_Step(cpu, ram);

        if (ram->drawFlag) {
            Window_RenderDisplay(window, ram);
            ram->drawFlag = 0;
        }

        usleep(2500);
    }

    Window_Close(window);

    free(cpu);
    free(ram);
    free(window);

    return 1;
}

void launchROMFile(const char *filename, uint8_t memory[MEMORY_SIZE]) {
    char fileSource[10] = "../roms/";
    strcat(fileSource, filename);

    FILE *file = fopen(fileSource, "rb");

    if (file == NULL) {
        printf("File not found");
        exit(0);
    }

    int counter = 0;
    uint8_t byte;

    while (fread(&byte, 1, 1, file) > 0) {
        memory[ROM_ALLOCATION + counter] = byte;

        counter++;
    }

    fclose(file);

}
