#include <ncursesw/curses.h>

// deklarasi fungsi level
void jalankanGameLabirin1();     // easy
void jalankanGameLabirin_L1();   // medium
void jalankanGameHard();         // hard

int menuUtama() {
    const char* menu[] = {
        "Easy",
        "Medium",
        "Hard",
        "Keluar"
    };

    int jumlahMenu = 4;
    int pilihan = 0;
keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);

    while (true) {
        clear();
mvprintw(5, 10, "===== GAME LABIRIN =====");
        mvprintw(6, 10, "Gunakan UP / DOWN lalu ENTER");

        for (int i = 0; i < jumlahMenu; i++) {
     if (i == pilihan) {
                attron(A_REVERSE);
        mvprintw(8 + i, 10, "> %s", menu[i]);
                     attroff(A_REVERSE);
            } else {
                mvprintw(8 + i, 10, "  %s", menu[i]);
            }
        }

        refresh();
  int ch = getch();
        if (ch == KEY_UP) {
            pilihan = (pilihan - 1 + jumlahMenu) % jumlahMenu;
        }
        else if (ch == KEY_DOWN) {
            pilihan = (pilihan + 1) % jumlahMenu;
        }
        else if (ch == '\n') {
            return pilihan;
        }
    }
}



