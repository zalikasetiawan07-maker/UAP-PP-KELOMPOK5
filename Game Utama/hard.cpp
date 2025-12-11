#include <ncursesw/curses.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>

// ======================================================
//  LABIRIN HARD (LABIRIN 3)
// ======================================================
static const std::vector<std::string> HARD_PETA = {
    "==========================================================================",
    "             |                              |             |             ||", 
    "             |                              |             |_____        ||",
    "  ______     |            ____________      |      |                    ||",
    "||           |     |     |            |     |      |______ ______       ||",
    "||           |     |     |            |     |             |             ||",
    "||      _____|_____|     |            |     |             |             ||",
    "||                 |     |      |     |     |             |      _______||",
    "||                 |     |      |     |     |      |      |             ||",
    "||____________     |     |______|     |     |      |      |             ||",
    "||     |           |            |     |     |      |      |             ||",
    "||     |           |            |     |     |      |      |______       ||",
    "||     |      _____|______      |     |     |      |             |        ",
    "||     |     |                  |     |     |      |             |        ",
    "||     |     |                  |     |     |______|______       |______  ",
    "||           |      ____________|     |                   |             ||",
    "||           |                  |     |                   |             ||",
    "||           |                  |     |____________       |______       ||",
    "||           |____________      |                                       ||",
    "||                              |                                       ||",
    "||                              |                                       ||",
    "==========================================================================",
};

// ======================================================
//  UTILITAS FILE
// ======================================================
bool HARD_bacaFileSkor(const std::string &namaFile, int &keluarNilai) {
    std::ifstream fileMasuk(namaFile);
    if (!fileMasuk.is_open()) return false;
    fileMasuk >> keluarNilai;
    return true;
}

bool HARD_tulisFileSkor(const std::string &namaFile, int nilai) {
    std::ofstream fileKeluar(namaFile, std::ios::trunc);
    if (!fileKeluar.is_open()) return false;
    fileKeluar << nilai;
    return true;
}

// ======================================================
//  ANIMASI VICTORY (HARD)
// ======================================================
void HARD_animasiKemenangan(int posY, int posX) {
    beep();
    const char* teks[] = {
        " _   _ _____ _____ _______ ______ ______   _    _  ",
        "| | | |_   _|  ___|__   __|  __  |  __  | | |  | | ",
        "| | | | | | | |      | |  | |  | | |__| | | |__| | ",
        "| | | | | | | |      | |  | |  | |  __  | |____  | ",
        "| |_| |_| |_| |___   | |  | |__| | |  | |_ ____| | ",
        "|_____|_____|_____|  |_|  |______|_|  |___|______| "
    };

    clear();
    for (int i = 0; i < 6; i++) {
        mvprintw(posY + i, posX, "%s", teks[i]);
        refresh();
        usleep(120000);
    }
    sleep(2);
}

// ======================================================
//  ANIMASI DEFEAT (HARD)
// ======================================================
void HARD_animasiKekalahan(int posY, int posX) {
    beep();
    const char* teks[] = {
        " _____   _____  ____  _____  ______  _______  ",
        "|  __ \\ |  ___||  __||  ___||  __  ||__   __| ",
        "| |  | || |__  | |__ | |___ | |__| |   | |    ",
        "| |  | ||  __| |  __||  ___||  __  |   | |    ",
        "| |__| || |___ | |   | |___ | |  | |   | |    ",
        "|_____/ |_____||_|   |_____||_|  |_|   |_|    "
    };

    clear();
    for (int i = 0; i < 6; i++) {
        mvprintw(posY + i, posX, "%s", teks[i]);
        refresh();
        usleep(120000);
    }
    sleep(2);
}
