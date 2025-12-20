#include "game.h"
// Fungsi SLL

// IS : menerima list player L dalam keadaan apa pun.
// FS : list player L berada pada kondisi kosong dengan first bernilai nullptr.
void createListPlayer(LPlayer &L){
    L.first = nullptr;
}

// IS : menerima data player berupa id, nama, class, race, dan level.
// FS : terbentuk satu node player baru dengan info sesuai data, wealth di-generate dari level, dan next bernilai nullptr.
adrPlayer allocatePlayer(playerInfotype x){
    adrPlayer p = new elmPlayer;

    x.Wealth = generateWealth(x.level);
    p->info = x;
    p->next = nullptr;
    return p;
}

// IS : menerima alamat node player yang mungkin bernilai nullptr atau valid.
// FS : node player dilepas dari memori dan alamatnya di-set menjadi nullptr.
void deallocatePlayer(adrPlayer &P){
    delete P;
    P = nullptr;
}

// IS : menerima list player.
// FS : menghasilkan nilai true jika list player kosong dan false jika list berisi data.
bool isEmptyPlayer(LPlayer L){
    return (L.first == nullptr);
}

// INSERT

// IS : menerima list player dan satu node player yang telah dialokasikan.
// FS : node player dimasukkan ke awal list player sehingga menjadi elemen pertama.
void insertPlayer(LPlayer &L, adrPlayer P){
        P->next = L.first;
        L.first = P;
}

// DELETE

// IS : menerima list player, list quest, dan id player yang akan dihapus.
// FS : seluruh relasi player pada setiap quest dihapus dan node player dihapus dari list player.
void deletePlayer(LPlayer &L, LQuest &QL, string idPlayer){
    adrPlayer p, b;
    adrRelasi r;
    adrQuest q;


    if (isEmptyPlayer(L)){
        cout << "   Player yang ingin dihapus, tidak ada";
        tidakAda();
    }else{
        p = findPlayer(L, idPlayer);
        if (p == nullptr){
            cout << RED<< "   Player dengan id " << idPlayer << " tidak ditemukan" << RESET<< endl;
            tidakAda();
        }else{
            q = QL.first;
            while (q != nullptr){
                r = findRelasi(q, idPlayer);
                while (r != nullptr){
                    deleteRelasi(q, idPlayer);
                    r = findRelasi(q, idPlayer);
                }
                q = q->next;
            }

            if (p == L.first){//del first
                L.first = p->next;
                p->next = nullptr;
                deallocatePlayer(p);
            }else if(p->next == nullptr && L.first != nullptr){//del last
                b = L.first;
                while (b->next->next != nullptr){
                    b=b->next;
                }
                b->next = nullptr;
                deallocatePlayer(p);
            }else{// before
                b = L.first;
                while (b->next != p){
                    b = b->next;
                }
                b->next = p->next;
                p->next = nullptr;
                deallocatePlayer(p);

            cout << "   Player berhasil dihapus " << endl;
            }
        }
    }
}


// FIND

// IS : menerima list player dan id player yang dicari.
// FS : menghasilkan alamat node player yang sesuai dengan id atau nullptr jika tidak ditemukan.
adrPlayer findPlayer(LPlayer L,  string idPlayer){
    adrPlayer p = L.first;

    while (p != nullptr && p->info.idPlayer != idPlayer){
        p = p->next;
    }

    return p;
}

// SHOW

// IS : menerima alamat node player.
// FS : data player ditampilkan ke layar.
void showPlayer(adrPlayer P){
    string strStat = "Lv. " + to_string(P->info.level) + " | " + P->info.playerClass + " | " + P->info.playerRace;
    string strGold = to_string(P->info.Wealth) + " g";
    garisKartu();
    cout<< R"(
    ||  Nama       : )"<< left<< setw(27)<< P->info.nama << R"(||
    ||  ID         : )"<< left<< setw(27)<< P->info.idPlayer << R"(||
    ||  Stats      : )"<< left<< setw(27)<< strStat<< R"(||
    ||  Wealth     : )"<< left<< setw(27)<< strGold<< R"(||
     \__________________________________________/
)";
}

// IS : menerima list player.
// FS : seluruh data player dalam list ditampilkan ke layar atau menampilkan pesan jika list kosong.
void showAllChild(LPlayer L, LQuest Q){
    adrPlayer P;
    int jQuest;
    P = L.first;
    while (P != nullptr){
        showPlayer(P);
        cout<< "    Jumlah Quest yang diikuti player: "<< countQuestOfOnePlayer(Q, P)<< endl;
        P = P->next;
    }
}

// IS : menerima list player dan id player.
// FS : data player dengan id tersebut ditampilkan ke layar atau menampilkan pesan jika tidak ditemukan.
void showOnePlayer(LPlayer L, string id){
    adrPlayer p = findPlayer(L, id);
    if (p != nullptr){
        showPlayer(p);
    }else{
        cout << RED<< "player yang anda cari tidak ada"<< RESET <<endl;
        tidakAda();
    }
}

//COUNT

// IS : menerima list quest dan list player.
// FS : menampilkan seluruh player yang tidak memiliki quest dan menghasilkan jumlah player tersebut.
int countPlayerWithoutQuest(LQuest QL, LPlayer PL){
    adrPlayer P = PL.first;
    int jumlah = 0;

    while (P != nullptr){
        bool punyaQuest = false;
        adrQuest q = QL.first;
        while (q != nullptr && !punyaQuest){
            if (findRelasi(q, P->info.idPlayer) != nullptr){
                punyaQuest = true;
            } else {
                q = q->next;
            }
        }
        if (punyaQuest == false){
            showPlayer(P);
            jumlah++;
        }
        P = P->next;
    }
    return jumlah;
}


// fungsi pendukung

// IS : menerima nilai level player.
// FS : menghasilkan nilai wealth secara acak sesuai rentang yang ditentukan oleh level.
int generateWealth(int level){
    int minGold, maxGold;

    if (level < 10){
        minGold = 3;
        maxGold = 15;
    } else if (level <= 25){
        minGold = 16;
        maxGold = 80;
    } else if (level <= 50){
        minGold = 90;
        maxGold = 450;
    } else if (level <= 75){
        minGold = 460;
        maxGold = 2300;
    } else{
        minGold = 2310;
        maxGold = 11550;
    }
    int wealth = minGold + (rand() % (maxGold - minGold + 1));

    return wealth;
}
