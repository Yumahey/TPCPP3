
#include <iostream>
#include <fstream>
#include <w32api/bh.h>

using namespace std;

void f(int a, float b, char * x){

}

int main(){

    char carlu[30];
    ifstream fic("D:\\C et C++\\TPCPP3\\cata2.txt");
    //streambuf * oldCountBuf = cin.rdbuf(fic.rdbuf());
    for (int i = 0; i < 10; ++i) {
        fic.getline(carlu, 30, ' ');
        //fic >> carlu;
        //cin >> carlu;
        cout << carlu << endl;
    }

    char SouC;
    int nbSection;
    while(1){
        fic >> SouC;
        char depart[30];
        char arrivee[30];
        char mt[30];
        if(SouC == 'S'){

        } else {
            fic >> nbSection;
            Trajet ** listeTraj = new Trajet*[nbSection];
            for (int i = 0; i < nbSection; ++i) {
                fic >> depart;
                fic >> arrivee;
                fic >> mt;
                listeTraj[i] = new TS(depart, blablabla);

            }
            newTrajet = new TC(listeTraj, bite);
            
        }
        break;
    }

    fic.close();

    return 0;
}
