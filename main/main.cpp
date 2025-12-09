
#include <iostream>
using namespace std;

//  Deklarasi fungsi dari folder Objek 
void karakter_opening();
void karakter_ending();
void tampilLabirin();

// fungsi dari folder Sistem game
void modeEasy();
void modeMedium();
void modeHard();

int main() {
    int pilih;

   karakter_opening();   

    cout << "\n=== GAME LABIRIN ===\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "Pilih mode: ";
    cin >> pilih;

    switch (pilih) {
    case 1: modeEasy(); break;
    case 2: modeMedium(); break;
    case 3: modeHard(); break;
    default:
        cout << "Pilihan tidak valid!\n";
    }

    karakter_ending();
    return 0;
}

