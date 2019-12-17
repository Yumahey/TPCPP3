/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : novembre 2019
    copyright            : (C) 2019 par Killian OECHSLIN et Thomas MIGNOT
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// Cette classe va servir à retenir les trajets rentrés par l'utilisateur dans un tableau dédié, mais également lui permet d'afficher tous les trajets disponibles
// ou d'effectuer une recherche (simple ou avancée) pour un voyage donné (défini par une ville de départ et d'arrivée) des trajets qui répondent à la demande
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	int Ajouter(Trajet* monTrajet);
	// Mode d'emploi : Permet de rajouter dans le catalogue un trajet (simple ou composé) via passage en paramètre de son pointeur (de type Trajet)
	//
	// Contrat : Le trajet pointé par "monTrajet" doit être de type TrajetSimple ou TrajetCompose

	void AfficherCatalogue() const;
	// Mode d'emploi : Affiche tous les trajets contenus dans le catalogue
	//

	void RechercheSimple(char* depart,char* arrivee) const;
	// Mode d'emploi : Recherche dans le catalogue les trajets qui partent de "depart" et qui arrive directement à "arrivee"
	//

	void RechercheAvancee(char* depart,char* arrivee) const;
	// Mode d'emploi : Recherche dans le catalogue les trajets ou combinaisons de trajets qui partent de "depart" et qui arrive à "arrivee"
	//

	void RechercheRecursive(char* departInitial,char* departActuel,char* arriveeFinale, int* tableTrajetParcouru, int profondeur) const;
	// Mode d'emploi : Méthode utilisée dans RechercheAvancee qui permet de parcourir en profondeur les trajets pour trouver ceux correspondant à la recherche
	//

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    Catalogue();
		// Mode d'emploi : Crée le catalogue en initialisant la liste de trajets (avec par défaut une taille de 1)
		//

    virtual ~Catalogue();
		//


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	Trajet** listeTrajetsCatalogue; // tableau qui permet le stockage (grâce à des pointeurs) des trajets présents dans le catalogue
	int nbTrajetsMax; // taille du tableau listeTrajets
	int nbTrajetsAct; // nombre de trajets effectivement stockés

};

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H
