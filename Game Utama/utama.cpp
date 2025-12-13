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
