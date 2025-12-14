
#include "highscore.h"
#include <fstream>
#include <iostream>

bool bacaSkor(const std::string &namaFile, int &nilai) {
    std::ifstream file(namaFile);
    if (!file.is_open()) {
        nilai = 0;
        return false;
    }
    file >> nilai;
    file.close();
    return true;
}

bool tulisSkor(const std::string &namaFile, int nilai) {
    std::ofstream file(namaFile, std::ios::trunc);
    if (!file.is_open()) return false;
    file << nilai;
    file.close();
    return true;
}

