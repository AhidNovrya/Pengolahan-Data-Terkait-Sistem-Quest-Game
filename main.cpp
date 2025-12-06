#include "game.h"

int main()
{
    adrPlayer P;
    LPlayer L ;
    playerInfotype x;

    for (int i = 0; i<1 ; i++){
        createListPlayer(L);
        cin >> x.idPlayer;
        cin >> x.level;
        cin >> x.nama;
        cin >> x.playerClass;
        cin >> x.PlayerRace;
        cin >> x.Wealth;
        P = allocatePlayer(x);
        insertPlayer(L, P);
    }
    showAllChild(L);

}
