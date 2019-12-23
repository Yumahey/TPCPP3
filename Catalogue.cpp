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


void Catalogue::Lire(ifstream & fic, char typeTraj, char* depart,  char* arrivee, int indiceD, int indiceF) {

	if (fic) {

		char typeTrajetCourant;
		int numLigneCourante = 0;
		while (1) {
		
			fic >> typeTrajetCourant;
			char departC[30];
			char arriveeC[30];
			char espace[1];
			char mt[30];
			char nbTrajet;
			int nbrTrajetASuppr = 0;
			
			++numLigneCourante;
			if (numLigneCourante > indiceF && indiceF!=-1) {
				break;
			}
			if ((indiceD == -1 && indiceF == -1) || (numLigneCourante >= indiceD && numLigneCourante <= indiceF)){

			if (typeTrajetCourant=='S') {
				fic.getline(espace, 1, ' ');
				fic.getline(departC, 30, '|');
				fic.getline(arriveeC, 30, '|');
				fic.getline(mt, 30, '\n');
	
				if (typeTraj=='S' || typeTraj==' ') {

					if ((strcmp(depart, "")==0 && (strcmp(arrivee, "") == 0)) || (strcmp(depart, departC) == 0 && strcmp(arrivee, arriveeC)==0)|| (strcmp(depart, departC) == 0 && strcmp(arrivee, "") == 0)|| (strcmp(depart, "") == 0 && strcmp(arrivee, arriveeC) == 0)) {

							TrajetSimple* trajetAjout=new TrajetSimple(departC, arriveeC, mt);
							this->Ajouter(trajetAjout);
					}

				}
			}

			else if (typeTrajetCourant == 'C') {

				char nbTrajStr[30];

				if (typeTraj == 'C' || typeTraj == ' ') {

						fic >> nbTrajStr;
						nbTrajet = atoi(nbTrajStr);
						fic.getline(espace, 1, ' ');
						Trajet** listeTrajet = new Trajet * [nbTrajet];
						bool cdtAjout = true;
						char villeAvant[30];
						char villeApres[30];
						
						for ( int i = 0;i < nbTrajet && cdtAjout == true;i++) {
							if (i == 0) {

								fic.getline(villeAvant, 30, '|');
								strcpy(departC, villeAvant);
								if ((strcmp(depart, "") != 0) && (strcmp(depart, departC) != 0)) {
									cdtAjout = false;
								}
							}
							fic.getline(villeApres, 30, '|');

							if (i == nbTrajet - 1) {

								strcpy(arriveeC, villeApres);
								if ((strcmp(arrivee, "") != 0) && (strcmp(arrivee, arriveeC) != 0)) {
									cdtAjout = false;
								}
							}

							if (i != nbTrajet - 1) {
								fic.getline(mt, 30, '|');
							}
							else {
								fic.getline(mt, 30, '\n');
							}

							listeTrajet[i] = new TrajetSimple(villeAvant, villeApres, mt);
							++nbrTrajetASuppr;
							strcpy(villeAvant, villeApres);
						}

						if (cdtAjout == true) {
						
							TrajetCompose* trajetCompo = new TrajetCompose(listeTrajet, nbTrajet);
							this->Ajouter(trajetCompo);
						}
						else {
							char buffer[500];
							fic.getline(buffer, 500, '\n');
							for (int j = 0;j < nbrTrajetASuppr;j++) {
								delete[] listeTrajet[j];
							}
						}

						delete[] listeTrajet;
				}
				else {
					char buffer[500];
					fic.getline(buffer, 500, '\n');
				}
			}

		}

		else {
			char buffer[500];
			fic.getline(buffer, 500, '\n');

		}

			if (fic.eof()) {
				break;
			}
		}
	}
	else {
		std::cerr << "Erreur d'ouverture du fichier "<<std::endl;
	}

	fic.close();
}

void Catalogue:: SelectionTrajet(ofstream& fic,char typeTraj, char* depart, char* arrivee, int indiceD, int indiceF) {

	int indiceDebut=1;
	int indiceFin=this->nbTrajetsAct;

	if (indiceD != -1) {
		indiceDebut = indiceD;
	}

	if (indiceF != -1) {
		indiceFin = indiceF;
	}

	for (int i = indiceDebut-1;i < indiceFin && i<nbTrajetsAct;i++) {
		
		if (verifVilles(depart, arrivee, listeTrajetsCatalogue[i]->getVilleDepart(), listeTrajetsCatalogue[i]->getVilleArrivee()) == true) {
	
			if (typeTraj == 'S' || typeTraj==' ') {
				TrajetSimple* trajetS = dynamic_cast<TrajetSimple*>(listeTrajetsCatalogue[i]);
				if (trajetS) {
					trajetS->ecriture(fic);
				}
			}
			 if (typeTraj == 'C' ||typeTraj == ' ') {
				TrajetCompose* trajetC = dynamic_cast<TrajetCompose*>(listeTrajetsCatalogue[i]);
				if (trajetC) {
					trajetC->ecriture(fic);
					
				}
			}
		}
	}
		fic.close();
}

bool Catalogue:: verifVilles(char* departS,char* arriveeS, char* depart, char* arrivee) {
	
	if (strcmp(arriveeS, "") == 0 && strcmp(departS, "") == 0) {

		return true;
	}

	if (strcmp(depart, departS) == 0 && strcmp(arrivee, arriveeS) == 0) {
		return true;
	}

	if (strcmp(depart, departS) == 0 && strcmp(arriveeS,"") == 0) {
		return true;
	}

	if (strcmp(arrivee, arriveeS) == 0 && strcmp(departS, "") == 0) {
		return true;
	}

	return false;

}

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
