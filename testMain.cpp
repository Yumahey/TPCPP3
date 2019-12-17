#include <iostream>
#include <cstring>

#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Catalogue.h"

using namespace std;

Catalogue catalogue;
int choixMenu=0; // stocke le choix de l'utilisateur
int valeurRetour=0; // permet de vérifier que l'utilisateur a bien rentré un chiffre valide
int nbTrajetRentre = 0; // permet de connaître le nombre de trajets simples saisis en une seule fois
char villeDepart[100]; // stocke la ville de départ rentrée par l'utilisateur
char villeArrivee[100]; // stocke la ville d'arrivée rentrée par l'utilisateur
char moyenTransport[100]; // stocke le moyen de transport rentré par l'utilisateur
char confirmationSuiteTrajet[50]; // permet d'enchaîner plusieurs trajets simples dans le cas de la saisie d'un trajet composé
TrajetSimple* trajetRentres; // stocke les trajets simples saisis

int main()
{
	trajetRentres = new TrajetSimple[1]; // par défaut le tableau est de taille 1

	while(1)
	{
		choixMenu=0;
		cout<<"Choix disponibles : "<<endl;
		cout<<"\t(1) Afficher le catalogue"<<endl;
		cout<<"\t(2) Ajouter un trajet au catalogue"<<endl;
		cout<<"\t(3) Rechercher un parcours (Recherche simple)"<<endl;
		cout<<"\t(4) Rechercher un parcours (Recherche complexe)"<<endl;
		cout<<"\t(5) Quitter le programme"<<endl;


		//gestion éventuelle des mauvaises saisies
		do {
			valeurRetour=scanf("%d",&choixMenu);
			getchar(); // enlève du buffer de lecture le "Entrer"

			if(valeurRetour!=1 || choixMenu <=0 || choixMenu>=6) // choix non valide ou la valeur saisie n'est pas un entier
			{
					cout<<"Veuillez entrer un nombre valide et strictement positif et strictement inférieur à 6"<<endl;
			}
		} while(valeurRetour!=1 || choixMenu <=0 || choixMenu >=6);

		switch(choixMenu)
		{
			case 1:
				catalogue.AfficherCatalogue();
				cout<<endl;
				break;
			case 2:
				nbTrajetRentre=0;
				cout<<"Entrez la ville de départ"<<endl;
				scanf("%[^\n]",villeDepart);
				getchar(); // enlève le "Entrer" du buffer de lecture
				cout<<"Entrez la ville de arrivée"<<endl;
				scanf("%[^\n]",villeArrivee);
				getchar();
				cout<<"Entrez le moyen de transport"<<endl;
				scanf("%[^\n]",moyenTransport);
				getchar();

				++nbTrajetRentre;
				// on copie le trajet dans le tableau
				trajetRentres[nbTrajetRentre-1]= TrajetSimple(villeDepart,villeArrivee,moyenTransport);

				cout<<"Le trajet a-t-il une suite ?\n\toui\n\tnon"<<endl;
				scanf("%s",confirmationSuiteTrajet);
				getchar();

				while(strcmp(confirmationSuiteTrajet,"oui")==0) // le trajet a une suite
				{
					// si le trajet a une suite, on prend directement comme point de départ la ville d'arrivée du trajet précédent
					strcpy(villeDepart,villeArrivee);
					// on ne demande donc que la ville d'arrivée du prochain trajet
					cout<<"Entrez la ville d'arrivée"<<endl;
					scanf("%[^\n]",villeArrivee);
					getchar();
					cout<<"Entrez le moyen de transport"<<endl;
					scanf("%[^\n]",moyenTransport);
					getchar();

					++nbTrajetRentre;
					// on agrandit le tableau de trajet
					TrajetSimple* tableauCopie = new TrajetSimple[nbTrajetRentre];
					for(int i=0;i<nbTrajetRentre-1;i++)
					{
						tableauCopie[i]=trajetRentres[i];
					}
					delete[] trajetRentres;
					trajetRentres = tableauCopie;
					trajetRentres[nbTrajetRentre-1]= TrajetSimple(villeDepart,villeArrivee,moyenTransport);


					cout<<"Le trajet a-t-il une suite ?\n\toui\n\tnon"<<endl;
					scanf("%s",confirmationSuiteTrajet);
					getchar();
				}

				if(nbTrajetRentre==1) //trajet simple
				{
					// on alloue une zone mémoire pour stocker le trajet
					Trajet* ptr_ts = new TrajetSimple(trajetRentres[0].getVilleDepart(),trajetRentres[0].getVilleArrivee(),trajetRentres[0].getTransport());
					catalogue.Ajouter(ptr_ts);
				}
				else //trajet composé
				{
					Trajet* ptr_tc = new TrajetCompose(trajetRentres,nbTrajetRentre);
					catalogue.Ajouter(ptr_tc);
				}

				// réinitialisation pour la prochaine saisie
				delete[] trajetRentres;
				trajetRentres = new TrajetSimple[1];

				break;

			case 3:
				cout<<"Recherche simple de parcours : "<<endl;
				cout<<"Entrez la ville de départ : ";
				scanf("%s",villeDepart);
				cout<<endl<<"Entrez la ville d'arrivée : ";
				scanf("%s",villeArrivee);
				cout<<endl;
				catalogue.RechercheSimple(villeDepart,villeArrivee);
				cout<<endl;
				break;
			case 4:
				cout<<"Recherche complexe de parcours : "<<endl;
				cout<<"Entrez la ville de départ : ";
				scanf("%s",villeDepart);
				cout<<endl<<"Entrez la ville d'arrivée : ";
				scanf("%s",villeArrivee);
				cout<<endl;
				catalogue.RechercheAvancee(villeDepart,villeArrivee);
				cout<<endl;
				break;
			case 5:
				// fin du programme, on libère la zone mémoire utilisée
				delete[] trajetRentres;
				return 0;
				break;
		}

	}
	return 0;
}
