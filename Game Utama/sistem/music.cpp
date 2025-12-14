#include "music.h"
#include <cstdlib>

void mainkanMusik() {
    std::string perintah = "mpg123 -q \"" + FILE_MUSIK + "\" &"; 
    system(perintah.c_str());
}

void hentikanMusik() {
    system("killall mpg123 2>/dev/null");
}

