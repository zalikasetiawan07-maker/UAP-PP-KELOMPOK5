#include <ncursesw/curses.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>

// ======================================================
//  LABIRIN EASY
// ======================================================
static const std::vector<std::string> LABIRIN = {
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
    "||     |     |      ______      |      ||",
    "||     |     |     |            |      ||",
    "||     |     |     |            |      ||",
    "||                 |      ______|      ||",
    "||                 |                   ||",
    "=========================================",
};

// ======================================================
//  UTILITAS FILE
// ======================================================
bool baca_file_skor(const std::string &namaFile, int &keluarNilai) {
    std::ifstream fileMasuk(namaFile);
    if (!fileMasuk.is_open()) return false;
    fileMasuk >> keluarNilai;
    return true;
}

bool tulis_file_skor(const std::string &namaFile, int nilai) {
    std::ofstream fileKeluar(namaFile, std::ios::trunc);
    if (!fileKeluar.is_open()) return false;
    fileKeluar << nilai;
    return true;
}

// ======================================================
//  ANIMASI VICTORY
// ======================================================
void animasiMenang(int posY, int posX) {
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
//  ANIMASI DEFEAT
// ======================================================
void animasiKalah(int posY, int posX) {
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

// ======================================================
//  MENU PAUSE
// ======================================================
bool menuJeda(int y, int x) {
    clear();
    mvprintw(y,     x, "=== MENU JEDA ===");
    mvprintw(y+2,   x, "[1] Lanjutkan");
    mvprintw(y+3,   x, "[2] Keluar");
    mvprintw(y+5,   x, "Pilih: ");
    refresh();

    while (true) {
        int tombol = getch();
        if (tombol == '1') return true;
        if (tombol == '2') return false;
    }
}

// ======================================================
//  GAMBAR LABIRIN
// ======================================================
void tampilkanLabirin(int tinggiLayar = 25, int lebarLayar = 80) {

    int tinggiLab = LABIRIN.size();
    int lebarLab = 0;

    // cari lebar terbesar
    for (auto &baris : LABIRIN)
        if ((int)baris.size() > lebarLab)
            lebarLab = baris.size();

    // posisi layar
    int layarY, layarX;
    getmaxyx(stdscr, layarY, layarX);

    int offsetY = (layarY - tinggiLayar) / 2;
    int offsetX = (layarX - lebarLayar) /  2;

    int startY = offsetY + (tinggiLayar - tinggiLab) / 2;
    int startX = offsetX + (lebarLayar - lebarLab) / 2;

    // gambar labirin
    for (int i = 0; i < tinggiLab; i++)
        mvaddnstr(startY + i, startX, LABIRIN[i].c_str(), LABIRIN[i].size());

    refresh();
}

// ======================================================
//  GERAK KARAKTER
// ======================================================
void gerakKarakterOtomatis() {

    const int tinggiLayar = 25;
    const int lebarLayar  = 80;

    const std::string fileSkor = "highscore.txt";
    const char hurufMakanan = '*';
    const int jumlahMakanan = 15;
    const int waktuMulai = 90;

    int tinggiLab = LABIRIN.size();
    int lebarLab = 0;
    for (auto &s : LABIRIN)
        if ((int)s.size() > lebarLab) lebarLab = s.size();

    // posisi labirin di layar
    int layarY, layarX;
    getmaxyx(stdscr, layarY, layarX);

    int offsetY = (layarY - tinggiLayar) / 2;
    int offsetX = (layarX - lebarLayar) / 2;

    int posLabY = offsetY + (tinggiLayar - tinggiLab) / 2;
    int posLabX = offsetX + (lebarLayar - lebarLab) / 2;

    // posisi karakter
    int posY = 10;
    int posX = 3;

    int arah = 0;     
    bool mulutTerbuka = true;

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    // skor
    int skorTertinggi = 0;
    baca_file_skor(fileSkor, skorTertinggi);

    int skor = 0;

    // daftar makanan
    std::vector<std::pair<int,int>> listMakanan;
    srand((unsigned)time(nullptr));

