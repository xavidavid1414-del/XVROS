#include <3ds.h>
#include <stdio.h>
#include "wifi/wifi.h"

int main(void)
{
    gfxInitDefault();

    PrintConsole top_console;
    PrintConsole bottom_console;

    consoleInit(GFX_TOP, &top_console);
    consoleInit(GFX_BOTTOM, &bottom_console);

    const XvrosWifiStatus wifi = xvros_wifi_get_status();

    consoleSelect(&top_console);
    printf("\x1b[1;1H");
    printf("XVROS\n");
    printf("New Nintendo 2DS XL environment\n");
    printf("--------------------------------\n\n");
    printf("SYSTEM SHELL 0.1\n\n");
    printf("Desktop: initializing\n");
    printf("Applications: planned\n");
    printf("Emulator center: planned\n");
    printf("XVROS Link: planned\n");

    consoleSelect(&bottom_console);
    printf("\x1b[1;1H");
    printf("XVROS CONTROL CENTER\n");
    printf("--------------------\n\n");
    printf("Wi-Fi signal: %u/3 bars\n", wifi.signal_strength);
    printf("Network connection manager: planned\n");
    printf("Settings: planned\n");
    printf("\nPress START to exit.\n");

    while (aptMainLoop())
    {
        hidScanInput();
        const u32 keys = hidKeysDown();
        if (keys & KEY_START)
            break;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
