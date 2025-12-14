#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// WARNA TEXT (ANSI CODES)
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Merah (Untuk Error/Hapus)
#define GREEN   "\033[32m"      // Hijau (Untuk Sukses/Tambah)
#define YELLOW  "\033[33m"      // Kuning (Untuk Gold/Highlight)
#define BLUE    "\033[34m"      // Biru (Untuk Judul/Info)
#define MAGENTA "\033[35m"      // Ungu (Untuk Item Langka/Epik)
#define CYAN    "\033[36m"      // Biru Muda (Untuk Dekorasi)

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
int generateWealth(int level);

//INSERT
void insertFirstQuest(LQuest &L, adrQuest Q);
void insertLastQuest(LQuest &L, adrQuest Q);
void insertAfterQuest(adrQuest prec, adrQuest Q);
void insertQuest(LQuest &L, adrQuest Q);
void inputQuest(LQuest &L);

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
    string idPlayer, nama, playerClass, playerRace;
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
void deallocatePlayer(adrPlayer &P);
bool isEmptyPlayer(LPlayer L);

//INSERT
void insertPlayer(LPlayer &L, adrPlayer P);

//DELETE
void deletePlayer(LPlayer &L, LQuest &QL, string idPlayer);

//FIND
adrPlayer findPlayer(LPlayer L, string idPlayer);

//PRINT to Display
void showPlayer(adrPlayer p);
void showAllChild(LPlayer L);
void showOnePlayer(LPlayer L, string nama);

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
void deleteAfterRelasi(adrQuest &Q, adrRelasi prec, adrRelasi &R);
void deleteRelasi(adrQuest &Q, string nameOrIdPlayer);
void deleteAllRelasi(adrQuest &Q);

//FIND
adrRelasi findRelasi(adrQuest Q, string nameOrIdPlayer);

//PRINT to Display
void showPlayersFromQuest(adrQuest Q);
void showAllQuestWithPlayers(LQuest L);
void showQuestFromPlayer(LQuest QL, adrPlayer P);
void showAllPlayersWithQuest();

//COUNT
int countQuestOfPlayer(LQuest QL, adrPlayer P);
int countPlayerOnQuest(adrQuest Q);

//EDIT
void editRelasi(adrQuest Q, adrPlayer P_lama, adrPlayer P_baru);


//[---------------TAMPILAN & MENU---------------]
void judul();
void garis();
void garisKartu();
void tampilanHome();
void tampilanMenuQuest();
void tampilanMenuPlayer();
void menuQuest(LQuest &L);
void menuPlayer(LQuest &QL, LPlayer &L);
void keluarGame();
void tidakAda();

#endif // GAME_H_INCLUDED
