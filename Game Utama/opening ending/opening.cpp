#include "opening.h"
#include <ncursesw/curses.h>
#include <unistd.h>
#include <vector>

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
