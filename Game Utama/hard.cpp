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

// ======================================================
//  MENU PAUSE (HARD)
// ======================================================
bool HARD_menuJeda(int y, int x) {
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
//  TAMPIlKAN LABIRIN HARD
// ======================================================
void HARD_tampilkanPeta(int tinggiLayar = 25, int lebarLayar = 80) {

    int tinggiLab = HARD_PETA.size();
    int lebarLab = 0;

    for (auto &baris : HARD_PETA)
        if ((int)baris.size() > lebarLab)
            lebarLab = baris.size();

    int layarY, layarX;
    getmaxyx(stdscr, layarY, layarX);

    int offsetY = (layarY - tinggiLayar) / 2;
    int offsetX = (layarX - lebarLayar) /  2;

    int startY = offsetY + (tinggiLayar - tinggiLab) / 2;
    int startX = offsetX + (lebarLayar - lebarLab) / 2;

    for (int i = 0; i < tinggiLab; i++)
        mvaddnstr(startY + i, startX, HARD_PETA[i].c_str(), HARD_PETA[i].size());

    refresh();
}

// ======================================================
//  GERAK KARAKTER (HARD)
// ======================================================
void HARD_gerakKarakter() {

    const int tinggiLayar = 25;
    const int lebarLayar  = 80;

    const std::string fileSkor = "highscore_hard.txt";
    const char iconMakanan = '*';
    const int jumlahMakanan = 35;
    const int waktuMulai = 150;

    int tinggiLab = HARD_PETA.size();
    int lebarLab = 0;
    for (auto &s : HARD_PETA)
        if ((int)s.size() > lebarLab) lebarLab = s.size();

    int layarY, layarX;
    getmaxyx(stdscr, layarY, layarX);

    int offsetY = (layarY - tinggiLayar) / 2;
    int offsetX = (layarX - lebarLayar) / 2;

    int posLabY = offsetY + (tinggiLayar - tinggiLab) / 2;
    int posLabX = offsetX + (lebarLayar - lebarLab) / 2;

    int posY = 1;
    int posX = 3;

    int arah = 0;
    bool mulutTerbuka = true;

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    int skorTertinggi = 0;
    HARD_bacaFileSkor(fileSkor, skorTertinggi);

    int skor = 0;

    std::vector<std::pair<int,int>> listMakanan;
    srand((unsigned)time(nullptr));

    while ((int)listMakanan.size() < jumlahMakanan) {
        int acakY = rand() % tinggiLab;
        int acakX = rand() % (int)HARD_PETA[acakY].size();

        if (HARD_PETA[acakY][acakX] != ' ') continue;

        bool duplikat = false;
        for (auto &p : listMakanan)
            if (p.first == acakY && p.second == acakX)
                duplikat = true;

        if (!duplikat) listMakanan.emplace_back(acakY, acakX);
    }

    auto gambarKarakter = [&](int y, int x) {
        const char *buka, *tutup;

        if (arah == 0)      { buka = "(O>"; tutup = "(o>"; }
        else if (arah == 1) { buka = "<O)"; tutup = "<o)"; }
        else if (arah == 2) { buka = ">O<"; tutup = ">o<"; }
        else                { buka = ">O<"; tutup = ">o<"; }

        mvprintw(posLabY + y, posLabX + x, "%s", (mulutTerbuka ? buka : tutup));
    };

    auto hapusKarakter = [&](int y, int x) {
        mvprintw(posLabY + y, posLabX + x, "   ");
    };

    auto gambarMakanan = [&]() {
        for (auto &p : listMakanan)
            mvaddch(posLabY + p.first, posLabX + p.second, iconMakanan);
    };

    auto hapusMakanan = [&](int y, int x) -> bool {
        for (size_t i = 0; i < listMakanan.size(); ++i) {
            if (listMakanan[i].first == y && listMakanan[i].second == x) {
                mvaddch(posLabY + y, posLabX + x, HARD_PETA[y][x]);
                listMakanan.erase(listMakanan.begin() + i);
                return true;
            }
        }
        return false;
    };

    auto cekMakan = [&](int cy, int cx) -> bool {
        bool makan = false;
        for (int dx = 0; dx < 3; dx++) {
            int fx = cx + dx;
            if (fx < 0 || fx >= (int)HARD_PETA[cy].size()) continue;
            if (hapusMakanan(cy, fx)) {
                skor++;
                makan = true;
            }
        }
        return makan;
    };

    mvprintw(posLabY - 1, posLabX, "WASD/Arrow = belok | ENTER = pause | Q = keluar");

    gambarMakanan();
    gambarKarakter(posY, posX);

    time_t mulaiWaktu = time(nullptr);
    int sisaWaktu = waktuMulai;

    while (true) {
        int tombol = getch();

        // PAUSE
        if (tombol == '\n') {
            bool lanjut = HARD_menuJeda(posLabY + tinggiLab/2, posLabX + lebarLab/2 - 7);

            clear();
            HARD_tampilkanPeta(25, 80);
            gambarMakanan();
            gambarKarakter(posY, posX);
            refresh();

            if (!lanjut) {
                if (skor > skorTertinggi) HARD_tulisFileSkor(fileSkor, skor);
                return;
            }
        }

        // KELUAR
        if (tombol == 'q' || tombol == 'Q') {
            if (skor > skorTertinggi) HARD_tulisFileSkor(fileSkor, skor);
            return;
        }

        // UBAH ARAH
        if (tombol == KEY_RIGHT || tombol=='d' || tombol=='D') arah = 0;
        if (tombol == KEY_LEFT  || tombol=='a' || tombol=='A') arah = 1;
        if (tombol == KEY_UP    || tombol=='w' || tombol=='W') arah = 2;
        if (tombol == KEY_DOWN  || tombol=='s' || tombol=='S') arah = 3;

        int nextY = posY, nextX = posX;
        if (arah == 0) nextX++;
        else if (arah == 1) nextX--;
        else if (arah == 2) nextY--;
        else if (arah == 3) nextY++;

        // WAKTU
        time_t sekarang = time(nullptr);
        sisaWaktu = waktuMulai - (int)difftime(sekarang, mulaiWaktu);
        if (sisaWaktu < 0) sisaWaktu = 0;

        mvprintw(posLabY - 3, posLabX, "Skor: %d  ", skor);
        mvprintw(posLabY - 3, posLabX + lebarLayar - 20, "Highscore: %d  ", skorTertinggi);
        mvprintw(posLabY - 2, posLabX + lebarLayar - 20, "Waktu: %02d:%02d  ",
                 sisaWaktu/60, sisaWaktu%60);

        if (sisaWaktu == 0) {
            if (skor > skorTertinggi) HARD_tulisFileSkor(fileSkor, skor);
            HARD_animasiKekalahan(posLabY + tinggiLab/2 - 3, posLabX + lebarLab/2 - 15);
            return;
        }

        // Cek pintu keluar
        if (nextY >= 0 && nextY < tinggiLab &&
            nextX >= 0 && nextX < (int)HARD_PETA[nextY].size()) {

            if ((nextX == 0 || nextX == (int)HARD_PETA[nextY].size()-1) &&
                HARD_PETA[nextY][nextX] == ' ') {

                if (skor > skorTertinggi) HARD_tulisFileSkor(fileSkor, skor);
                HARD_animasiKemenangan(posLabY + tinggiLab/2 - 3, posLabX + lebarLab/2 - 15);
                return;
            }
        }

        // Cek tabrakan
        if (nextY < 0 || nextY >= tinggiLab ||
            nextX < 0 || nextX >= (int)HARD_PETA[nextY].size() ||
            HARD_PETA[nextY][nextX] != ' ') {

            if (skor > skorTertinggi) HARD_tulisFileSkor(fileSkor, skor);
            HARD_animasiKekalahan(posLabY + tinggiLab/2 - 3, posLabX + lebarLab/2 - 15);
            return;
        }

        // Gerak
        hapusKarakter(posY, posX);
        gambarMakanan();

        posY = nextY;
        posX = nextX;
        mulutTerbuka = !mulutTerbuka;

        if (cekMakan(posY, posX)) {
            beep();
            gambarMakanan();
        }
        gambarKarakter(posY, posX);

        refresh();

        if (listMakanan.empty()) {
            if (skor > skorTertinggi) HARD_tulisFileSkor(fileSkor, skor);
            HARD_animasiKemenangan(posLabY + tinggiLab/2 - 3, posLabX + lebarLab/2 - 15);
            return;
        }

        usleep(450000);
    }
}

// ======================================================
//  FUNGSI UTAMA GAME LABIRIN HARD
// ======================================================
void jalankanGameHard() {

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_GREEN);
        bkgd(COLOR_PAIR(1));
    }

    clear();
    curs_set(0);
    HARD_tampilkanPeta(25, 80);
    HARD_gerakKarakter();

    refresh();
}
