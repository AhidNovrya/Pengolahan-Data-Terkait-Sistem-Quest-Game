#include "game.h"

adrRelasi allocateRelasi(adrPlayer P){
    adrRelasi r = new elmRelasi;

    r->player = p;
    r->next = nullptr;
    return r;
}

bool isEmptyRelasi(adrQuest Q){
    return Q->relasi == nullptr;
}

void insertRelasi(adrQuest &Q, adrPlayer P){
    adrRelasi C, R = allocateRelasi(P);

    if (isEmptyRelasi(Q)){
        Q->relasi = R;
    } else {
        C = Q->relasi;
        while (C->next != nullptr){
            C = C->next;
        }
        C->next = R;
    }
}

//void deleteRelasi(adrQuest &Q, adrPlayer P);

//void deleteAllRelasi(adrQuest Q);
