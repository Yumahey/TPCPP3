//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

#include <iostream>
#include <cstring>
#include  <fstream>
//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Catalogue::Lire(ifstream &fic, char typeTraj, char *depart, char *arrivee, int indiceD, int indiceF)
{
    if (fic) // si le flux est valide
    {
        char typeTrajetCourant;
        int numLigneCourante = 0;
        while (1) // parcours d'une ligne par tour de boucle
        {
            typeTrajetCourant = 'X';// valeur initiale différente des 2 valeurs possibles afin
            // qu'il n'y ait pas lecture des lignes vides après les trajets s'il y en a
            fic >> typeTrajetCourant;
            char departC[30];//depart trajet en cours
            char arriveeC[30];//arrivee trajet en cours
            char espace[1];//buffer pour vider les espaces
            char mt[30];//moyen de transport
            int nbrTrajetASuppr = 0;
            ++numLigneCourante;

            if (numLigneCourante > indiceF && indiceF != -1) //si on depasse l'indice max de selection
            {
                break;
            }
            // si la ligne est dans l'intervalle choisi
            if ((indiceD == -1 && indiceF == -1) || (numLigneCourante >= indiceD && numLigneCourante <= indiceF))
            {
                if (typeTrajetCourant == 'S') // si le trajet lu est un trajet simple
                {
                    fic.getline(espace, 1, ' ');
                    fic.getline(departC, 30, '|');
                    fic.getline(arriveeC, 30, '|');
                    fic.getline(mt, 30, '\n');

                    if (typeTraj == 'S' || typeTraj == ' ') // si on cherche les trajets simples ou tous types
                    {
                        if ((strcmp(depart, "") == 0 && (strcmp(arrivee, "") == 0)) ||
                            (strcmp(depart, departC) == 0 && strcmp(arrivee, arriveeC) == 0) ||
                            (strcmp(depart, departC) == 0 && strcmp(arrivee, "") == 0) ||
                            (strcmp(depart, "") == 0 && strcmp(arrivee, arriveeC) == 0))
                        {
                            //si les criteres correspondent a la selection, on ajoute le trajet Simple lu au catalogue
                            TrajetSimple *trajetAjout = new TrajetSimple(departC, arriveeC, mt);
                            this->Ajouter(trajetAjout);

                        }
                    }
                } else if (typeTrajetCourant == 'C') // si le trajet lu est un trajet compose
                {
                    char nbTrajStr[30];

                    if (typeTraj == 'C' || typeTraj == ' ') // si on cherche les trajets composes ou tous types
                    {
                        fic >> nbTrajStr;
                        int nbTrajetCourant = atoi(nbTrajStr); //lecture du nombre de trajets composant le Trajet Compose
                        fic.getline(espace, 1, ' ');

                        Trajet **listeTrajet = new Trajet *[nbTrajetCourant];//liste de pointeurs de trajet stockant les trajets simples du trajet Compose
                        bool cdtAjout = true;
                        char villeAvant[30];//buffers pour accueillir les villes du trajet Compose du fichier
                        char villeApres[30];

                        for (int i = 0; i < nbTrajetCourant && cdtAjout == true; i++) // pour chaque sous-trajet
                        {
                            //parcours du trajetCompose en cours de lecture
                            if (i == 0)
                            {
                                //lecture de la 1ere ville de depart
                                fic.getline(villeAvant, 30, '|');
                                strcpy(departC, villeAvant);
                                if ((strcmp(depart, "") != 0) && (strcmp(depart, departC) != 0))
                                {
                                    //verification critere ville de depart
                                    cdtAjout = false;
                                }
                            }
                            fic.getline(villeApres, 30, '|');//lecture villes successives

                            if (i == nbTrajetCourant - 1)
                            {
                                strcpy(arriveeC, villeApres);
                                if ((strcmp(arrivee, "") != 0) && (strcmp(arrivee, arriveeC) != 0))
                                {
                                    //verification critere ville d'arrivee
                                    cdtAjout = false;
                                }
                            }

                            if (i != nbTrajetCourant - 1)
                            {
                                fic.getline(mt, 30, '|');
                            }
                            else
                            {
                                if (cdtAjout == true)
                                {
                                    fic.getline(mt, 30, '\n');
                                }

                            }
                            listeTrajet[i] = new TrajetSimple(villeAvant, villeApres,mt);//creation du trajet Simple lu et ajout dans la liste
                            ++nbrTrajetASuppr;
                            strcpy(villeAvant, villeApres);
                        }

                        if (cdtAjout == true)
                        {
                            //si tous les criteres de selection sont reunis, on ajoute au catalogue
                            TrajetCompose *trajetCompo = new TrajetCompose(listeTrajet, nbTrajetCourant);
                            this->Ajouter(trajetCompo);
                        }
                        else
                        {
                            //pas d'ajout du trajet au catalogue car ne correspond pas a la selection
                            char buffer[500];
                            fic.getline(buffer, 500, '\n');//on passse a la ligne suivante
                            for (int j = 0; j < nbrTrajetASuppr; j++)
                            {
                                delete listeTrajet[j];// on vide l'espace memoire cree inutilement
                            }
                        }
                        delete[] listeTrajet;

                    }
                    else
                    {
                        //pas d'ajout du trajet au catalogue car ne correspond pas a la selection
                        char buffer[500];
                        fic.getline(buffer, 500, '\n');
                    }
                }
                else
                {
                    //pas d'ajout du trajet au catalogue car identificateur ne correspond pas
                    char buffer[500];
                    fic.getline(buffer, 500, '\n');
                }

            }
            else
            {
                //pas d'ajout du trajet au catalogue car ne correspond pas a la selection
                char buffer[500];
                fic.getline(buffer, 500, '\n');
            }

            if (fic.eof())
            {
                //fin de lecture du fichier
                break;
            }
        }
    }
    else
    {
        std::cerr << "Erreur d'ouverture du fichier " << std::endl;
    }

    fic.close();
}

void Catalogue::SelectionTrajet
        (ofstream &fic, char typeTraj, char *depart, char *arrivee, int indiceD, int indiceF) const
{
    int indiceDebut = 1;//par defaut on parcourt tous les trajets du catalogue
    int indiceFin = this->nbTrajetsAct;

    if (indiceD != -1)
    {
        indiceDebut = indiceD;
    }

    if (indiceF != -1)
    {
        indiceFin = indiceF;
    }

    for (int i = indiceDebut - 1; i < indiceFin && i < nbTrajetsAct; i++)
    {
        //parcours du catalogue sur les indices choisis
        if (verifVilles(depart, arrivee, listeTrajetsCatalogue[i]->getVilleDepart(),listeTrajetsCatalogue[i]->getVilleArrivee()) == true)
        {
            if (typeTraj == 'S' || typeTraj == ' ')
            {
                TrajetSimple *trajetS = dynamic_cast<TrajetSimple *>(listeTrajetsCatalogue[i]);//on teste si le trajet d'indice i est un trajet Simple
                if (trajetS)
                {
                    trajetS->ecriture(fic);
                }
            }
            if (typeTraj == 'C' || typeTraj == ' ')
            {
                TrajetCompose *trajetC = dynamic_cast<TrajetCompose *>(listeTrajetsCatalogue[i]);//on teste si le trajet d'indice i est un trajet Compose
                if (trajetC)
                {
                    trajetC->ecriture(fic);

                }
            }
        }
    }

    fic.close();
}

bool Catalogue::verifVilles(char *departS, char *arriveeS, char *depart, char *arrivee) const
{
    if (strcmp(arriveeS, "") == 0 && strcmp(departS, "") == 0)
    {
        //aucun critere de selection sur les villes
        return true;
    }

    if (strcmp(depart, departS) == 0 && strcmp(arrivee, arriveeS) == 0)
    {
        //critere de selection respecte sur les villes de depart et d'arrivee
        return true;
    }

    if (strcmp(depart, departS) == 0 && strcmp(arriveeS, "") == 0)
    {
        //critere de selection sur la ville de depart uniquement
        return true;
    }

    if (strcmp(arrivee, arriveeS) == 0 && strcmp(departS, "") == 0)
    {
        //critere de selection  sur la ville d'arrivee uniquement
        return true;
    }

    return false;

}

int Catalogue::Ajouter(Trajet *unTrajet)
{
    if (this->nbTrajetsAct == this->nbTrajetsMax) // vérifie si la liste a besoin d'être agrandie
    {
        this->nbTrajetsMax *= 2; // on double à chaque fois la taille pour effectuer l'agrandissement moins de fois si l'utilisateur rentre beaucoup de trajets
        Trajet **tableauTemp = new Trajet *[this->nbTrajetsMax];
        for (int i = 0; i < this->nbTrajetsAct; i++) {
            tableauTemp[i] = this->listeTrajetsCatalogue[i];
        }
        delete[] listeTrajetsCatalogue;
        listeTrajetsCatalogue = tableauTemp;
    }
    // ajout du trajet (grâce à son pointeur)
    this->listeTrajetsCatalogue[this->nbTrajetsAct] = unTrajet;
    this->nbTrajetsAct++;
    return 1;
}

void Catalogue::RechercheSimple(char *depart, char *arrivee) const
{
    cout << "==== Liste des trajets allant de " << depart << " à " << arrivee << " : ====" << endl;
    for (int i = 0; i < this->nbTrajetsAct; i++) {
        // on regarde pour chaque trajet si sa ville de départ et sa ville d'arrivée (directe) correspondent à la recherche
        if (strcmp(this->listeTrajetsCatalogue[i]->getVilleDepart(), depart) == 0 &&
            strcmp(this->listeTrajetsCatalogue[i]->getVilleArrivee(), arrivee) == 0) {
            cout << "------ Nouveau Trajet ------" << endl;
            this->listeTrajetsCatalogue[i]->AfficherTrajet();
            cout << endl;
        }
    }
}

void Catalogue::RechercheAvancee(char *depart, char *arrivee) const
{
    // lance la recherche avancée en initialisant un tableau permettant de retenir les trajets déjà parcourus dans la recherche
    cout << "==== Liste des trajets allant de " << depart << " à " << arrivee << " : ====" << endl;
    int *tableTrajetDejaParcouru = new int[this->nbTrajetsAct];
    for (int a = 0; a < this->nbTrajetsAct; a++) {
        tableTrajetDejaParcouru[a] = 0;
    }
    RechercheRecursive(depart, depart, arrivee, tableTrajetDejaParcouru, 1);
    delete[] tableTrajetDejaParcouru;

}

void Catalogue::RechercheRecursive
        (char *departInitial, char *departActuel, char *arriveeFinale, int *tableTrajetParcouru,int profondeur) const
{
    // Algorithme : recherche en backtracking qui parcourt en profondeur tous les trajets possibles et retient ceux qui partent de "departInitial" et arrivent à "arriveeFinale"
    for (int i = 0; i < this->nbTrajetsAct; i++) {
        if (strcmp(this->listeTrajetsCatalogue[i]->getVilleArrivee(), departInitial) !=
            0) // permet de ne pas revenir au point de départ ce qui ne servirait à rien dans la recherche
        {
            if (tableTrajetParcouru[i] == 0 && strcmp(this->listeTrajetsCatalogue[i]->getVilleDepart(), departActuel) ==
                                               0) // vérifie que l'on n'a pas encore parcouru ce trajet et qu'il part de là où l'on se trouve ("depart")
            {
                if (strcmp(this->listeTrajetsCatalogue[i]->getVilleArrivee(), arriveeFinale) ==
                    0) // ce trajet arrive à la destination recherchée ("arrivee")
                {
                    tableTrajetParcouru[i] = profondeur; // permet l'affichage du trajet "dans l'ordre" grâce à la profondeur à laquelle il se trouve dans la recherche
                    cout << "------ Nouveau Trajet ------" << endl;
                    for (int p = 1; p <= profondeur; p++) {
                        for (int j = 0; j < this->nbTrajetsAct; j++) {
                            if (tableTrajetParcouru[j] ==
                                p) // affiche les trajets par ordre de profondeur (de 1 à "profondeur")
                            {
                                this->listeTrajetsCatalogue[j]->AfficherTrajet();
                                cout << endl;
                            }
                        }
                    }
                    tableTrajetParcouru[i] = 0; // remet le trajet dans un état "non parcouru" pour la suite de la recherche
                } else {
                    tableTrajetParcouru[i] = profondeur;
                    RechercheRecursive(departInitial, this->listeTrajetsCatalogue[i]->getVilleArrivee(), arriveeFinale,
                                       tableTrajetParcouru, profondeur +
                                                            1); // si on n'est pas encore arrivé à la destination finale, on relance la méthode à partir de l'arrivée du trajet actuellement considéré
                    tableTrajetParcouru[i] = 0;
                }
            }
        }
    }
}

void Catalogue::AfficherCatalogue() const
{
    if (this->nbTrajetsAct == 0) {
        cout << endl << "Le catalogue est vide" << endl;
        return;
    }
    cout << "Les trajets présents dans le catalogue sont les suivants : " << endl;
    for (int i = 0; i < this->nbTrajetsAct; i++) {
        this->listeTrajetsCatalogue[i]->AfficherTrajet();
        cout << endl;
    }
}

int Catalogue::GetNbTrajetsAct() const
{
    return this->nbTrajetsAct;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue()
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif

    this->listeTrajetsCatalogue = new Trajet *[1]; // par défaut initialise la taille maximale du catalogue à 1
    this->nbTrajetsMax = 1;
    this->nbTrajetsAct = 0;
} //----- Fin de Catalogue (constructeur par défaut)

Catalogue::~Catalogue()
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    for (int i = 0; i < this->nbTrajetsAct; i++) {
        delete this->listeTrajetsCatalogue[i]; // détruit chaque trajet présent dans le catalogue
    }
    delete[] this->listeTrajetsCatalogue;
} //----- Fin de ~Catalogue

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
