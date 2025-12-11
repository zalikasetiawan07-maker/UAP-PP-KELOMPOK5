# UAP-PP-KELOMPOK5

Project ini disusun untuk memenuhi ujian akhir Praktikum (UAP) mata kuliah pengenalan pemrograman, dimana tugasnya adalah membuat game sederhana dengan menggunakan bahasa pemrograman c++ berbasis terminal interaktif.

berikut adalah anggota kelompok yang menyusun project ini:
1. Tessa Aufi Muzakiah (2517051029)
2. Zalika Dinar Alhena Setiawan (2517051007)
3. Chalilaika Novikri (2517051027)

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
1. Easy	Biru	Labirin kecil dan paling sederhana
2. Medium	Cyan	Labirin lebih luas dan bercabang
3. Hard	Hijau	Labirin paling sulit dengan jalur kompleks

C. Sistem Makanan (Collectibles)
Di dalam labirin tersebar makanan yang bisa diambil pemain:
1. Setiap makanan menambah skor
2. Mendorong pemain untuk menjelajah
3. Menjadi ciri khas game BYTEMUNCH (“Byte” + “Munch”)

D. Timer
Game memiliki timer:
1. Jika waktu habis → pemain defeat
2. Jika pemain keluar sebelum waktu habis → lanjut ke penilaian akhir
3. Timer membuat permainan terasa lebih menantang dan memacu pemain untuk bergerak cepat.

E. Sistem Skor
Skor dihitung berdasarkan:
1. Jumlah makanan yang berhasil dimakan

F. Pause Menu
Selama bermain, pemain bisa membuka menu jeda (dengan menekan ENTER):
1. Lanjutkan
2. Keluar
3. Pause menu memudahkan pemain berhenti sejenak tanpa kehilangan progres.

G. End Screen
Setelah permainan selesai, pemain akan melihat:
1. Victory → jika berhasil keluar dari labirin
2. Defeat → jika waktu habis atau memilih keluar
