#include "highscore.h"
#include <fstream>

int bacaHighScore(const std::string& namaFile) {
    std::ifstream file(namaFile);
    int skor = 0;
    if (file.is_open()) {
        file >> skor;
    }
    return skor;
}

void simpanHighScore(const std::string& namaFile, int skorBaru) {
    int skorLama = bacaHighScore(namaFile);
    if (skorBaru > skorLama) {
        std::ofstream file(namaFile, std::ios::trunc);
        file << skorBaru;
    }
}
