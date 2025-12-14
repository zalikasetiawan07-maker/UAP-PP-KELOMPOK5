#include "ending.h"
#include <ncursesw/curses.h>
#include <unistd.h>

void tampilEnding(int skor) {
    clear();

    mvprintw(5, 10, "TERIMA KASIH TELAH BERMAIN!");
    mvprintw(7, 10, "Skor Akhir : %d", skor);
    mvprintw(9, 10, "Dibuat oleh:");
    mvprintw(10, 10, "Nama Kamu");

    refresh();
    sleep(3);
}
