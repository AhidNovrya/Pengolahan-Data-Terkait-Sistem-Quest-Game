#include "game.h"

int main(){
    srand(time(0));

    LQuest L;
    LPlayer P;
    int n;
    bool running = true;

    createListQuest(L);
    createListPlayer(P);

    while (running){
        system("cls");
        tampilanHome();
        cin>> n;
        switch (n){
        case 1:
            menuQuest(L);
            break;
        case 2:
            break;
        default:
            running = false;
        }
        if (running) {
            system("pause");
        }
    }
}
