#include "music.h"
#include <cstdlib>

void mainkanMusik(const std::string &fileMusik) {
    std::string perintah = "mpg123 -q \"" + fileMusik + "\" &"; 
    system(perintah.c_str());
}

void hentikanMusik() {
    system("killall mpg123 2>/dev/null");
}
