#include <ncursesw/curses.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>

// ======================================================
//  LABIRIN ASLI - VARIABEL L1
// ======================================================
static const std::vector<std::string> LABIRIN_L1 = {
    "=========================================       ",
    "||                   |                  |     ||",
    "||       ______      |       _____      |     ||",
    "||      |            |      |     |     |     ||",
    "||      |            |      |     |     |     ||",
    "||      |      ______|      |     |     |     ||",
    "||      |            |      |     |     |     ||",
    "||      |            |      |     |           ||",
    "||      |            |            |           ||",
    "||      |______      |            |___________||",
    "||      |      |     |______      |           ||",
    "||             |            |     |           ||",
    "||             |            |     |           ||",
    "||______       |______      |     |     |     ||",
    "                      |                 |     ||",
    "                      |                 |     ||",
    "                      |                 |     ||",
    "================================================",
};

// ======================================================
//  UTILITAS FILE (L1)
// ======================================================
bool baca_file_skor_L1(const std::string &namaFile_L1, int &keluarNilai_L1) {
    std::ifstream fileMasuk_L1(namaFile_L1);
    if (!fileMasuk_L1.is_open()) return false;
    fileMasuk_L1 >> keluarNilai_L1;
    return true;
}

bool tulis_file_skor_L1(const std::string &namaFile_L1, int nilai_L1) {
    std::ofstream fileKeluar_L1(namaFile_L1, std::ios::trunc);
    if (!fileKeluar_L1.is_open()) return false;
    fileKeluar_L1 << nilai_L1;
    return true;
}

// ======================================================
//  ANIMASI MENANG (L1)
// ======================================================
void animasiMenang_L1(int posY_L1, int posX_L1) {
    beep();
    const char* teks_L1[] = {
        " _   _ _____ _____ _______ ______ ______   _    _  ",
        "| | | |_   _|  ___|__   __|  __  |  __  | | |  | | ",
        "| | | | | | | |      | |  | |  | | |__| | | |__| | ",
        "| | | | | | | |      | |  | |  | |  __  | |____  | ",
        "| |_| |_| |_| |___   | |  | |__| | |  | |_ ____| | ",
        "|_____|_____|_____|  |_|  |______|_|  |___|______| "
    };

    clear();
    for (int i = 0; i < 6; i++) {
        mvprintw(posY_L1 + i, posX_L1, "%s", teks_L1[i]);
        refresh();
        usleep(120000);
    }
    sleep(2);
}

// ======================================================
//  ANIMASI KALAH (L1)
// ======================================================
void animasiKalah_L1(int posY_L1, int posX_L1) {
    beep();
    const char* teks_L1[] = {
        " _____   _____  ____  _____  ______  _______  ",
        "|  __ \\ |  ___||  __||  ___||  __  ||__   __| ",
        "| |  | || |__  | |__ | |___ | |__| |   | |    ",
        "| |  | ||  __| |  __||  ___||  __  |   | |    ",
        "| |__| || |___ | |   | |___ | |  | |   | |    ",
        "|_____/ |_____||_|   |_____||_|  |_|   |_|    "
    };

    clear();
    for (int i = 0; i < 6; i++) {
        mvprintw(posY_L1 + i, posX_L1, "%s", teks_L1[i]);
        refresh();
        usleep(120000);
    }
    sleep(2);
}

// ======================================================
//  MENU JEDA (L1)
// ======================================================
bool menuJeda_L1(int y_L1, int x_L1) {
    clear();
    mvprintw(y_L1,     x_L1, "=== MENU JEDA ===");
    mvprintw(y_L1+2,   x_L1, "[1] Lanjutkan");
    mvprintw(y_L1+3,   x_L1, "[2] Keluar");
    mvprintw(y_L1+5,   x_L1, "Pilih: ");
    refresh();

    while (true) {
        int tombol_L1 = getch();
        if (tombol_L1 == '1') return true;
        if (tombol_L1 == '2') return false;
    }
}

// ======================================================
//  TAMPILKAN LABIRIN (L1)
// ======================================================
void tampilkanLabirin_L1(int tinggiLayar_L1 = 25, int lebarLayar_L1 = 80) {

    int tinggiLab_L1 = LABIRIN_L1.size();
    int lebarLab_L1 = 0;

    // cari lebar terbesar
    for (auto &baris_L1 : LABIRIN_L1)
        if ((int)baris_L1.size() > lebarLab_L1)
            lebarLab_L1 = baris_L1.size();

    // posisi layar
    int layarY_L1, layarX_L1;
    getmaxyx(stdscr, layarY_L1, layarX_L1);

    int offsetY_L1 = (layarY_L1 - tinggiLayar_L1) / 2;
    int offsetX_L1 = (layarX_L1 - lebarLayar_L1) /  2;

    int startY_L1 = offsetY_L1 + (tinggiLayar_L1 - tinggiLab_L1) / 2;
    int startX_L1 = offsetX_L1 + (lebarLayar_L1 - lebarLab_L1) / 2;

    // gambar labirin
    for (int i = 0; i < tinggiLab_L1; i++)
        mvaddnstr(startY_L1 + i, startX_L1, LABIRIN_L1[i].c_str(), LABIRIN_L1[i].size());

    refresh();
}

// ======================================================
//  GERAK KARAKTER OTOMATIS (L1)
// ======================================================
void gerakKarakterOtomatis_L1() {

    const int tinggiLayar_L1 = 25;
    const int lebarLayar_L1  = 80;

    const std::string fileSkor_L1 = "highscore_l1.txt";
    const char hurufMakanan_L1 = '*';
    const int jumlahMakanan_L1 = 25;
    const int waktuMulai_L1 = 120;

    int tinggiLab_L1 = LABIRIN_L1.size();
    int lebarLab_L1 = 0;
    for (auto &s_L1 : LABIRIN_L1)
        if ((int)s_L1.size() > lebarLab_L1) lebarLab_L1 = s_L1.size();

    // posisi labirin di layar
    int layarY_L1, layarX_L1;
    getmaxyx(stdscr, layarY_L1, layarX_L1);

    int offsetY_L1 = (layarY_L1 - tinggiLayar_L1) / 2;
    int offsetX_L1 = (layarX_L1 - lebarLayar_L1) / 2;

    int posLabY_L1 = offsetY_L1 + (tinggiLayar_L1 - tinggiLab_L1) / 2;
    int posLabX_L1 = offsetX_L1 + (lebarLayar_L1 - lebarLab_L1) / 2;

    // posisi karakter
    int posisiPemainY_L1 = 15;
    int posisiPemainX_L1 = 3;

    int arah_L1 = 0;     
    bool mulutTerbuka_L1 = true;

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    // skor
    int skorTertinggi_L1 = 0;
    baca_file_skor_L1(fileSkor_L1, skorTertinggi_L1);

    int skor_L1 = 0;

    // daftar makanan
