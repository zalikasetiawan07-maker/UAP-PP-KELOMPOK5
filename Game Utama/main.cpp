#include <ncursesw/curses.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include "easy.cpp"
#include "medium.cpp"
#include "hard.cpp"
#include "music.h"

// Deklarasi fungsi game
void jalankanGameLabirin1();
void jalankanGameLabirin_L1();
void jalankanGameHard();

// =============================================================
//                     FUNGSI SAMBUTAN
// =============================================================
void tampilkanSambutan() {
    clear();

    std::vector<std::string> daftarTeks = {
        "SELAMAT DATANG DI GAME",
        "\"BYTEMUNCH\""
    };

    int lebarKotak = 40;
    int tinggiKotak = 7;

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    int posisiY = (maxY - tinggiKotak) / 2;
    int posisiX = (maxX - lebarKotak) / 2;

    WINDOW* kotak = newwin(tinggiKotak, lebarKotak, posisiY, posisiX);
    wbkgd(kotak, COLOR_PAIR(1));
    box(kotak, 0, 0);

    for (int i = 0; i < daftarTeks.size(); i++) {
        int posX = (lebarKotak - daftarTeks[i].size()) / 2;
        mvwprintw(kotak, 2 + i, posX, "%s", daftarTeks[i].c_str());
    }

    wrefresh(kotak);
    sleep(2);

    delwin(kotak);
    clear(); 
    refresh();
}

// =============================================================
//                   FUNGSI DIALOG
// =============================================================
void tampilkanDialog() {

    std::vector<std::string> daftarDialog = {
        "Halo petualang! Selamat datang di dunia BYTEMUNCH.",
        "Aku adalah penjaga awal yang akan memandumu.",
        "Perjalananmu akan segera dimulai.",
        "Tapi sebelum itu... siapa nama karaktermu?"
    };

    std::vector<std::vector<std::string>> asciiKarakter = {
        {"  ($_$) ", "   /|\\  ", "   / \\  "},
        {"  (o_o)  ", "  <| |   ", "   / \\  "},
        {"  (*w*) ", "   /|>   ", "   / \\   "},
        {"  (+_+) ", "   /|\\  ", "   / \\  "}
    };

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    int lebarKotak = 70;
    int tinggiKotak = 5;

    int posisiY = maxY - tinggiKotak - 2;
    int posisiX = (maxX - lebarKotak) / 2;

    WINDOW* kotak = newwin(tinggiKotak, lebarKotak, posisiY, posisiX);
    wbkgd(kotak, COLOR_PAIR(1));

    int idx = 0;

    while (idx < daftarDialog.size()) {
        werase(kotak);
        box(kotak, 0, 0);

        int posTeks = (lebarKotak - daftarDialog[idx].size()) / 2;
        mvwprintw(kotak, 2, posTeks, "%s", daftarDialog[idx].c_str());
        wrefresh(kotak);

        int by = posisiY - 4;
        int bx = posisiX + 2;

        for (int i = 0; i < asciiKarakter[idx].size(); i++) {
            mvprintw(by + i, bx, "%s", asciiKarakter[idx][i].c_str());
        }

        refresh();

        int tombol = getch();
        if (tombol == ' ') idx++;
    }

    delwin(kotak);
    clear();
    refresh();
}

// =============================================================
//                 MINTA NAMA PEMAIN
// =============================================================
std::string mintaNamaKarakter() {
    clear();

    std::string teks = "Masukkan nama karakter: ";

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    mvprintw(maxY/2 - 1, (maxX - teks.size()) / 2, "%s", teks.c_str());
    move(maxY/2, (maxX / 2) - 10);

    echo();
    char namaTmp[50];
    getstr(namaTmp);
    noecho();

    return namaTmp;
}

// =============================================================
//                   MENU LEVEL (VERSI BESAR)
// =============================================================
int menuLevel() {

    std::vector<std::string> pilihanMenu = {
        "[ Easy ]",
        "[ Medium ]",
        "[ Hard ]",
        "[ Exit ]"
    };

    int pilihan = 0;

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    // ukuran besar
    int tinggi = 18;
    int lebar = 60;

    int startY = (maxY - tinggi) / 2;
    int startX = (maxX - lebar) / 2;

    WINDOW* menuWin = newwin(tinggi, lebar, startY, startX);
    keypad(menuWin, TRUE);

    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    while (true) {
        werase(menuWin);
        box(menuWin, 0, 0);

        std::string judul = "Pilih Level Permainan";
        mvwprintw(menuWin, 2, (lebar - judul.size()) / 2, "%s", judul.c_str());

        for (int i = 0; i < pilihanMenu.size(); i++) {
            int posX = (lebar - pilihanMenu[i].size()) / 2;
            int posY = 6 + (i * 2);

            if (i == pilihan) {
                wattron(menuWin, COLOR_PAIR(2));
                mvwprintw(menuWin, posY, posX, "%s", pilihanMenu[i].c_str());
                wattroff(menuWin, COLOR_PAIR(2));
            } else {
                mvwprintw(menuWin, posY, posX, "%s", pilihanMenu[i].c_str());
            }
        }

        wrefresh(menuWin);

        int key = wgetch(menuWin);

        if (key == KEY_UP || key == 'w') pilihan--;
        if (key == KEY_DOWN || key == 's') pilihan++;

        if (pilihan < 0) pilihan = pilihanMenu.size() - 1;
        if (pilihan >= pilihanMenu.size()) pilihan = 0;

        if (key == '\n') {
            delwin(menuWin);
            return pilihan;
        }
    }
}

// =============================================================
//                           MAIN
// =============================================================
int main() {

    bool jalan = true;
    bool pertama = true;
mainkanMusik("music(1).wav");
    while (jalan) {

        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);

        start_color();
        init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
        bkgd(COLOR_PAIR(1));

        clear();
        refresh();

        if (pertama) {
            tampilkanSambutan();
            tampilkanDialog();
            std::string nama = mintaNamaKarakter();

            clear();
            mvprintw(5, 5, "Selamat datang, %s!", nama.c_str());
            refresh();
            sleep(1);

            pertama = false;
        }

        int levelDipilih = menuLevel();

        clear();
        refresh();
        endwin();

        if (levelDipilih == 0) jalankanGameLabirin1();
        else if (levelDipilih == 1) jalankanGameLabirin_L1();
        else if (levelDipilih == 2) jalankanGameHard();
        else jalan = false;
    }
hentikanMusik();
    endwin();
    return 0;
}
