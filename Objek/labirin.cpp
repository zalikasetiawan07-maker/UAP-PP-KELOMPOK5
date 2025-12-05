#include <ncurses.h>

void tampilkanLabirin1() {
    // Ukuran layar yang ditetapkan
    int layarTinggi1 = 25;
    int layarLebar1  = 80;

    //labirin dari kumpulan karakter
const char* kotak1[] = {
        "=========================================",
        "||           |           |             ||", 
        "||           |           |             ||",
        "||     |     |           |             ||",
        "||     |     |     |     |      |      ||",
        "||     |_____|     |     |      |      ||",
        "||                 |            |        ",
        "||                 |            |        ",
        "||___________      |____________|        ",
        "             |                  |      ||",
        "             |                  |      ||",
        "  _____      |                  |      ||",
        "||     |     |      ______      |______||",
        "||     |     |     |            |      ||",
        "||     |     |     |            |      ||",
        "||                 |      ______|      ||",
        "||                 |                   ||",
        "=========================================",
    };
 int baris1 = 18;
    int kolom1 = 38;

    // Hitung posisi tengah layar 15x80
    int mulaiY1 = (layarTinggi1 - baris1) / 2;
    int mulaiX1 = (layarLebar1  - kolom1) / 2;

    // Gambar labirin
    for (int i = 0; i < baris1; i++) {
        mvprintw(mulaiY1 + i, mulaiX1, "%s", kotak1[i]);
    }
}

void tampilkanLabirin2() {
    // Ukuran layar yang ditetapkan
    int layarTinggi2 = 25;
    int layarLebar2  = 80;



