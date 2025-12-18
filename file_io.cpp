#include "game.h"

void saveData(LQuest LQ, LPlayer LP) {
    ofstream file;

    // 1. SIMPAN PLAYER (players.txt)
    file.open("data/players.txt");
    adrPlayer P = LP.first;
    while (P != nullptr) {
        // Format: ID, Nama, Class, Race, Level, Wealth
        file << P->info.idPlayer << endl;
        file << P->info.nama << endl;
        file << P->info.playerClass << endl;
        file << P->info.playerRace << endl;
        file << P->info.level << endl;
        file << P->info.Wealth << endl;
        P = P->next;
    }
    file.close();

    // 2. SIMPAN QUEST (quests.txt)
    file.open("data/quests.txt");
    adrQuest Q = LQ.first;
    while (Q != nullptr) {
        // Format: NamaQuest, LevelMin, Dif, Reward
        file << Q->info.namaQuest << endl;
        file << Q->info.levelMin << endl;
        file << Q->info.dif << endl;
        file << Q->info.reward << endl;
        Q = Q->next;
    }
    file.close();

    // 3. SIMPAN RELASI (relasi.txt)
    file.open("data/relasi.txt");
    Q = LQ.first;
    while (Q != nullptr) {
        adrRelasi R = Q->firstRelasi;
        while (R != nullptr) {
            file << Q->info.namaQuest << endl;
            file << R->player->info.idPlayer << endl;
            R = R->next;
        }
        Q = Q->next;
    }
    file.close();

    cout << GREEN << "    [SYSTEM] Data berhasil disimpan ke file txt!" << RESET << endl;
}

void loadData(LQuest &LQ, LPlayer &LP) {
    ifstream file;
    string tempString;
    int tempInt;

    // 1. LOAD PLAYER
    file.open("data/players.txt");
    if (file.is_open()) {
        playerInfotype pData;
        while (file >> pData.idPlayer) {
            file.ignore();
            getline(file, pData.nama);
            file >> pData.playerClass;
            file >> pData.playerRace;
            file >> pData.level;
            file >> pData.Wealth;

            adrPlayer P = allocatePlayer(pData);

            P->info.Wealth = pData.Wealth;
            insertPlayer(LP, P);
        }
        file.close();
        cout << GREEN << "    [SYSTEM] Data Player berhasil dimuat." << RESET << endl;
    }

    // 2. LOAD QUEST
    file.open("data/quests.txt");
    if (file.is_open()) {
        questInfotype qData;
        while (file >> tempString) {

            qData.namaQuest = tempString;

            file >> qData.levelMin;
            file >> qData.dif;
            file >> qData.reward;

            adrQuest Q = allocateQuest(qData);

            Q->info.dif = qData.dif;
            Q->info.reward = qData.reward;
            insertLastQuest(LQ, Q);
        }
        file.close();
        cout << GREEN << "    [SYSTEM] Data Quest berhasil dimuat." << RESET << endl;
    }

    // 3. LOAD RELASI
    file.open("data/relasi.txt");
    if (file.is_open()) {
        string qName, pID;
        while (file >> qName) {
            file >> pID;

            adrQuest Q = findQuest(LQ, qName);
            adrPlayer P = findPlayer(LP, pID);

            if (Q != nullptr && P != nullptr) {
                insertRelasi(Q, P);
            }
        }
        file.close();
        cout << GREEN << "    [SYSTEM] Data Relasi berhasil dimuat." << RESET << endl;
    }
}
