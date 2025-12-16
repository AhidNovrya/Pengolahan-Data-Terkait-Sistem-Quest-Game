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
    cout<< "    PILIH MENU (1-3): ";
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
||--------------------------------------------------------||
||  0. Back                                               ||
)";
    garis();
    cout<< endl;
    cout<< "    Silakan pilih (0/1/2/3/4): ";
}

void tampilanMenuPlayer(){
    cout<< R"(
||                                                        ||
||  1. Menambahkan Player                                 ||
||  2. Menghapus Player                                   ||
||  3. Mencari Player                                     ||
||  4. Menampilan semua Player                            ||
||                                                        ||
||--------------------------------------------------------||
||  0. Back                                               ||
)";
    garis();
    cout<< endl;
    cout<< "    Silakan pilih (0/1/2/3/4):";
}


void menuQuest(LQuest &L){
    string nQuestHapus, nQuestFind;
    int n;
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
            inputQuest(L);
            break;
        case 2:
            cout<< "    Silakan masukan nama QUEST yang ingin dihapus : ";
            cin>> nQuestHapus;
            deleteQuest(L, nQuestHapus);
            break;
        case 3:
            cout<< "    Silakan masukan nama QUEST: ";
            cin>> nQuestFind;
            showOneQuest(L, nQuestFind);
            break;
        case 4:
            showAllQuest(L);
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
            cout<< "Silakan masukan jumlah PLAYER yang akan ditambahkan : "<< endl;
            cin>> j;
            for (int i=0; i<j; i++){
                cout << "Id Player : ";
                cin >> x.idPlayer;
                cout << "Nama Player : ";
                cin >> x.nama;
                cout << "Class Player : ";
                cin >> x.playerClass;
                cout << "Ras Player : ";
                cin >> x.playerRace;
                cout << "Level Player : ";
                cin >> x.level;


                P = allocatePlayer(x);
                insertPlayer(L, P);
                cout<< endl;
            }
            break;
        case 2:
            cout<< "Silakan masukan id PLAYER yang ingin dihapus : ";
            cin>> nPlayerHapus;
            deletePlayer(L, QL, nPlayerHapus);
            break;
        case 3:
            cout<< "Silakan masukan Id PLAYER : ";
            cin>> nPlayerFind;
            showOnePlayer(L, nPlayerFind);
            break;
        case 4:
            showAllChild(L);
            break;
        case 5:
            //countPlayerWithoutQuest(LQuest, LPlayer);
        default:
            cout<< "Mohon pilih menu yang tertera!!"<< endl;
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

