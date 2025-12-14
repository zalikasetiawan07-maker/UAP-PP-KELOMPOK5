#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>

// Fungsi baca dan tulis skor untuk tiap level
bool bacaSkor(const std::string &namaFile, int &nilai);
bool tulisSkor(const std::string &namaFile, int nilai);

#endif

