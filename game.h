#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
using namespace std;

//Parent (DLL)
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
    adrRelasi relasi;
};

struct LQuest{
    adrQuest first;
    adrQuest last;
};

void createListQuest(LQuest &L);
adrQuest allocateQuest(questInfotype x);
void deallocateQuest(adrQuest &Q);
bool isEmptyQuest(LQuest L);

//kondisi untuk urutan insertQuest berdasarkan dif dan levelMin
bool isLess(adrQuest A, adrQuest B);

//insert
void insertFirstQuest(LQuest &L, adrQuest Q);
void insertLastQuest(LQuest &L, adrQuest Q);
void insertAfterQuest(LQuest &L, adrQuest prec, adrQuest Q);
void insertQuest(LQuest &L, adrQuest Q);

//delete
void deleteFirstQuest(LQuest &L, adrQuest &Q);
void deleteLastQuest(LQuest &L, adrQuest &Q);
void deleteAfterQuest(adrQuest prec, adrQuest &Q);
void deleteQuest(LQuest &L, string namaQuest);

adrQuest findQuest(LQuest L, string namaQuest);

void showAllQuest(LQuest L);


//Child (SLL)
struct player{
    string idPlayer, nama, playerClass;
    int level, power;
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
void insertPlayer(LPlayer &L, adrPlayer P);
void deletePlayer(LPlayer &L, LQuest &QL, adrPlayer P);
adrPlayer findPlayer(LPlayer L, string idPlayer);
void showAllChild(LPlayer L);
int countPlayerWithoutQuest(LQuest QL, LPlayer PL);


//Relasi (SLL per quest)
struct elmRelasi{
    adrPlayer player;
    adrRelasi next;
};

adrRelasi allocateRelasi(adrPlayer P);
bool isEmptyRelasi(adrQuest Q);

void insertRelasi(adrQuest &Q, adrPlayer P);

void deleteRelasi(adrQuest &Q, adrPlayer P);
void deleteAllRelasi(adrQuest &Q);

adrRelasi findRelasi(adrQuest Q, adrPlayer P);

void printRelasi(adrQuest Q);
void printParentFromChild(LQuest QL, adrPlayer P);

void showQuestFromPlayer(LQuest QL, adrPlayer P);
void showPlayersFromQuest(adrQuest Q);
void showAllQuestWithPlayers(LQuest L);

int countQuestOfPlayer(LQuest QL, adrPlayer P);
int countPlayerOnQuest(adrQuest Q);

void editRelasi(adrQuest Q, adrPlayer P_lama, adrPlayer P_baru);

#endif // GAME_H_INCLUDED
