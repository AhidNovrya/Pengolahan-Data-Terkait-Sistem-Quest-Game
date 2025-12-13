#include "game.h"
// Fungsi SLL
void createListPlayer(LPlayer &L){
    L.first = nullptr;
}

adrPlayer allocatePlayer(playerInfotype x){
    adrPlayer p = new elmPlayer;

    x.Wealth = generateWealth(x.level);
    p->info = x;
    p->next = nullptr;
    return p;
}
void deallocatePlayer(adrPlayer &P){
    delete P;
    P = nullptr;
}

bool isEmptyPlayer(LPlayer L){
    return (L.first == nullptr);
}

// INSERT
void insertPlayer(LPlayer &L, adrPlayer P){
        P->next = L.first;
        L.first = P;
}

// DELETE
void deletePlayer(LPlayer &L, LQuest &QL, string idPlayer){
    adrPlayer p, b;
    adrRelasi r;
    adrQuest q;


    if (isEmptyPlayer(L)){
        cout << "Player yang inging dihapus, tidak ada";
        tidakAda();
    }else{
        p = findPlayer(L, idPlayer);
        if (p == nullptr){
            cout << "Player dengan id " << idPlayer << " tidak ditemukan" << endl;
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

            cout << "Player berhasil dihapus " << endl;
        }
    }
}
}






// FIND
adrPlayer findPlayer(LPlayer L,  string idPlayer){
    adrPlayer p = L.first;

    while (p != nullptr && p->info.idPlayer != idPlayer){
        p = p->next;
    }

    return p;
}

// SHOW
void showPlayer(adrPlayer P){
    cout<< "--------------------------------------------------"<< endl;
    cout << "Nama       : "<< P->info.nama << endl;
    cout << "ID         : "<< P->info.idPlayer << endl;
    cout << "Stats      : "<< "Lv " << P->info.level << " | " << P->info.playerClass << " | " << P->info.playerRace << endl;
    cout << "Wealth     : "<< P->info.Wealth << "g" << endl;
}

void showAllChild(LPlayer L){
    adrPlayer P;
    P = L.first;
    while (P != nullptr){
        cout<< "--------------------------------------------------"<< endl;
        cout << "Nama       : "<< P->info.nama << endl;
        cout << "ID         : "<< P->info.idPlayer << endl;
        cout << "Stats      : "<< "Lv " << P->info.level << " | " << P->info.playerClass << " | " << P->info.playerRace << endl;
        cout << "Wealth     : "<< P->info.Wealth << "g" << endl;
        P = P->next;
    }
}

void showOnePlayer(LPlayer L, string id){
    adrPlayer p = findPlayer(L, id);
    if (p != nullptr){
        showPlayer(p);
    }else{
        cout << "player yang anda cari tidak ada";
    }
}
// fungsi pendukung
int countPlayerWithoutQuest(LQuest QL, LPlayer PL){
    adrPlayer P;
    adrQuest q;

    int jumlah = 0;
    P = PL.first;
    q = QL.first;
    while (P != nullptr){
        if (findRelasi(q, P->info.idPlayer) == nullptr){
            cout<< "--------------------------------------------------"<< endl;
            cout << "Nama       : "<< P->info.nama << endl;
            cout << "ID         : "<< P->info.idPlayer << endl;
            cout << "Stats      : "<< "Lv " << P->info.level << " | " << P->info.playerClass << " | " << P->info.playerRace << endl;
            cout << "Wealth     : "<< P->info.Wealth << "g" << endl;
            jumlah ++;
        }
        P = P->next;
    }

    return jumlah;
}
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
