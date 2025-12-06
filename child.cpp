#include "game.h"

void createListPlayer(LPlayer &L){
    L.first = nullptr;
}
adrPlayer allocatePlayer(playerInfotype x){
    adrPlayer p = new elmPlayer;

    p->info = x;
    p->next = nullptr;
    return p;
}
bool isEmptyPlayer(LPlayer L){
    return (L.first == nullptr);
}

void insertPlayer(LPlayer &L, adrPlayer P){
        P->next = L.first;
        L.first = P;
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
void showAllChild(LPlayer L){
    adrPlayer P;
    P = L.first;
    while (P != nullptr){
        cout << "Nama       : "<< P->info.nama << endl;
        cout << "ID         : "<< P->info.idPlayer << endl;
        cout << "Stats      : "<< "Lv " << P->info.level << " | " << P->info.playerClass << " | " << P->info.PlayerRace << endl;
        cout << "Wealth     : "<< P->info.Wealth << "g" << endl;
        P = P->next;
    }
}
void showQuestFromPlayer(LQuest QL, adrPlayer P);
int countQuestOfPlayer(LQuest QL, adrPlayer P){

}
int countPlayerWithoutQuest(LQuest QL, LPlayer PL);
