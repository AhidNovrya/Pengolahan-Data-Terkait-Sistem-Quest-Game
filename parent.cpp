#include "game.h"

//[---------------DLL---------------]
void createListQuest(LQuest &L){
    L.first = nullptr;
    L.last = nullptr;
}

adrQuest allocateQuest(questInfotype x){
    adrQuest q = new elmQuest;

    x.dif = generateDif(x.levelMin);
    x.reward = generateReward(x.dif);

    q->info = x;
    q->next = nullptr;
    q->prev = nullptr;
    q->firstRelasi = nullptr;

    return q;
}

void deallocateQuest(adrQuest &Q){
    delete Q;
    Q = nullptr;
}


bool isEmptyQuest(LQuest L){
    return (L.first == nullptr) && (L.last == nullptr);
}


//[---------------FUNGSI PENDUKUNG]---------------]
bool isLess(adrQuest A, adrQuest B){
    if (A->info.dif < B->info.dif) {
        return true;
    } else if (A->info.dif == B->info.dif) {
        return A->info.levelMin < B->info.levelMin;
    }
    return false;
}

int generateDif(int levelMin){
    if (levelMin < 10){
        return 1;
    } else if (levelMin <= 25){
        return 2;
    } else if (levelMin <= 50){
        return 3;
    } else if (levelMin <= 80){
        return 4;
    } else{
        return 5;
    }
}

int generateReward(int difficulty){
    int minGold, maxGold;

    switch (difficulty) {
    case 1: // Baby
        minGold = 1;
        maxGold = 5;
        break;
    case 2: // Easy
        minGold = 5;
        maxGold = 13;
        break;
    case 3: // Normal
        minGold = 14;
        maxGold = 30;
        break;
    case 4: // Hard
        minGold = 30;
        maxGold = 50;
        break;
    default: // Extreme
        minGold = 50;
        maxGold = 75;
        break;
    }

    // Rumus Random Range
    int reward = minGold + (rand() % (maxGold - minGold + 1));

    return reward;
}

string printDif(int dif){
    switch (dif){
    case 1:
        return "Baby";
    case 2:
        return "Easy";
    case 3:
        return "Normal";
    case 4:
        return "Hard";
    default:
        return "Extreme";
    }
}

//[---------------INSERT---------------]
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
    if (prec->next != nullptr){
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

void inputQuest(LQuest &L){
    adrQuest Q;
    questInfotype x;
    int j, levelMin;

    cout<< "    Silakan masukan jumlah QUEST yang akan ditambahkan : ";
    cin>> j;
    for (int i=0; i<j; i++){
        cout<< "    Nama Quest : ";
        cin>> x.namaQuest;
        levelMin = 0;
        while (levelMin < 1 || levelMin > 100){
            cout<< "    Level Minimal (1-100): ";
            cin>> levelMin;
            if (levelMin >= 1 && levelMin <= 100){
                x.levelMin = levelMin;
            } else{
                cout<< RED<< "    Maaf, input tidak valid. harap masukan nilai yang sesuai!!"<< RESET<< endl;
            }
        }

        Q = allocateQuest(x);
        insertQuest(L, Q);
        cout<< endl;
    }
}

//[---------------DELETE---------------]
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
            cout << RED<< "   Maaf, Quest tidak ditemukan!!"<< RESET<< endl;
        }
    } else {
        cout << BLUE<< "   List quest kosong!!"<< RESET<< endl;
    }
}


//[---------------FIND---------------]
adrQuest findQuest(LQuest L, string namaQuest){
    adrQuest q = L.first;

    while (q != nullptr && q->info.namaQuest != namaQuest){
        q = q->next;
    }

    return q;
}


//[---------------COUNT---------------]
int countAllQuest(LQuest L){
    adrQuest q = L.first;
    int n = 0;

    while (q != nullptr){
        n += 1;
        q = q->next;
    }
    return n;
}


//[---------------PRINT to DISPLAY---------------]
void showQuest(adrQuest q){
    garisKartu();
    cout<< R"(
    ||  Nama Quest        : )"<< left<< setw(20)<< q->info.namaQuest<< R"(||
    ||  Tingkat Kesulitan : )"<< left<< setw(20)<< printDif(q->info.dif)<< R"(||
    ||  Level Minimum     : )"<< left<< setw(20)<< q->info.levelMin<< R"(||
    ||  Hadiah            : )"<< left<< setw(20)<< q->info.reward<< R"(||
     \__________________________________________/
)";
}

void showOneQuest(LQuest L, string namaQuest){
    adrQuest q = findQuest(L, namaQuest);
    if (q != nullptr){
        showQuest(q);
    } else{
        cout<< RED<< "    Maaf, QUEST tidak ditemukan!!"<< RESET<< endl;
    }
}

void showAllQuest(LQuest L){
    if (!isEmptyQuest(L)){
        adrQuest q = L.first;

        cout<< "    Jumlah Quest saat ini adalah : "<< countAllQuest(L)<< endl;
        while (q != nullptr){
            showQuest(q);
            q = q->next;
        }
    } else{
        cout<< BLUE<< "    List quest kosong!!"<< RESET<< endl;
    }

    cout<< endl;
}
