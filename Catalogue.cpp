//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

int Catalogue::Ajouter(Trajet* unTrajet) {
	if(this->nbTrajetsAct==this->nbTrajetsMax) // vérifie si la liste a besoin d'être agrandie
	{
		this->nbTrajetsMax *= 2; // on double à chaque fois la taille pour effectuer l'agrandissement moins de fois si l'utilisateur rentre beaucoup de trajets
		Trajet** tableauTemp = new Trajet* [this->nbTrajetsMax];
		for(int i=0;i<this->nbTrajetsAct;i++)
		{
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

void Catalogue::RechercheSimple(char* depart,char* arrivee) const
{
	cout<<"==== Liste des trajets allant de "<<depart<<" à "<<arrivee<<" : ===="<<endl;
	for(int i=0;i<this->nbTrajetsAct;i++)
	{
		// on regarde pour chaque trajet si sa ville de départ et sa ville d'arrivée (directe) correspondent à la recherche
		if(strcmp(this->listeTrajetsCatalogue[i]->getVilleDepart(),depart)==0 &&strcmp(this->listeTrajetsCatalogue[i]->getVilleArrivee(),arrivee)==0)
		{
			cout << "------ Nouveau Trajet ------" << endl;
			this->listeTrajetsCatalogue[i]->AfficherTrajet();
			cout<<endl;
		}
	}
}

void Catalogue::RechercheAvancee(char* depart,char* arrivee) const
{
	// lance la recherche avancée en initialisant un tableau permettant de retenir les trajets déjà parcourus dans la recherche
	cout<<"==== Liste des trajets allant de "<<depart<<" à "<<arrivee<<" : ===="<<endl;
	int* tableTrajetDejaParcouru = new int [this->nbTrajetsAct];
	for (int a = 0;a < this->nbTrajetsAct;a++) {
		tableTrajetDejaParcouru[a] = 0;
	}
	RechercheRecursive(depart,depart, arrivee, tableTrajetDejaParcouru,1);
	delete[] tableTrajetDejaParcouru;

}

void Catalogue::RechercheRecursive(char* departInitial,char* departActuel,char* arriveeFinale, int* tableTrajetParcouru, int profondeur) const
{ // Algorithme : recherche en backtracking qui parcourt en profondeur tous les trajets possibles et retient ceux qui partent de "departInitial" et arrivent à "arriveeFinale"
	for (int i = 0;i < this->nbTrajetsAct;i++)
	{
		if(strcmp(this->listeTrajetsCatalogue[i]->getVilleArrivee(), departInitial) != 0) // permet de ne pas revenir au point de départ ce qui ne servirait à rien dans la recherche
		{
			if (tableTrajetParcouru[i] == 0 && strcmp(this->listeTrajetsCatalogue[i]->getVilleDepart(), departActuel) == 0) // vérifie que l'on n'a pas encore parcouru ce trajet et qu'il part de là où l'on se trouve ("depart")
			{
				if (strcmp(this->listeTrajetsCatalogue[i]->getVilleArrivee(), arriveeFinale) == 0) // ce trajet arrive à la destination recherchée ("arrivee")
				{
					tableTrajetParcouru[i] = profondeur; // permet l'affichage du trajet "dans l'ordre" grâce à la profondeur à laquelle il se trouve dans la recherche
					cout << "------ Nouveau Trajet ------" << endl;
					for (int p = 1;p <= profondeur;p++)
					{
						for (int j = 0;j < this->nbTrajetsAct;j++)
						{
							if (tableTrajetParcouru[j] == p) // affiche les trajets par ordre de profondeur (de 1 à "profondeur")
							{
								this->listeTrajetsCatalogue[j]->AfficherTrajet();
								cout << endl;
							}
						}
					}
					tableTrajetParcouru[i] = 0; // remet le trajet dans un état "non parcouru" pour la suite de la recherche
				}
				else
				{
					tableTrajetParcouru[i] = profondeur;
					RechercheRecursive(departInitial, this->listeTrajetsCatalogue[i]->getVilleArrivee(), arriveeFinale, tableTrajetParcouru,profondeur+1); // si on n'est pas encore arrivé à la destination finale, on relance la méthode à partir de l'arrivée du trajet actuellement considéré
					tableTrajetParcouru[i] = 0;
				}
			}
		}
	}
}

void Catalogue::AfficherCatalogue() const
{
	if(this->nbTrajetsAct==0)
	{
		cout<<endl<<"Le catalogue est vide"<<endl;
		return;
	}
	cout<<"Les trajets présents dans le catalogue sont les suivants : "<<endl;
	for(int i=0;i<this->nbTrajetsAct;i++)
	{
		this->listeTrajetsCatalogue[i]->AfficherTrajet();
		cout<<endl;
	}
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue()
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif

	this->listeTrajetsCatalogue = new Trajet* [1]; // par défaut initialise la taille maximale du catalogue à 1
	this->nbTrajetsMax = 1;
	this->nbTrajetsAct = 0;
} //----- Fin de Catalogue (constructeur par défaut)

Catalogue::~Catalogue()
{
	#ifdef MAP
	    cout << "Appel au destructeur de <Catalogue>" << endl;
	#endif
	for(int i=0;i<this->nbTrajetsAct;i++)
	{
		delete this->listeTrajetsCatalogue[i]; // détruit chaque trajet présent dans le catalogue
	}
	delete[] this->listeTrajetsCatalogue;
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
