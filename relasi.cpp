#include "game.h"

// IS : menerima alamat node player yang valid.
// FS : mengalokasikan satu node relasi baru, mengisi player menunjuk ke node player tersebut, next bernilai nullptr, lalu mengembalikan alamat relasi.
adrRelasi allocateRelasi(adrPlayer P){
    adrRelasi r = new elmRelasi;

    r->player = P;
    r->next = nullptr;
    return r;
}

// IS : menerima alamat node relasi yang mungkin bernilai nullptr atau valid.
// FS : jika alamat valid maka node relasi dilepas dari memori dan alamatnya di-set menjadi nullptr.
void deallocateRelasi(adrRelasi R){
    delete R;
    R = nullptr;
}

// IS : menerima alamat node quest.
// FS : menghasilkan nilai true jika daftar relasi pada quest kosong dan false jika berisi data relasi.
bool isEmptyRelasi(adrQuest Q){
    return Q->firstRelasi == nullptr;
}


//[---------------INSERT---------------]

// IS : menerima alamat node quest dan alamat node player.
// FS : membentuk satu relasi baru untuk player tersebut dan memasukkannya ke akhir daftar relasi milik quest.
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
// IS : menerima alamat node quest dan sebuah variabel penampung alamat relasi.
// FS : relasi pertama pada quest dilepas dari daftar relasi, disimpan ke variabel penampung, dan relasi tersebut terputus dari daftar.
void deleteFirstRelasi(adrQuest &Q, adrRelasi &R){
    R = Q->firstRelasi;

    Q->firstRelasi = R->next;
    R->next = nullptr;
}

// IS : menerima alamat node quest dan sebuah variabel penampung alamat relasi.
// FS : relasi terakhir pada quest dilepas dari daftar relasi, disimpan ke variabel penampung, dan relasi tersebut terputus dari daftar.
void deleteLastRelasi(adrQuest &Q, adrRelasi &R){
    adrRelasi i = Q->firstRelasi;

    while (i->next->next != nullptr){
        i = i->next;
    }

    R = i->next;
    i->next = nullptr;
}

// IS : menerima alamat node quest, alamat relasi target yang akan dihapus, dan sebuah variabel penampung alamat relasi.
// FS : relasi target dilepas dari daftar relasi, node sebelumnya dihubungkan ke node setelah target, lalu target disimpan ke variabel penampung dan terputus dari daftar.
void deleteAfterRelasi(adrQuest &Q, adrRelasi prec, adrRelasi &R){
    adrRelasi i = Q->firstRelasi;
    R = prec;

    while (i != nullptr && i->next != prec){
        i = i->next;
    }

    i->next = R->next;
    R->next = nullptr;
}

// IS : menerima alamat node quest dan sebuah identitas player berupa id atau nama.
// FS : jika relasi player ditemukan maka relasi tersebut dilepas dari daftar relasi quest lalu didealokasi dari memori, jika tidak ditemukan maka menampilkan pesan.
void deleteRelasi(adrQuest &Q, string nameOrIdPlayer){
    adrRelasi R;
    adrRelasi relasiTarget;

    if (!isEmptyRelasi(Q)){
        relasiTarget = findRelasi(Q, nameOrIdPlayer);

        if (relasiTarget != nullptr){
            if (relasiTarget == Q->firstRelasi){
                deleteFirstRelasi(Q, R);
            } else if (relasiTarget->next != nullptr){
                adrRelasi prec = Q->firstRelasi;
                while(prec->next != relasiTarget){
                    prec = prec->next;
                }
                deleteAfterRelasi(Q, prec, R);
            } else{
                deleteLastRelasi(Q, R);
            }

            deallocateRelasi(R);
        } else{
            cout<< "    Player "<< nameOrIdPlayer<< " tidak ditemukan"<< endl;
        }
    } else{
        cout<< "    tidak ada Player yang menjalankan Quest ini"<< endl;

    }
}

// IS : menerima alamat node quest.
// FS : seluruh relasi pada quest dihapus dan didealokasi sehingga daftar relasi menjadi kosong.
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
// IS : menerima alamat node quest dan sebuah identitas player berupa id atau nama.
// FS : menghasilkan alamat relasi yang playernya cocok dengan identitas tersebut, atau menghasilkan nullptr jika tidak ada yang cocok.
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
// IS : menerima alamat node quest.
// FS : menampilkan seluruh player yang sedang menjalankan quest tersebut, atau menampilkan pesan jika tidak ada relasi.
void showPlayersFromQuest(adrQuest Q){
    if (!isEmptyRelasi(Q)){
        adrRelasi R = Q->firstRelasi;

        cout<< "    Player yang sedang menjalankan Quest "<< Q->info.namaQuest<< " :"<< endl;
        while (R != nullptr){
            showPlayer(R->player);
            R = R->next;
        }
    } else{
        cout<< "    tidak ada player yang sedang menjalankan Quest ini!!"<< endl;
    }
    cout<< endl;
}

// IS : menerima list quest.
// FS : menampilkan seluruh quest dan daftar player yang menjalankan masing masing quest, atau menampilkan pesan jika tidak ada quest.
void showAllQuestWithPlayers(LQuest L){
    if (!isEmptyQuest(L)){
        adrQuest q = L.first;

        while (q != nullptr){
            showQuest(q);
            cout<< R"(||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
                      \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/)";
            showPlayersFromQuest(q);
        }
    } else{
        cout<< "    tidak ada Quest saat ini!!"<< endl;
    }
}

// IS : menerima list quest dan alamat node player.
// FS : menampilkan daftar quest yang sedang dijalankan oleh player tersebut berdasarkan relasi yang ditemukan pada tiap quest.
void showQuestFromPlayer(LQuest QL, adrPlayer P){
    if (!isEmptyQuest(QL)){
        adrQuest q = QL.first;

        cout<< "    Player ini sedang melakukan quest: ";
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

// IS : menerima list quest dan list player.
// FS : menampilkan setiap player lalu menampilkan quest yang sedang dijalankan oleh player tersebut.
void showAllPlayersWithQuest(LQuest QL, LPlayer PL){
    if (!isEmptyPlayer(PL)){
        adrPlayer p = PL.first;

        while (p != nullptr){
            showPlayer(p);
            showQuestFromPlayer(QL, p);
            p = p->next;
        }
    }
}

//[---------------COUNT---------------]

// IS : menerima alamat node quest.
// FS : menghasilkan jumlah relasi player yang ada pada quest tersebut.
int countPlayerInQuest(adrQuest Q){
    int i = 0;
    adrRelasi R = Q->firstRelasi;

    while (R != nullptr){
        i++;
        R = R->next;
    }
    return i;
}

// IS : menerima list quest.
// FS : menghasilkan total jumlah relasi player dari seluruh quest yang ada pada list quest.
int countPlayerInAllQuest(LQuest Q){
    int total = 0, i = 0;
    adrQuest q = Q.first;

    while (q != nullptr){
        i = countPlayerInQuest(q);
        total += i;
        q = q->next;
    }
    return total;
}

// IS : menerima list quest dan alamat node player.
// FS : menghasilkan jumlah quest yang diikuti oleh player tersebut berdasarkan relasi yang ditemukan.
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


//[---------------EDIT---------------]

// IS : menerima alamat node quest, alamat player lama, dan alamat player baru.
// FS : jika player lama ada pada relasi quest dan player baru belum ada pada quest tersebut maka relasi player lama diganti menjadi player baru, jika tidak memenuhi syarat maka menampilkan pesan gagal.
void editRelasi(adrQuest Q, adrPlayer P_lama, adrPlayer P_baru) {
    if (P_lama == nullptr || P_baru == nullptr) {
        cout<< RED<< "    Error: Data player tidak valid."<< RESET<< endl;
    } else{
        adrRelasi R = findRelasi(Q, P_lama->info.idPlayer);

        if (R != nullptr) {
            // Cek apakah P_baru SUDAH ADA di quest ini?
            if (findRelasi(Q, P_baru->info.idPlayer) == nullptr) {
                R->player = P_baru; // Ganti pointer playernya
                cout<< GREEN<< "    Player "<< P_baru->info.nama<< " Berhasil menggantikan player "<< P_lama->info.nama<< RESET<< endl;
            } else {
                cout<< RED<< "    Gagal: Player pengganti sudah ada di Quest ini!"<< RESET<< endl;
            }
        } else {
            cout<< RED<< "    Gagal: Player lama tidak ditemukan di Quest ini!"<< RESET<< endl;
        }
    }
}
