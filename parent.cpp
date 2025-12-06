#include "game.h"

void createListQuest(LQuest &L){
    L.first = nullptr;
    L.last = nullptr;
}

adrQuest allocateQuest(questInfotype x){
    adrQuest p = new elmQuest;

    p->info = x;
    p->next = nullptr;
    p->prev = nullptr;
    p->relasi = nullptr;

    return p;
}

void deallocateQuest(adrQuest &Q){
    delete Q;
    Q = nullptr;
}


bool isEmptyQuest(LQuest L){
    return (L.first == nullptr) && (L.last == nullptr);
}


bool isLess(adrQuest A, adrQuest B){
    if (A->info.dif < B->info.dif) {
        return true;
    } else if (A->info.dif == B->info.dif) {
        return A->info.levelMin < B->info.levelMin;
    }
    return false;
}


void insertFirstQuest(LQuest &L, adrQuest Q){
    if (isEmptyQuest(L)){
        L.first = Q;
        L.last = Q;
    } else {
        Q->next = L.first;
        L.first->prev = Q;
        L.first = Q;
    }
}

void insertLastQuest(LQuest &L, adrQuest Q){
    if (isEmptyQuest(L)){
        L.first = Q;
        L.last = Q;
    } else {
        L.last->next = Q;
        Q->prev = L.last;
        L.last = Q;
    }
}

void insertAfterQuest(adrQuest prec, adrQuest Q){
    Q->next = prec->next;
    if (prec->next != NULL){
        prec->next->prev = Q;
    }
    prec->next = Q;
    Q->prev = prec;
}

//Urutan Quest berdasarkan dificulity dan levelMin
void insertQuest(LQuest &L, adrQuest Q){
    if (isEmptyQuest(L)) {
        insertFirstQuest(L, Q);

    } else if (isLess(Q, L.first)) {
        insertFirstQuest(L, Q);

    } else if (!isLess(Q, L.last)) {
        insertLastQuest(L, Q);

    } else {
        adrQuest P = L.first;
        while (P != NULL && isLess(P, Q)) {
            P = P->next;
        }
        insertAfterQuest(P->prev, Q);
    }
}


void deleteFirstQuest(LQuest &L, adrQuest &Q){
    Q = L.first;
    if (L.first == L.last){
        L.first = nullptr;
        L.last = nullptr;
    } else {
        L.first = Q->next;
        L.first->prev = nullptr;
        Q->next = nullptr;
    }
}

void deleteLastQuest(LQuest &L, adrQuest &Q){
    Q = L.last;
    if (L.first == L.last){
        L.first = nullptr;
        L.last = nullptr;
    } else {
        L.last = Q->prev;
        L.last->next = nullptr;
        Q->prev = nullptr;
    }
}

void deleteAfterQuest(LQuest &L, adrQuest prec, adrQuest &Q){
    Q = prec->next;
    prec->next = Q->next;
    if (Q->next != nullptr){
        Q->next->prev = prec;
    } else {
        L.last = prec;
    }
    Q->next = nullptr;
    Q->prev = nullptr;
}

void deleteQuest(LQuest &L, string namaQuest){
    adrQuest P = nullptr;
    adrQuest Q = nullptr;

    if (!isEmptyQuest(L)) {
        P = findQuest(L, namaQuest);

        if (P != nullptr) {
            deleteAllRelasi(P);

            if (P == L.first){
                deleteFirstQuest(L, Q);
            } else if (P == L.last){
                deleteLastQuest(L, Q);
            } else {
                deleteAfterQuest(L, P->prev, Q);
            }

            deallocateQuest(Q);
        } else {
            cout << "Quest tidak ditemukan" << endl;
        }
    } else {
        cout << "List quest kosong" << endl;
    }
}

adrQuest findQuest(LQuest L, string namaQuest){
    adrQuest p = L.first;

    while (p != nullptr && p->info.namaQuest != namaQuest){
        p = p->next;
    }

    return p;
}

void showAllQuest(Lquest L){
    adrQuest p = L.first;
    while (p != nullptr){
        cout<< "Nama Quest          : "<< p->info.namaQuest<< endl;
        cout<< "Tingkat Kesulitan   : "<< p->info.dif<< endl;
        cout<< "Level Minimum       : "<< p->info.levelMin<< endl;
        cout<< "Hadiah              : "<< p->info.reward<< endl;
    }
}
