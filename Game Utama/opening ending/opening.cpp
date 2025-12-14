#include "opening.h"
#include <ncursesw/curses.h>
#include <unistd.h>

void tampilOpening() {
    clear();

    const char* teks[] = {
        "  _       ___    ____   ___   ____  ___  ",
        " | |     /   \\  | __ ) / _ \\ |  _ \\|_ _| ",
        " | |    | | | | |  _ \\| | | || |_) || |  ",
        " | |___ | |_| | | |_) | |_| ||  _ < | |  ",
        " |_____| \\___/  |____/ \\___/ |_| \\_\\___| "
    };

    int y = 5;
    int x = 10;

    for (int i = 0; i < 5; i++) {
        mvprintw(y + i, x, "%s", teks[i]);
        refresh();
        usleep(200000);
    }

    mvprintw(y + 7, x, "Tekan tombol apa saja untuk mulai...");
    refresh();
    getch();
}
