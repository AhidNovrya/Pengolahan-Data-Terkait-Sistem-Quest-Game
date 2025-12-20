#include "game.h"

// IS : program memanggil tampilan judul saat akan menampilkan halaman utama.
// FS : judul aplikasi dan ASCII art ditampilkan ke layar.
void judul(){
    cout<< R"(
  |
  |
  + \                       __==-_      _-==__
  \\.Q_.*=.             _--^###//        \\###^--_
   `(#'/.\|            -#####//   (    )   \\#####-
    .>' (_--.         -#####//    |\^^/|    \\#####-
 _=/d   ,^\          _/####//     (@::@)     \\####\_
~~ \)-'   '         /####((        \\//        ))####\
   / |             -#####\\        (oo)        //#####-
  '  '            -#######\\      / VV \      //#######-
//========================================================\\
||    ____  __  ________________  ________   __  _______  ||
||   / __ \/ / / / __/ __/_  __/ / ___/ _ | /  |/  / __/  ||
||  / /_/ / /_/ / _/_\ \  / /   / (_ / __ |/ /|_/ / _/    ||
||  \___\_\____/___/___/ /_/    \___/_/ |_/_/  /_/___/    ||
||                                                        ||
||   By : Ahid Novryan & Muhammad Gyan Kaushal            ||
)";
    garis();
}

// IS : program membutuhkan pemisah antar bagian tampilan.
// FS : garis pembatas panjang ditampilkan ke layar.

void garis(){
    cout<< "============================================================";
}

// IS : program membutuhkan pemisah tampilan dalam bentuk kartu.
// FS : garis pembatas gaya kartu ditampilkan ke layar.
void garisKartu(){
    cout<< R"(     /==========================================\)";
}

// IS : pengguna berada pada kondisi awal sebelum memilih fitur pada program.
// FS : halaman home ditampilkan berisi judul dan pilihan menu utama.
void tampilanHome(){
    cout<< R"(
||                                                        ||
||  1. Manajeman Quest                                    ||
||  2. Manajeman Player                                   ||
||                                                        ||
||--------------------------------------------------------||
||  0. Exit                                               ||
)";
    garis();
    cout<< endl;
    cout<< "    PILIH MENU (0-2): ";
}


//[---------------QUEST---------------]

// IS : pengguna memilih masuk ke bagian quest.
// FS : tampilan menu quest ditampilkan berisi daftar pilihan pengelolaan quest.
void tampilanMenuQuest(){
    judul();
    cout<< R"(
||                                                        ||
||  1. Menambahkan QUEST                                  ||
||  2. Menghapus QUEST                                    ||
||  3. Mencari QUEST                                      ||
||  4. Menampilan semua QUEST                             ||
||                                                        ||
||  [MANAJEMEN PARTY]                                     ||
||  5. Daftarkan Player ke Quest (Ambil Misi)             ||
||  6. Keluarkan Player dari Quest (Kick)                 ||
||  7. Tukar Player dalam Quest (Edit Party)              ||
||  8. Lihat Daftar Player di Quest Tertentu              ||
||                                                        ||
||--------------------------------------------------------||
||  0. Back                                               ||
)";
    garis();
    cout<< endl;
    cout<< "    Silakan pilih (0-8): ";
}

// IS : pengguna memilih masuk ke bagian player.
// FS : tampilan menu player ditampilkan berisi daftar pilihan pengelolaan player.
void tampilanMenuPlayer(){
    judul();
    cout<< R"(
||                                                        ||
||  1. Menambahkan Player                                 ||
||  2. Menghapus Player                                   ||
||  3. Mencari Player                                     ||
||  4. Menampilan semua Player                            ||
||  5. Menampilan Player yang tidak mengikuti Quest       ||
||                                                        ||
||  [STATUS PLAYER]                                       ||
||  6. Cek Quest Aktif Player (Lihat Kesibukan)           ||
||                                                        ||
||--------------------------------------------------------||
||  0. Back                                               ||
)";
    garis();
    cout<< endl;
    cout<< "    Silakan pilih (0-6):";
}

// IS : pengguna berada di menu quest dan akan menjalankan navigasi berdasarkan pilihan input.
// FS : proses menu quest berjalan sesuai pilihan pengguna sampai pengguna kembali ke menu sebelumnya.
void menuQuest(LQuest &LQ, LPlayer &LP){
    string nQuestHapus, nQuestFind, idPlayer, idBaru;
    int n;
    adrQuest q;
    adrPlayer p, pBaru;
    bool running = true;

    while (running){
        system("cls");
        tampilanMenuQuest();
        cin>> n;
        cout<< endl;
        switch (n){
        case 0:
            running = false;
            break;
        case 1:
            inputQuest(LQ);
            break;
        case 2:
            cout<< "    Silakan masukan nama QUEST yang ingin dihapus : ";
            cin>> nQuestHapus;
            deleteQuest(LQ, nQuestHapus);
            break;
        case 3:
            cout<< "    Silakan masukan nama QUEST: ";
            cin>> nQuestFind;
            showOneQuest(LQ, nQuestFind);
            break;
        case 4:
            showAllQuest(LQ);
            break;
        case 5:
            cout<< "    Silakan masukan nama QUEST: ";
            cin>> nQuestFind;
            q = findQuest(LQ, nQuestFind);
            if (q != nullptr){
                cout<< "    Silakan masukan ID PLAYER: ";
                cin>> idPlayer;
                p = findPlayer(LP, idPlayer);
                if (p != nullptr){
                    if (p->info.level < q->info.levelMin) {
                        cout << RED << "    Gagal! level player kurang dari level minimum " << q->info.levelMin << RESET << endl;
                    }else if(findRelasi(q, p->info.idPlayer) == nullptr) {
                        insertRelasi(q, p);
                        cout<< GREEN<< "    "<< p->info.nama<< " berhasil mengambil quest"<< RESET<< endl;
                    } else {
                        cout<< RED<< "    Player sudah mengambil quest ini!"<< RESET<< endl;
                    }
                } else{
                    cout<< RED<< "   Player tidak ditemukan!!"<< RESET<< endl;
                }
            } else{
                cout<< RED<< "   Quest tidak ditemukan!!"<< RESET<< endl;
            }
            break;
        case 6:
            cout<< "    Masukan Nama QUEST: ";
            cin>> nQuestFind;
            q = findQuest(LQ, nQuestFind);
            if (q != nullptr){
                cout<< "    Silakan masukan ID PLAYER: ";
                cin>> idPlayer;
                deleteRelasi(q, idPlayer);
            } else{
                cout<< RED<< "    Quest tidak ditemukkan!!"<< RESET<< endl;
            }
            break;
        case 7:
            cout << "   Masukan Nama Quest: ";
            cin >> nQuestFind;
            q = findQuest(LQ, nQuestFind);
            if (q != NULL) {
                cout << "   ID Player LAMA: "; cin >> idPlayer;
                p = findPlayer(LP, idPlayer);
                cout << "   ID Player PENGGANTI: "; cin >> idBaru;
                pBaru = findPlayer(LP, idBaru);

                if (p != NULL && pBaru != NULL) {
                    editRelasi(q, p, pBaru);
                } else { cout << RED << "   Data Player tidak valid!" << RESET << endl; }
            } else { cout << RED << "   Quest tidak ditemukan!" << RESET << endl; }
            break;

        case 8:
            cout << "   Masukan Nama Quest: ";
            cin >> nQuestFind;
            q = findQuest(LQ, nQuestFind);
            if (q != NULL) {
                showPlayersFromQuest(q);
            } else { cout << RED << "   Quest tidak ditemukan!" << RESET << endl; }
            break;
        default:
            cout<< RED<< "    Mohon pilih menu yang tertera!!"<< RESET<< endl;
            break;
        }
        if (running) {
             system("pause");
        }
    }
}

// IS : pengguna berada di menu player dan akan menjalankan navigasi berdasarkan pilihan input.
// FS : proses menu player berjalan sesuai pilihan pengguna sampai pengguna kembali ke menu sebelumnya.
void menuPlayer(LQuest &QL, LPlayer &L){
    adrPlayer P;
    playerInfotype x;
    string nPlayerHapus, nPlayerFind;
    int n, j, c, r;
    bool running = true;

    while (running){
        system("cls");
        tampilanMenuPlayer();
        cin>> n;
        cout<< endl;
        switch (n){
        case 0:
            running = false;
            break;
        case 1:
            cout<< "    Silakan masukan jumlah PLAYER yang akan ditambahkan : ";
            cin>> j;
            for (int i=0; i<j; i++){
                cout << "    Id Player : ";
                cin >> x.idPlayer;
                if (x.idPlayer.length() != 4) {
                    cout << RED <<"ID Player harus 4 karakter!" << RESET << endl;
                    break;
                }

            cout << "    Nama Player(Tanpa Spasi) : ";
            cin >> x.nama;

            cout << CYAN << R"(
    Pilih Class Player (c):
    1. Fighter
    2. Wizard
    3. Palladin
    4. Bard
    5. Ranger
)" << RESET;
    cout << "    Pilihan (1-5):";
            cin >> c;

            switch (c) {
                case 1: x.playerClass = "Fighter"; break;
                case 2: x.playerClass = "Wizard";  break;
                case 3: x.playerClass = "Palladin";break;
                case 4: x.playerClass = "Bard";    break;
                case 5: x.playerClass = "Ranger";  break;
                default:
                    cout << RED << "Class tidak valid!" << RESET << endl;
                    break;
            }

            cout << GREEN << R"(    Pilih Ras Player (r):
    1. Human
    2. Orc
    3. Elf
    4. Dwarf
    5. Tabaxi
)" << RESET;
            cout << "    Pilihan (1-5):";
            cin >> r;
            cout << endl;

            switch (r) {
                case 1: x.playerRace = "Human";  break;
                case 2: x.playerRace = "Orc";    break;
                case 3: x.playerRace = "Elf";    break;
                case 4: x.playerRace = "Dwarf";  break;
                case 5: x.playerRace = "Tabaxi"; break;
                default:
                    cout << RED << "Ras tidak valid!" << RESET << endl;
                    break;
}
            cout << "   Level Player : ";
            cin >> x.level;
            cout << endl;

            P = allocatePlayer(x);
            insertPlayer(L, P);
            cout<< endl;
            }
            break;
        case 2:
            cout<< "    Silakan masukan id PLAYER yang ingin dihapus : ";
            cin>> nPlayerHapus;
            deletePlayer(L, QL, nPlayerHapus);
            break;
        case 3:
            cout<< "    Silakan masukan Id PLAYER : ";
            cin>> nPlayerFind;
            showOnePlayer(L, nPlayerFind);
            break;
        case 4:
            showAllChild(L);
            break;
        case 5:
            j = countPlayerWithoutQuest(QL, L);
            cout<< "    Jumlah Player yang tidak memiliki Quest adalah: "<< j<< endl;
            break;
        case 6:
            cout << "    Masukan ID Player: "; cin >> nPlayerFind;
            P = findPlayer(L, nPlayerFind);
            if (P != NULL) {
                showPlayer(P);
                cout << endl;
                showQuestFromPlayer(QL, P);
            } else {
                cout << RED << "    Player tidak ditemukan!" << RESET << endl;
            }
            break;
        default:
            cout<< RED<< "    Mohon pilih menu yang tertera!!"<< RESET<< endl;
            break;
        }
        if (running) {
             system("pause");
        }
    }
}

// IS : pengguna memilih opsi keluar dari program.
// FS : ditampilkan pesan penutup menggunakan ASCII art.
void keluarGame(){
cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#-=++....        " << endl;
cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%=*===:.        " << endl;
cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%===:..        " << endl;
cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+===..       " << endl;
cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%====:  .    " << endl;
cout << "%%%%%%%%%%%%%%%%%%%%%%%%%#%#%%%%%%%%%%%%%%%%%%%+#==-..    " << endl;
cout << "%%%%%%%%%%%%%%%%%%%%%%%*#@@%%%%%%%%%%%%%%%%%%%%%-**==.    " << endl;
cout << "%%%%%%%%%%%%%%%%%%%%%**%*@@@%%%%%%%%%%%%%%%#%%%%%==*=- .  " << endl;
cout << "%%%%%%%%%%%%%%%%%%%%%%%%*@@@@#%%%%%%%%%%%%%*%%%%%*===-..  " << endl;
cout << "%%%%%%+#%%%%%%%%%%%%%%%#%@@@@@@%%%%%%%%%%%%##%%%%%=--#: .." << endl;
cout << "%%%%%%%###%%%%%%%%%*%%%#%@@@**%@*%%%%%%%%%%%+%%%%%+=*%+..." << endl;
cout << "%%%%%%%#%%%%%%%%%%%*#%%#@*-%+==#+-+#%%%%%%%%#%%%%%+*%%#..." << endl;
cout << "%%%%%%**%%%%%%%%%%#%#%%*#@%-======##=@@@%%%%%%%%%%#%%%%:.." << endl;
cout << "%%%%%%%+==*##*##%@@@@@@@@@+#####===@@@@@%%%%%%%%%%%#%%%+.." << endl;
cout << "%%%%*-@%=-%%+*@@@@@@@@@@@@#%%####=*@@@@@#%%%%%%%%%%#%%%#.." << endl;
cout << "%%#++@#=-====*@@@@@@@@@@@@@#+##**@@@%%%%%%%%%%%%%%%*%%=*.." << endl;
cout << "#@%+@@**###+=+@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%%*%#...." << endl;
cout << "@@%%@@@*####=%@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%%%%%%*%%*...." << endl;
cout << "@@@@@@@@%*+%@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%*%%%%+.  ." << endl;
cout << "*@@@@@%%%%%@@@@@@@@%######@@@@@@@@@@@@%#%%%%%#***#######**" << endl;
cout << ".#@@%%%%%%%%@@@@@@@@*%%%%%%%#%@@@@@@@%#*%%**########**%@%*" << endl;
cout << "..#@%%%%%%%@@@@@@@@@*%%%%%%%%%*@@@@@#*+++#########*%@@@@@@" << endl;
cout << "...#@%%%%%%@@@@@@@@@*%%%%%%%%%%*@%#@@+=##########+@@@@@@@@" << endl;
cout << "=**+++=+*#%%%%@@@@@@%%%%%%%%%%%#%@@@@*###########%@@@@@@@@" << endl;
cout << "++++++++=+++*@@#=*%%##%%%%%%%%%%%*@@*###########+@@@@@@@@@" << endl;
cout << "+++++==%%%%%##%==@@@@@%@@%%%%%%*@%@#############+@@@@@@@@@" << endl;
cout << "%=+++*+%%%%%+##+*@@@@@#@@@@*+*@@#@*###########**@@@@@@@@@@" << endl;
cout << "@@@%##=%%%%%+*##*#@@@@%#@%*****%@*########*#%@@@@@@%#%@@@@" << endl;
cout << "@@@%+#****+**+*%@@@%#%%@#@=**+@@%*######*%@@@@@@@@@@@@@@@@" << endl;
cout << "@@@@=*#######*@@@@@@@@@@@%%+***%*########*@@@@@@@@@@@@@@@@" << endl;
cout << "@@@@%=*#####%@@@@@@@@@@@@@@****#+##########@@@@@@@@@@@@@@@" << endl;
}

// IS : terjadi kondisi data kosong atau hasil pencarian tidak ditemukan pada suatu menu.
// FS : pesan informasi bahwa data tidak ada ditampilkan ke layar melalui ASCII art.
void tidakAda(){
    cout << YELLOW << R"(
             :##+.
             .#####+.                          .=*#-
             :*#######=                    :+*#####=
              :*########*-    ..:::....=+##########+
               :+#################################=.
                 -##############################=.
                   -##########################+.
                   +########################*:
                  :####* .##########=. =#####*
                  +####=:=##########+-=#######-
                 -*+#########++##########**###-
                 :===+#################=====###.
                 -===*######*-**+######=====###=
                 =###########****+#############+
                 .*#############################.
                  .#############################=
                  :##############################:
)" << RESET << endl;
}








