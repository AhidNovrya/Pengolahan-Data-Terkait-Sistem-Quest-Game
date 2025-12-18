#include "game.h"

int main(){
    srand(time(0));

    LQuest Q;
    LPlayer P;
    int n;
    bool running = true;

    createListQuest(Q);
    createListPlayer(P);

    loadData(Q, P);

    while (running){
        system("cls");
        judul();
        tampilanHome();
        cin>> n;
        switch (n){
        case 0:
            saveData(Q, P);
            keluarGame();
            running = false;
            break;
        case 1:
            menuQuest(Q, P);
            break;
        case 2:
            menuPlayer(Q, P);
            break;
        default:
            cout<< RED<< "    Mohon pilih menu yang tertera!!"<< RESET<< endl;
        }
        if (running) {
            system("pause");
        }
    }
}
