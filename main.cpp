#include <iostream>
#include <fstream>
#include <cstring>

#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Catalogue.h"


using namespace std;

// Mode d'emploi : Permet la selection des criteres pour le chargement ou la sauvegarde de fichiers, via le terminal
// mode : 'L' ou 'S' selon qu'on souhaite Lire ou Sauvegarder
// les autres parametres sont les variables dans lesquelles on mettra les valeurs des criteres
//
// Contrat : mode doit valoir 'L' ou 'S', nomFile doit pointer vers un tableau suffisament grand pour stocker le nom
// du fichier (on prend 50), de meme pour villeDepart et villeArrivee (on prend 30)
int selectionFichier(char mode, char * nomFile, char & typeTraj, char * villeDepart, char * villeArrivee, int & indiceD, int & indiceF)
{
    cout << "Nom du fichier a charger/sauvegarder :" << endl;
    cin.getline(nomFile, 50, '\n');
    ifstream fichier(nomFile);
    char carlu;
    int nbLignes = 1;
    char reponse[30];

    // si on est en mode lecture, on compte le nombre de lignes du fichier et on affiche
    if(mode == 'L')
    {
        char fichierVide = 1;
        while ((carlu = fichier.get()) != EOF)
        {
            fichierVide = 0;
            if (carlu == '\n')
            {
                carlu = fichier.get();
                if((carlu == 'S') || (carlu == 'C'))
                {
                    nbLignes++;
                }
            }
        }
        if(fichierVide == 1)
        {
            cout << "Fichier vide" << endl;
            return 1; // return de code d'erreur
        }
        cout << nbLignes << " trajet" << ((nbLignes > 1) ? "s" : "") << " trouve" << ((nbLignes > 1) ? "s" : "")
             << endl;
    }

    // on demande trajet simple/compose/les deux
    cout << "Charger les trajets simples (taper S), les trajets composes (taper C), ou les deux (appuyer directement sur touche Entrée) ?" << endl;
    cin.getline(reponse,30,'\n');
    if(strcmp(reponse,"S")==0 || strcmp(reponse,"s")==0)
    {
        typeTraj='S';
    }
    else if(strcmp(reponse,"C")==0 || strcmp(reponse,"c")==0)
    {
        typeTraj='C';
    }
    else
    {
        typeTraj=' ';
    }

    // on demande la ville de depart
    cout << "Charger les trajets partant de quelle ville ? (Si toutes, appuyer directement sur touche Entrée)" << endl;
    cin.getline(villeDepart, 30, '\n');
    if(strcmp(villeDepart, "") == 0)
    {
        strcpy(villeDepart, "");
    }

    // on demande la ville d'arrivee
    cout << "Charger les trajets arrivant a quelle ville ? (Si toutes, appuyer directement sur touche Entrée)" << endl;
    cin.getline(villeArrivee, 30, '\n');
    if(strcmp(villeArrivee, "") == 0)
    {
        strcpy(villeArrivee, "");
    }

    // on demande l'indice de debut
    cout << "Charger les trajets a partir de quel indice inclus ? (Si a partir du debut,appuyer directement sur touche Entrée)" << endl;
    cin.getline(reponse,30,'\n');
    if(strcmp(reponse,"")==0)
    {
        indiceD=-1;
    }
    else
    {
        indiceD=atoi(reponse);
    }

    // on demande l'indice de fin
    cout << "Charger les trajets jusqu'a quel indice inclus ? (Si jusqu'a la fin, appuyer directement sur touche Entrée)" << endl;
    cin.getline(reponse,30,'\n');
    if(strcmp(reponse,"")==0)
    {
        indiceF=-1;
    }
    else
    {
        indiceF=atoi(reponse);
    }

    // le retour ne sert qu'a savoir si l'operation s'est bien passee,
    // les valeurs sont stockees dans les variables passees en parametre par reference/pointeur
    return 0;
}

int main()
{
    Catalogue catalogue;
    int choixMenu=0; // stocke le choix de l'utilisateur
    int nbTrajetRentre = 0; // permet de connaître le nombre de trajets simples saisis en une seule fois
    char villeDepart[100]; // stocke la ville de départ rentrée par l'utilisateur
    char villeArrivee[100]; // stocke la ville d'arrivée rentrée par l'utilisateur
    char moyenTransport[100]; // stocke le moyen de transport rentré par l'utilisateur
    char confirmationSuiteTrajet[50]; // permet d'enchaîner plusieurs trajets simples dans le cas de la saisie d'un trajet composé
    Trajet** trajetRentres=new Trajet*[1]; // stocke les trajets saisis (par défaut le tableau est de taille 1)

    //Variables pour les fichiers d'entrés et sorties
    ifstream testIn;//fichier de lecture
    ofstream testOut;//fichier de sauvegarde
    char nomFile[50];
    char typeTraj;
    char ville1[30];//ville depart selection
    char ville2[30];// ville d'arrivee selection
    int indiceD;
    int indiceF;

    while(1)
    {
        choixMenu=0;
        cout<<"Choix disponibles : "<<endl;
        cout<<"\t(1) Afficher le catalogue"<<endl;
        cout<<"\t(2) Ajouter un trajet au catalogue"<<endl;
        cout<<"\t(3) Rechercher un parcours (Recherche simple)"<<endl;
        cout<<"\t(4) Rechercher un parcours (Recherche complexe)"<<endl;
        cout<< "\t(5) Lecture selective d'un fichier" << endl;
        cout<< "\t(6) Sauvegarde selective dans un fichier" << endl;
        cout<<"\t(7) Quitter le programme"<<endl;

        // entree de l'option choisie et gestion des mauvaises saisies
        choixMenu = 0;
        cin >> choixMenu;
        while((choixMenu <= 0) || (choixMenu >= 8))
        {
            while(cin.fail())
            {
                cout << "Veuillez entrer un nombre valide, strictement positif et strictement inférieur à 8" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> choixMenu;
            }
            if((choixMenu <= 0) || (choixMenu >= 8))
            {
                cout << "Veuillez entrer un nombre valide, strictement positif et strictement inférieur à 8" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                cin >> choixMenu;
            }
        }
        cin.clear();
        cin.ignore(10000, '\n');

        // on entre dans le menu de la bonne option
        switch(choixMenu)
        {
            case 1: // affichage du catalogue
                catalogue.AfficherCatalogue();
                cout<<endl;
                break;

            case 2: // ajout d'un trajet
                nbTrajetRentre=0;
                // caracteristique du trajet, ou du premier trajet en cas de trajet compose
                cout << "Entrez la ville de départ" << endl;
                cin.getline(villeDepart, 30, '\n');
                cout << "Entrez la ville d'arrivée" << endl;
                cin.getline(villeArrivee, 30, '\n');
                cout << "Entrez le moyen de transport" << endl;
                cin.getline(moyenTransport, 30, '\n');

                ++nbTrajetRentre;
                // on copie le trajet dans le tableau
                trajetRentres[nbTrajetRentre-1]=new TrajetSimple(villeDepart,villeArrivee,moyenTransport);

                // on determine si il s'agit d'un trajet simple ou compose
                cout << "Le trajet a-t-il une suite ?\n\toui\n\tnon" << endl;
                cin.getline(confirmationSuiteTrajet, 30, '\n');

                while(strcmp(confirmationSuiteTrajet,"oui")==0) // le trajet a une suite
                {
                    // si le trajet a une suite, on prend directement comme point de départ la ville d'arrivée du trajet précédent
                    strcpy(villeDepart,villeArrivee);
                    // on ne demande donc que la ville d'arrivée du prochain trajet
                    cout << "Entrez la ville d'arrivée" << endl;
                    cin.getline(villeArrivee, 30, '\n');
                    cout << "Entrez le moyen de transport" << endl;
                    cin.getline(moyenTransport, 30, '\n');

                    ++nbTrajetRentre;
                    // on agrandit le tableau de trajet
                    Trajet** tableauCopie = new Trajet*[nbTrajetRentre];
                    for(int i=0;i<nbTrajetRentre-1;i++)
                    {
                        tableauCopie[i]=trajetRentres[i];
                    }
                    delete[] trajetRentres;
                    trajetRentres = tableauCopie;
                    trajetRentres[nbTrajetRentre-1]= new TrajetSimple(villeDepart,villeArrivee,moyenTransport);

                    cout << "Le trajet a-t-il une suite ?\n\toui\n\tnon" << endl;
                    cin.getline(confirmationSuiteTrajet, 30, '\n');
                }

                // on ajoute le trajet au catalogue
                if(nbTrajetRentre==1) //trajet simple
                {
                    catalogue.Ajouter(trajetRentres[0]);
                }
                else //trajet composé
                {
                    Trajet* ptr_tc = new TrajetCompose(trajetRentres,nbTrajetRentre);
                    catalogue.Ajouter(ptr_tc);
                }

                // réinitialisation pour la prochaine saisie
                delete[] trajetRentres;
                trajetRentres = new Trajet*[1];
                break;

            case 3: // recherche simple
                if(catalogue.GetNbTrajetsAct() == 0)
                {
                    cout << "Le catalogue est vide" << endl;
                    break;
                }
                cout << endl << "Recherche simple de parcours : \n\n";
                cout << "Entrez la ville de départ : ";
                cin.getline(villeDepart, 30, '\n');
                cout << "Entrez la ville d'arrivée : ";
                cin.getline(villeArrivee, 30, '\n');
                cout << endl;
                catalogue.RechercheSimple(villeDepart,villeArrivee);
                cout << endl;
                break;

            case 4: // recherche complexe
                if(catalogue.GetNbTrajetsAct() == 0)
                {
                    cout << endl << "Le catalogue est vide" << endl << endl;
                    break;
                }
                cout << "Recherche complexe de parcours : " << endl;
                cout << "Entrez la ville de départ : ";
                cin.getline(villeDepart, 30, '\n');
                cout << endl << "Entrez la ville d'arrivée : ";
                cin.getline(villeArrivee, 30, '\n');
                cout << endl;
                catalogue.RechercheAvancee(villeDepart,villeArrivee);
                cout << endl;
                break;

            case 5: // lecture selelective d'un fichier
                if(selectionFichier('L', nomFile, typeTraj, ville1, ville2, indiceD, indiceF) == 0) {
                    testIn.open(nomFile);
                    catalogue.Lire(testIn, typeTraj, ville1, ville2, indiceD, indiceF);
                }
                break;

            case 6: //sauvegarde selective dans un fichier
                if(catalogue.GetNbTrajetsAct() == 0)
                {
                    cout << endl << "Le catalogue est vide" << endl << endl;
                    break;
                }
                cout << "Le catalogue contient " << catalogue.GetNbTrajetsAct() << " trajets." << endl;
                selectionFichier('S', nomFile, typeTraj, ville1, ville2, indiceD, indiceF);
                testOut.open(nomFile, ios::app);
                catalogue.SelectionTrajet(testOut, typeTraj, ville1, ville2, indiceD, indiceF);
                break;

            case 7: // fin du programme, on libère la zone mémoire utilisée
                cout << "Au revoir !" << endl;
                delete[] trajetRentres;
                return 0;
        }
    }

    return 0;
}