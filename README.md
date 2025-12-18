# ⚔️ Quest & Player Management System

> **Tugas Besar Algoritma dan Pemrograman** > Aplikasi Console C++ untuk mengelola data Quest (Misi) dan Player (Pemain) menggunakan Struktur Data Linked List dan Relasi.

---

## 📖 Deskripsi Project

Aplikasi ini mensimulasikan sistem *party* dalam sebuah game RPG. Program ini memungkinkan pengguna untuk:
1. Membuat dan mengelola **Quest** (Misi).
2. Membuat dan mengelola **Player** (Pemain).
3. Menghubungkan Player ke Quest (Sistem Relasi/Party).
4. Menyimpan data secara otomatis agar tidak hilang saat program ditutup (**Data Persistence**).

### 🛠️ Struktur Data
Project ini menggunakan implementasi **Linked List** murni tanpa library STL (seperti `std::list` atau `std::vector`), sesuai dengan spesifikasi Tugas Besar:
* **Parent (Quest):** Double Linked List (DLL).
* **Child (Player):** Single Linked List (SLL).
* **Relasi:** Single Linked List yang tersimpan di dalam setiap Node Quest (List of Lists).

---

## ⚠️ PENTING: Aturan Penggunaan (SOP)

Karena program ini dirancang menggunakan fungsi input standar C++ (`cin >>`) untuk mematuhi batasan penggunaan library tertentu, harap perhatikan aturan berikut saat input data:

🚨 **DILARANG MENGGUNAKAN SPASI** 🚨

Saat memasukkan **Nama Quest** atau **Nama Player**, gunakan *underscore* (`_`) atau *dash* (`-`) sebagai pengganti spasi.

* ❌ **Salah:** `Memburu Naga Api` (Program akan error/looping)
* ✅ **Benar:** `Memburu_Naga_Api` atau `Memburu-Naga-Api`

---

## 🚀 Fitur Utama

### 1. Manajemen Quest (Parent)
* **Insert:** Menambahkan Quest baru (Otomatis urut berdasarkan *Difficulty* dan *Level Min*).
* **Delete:** Menghapus Quest (Otomatis menghapus relasi dengan player di dalamnya).
* **Show:** Menampilkan daftar Quest beserta statusnya.

### 2. Manajemen Player (Child)
* **Insert:** Menambahkan Player baru (Stats Wealth digenerate otomatis).
* **Delete:** Menghapus Player (Otomatis keluar dari semua quest yang diikuti).
* **Show:** Melihat status player dan quest apa saja yang sedang diikuti.
* **Count:** Menghitung jumlah player yang "menganggur" (tidak punya quest).

### 3. Manajemen Party (Relasi)
* **Join Quest:** Mendaftarkan Player ke dalam Quest.
* **Kick Member:** Mengeluarkan Player dari Quest tertentu.
* **Edit Party:** Menukar Player dalam quest dengan Player lain (Validasi agar tidak duplikat).

### 4. File I/O (Penyimpanan Data)
* Data Quest, Player, dan Relasi otomatis **disimpan** ke file `.txt` saat program keluar.
* Data otomatis **dimuat kembali** (Load) saat program dijalankan.

---

## ⚙️ Cara Kompilasi & Menjalankan

### Opsi 1: Menggunakan Code::Blocks
1.  Buka file `FILE_TUBES.cbp` (jika ada) atau buat Project baru.
2.  Pastikan semua file `.cpp` berikut masuk ke dalam project:
    * `main.cpp`
    * `parent.cpp`
    * `child.cpp`
    * `relasi.cpp`
    * `MenuTampilan.cpp`
    * `file_io.cpp`
3.  Klik **Build & Run** (F9).

### Opsi 2: Menggunakan Terminal / CMD (Manual)
Jika Anda ingin menjalankan tanpa IDE, ikuti langkah ini:

1.  Pastikan folder `data` sudah tersedia di direktori yang sama.
2.  Jalankan perintah compile berikut:
    ```bash
    g++ main.cpp parent.cpp child.cpp relasi.cpp MenuTampilan.cpp file_io.cpp -o game
    ```
3.  Jalankan program:
    * **Windows:** `game.exe`
    * **Linux/Mac:** `./game`

---

## 📂 Struktur Folder & File

```text
.
├── data/                 # Folder wajib untuk menyimpan file .txt
│   ├── players.txt       # Database Player
│   ├── quests.txt        # Database Quest
│   └── relasi.txt        # Database Relasi
├── game.h                # Header file (Deklarasi Struct & Fungsi)
├── main.cpp              # Program Utama
├── parent.cpp            # Implementasi fungsi Quest
├── child.cpp             # Implementasi fungsi Player
├── relasi.cpp            # Implementasi fungsi Relasi
├── MenuTampilan.cpp      # Tampilan Menu UI
└── file_io.cpp           # Fungsi Save & Load Data
