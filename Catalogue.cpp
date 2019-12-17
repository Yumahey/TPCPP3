/*************************************************************************
                           Catalogue  -  Stocke la liste des trajets et
                           permet de la gerer (ajout, recherche, affichage)
                             -------------------
    début                : 19/11/2019
    copyright            : (C) 2019 par Emma Neiss, Yann Dupont
    e-mail               : emma.neiss@insa-lyon.fr  yann.dupont@insa-lyon.fr
*************************************************************************/

//----- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"

//------------------------------------------------------------- Constantes
static int CODE0 = 48;
static int CODE9 = 57;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Catalogue::Afficher() const
{
#ifdef MAP
    cerr << "Appel a la methode Afficher de Catalogue" << endl;
#endif
    unsigned int i;
    for (i = 0; i < tailleAct; i++) {
        cout << i+1 << " - ";
        listeTrajets[i]->Afficher();
    }
    if(tailleAct == 0){
        cout << "Aucun trajet repertorie !" << endl;
    }
}

void Catalogue::AjouterTrajet()
{
#ifdef MAP
    cerr << "Appel a la methode AjouterTrajet de Catalogue" << endl;
#endif
    // on determine si l'utilisateur veut ajouter un trajet simple ou compose
    cout << "1 : Trajet simple;   2 : Trajet compose" << endl;
    char choix;
    cin >> choix;
    cin.ignore(10000, '\n');
    while(choix != '1' && choix != '2') {
        cout << "Choix incorrect" << endl;
        cin >> choix;
        cin.ignore(10000, '\n');
    }

    // on cree les variables pour stocker les informations sur le nouveau trajet
    Ville villeDepart = new char[MAX_CHAR_VILLE];
    Ville villeArrivee = new char[MAX_CHAR_VILLE];
    MT mt = new char[MAX_CHAR_VILLE];
    unsigned int nbSections = 0;

    if(choix == '2'){ // si c'est un trajet compose
        cout << "Nombre de sections :" << endl;

        // recuperation de nbSection securisee
        char input;
        while(true){
            cin >> input;
            if((CODE0<=input) && (input<=CODE9)){ // le caractere suivant est un chiffre
                nbSections = nbSections*10 + input-CODE0;
            } else {
                cin.ignore(10000, '\n');
                if(nbSections == 0){ // si ce n'est pas un chiffre, on redemande une entree tant que nbSection est nul
                    cout << "Choix incorrect" << endl;
                    continue;
                }
                break; // on a eu un caractere non-chiffre mais nbSection est deja determine -> on sort
            }
            cerr << int(cin.peek()) << endl;
            if((cin.peek() == 10) && (nbSections != 0)){ // si il n'y a plus de caractere a lire
                break;
            }
        }
        cin.ignore(10000, '\n');

        cout << "1er trajet" << endl;
    }

    cout << "Ville de depart :" << endl;
    cin.getline(villeDepart, MAX_CHAR_VILLE, '\n');

    cout << "Ville d'arrivee :" << endl;
    cin.getline(villeArrivee, MAX_CHAR_VILLE, '\n');

    cout << "Moyen de transport :" << endl;
    cin.getline(mt, MAX_CHAR_VILLE, '\n');

    // on cree le nouveau trajet
    Trajet * newTrajet;
    if(choix == '1'){ // trajet simple
        newTrajet = new TS(villeDepart, villeArrivee, mt);
    } else { //if (choix == 2){ // on lit les entrees pour determiner toutes les sections du trajet (compose)
        Trajet ** newListeTrajets = new Trajet*[nbSections];
        unsigned int i;
        newListeTrajets[0] = new TS(villeDepart, villeArrivee, mt);
        for (i = 1; i < nbSections; i++) { // pour chaque section, on demande les informations correspondantes
            //villeDepart = villeArrivee;
            strcpy(villeDepart, villeArrivee);
            cout << i+1 << "e trajet" << endl;
            cout << "Ville d'arrivee :" << endl;
            cin.getline(villeArrivee, MAX_CHAR_VILLE, '\n');
            cout << "Moyen de transport :" << endl;
            cin.getline(mt, MAX_CHAR_VILLE, '\n');
            newListeTrajets[i] = new TS(villeDepart, villeArrivee, mt);
        }
        newTrajet = new TC(nbSections, newListeTrajets);
        delete[] newListeTrajets;
    }

    // On place le nouveau trajet dans le catalogue
    if(tailleAct == tailleMax){
        AggrandirListe();
    }
    listeTrajets[tailleAct] = newTrajet;
    tailleAct++;
    delete[] villeDepart;
    delete[] villeArrivee;
    delete[] mt;
}

void Catalogue::RechercheTrajet() const
// Algorithme :
// Parcourt la liste de trajets du Catalogue, teste pour chacun si
// le depart et l'arrivee correspondent a ceux entres par l'utilisateur
{
#ifdef MAP
    cerr << "Appel a la methode RechercheTrajet de Catalogue" << endl;
#endif
    Ville villeDepart = new char[30];
    Ville villeArrivee = new char[30];
    cout << "Ville de depart :" << endl;
    cin.getline(villeDepart, MAX_CHAR_VILLE, '\n');
    cout << "Ville d'arrivee :" << endl;
    cin.getline(villeArrivee, MAX_CHAR_VILLE, '\n');

    unsigned int i, trouve = 0;
    for (i = 0; i < tailleAct; i++) {
        if((strcmp(villeDepart, listeTrajets[i]->getDepart()) == 0) && (strcmp(villeArrivee, listeTrajets[i]->getArrivee()) == 0)){
            cout << "Trajet trouve : ";
            listeTrajets[i]->Afficher();
            trouve = 1; // on a trouve au moins un trajet correspondant
        }
    }

    if(trouve == 0){ // si on n'a trouve aucun trajet, on affiche un message
        cout << "Aucun trajet trouve." << endl;
    }

    delete[] villeDepart;
    delete[] villeArrivee;
}


//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( const Catalogue & unCatalogue )
{
#ifdef MAP
    cerr << "Appel au constructeur de copie de Catalogue" << endl;
#endif
    tailleMax = unCatalogue.tailleMax;
    tailleAct = unCatalogue.tailleAct;
    listeTrajets = new Trajet*[unCatalogue.tailleMax];
    unsigned int i;
    for (i = 0; i < tailleAct; i++) {
        listeTrajets[i] = new Trajet(*unCatalogue.listeTrajets[i]);
    }
} //----- Fin de Catalogue (constructeur de copie)


Catalogue::Catalogue ( )
{
#ifdef MAP
    cerr << "Appel au constructeur de Catalogue" << endl;
#endif
    listeTrajets = new Trajet*[TAILLEDEFAUT];
    tailleMax = TAILLEDEFAUT;
    tailleAct = 0;
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
{
#ifdef MAP
    cerr << "Appel au destructeur de Catalogue" << endl;
#endif
    unsigned int i;
    for (i = 0; i < tailleAct; i++) {
        delete listeTrajets[i];
    }
    delete[] listeTrajets;
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void Catalogue::AggrandirListe()
{
#ifdef MAP
    cerr << "Appel a la methode AggrandirListe de Catalogue" << endl;
#endif
    tailleMax = 2 * tailleMax;
    Trajet ** nouvelleListeTrajets = new Trajet*[tailleMax];
    unsigned int i;
    for (i = 0; i < tailleAct; i++) {
        nouvelleListeTrajets[i] = listeTrajets[i];
    }
    delete[] listeTrajets;
    listeTrajets = nouvelleListeTrajets;
}

