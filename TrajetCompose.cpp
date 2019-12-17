//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void TrajetCompose::AfficherTrajet() const
// Algorithme : affiche le trajet composé en appelant à tour de rôle les méthodes AfficherTrajet() de chaque trajet simple le composant
//
{
	for (int i = 0;i < this->nbTrajets;i++)
	{
		this->listeTrajets[i]->AfficherTrajet();

		if (i != (this->nbTrajets - 1)) // si ce n'est pas le dernier trajet simple, affiche un "-" pour séparer les affichages
		{
				cout << " -";
		}
	}
}
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

TrajetCompose::TrajetCompose(Trajet** listeTrajet, int nbTrajets)
	:Trajet(listeTrajet[0]->getVilleDepart(), listeTrajet[nbTrajets-1]->getVilleArrivee()), nbTrajets(nbTrajets)
{

	#ifdef MAP
		cout << "Appel au constructeur de <TrajetCompose>" << endl;
	#endif

	this->listeTrajets = new Trajet*[nbTrajets];
	for(int i=0;i<nbTrajets;i++)
	{
		this->listeTrajets[i] = listeTrajet[i];
	}

} //----- Fin de TrajetCompose


TrajetCompose::~TrajetCompose()
{
#ifdef MAP
	cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif

	for(int i=0;i<this->nbTrajets;i++)
	{
		delete this->listeTrajets[i];
	}
	delete[] this->listeTrajets;

} //----- Fin de ~TrajetCompose


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
