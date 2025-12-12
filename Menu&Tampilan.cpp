#include "game.h"

void tampilanHome(){
    cout<< "1. Quest"<< endl;
    cout<< "2. Player"<< endl;
    cout<< "3. Exit"<< endl;
    cout<< "Silakan pilih (1/2/3):";
}


//[---------------QUEST---------------]
void tampilanMenuQuest(){
    cout<< "1. Menambahkan QUEST"<< endl;
    cout<< "2. Menghapus QUEST"<< endl;
    cout<< "3. Mencari QUEST"<< endl;
    cout<< "4. Menampilan semua QUEST"<< endl;
    cout<< "5. Back"<< endl;
    cout<< "Silakan pilih (1/2/3/4/5):";
}

void menuQuest(LQuest &L){
    adrQuest Q;
    questInfotype x;
    string nQuestHapus, nQuestFind;
    int n, j;
    bool running = true;

    while (running){
        system("cls");
        tampilanMenuQuest();
        cin>> n;
        cout<< endl;
        switch (n){
        case 1:
            cout<< "Silakan masukan jumlah QUEST yang akan ditambahkan : "<< endl;
            cin>> j;
            for (int i=0; i<j; i++){
                cout<< "Nama Quest : ";
                cin>> x.namaQuest;
                cout<< "Level Minimal : ";
                cin>> x.levelMin;

                Q = allocateQuest(x);
                insertQuest(L, Q);
                cout<< endl;
            }
            break;
        case 2:
            cout<< "Silakan masukan nama QUEST yang ingin dihapus : ";
            cin>> nQuestHapus;
            deleteQuest(L, nQuestHapus);
            break;
        case 3:
            cout<< "Silakan masukan nama QUEST";
            cin>> nQuestFind;
            showOneQuest(L, nQuestFind);
            break;
        case 4:
            showAllQuest(L);
            break;
        default:
            running = false;
            break;
        }
        if (running) {
             system("pause");
        }
    }
}
