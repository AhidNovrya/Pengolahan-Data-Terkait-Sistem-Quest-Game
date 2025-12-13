#include "game.h"

adrRelasi allocateRelasi(adrPlayer P){
    adrRelasi r = new elmRelasi;

    r->player = P;
    r->next = nullptr;
    return r;
}

void deallocateRelasi(adrRelasi R){
    delete R;
    R = nullptr;
}

bool isEmptyRelasi(adrQuest Q){
    return Q->firstRelasi == nullptr;
}


//[---------------INSERT---------------]
void insertRelasi(adrQuest &Q, adrPlayer P){
    adrRelasi C, R = allocateRelasi(P);

    if (isEmptyRelasi(Q)){
        Q->firstRelasi = R;
    } else {
        C = Q->firstRelasi;
        while (C->next != nullptr){
            C = C->next;
        }
        C->next = R;
    }
}


//[---------------DELETE---------------]
void deleteFirstRelasi(adrQuest &Q, adrRelasi &R){
    R = Q->firstRelasi;

    Q->firstRelasi = R->next;
    R->next = nullptr;
}

void deleteLastRelasi(adrQuest &Q, adrRelasi &R){
    adrRelasi i = Q->firstRelasi;

    while (i->next->next != nullptr){
        i = i->next;
    }

    R = i->next;
    i->next = nullptr;
}

void deleteNodeRelasi(adrQuest &Q, adrRelasi prec, adrRelasi &R){
    adrRelasi i = Q->firstRelasi;
    R = prec;

    while (i != nullptr && i->next != prec){
        i = i->next;
    }

    i->next = R->next;
    R->next = nullptr;
}

void deleteRelasi(adrQuest &Q, string nameOrIdPlayer){
    adrRelasi R;
    adrRelasi relasiTarget;

    if (!isEmptyRelasi(Q)){
        relasiTarget = findRelasi(Q, nameOrIdPlayer);

        if (relasiTarget != nullptr){
            if (relasiTarget == Q->firstRelasi){
                deleteFirstRelasi(Q, R);
            } else if (relasiTarget->next != nullptr){
                deleteNodeRelasi(Q, relasiTarget, R);
            } else{
                deleteLastRelasi(Q, R);
            }

            deallocateRelasi(R);
        } else{
            cout<< "Player "<< nameOrIdPlayer<< " tidak ditemukan"<< endl;
        }
    } else{
        cout<< "tidak ada Player yang menjalankan Quest ini"<< endl;
    }
}

void deleteAllRelasi(adrQuest &Q){
    adrRelasi R = Q->firstRelasi;
    adrRelasi temp;

    while (R != nullptr){
        temp = R;
        R = R->next;

        deallocateRelasi(temp);
    }

    Q->firstRelasi = nullptr;
}


//[---------------FIND---------------]
adrRelasi findRelasi(adrQuest Q, string nameOrIdPlayer){
    adrRelasi R = Q->firstRelasi;

    while (R != nullptr){
        if (R->player->info.idPlayer == nameOrIdPlayer || R->player->info.nama == nameOrIdPlayer){
            return R;
        }
        R = R->next;
    }
    return R;
}


//[---------------PRINT to DISPLAY---------------]
void showPlayersFromQuest(adrQuest Q){
    if (!isEmptyRelasi(Q)){
        adrRelasi R = Q->firstRelasi;

        cout<< "Player yang sedang menjalankan Quest "<< Q->info.namaQuest<< " :"<< endl;
        while (R != nullptr){
            cout<< "--------------------------------------------------"<< endl;
            cout<< "Nama       : "<< R->player->info.nama<< endl;
            cout<< "ID         : "<< R->player->info.idPlayer<< endl;
            cout<< "Stats      : "<< "Lv "<< R->player->info.level<< " | "<< R->player->info.playerClass<< " | "<< R->player->info.PlayerRace<< endl;
            cout<< "Wealth     : "<< R->player->info.Wealth<< "g"<< endl;
            R = R->next;
        }
    } else{
        cout<< "tidak ada player yang sedang menjalankan Quest ini!!"<< endl;
    }
    cout<< endl;
}

void showAllQuestWithPlayers(LQuest L){
    if (!isEmptyQuest(L)){
        adrQuest q = L.first;

        while (q != nullptr){
            showQuest(q);
            cout<< "||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||"<< endl;
            cout<< "\/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/"<< endl;
            showPlayersFromQuest(q);
            q = q->next;
        }
    } else{
        cout<< "tidak ada Quest saat ini!!"<< endl;
    }
}

void showQuestFromPlayer(LQuest QL, adrPlayer P){
    if (!isEmptyQuest(QL)){
        adrQuest q = QL.first;

        cout<< "Player ini sedang melakukan quest: "<< endl;
        while (q != nullptr){
            adrRelasi r = findRelasi(q, P->info.nama);

            if (r != nullptr){
                cout<< q->info.namaQuest<< " ,";
            }
            q = q->next;
        }
        cout<< endl;
    }
}

void showAllPlayersWithQuest(LQuest QL, LPlayer PL){
    if (!isEmptyPlayer(PL)){
        adrPlayer p = PL.first;

        while (p != nullptr){
            showChild(p);
            showQuestFromPlayer(QL, p);
            p = p->next;
        }
    }
}


//[---------------COUNT---------------]
int countPlayerInQuest(adrQuest Q){
    int i = 0;
    adrRelasi R = Q->firstRelasi;

    while (R != nullptr){
        i++;
        R = R->next;
    }
    return i;
}

int countPlayerInAllQuest(LQuest Q){
    int total = 0, i = 0;
    adrQuest q = Q.first;

    while (q != nullptr){
        i = countPlayerInQuest(q);
        total += i;
    }
    return total;
}

int countQuestOfOnePlayer(LQuest QL, adrPlayer P){
    adrQuest Q = QL.first;
    int i = 0;

    while (Q != nullptr){
        if (findRelasi(Q, P->info.nama) != nullptr){
            i++;
        }
        Q = Q->next;
    }
    return i;
}
