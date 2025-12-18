#include "game.h"

void judul(){
    cout<< R"(
//========================================================\\
||    ____  __  ________________  ________   __  _______  ||
||   / __ \/ / / / __/ __/_  __/ / ___/ _ | /  |/  / __/  ||
||  / /_/ / /_/ / _/_\ \  / /   / (_ / __ |/ /|_/ / _/    ||
||  \___\_\____/___/___/ /_/    \___/_/ |_/_/  /_/___/    ||
||                                                        ||
)";
    garis();
}

void garis(){
    cout<< "============================================================";
}

void garisKartu(){
    cout<< R"(     /==========================================\)";
}

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
                    if (findRelasi(q, p->info.idPlayer) == nullptr) {
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

void menuPlayer(LQuest &QL, LPlayer &L){
    adrPlayer P;
    playerInfotype x;
    string nPlayerHapus, nPlayerFind;
    int n, j;
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
                cout << "    Nama Player : ";
                cin >> x.nama;
                cout << "    Class Player : ";
                cin >> x.playerClass;
                cout << "    Ras Player : ";
                cin >> x.playerRace;
                cout << "    Level Player : ";
                cin >> x.level;


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
void tidakAda(){
    cout << "         :##+.                                               " << endl;
    cout << "         .#####+.                          .=*#-             " << endl;
    cout << "         :*#######=                    :+*#####=             " << endl;
    cout << "          :*########*-    ..:::....=+##########+             " << endl;
    cout << "           :+#################################=.             " << endl;
    cout << "             -##############################=.               " << endl;
    cout << "               -##########################+.                 " << endl;
    cout << "               +########################*:                   " << endl;
    cout << "              :####* .##########=. =#####*                   " << endl;
    cout << "              +####=:=##########+-=#######-                  " << endl;
    cout << "             -*+#########++##########**###-                  " << endl;
    cout << "             :===+#################=====###.                 " << endl;
    cout << "             -===*######*-**+######=====###=                 " << endl;
    cout << "             =###########****+#############+                 " << endl;
    cout << "             .*#############################.                " << endl;
    cout << "              .#############################=                " << endl;
    cout << "              :##############################:               " << endl;
}

