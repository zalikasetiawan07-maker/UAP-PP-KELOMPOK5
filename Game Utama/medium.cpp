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
    std::vector<std::pair<int,int>> daftarMakanan_L1;
    srand((unsigned)time(nullptr));

    while ((int)daftarMakanan_L1.size() < jumlahMakanan_L1) {
        int acakY_L1 = rand() % tinggiLab_L1;
        int acakX_L1 = rand() % (int)LABIRIN_L1[acakY_L1].size();

        if (LABIRIN_L1[acakY_L1][acakX_L1] != ' ') continue;

        bool duplikat_L1 = false;
        for (auto &p_L1 : daftarMakanan_L1)
            if (p_L1.first == acakY_L1 && p_L1.second == acakX_L1)
                duplikat_L1 = true;

        if (!duplikat_L1) daftarMakanan_L1.emplace_back(acakY_L1, acakX_L1);
    }

    // fungsi gambar karakter
    auto gambarKarakter_L1 = [&](int y_L1, int x_L1) {
        const char *buka_L1, *tutup_L1;

        if (arah_L1 == 0)      { buka_L1 = "(O>"; tutup_L1 = "(o>"; }
        else if (arah_L1 == 1) { buka_L1 = "<O)"; tutup_L1 = "<o)"; }
        else if (arah_L1 == 2) { buka_L1 = ">O<"; tutup_L1 = ">o<"; }
        else                   { buka_L1 = ">O<"; tutup_L1 = ">o<"; }

        mvprintw(posLabY_L1 + y_L1, posLabX_L1 + x_L1, "%s", (mulutTerbuka_L1 ? buka_L1 : tutup_L1));
    };

    auto hapusKarakter_L1 = [&](int y_L1, int x_L1) {
        mvprintw(posLabY_L1 + y_L1, posLabX_L1 + x_L1, "   ");
    };

    auto gambarMakanan_L1 = [&]() {
        for (auto &p_L1 : daftarMakanan_L1)
            mvaddch(posLabY_L1 + p_L1.first, posLabX_L1 + p_L1.second, hurufMakanan_L1);
    };

    auto hapusMakanan_L1 = [&](int y_L1, int x_L1) -> bool {
        for (size_t i_L1 = 0; i_L1 < daftarMakanan_L1.size(); ++i_L1) {
            if (daftarMakanan_L1[i_L1].first == y_L1 && daftarMakanan_L1[i_L1].second == x_L1) {
                mvaddch(posLabY_L1 + y_L1, posLabX_L1 + x_L1, LABIRIN_L1[y_L1][x_L1]);
                daftarMakanan_L1.erase(daftarMakanan_L1.begin() + i_L1);
                return true;
            }
        }
        return false;
    };

    auto cekMakan_L1 = [&](int cy_L1, int cx_L1) -> bool {
        bool makan_L1 = false;
        for (int dx_L1 = 0; dx_L1 < 3; dx_L1++) {
            int fx_L1 = cx_L1 + dx_L1;
            if (fx_L1 < 0 || fx_L1 >= (int)LABIRIN_L1[cy_L1].size()) continue;
            if (hapusMakanan_L1(cy_L1, fx_L1)) {
                skor_L1++;
                makan_L1 = true;
            }
        }
        return makan_L1;
    };

    mvprintw(posLabY_L1 - 1, posLabX_L1, "WASD/Arrow = belok | ENTER = pause | Q = keluar");

    gambarMakanan_L1();
    gambarKarakter_L1(posisiPemainY_L1, posisiPemainX_L1);

    time_t mulaiWaktu_L1 = time(nullptr);
    int sisaWaktu_L1 = waktuMulai_L1;

    while (true) {

        int tombol_L1 = getch();

        // PAUSE
        if (tombol_L1 == '\n') {
            bool lanjut_L1 = menuJeda_L1(posLabY_L1 + tinggiLab_L1/2, posLabX_L1 + lebarLab_L1/2 - 7);

            clear();
            tampilkanLabirin_L1(25, 80);
            gambarMakanan_L1();
            gambarKarakter_L1(posisiPemainY_L1, posisiPemainX_L1);
            refresh();

            if (!lanjut_L1) {
                if (skor_L1 > skorTertinggi_L1) tulis_file_skor_L1(fileSkor_L1, skor_L1);
                return;
            }
        }

        // KELUAR
        if (tombol_L1 == 'q' || tombol_L1 == 'Q') {
            if (skor_L1 > skorTertinggi_L1) tulis_file_skor_L1(fileSkor_L1, skor_L1);
            return;
        }

        // UBah arah
        if (tombol_L1 == KEY_RIGHT || tombol_L1=='d' || tombol_L1=='D') arah_L1 = 0;
        if (tombol_L1 == KEY_LEFT  || tombol_L1=='a' || tombol_L1=='A') arah_L1 = 1;
        if (tombol_L1 == KEY_UP    || tombol_L1=='w' || tombol_L1=='W') arah_L1 = 2;
        if (tombol_L1 == KEY_DOWN  || tombol_L1=='s' || tombol_L1=='S') arah_L1 = 3;

        int nextY_L1 = posisiPemainY_L1, nextX_L1 = posisiPemainX_L1;
        if (arah_L1 == 0) nextX_L1++;
        else if (arah_L1 == 1) nextX_L1--;
        else if (arah_L1 == 2) nextY_L1--;
        else if (arah_L1 == 3) nextY_L1++;

        // Hitung waktu
        time_t sekarang_L1 = time(nullptr);
        sisaWaktu_L1 = waktuMulai_L1 - (int)difftime(sekarang_L1, mulaiWaktu_L1);
        if (sisaWaktu_L1 < 0) sisaWaktu_L1 = 0;

        mvprintw(posLabY_L1 - 3, posLabX_L1, "Skor: %d  ", skor_L1);
        mvprintw(posLabY_L1 - 3, posLabX_L1 + lebarLayar_L1 - 20, "Highscore: %d  ", skorTertinggi_L1);
        mvprintw(posLabY_L1 - 2, posLabX_L1 + lebarLayar_L1 - 20, "Waktu: %02d:%02d  ",
                 sisaWaktu_L1/60, sisaWaktu_L1%60);

        if (sisaWaktu_L1 == 0) {
            if (skor_L1 > skorTertinggi_L1) tulis_file_skor_L1(fileSkor_L1, skor_L1);
            animasiKalah_L1(posLabY_L1 + tinggiLab_L1/2 - 3, posLabX_L1 + lebarLab_L1/2 - 15);
            return;
        }

        // cek pintu keluar
        if (nextY_L1 >= 0 && nextY_L1 < tinggiLab_L1 &&
            nextX_L1 >= 0 && nextX_L1 < (int)LABIRIN_L1[nextY_L1].size()) {

            if ((nextX_L1 == 0 || nextX_L1 == (int)LABIRIN_L1[nextY_L1].size()-1) &&
                LABIRIN_L1[nextY_L1][nextX_L1] == ' ') {

                if (skor_L1 > skorTertinggi_L1) tulis_file_skor_L1(fileSkor_L1, skor_L1);
                animasiMenang_L1(posLabY_L1 + tinggiLab_L1/2 - 3, posLabX_L1 + lebarLab_L1/2 - 15);
                return;
            }
        }

        // cek tabrakan dinding
        if (nextY_L1 < 0 || nextY_L1 >= tinggiLab_L1 ||
            nextX_L1 < 0 || nextX_L1 >= (int)LABIRIN_L1[nextY_L1].size() ||
            LABIRIN_L1[nextY_L1][nextX_L1] != ' ') {

            if (skor_L1 > skorTertinggi_L1) tulis_file_skor_L1(fileSkor_L1, skor_L1);
            animasiKalah_L1(posLabY_L1 + tinggiLab_L1/2 - 3, posLabX_L1 + lebarLab_L1/2 - 15);
            return;
        }

        // gerak karakter
        hapusKarakter_L1(posisiPemainY_L1, posisiPemainX_L1);
        gambarMakanan_L1();

        posisiPemainY_L1 = nextY_L1;
        posisiPemainX_L1 = nextX_L1;
        mulutTerbuka_L1 = !mulutTerbuka_L1;

        if (cekMakan_L1(posisiPemainY_L1, posisiPemainX_L1)) {
            beep();
            gambarMakanan_L1();
        }
        gambarKarakter_L1(posisiPemainY_L1, posisiPemainX_L1);
        refresh();

        if (daftarMakanan_L1.empty()) {
            if (skor_L1 > skorTertinggi_L1) tulis_file_skor_L1(fileSkor_L1, skor_L1);
            animasiMenang_L1(posLabY_L1 + tinggiLab_L1/2 - 3, posLabX_L1 + lebarLab_L1/2 - 15);
            return;
        }

        usleep(450000);
    }
}

// ======================================================
//  FUNGSI GAME UTAMA (L1) - dipanggil dari main
// ======================================================
void jalankanGameLabirin_L1() {

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_CYAN);
        bkgd(COLOR_PAIR(1));
    }

    clear();
    curs_set(0);
    tampilkanLabirin_L1(25, 80);
    gerakKarakterOtomatis_L1();

    refresh();
}
