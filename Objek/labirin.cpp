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



void tampilkanLabirin2() {
    // Ukuran layar yang ditetapkan
    int layarTinggi2 = 25;
    int layarLebar2  = 80;

