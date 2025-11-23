#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
using namespace std;

//Parent (DLL)
struct quest{
    string namaQuest;
    int levelMin, dificulity, reward;
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
bool isEmpty(LQuest L);
void insertQuest(LQuest &L, adrQuest Q);
void deleteQuest(LQuest &L, adrQuest Q);
adrQuest findQuest(LQuest L, string namaQuest);
void showAllQuest(Lquest L);
void showPlayersFromQuest(adrQuest Q);
void showAllQuestWithPlayers(LQuest L);
int countPlayerOnQuest(adrQuest Q);


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
void showQuestFromPlayer(LQuest QL, adrPlayer P);
int countQuestOfPlayer(LQuest QL, adrPlayer P);
int countPlayerWithoutQuest(LQuest QL, LPlayer PL);


//Relasi (SLL per quest)
struct elmRelasi{
    adrPlayer player;
    adrRelasi next;
};

adrRelasi allocateRelasi(adrPlayer P);
bool isEmptyRelasi(adrQuest Q);
void insertRelasi(adrQuest Q, adrPlayer P);
void deleteRelasi(adrQuest Q, adrPlayer P);
adrRelasi findRelasi(adrQuest Q, adrPlayer P);
void printRelasi(adrQuest Q);
void printParentFromChild(LQuest QL, adrPlayer P);
void editRelasi(adrQuest Q, adrPlayer P_lama, adrPlayer P_baru);


#endif // GAME_H_INCLUDED
