#include "game.h"

//[---------------DLL---------------]
// IS : menerima list quest dalam kondisi apa pun.
// FS : list quest berada pada kondisi kosong dengan first bernilai nullptr.
void createListQuest(LQuest &L){
    L.first = nullptr;
    L.last = nullptr;
}

// IS : menerima data quest berupa nama quest, level minimum, difficulty, dan reward.
// FS : terbentuk satu node quest baru dengan info sesuai data dan pointer relasi bernilai nullptr.
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

// IS : menerima alamat node quest yang mungkin bernilai nullptr atau valid.
// FS : node quest dilepas dari memori dan alamatnya di-set menjadi nullptr.
void deallocateQuest(adrQuest &Q){
    delete Q;
    Q = nullptr;
}

// IS : menerima list quest.
// FS : menghasilkan nilai true jika list quest kosong dan false jika list berisi data.
bool isEmptyQuest(LQuest L){
    return (L.first == nullptr) && (L.last == nullptr);
}


//[---------------FUNGSI PENDUKUNG]---------------]

// IS : menerima dua nilai integer sebagai pembanding.
// FS : menghasilkan true jika nilai pertama lebih kecil dari nilai kedua dan false jika tidak.
bool isLess(adrQuest A, adrQuest B){
    if (A->info.dif < B->info.dif) {
        return true;
    } else if (A->info.dif == B->info.dif) {
        return A->info.levelMin < B->info.levelMin;
    }
    return false;
}

// IS : menerima level minimum quest.
// FS : menghasilkan nilai difficulty berdasarkan rentang level minimum.
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

// IS : menerima nilai difficulty quest.
// FS : menghasilkan nilai reward secara acak sesuai rentang reward untuk difficulty tersebut.
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

// IS : menerima nilai difficulty quest.
// FS : menghasilkan string representasi difficulty untuk kebutuhan tampilan.
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
// IS : menerima list quest dan satu node quest yang sudah dialokasikan.
// FS : node quest dimasukkan ke awal list quest dan first menunjuk node tersebut, last ikut menyesuaikan jika list sebelumnya kosong.
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

// IS : menerima list quest dan satu node quest yang sudah dialokasikan.
// FS : node quest dimasukkan ke akhir list quest dan last menunjuk node tersebut, first ikut menyesuaikan jika list sebelumnya kosong.
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

// IS : menerima list quest, alamat node quest sebelumnya, dan node quest baru.
// FS : node quest baru disisipkan setelah node sebelumnya, dan last ikut menyesuaikan jika sisip dilakukan di akhir list.
void insertAfterQuest(adrQuest prec, adrQuest Q){
    Q->next = prec->next;
    if (prec->next != nullptr){
        prec->next->prev = Q;
    }
    prec->next = Q;
    Q->prev = prec;
}

//Urutan Quest berdasarkan dificulity dan levelMin

// IS : menerima list quest dan node quest baru.
// FS : node quest dimasukkan ke list sesuai aturan pengurutan yang dipakai program, bisa di awal, di akhir, atau setelah node tertentu.
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

// IS : pengguna berada pada kondisi akan menambahkan quest baru.
// FS : data quest dibaca dari input pengguna, dibuat node quest baru, lalu dimasukkan ke list quest sesuai aturan insert.
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
                levelMin = 0;
            }
        }

        Q = allocateQuest(x);
        insertQuest(L, Q);
        cout<< endl;
    }
}

//[---------------DELETE---------------]
// IS : menerima list quest yang tidak kosong.
// FS : node quest pertama dilepas dari list, first berpindah ke node berikutnya, dan last ikut menyesuaikan jika list menjadi kosong.
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

// IS : menerima list quest yang tidak kosong.
// FS : node quest terakhir dilepas dari list, last berpindah ke node sebelumnya, dan first ikut menyesuaikan jika list menjadi kosong.
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

// IS : menerima list quest, alamat node quest sebelumnya, dan variabel penampung.
// FS : node setelah node sebelumnya dilepas dari list dan disimpan ke penampung, last ikut menyesuaikan jika yang dihapus adalah node terakhir.
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

// IS : menerima list quest dan nama quest yang akan dihapus.
// FS : jika quest ditemukan maka node quest tersebut dilepas dari list dengan penanganan kasus awal, tengah, atau akhir, lalu didealokasi dari memori.
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
            tidakAda();
        }
    } else {
        cout << BLUE<< "   List quest kosong!!"<< RESET<< endl;
    }
}


//[---------------FIND---------------]

// IS : menerima list quest dan nama quest yang dicari.
// FS : menghasilkan alamat node quest yang sesuai dengan nama quest atau nullptr jika tidak ditemukan.
adrQuest findQuest(LQuest L, string namaQuest){
    adrQuest q = L.first;

    while (q != nullptr && q->info.namaQuest != namaQuest){
        q = q->next;
    }

    return q;
}


//[---------------COUNT---------------]

// IS : menerima list quest.
// FS : menghasilkan jumlah total node quest di dalam list.
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

// IS : menerima alamat node quest yang valid.
// FS : data quest ditampilkan ke layar sesuai format tampilan yang digunakan program.
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

// IS : menerima list quest dan nama quest yang ingin ditampilkan.
// FS : jika quest ditemukan maka detail quest ditampilkan, jika tidak ditemukan maka menampilkan pesan bahwa quest tidak ada.
void showOneQuest(LQuest L, string namaQuest){
    adrQuest q = findQuest(L, namaQuest);
    if (q != nullptr){
        showQuest(q);
    } else{
        cout<< RED<< "    Maaf, QUEST tidak ditemukan!!"<< RESET<< endl;
        tidakAda();
    }
}

// IS : menerima list quest.
// FS : jika list tidak kosong maka seluruh quest ditampilkan satu per satu beserta jumlah quest, jika kosong maka menampilkan pesan list kosong.
void showAllQuest(LQuest L){
    if (!isEmptyQuest(L)){
        adrQuest q = L.first;

        cout<< "    Jumlah Quest saat ini adalah : "<< countAllQuest(L)<< endl;
        while (q != nullptr){
            showQuest(q);
            q = q->next;
        }
        cout<< "    Total player yang sedang mengikuti quest adalah: "<< countPlayerinAllQuest(L)<< endl;
    } else{
        cout<< BLUE<< "    List quest kosong!!"<< RESET<< endl;
    }

    cout<< endl;
}
