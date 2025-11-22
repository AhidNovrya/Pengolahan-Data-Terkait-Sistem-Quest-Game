#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
using namespace std;

//DLL
struct quest{
    string nama;
    int dificulity, reward;
};

typedef quest questInfotype;
typedef struct elmQuest *adrQuest;

struct elmQuest{
    questInfotype info;
    adrQuest next;
    adrQuest prev;
};

struct LQuest{
    adrQuest first;
    adrQuest last;
};


//SLL
struct player{
    string nama, class;
    int level;
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


//


#endif // GAME_H_INCLUDED
