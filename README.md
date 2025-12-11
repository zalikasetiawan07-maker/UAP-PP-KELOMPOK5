# UAP-PP-KELOMPOK5

Project ini disusun untuk memenuhi ujian akhir Praktikum (UAP) mata kuliah pengenalan pemrograman, dimana tugasnya adalah membuat game sederhana dengan menggunakan bahasa pemrograman c++ berbasis terminal interaktif.

berikut adalah anggota kelompok yang menyusun project ini:
Tessa Aufi Muzakiah (2517051029)
Zalika Dinar Alhena Setiawan (2517051007)
Chalilaika Novikri (2517051027)

-BYTEMUNCH-

BYTEMUNCH adalah game petualangan berbasis terminal yang dibuat menggunakan bahasa C dan library ncurses. Di dalam game ini, pemain menjelajahi labirin, mengumpulkan makanan, mengalahkan waktu, dan berusaha keluar dengan selamat.

A. Fitur Utama
1. Opening Screen (berwarna magenta)
Saat game dijalankan, pemain disambut layar pembuka dengan ucapan selamat datang dan percakapan singkat sebelum masuk ke permainan.
2. Input Nama Pemain
Pemain memasukkan nama, lalu game menampilkan sapaan personal.
3. Menu Utama (berwarna magenta)
Menu berisi:
[Easy]
[Medium]
[Hard]
[Exit]
Setiap level memiliki labirin, warna, dan tingkat kesulitan yang berbeda.

B. Labirin & Level
Setiap tingkat kesulitan menggunakan warna terminal yang berbeda agar pemain mudah mengenali suasana level:
Level	Warna Terminal	Deskripsi :
Easy	Biru	Labirin kecil dan paling sederhana
Medium	Cyan	Labirin lebih luas dan bercabang
Hard	Hijau	Labirin paling sulit dengan jalur kompleks

C. Sistem Makanan (Collectibles)
Di dalam labirin tersebar makanan yang bisa diambil pemain:
Setiap makanan menambah skor
Mendorong pemain untuk menjelajah
Menjadi ciri khas game BYTEMUNCH (“Byte” + “Munch”)

D. Timer
Game memiliki timer:
Jika waktu habis → pemain defeat
Jika pemain keluar sebelum waktu habis → lanjut ke penilaian akhir
Timer membuat permainan terasa lebih menantang dan memacu pemain untuk bergerak cepat.

E. Sistem Skor
Skor dihitung berdasarkan:
Jumlah makanan yang berhasil dimakan

F. Pause Menu
Selama bermain, pemain bisa membuka menu jeda (dengan menekan ENTER):
1. Lanjutkan
2. Keluar
Pause menu memudahkan pemain berhenti sejenak tanpa kehilangan progres.

G. End Screen
Setelah permainan selesai, pemain akan melihat:
Victory → jika berhasil keluar dari labirin
Defeat → jika waktu habis atau memilih keluar
