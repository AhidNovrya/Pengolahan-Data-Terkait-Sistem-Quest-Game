#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//[---------------Parent (DLL)---------------]
struct quest{
    string namaQuest;
    int levelMin, dif, reward;
};

typedef quest questInfotype;
typedef struct elmQuest *adrQuest;
typedef struct elmRelasi *adrRelasi;

struct elmQuest{
    questInfotype info;
    adrQuest next;
    adrQuest prev;
    adrRelasi firstRelasi;
};

struct LQuest{
    adrQuest first;
    adrQuest last;
};

void createListQuest(LQuest &L);
adrQuest allocateQuest(questInfotype x);
void deallocateQuest(adrQuest &Q);
bool isEmptyQuest(LQuest L);

//FUNGSI PENDUKUNG
//kondisi untuk urutan insertQuest berdasarkan dif dan levelMin
bool isLess(adrQuest A, adrQuest B);
int generateDif(int levelMin);
int generateReward(int difficulty);

//INSERT
void insertFirstQuest(LQuest &L, adrQuest Q);
void insertLastQuest(LQuest &L, adrQuest Q);
void insertAfterQuest(adrQuest prec, adrQuest Q);
void insertQuest(LQuest &L, adrQuest Q);

//DELETE
void deleteFirstQuest(LQuest &L, adrQuest &Q);
void deleteLastQuest(LQuest &L, adrQuest &Q);
void deleteAfterQuest(LQuest &L, adrQuest prec, adrQuest &Q);
void deleteQuest(LQuest &L, string namaQuest);

//FIND
adrQuest findQuest(LQuest L, string namaQuest);

//COUNT
int countAllQuest(LQuest L);

//PRINT to Display
void showQuest(adrQuest q);
void showOneQuest(LQuest L, string namaQuest);
void showAllQuest(LQuest L);


//[---------------Child (SLL)---------------]
struct player{
    string idPlayer, nama, playerClass, PlayerRace;
    int level, Wealth;
};

typedef player playerInfotype;
typedef struct elmPlayer *adrPlayer;

struct elmPlayer{
    playerInfotype info;
    adrPlayer next;
};

struct LPlayer{
    adrPlayer first;
};

void createListPlayer(LPlayer &L);
adrPlayer allocatePlayer(playerInfotype x);
bool isEmptyPlayer(LPlayer L);

//INSERT
void insertPlayer(LPlayer &L, adrPlayer P);

//DELETE
void deletePlayer(LPlayer &L, LQuest &QL, adrPlayer P);

//FIND
adrPlayer findPlayer(LPlayer L, string idPlayer);

//PRINT to Display
void showChild(adrPlayer p);
void showAllChild(LPlayer L);

//COUNT
int countPlayerWithoutQuest(LQuest QL, LPlayer PL);


//[---------------Relasi (SLL per quest)---------------]
struct elmRelasi{
    adrPlayer player;
    adrRelasi next;
};

adrRelasi allocateRelasi(adrPlayer P);
void deallocateRelasi(adrRelasi R);
bool isEmptyRelasi(adrQuest Q);

//INSERT
void insertRelasi(adrQuest &Q, adrPlayer P);

//DELETE
void deleteFirstRelasi(adrQuest &Q, adrRelasi &R);
void deleteLastRelasi(adrQuest &Q, adrRelasi &R);
void deleteNodeRelasi(adrQuest &Q, adrRelasi prec, adrRelasi &R);
void deleteRelasi(adrQuest &Q, string nameOrIdPlayer);
void deleteAllRelasi(adrQuest &Q);

//FIND
adrRelasi findRelasi(adrQuest Q, string nameOrIdPlayer);

//PRINT to Display
void showPlayersFromQuest(adrQuest Q);
void showAllQuestWithPlayers(LQuest L);
void showQuestFromPlayer(LQuest QL, adrPlayer P);
void showAllPlayersWithQuest(LQuest QL, LPlayer PL);

//COUNT
int countPlayerInQuest(adrQuest Q);
int countPlayerInAllQuest(LQuest Q);
int countQuestOfOnePlayer(LQuest QL, adrPlayer P);

//EDIT
void editRelasi(adrQuest Q, adrPlayer P_lama, adrPlayer P_baru);


//[---------------TAMPILAN & MENU---------------]
void tampilanHome();
void tampilanMenuQuest();
void menuQuest(LQuest &L);

#endif // GAME_H_INCLUDED
