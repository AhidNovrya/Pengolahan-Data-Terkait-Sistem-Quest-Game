#include "game.h"

void createListPlayer(LPlayer &L){
    L.first = nullptr;
    L.last = nullptr;
}
adrPlayer allocatePlayer(playerInfotype x){
    adrPlayer p = new elmPlayer;

    p->info = x;
    p->next = nullptr;
    p->prev = nullptr;
    p->relasi = nullptr;

    return p;
}
bool isEmptyPlayer(LPlayer L){
    return (L.first == nullptr) && (L.last == nullptr);
}

void insertPlayer(LPlayer &L, adrPlayer P){
    if (isEmptyPlayer(L)){
        L.first = P;
        L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}
void deletePlayer(LPlayer &L, LQuest &QL, adrPlayer P){

}
adrPlayer findPlayer(LPlayer L, string idPlayer){
    adrPlayer p = L.first;

    while (p != nullptr && p->info.idPlayer != idPlayer){
        p = p->next;
    }

    return p;
}
void showAllChild(LPlayer L);
void showQuestFromPlayer(LQuest QL, adrPlayer P);
int countQuestOfPlayer(LQuest QL, adrPlayer P);
int countPlayerWithoutQuest(LQuest QL, LPlayer PL);
