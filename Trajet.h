/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : novembre 2019
    copyright            : (C) 2019 par Killian OECHSLIN et Thomas MIGNOT
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
// Classe purement abstraite et classe mère de TrajetSimple et TrajetCompose,
// permettant de regrouper les caractéristiques communes de ces 2 classes
//
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    virtual void AfficherTrajet() const=0;
    // Mode d'emploi : permet d'afficher les caractéristiques propres à un trajet (Simple ou Composé)
    //
    // Contrat : doit être redéfinie dans les classes filles TrajetSimple et TrajetCompose

    char* getVilleDepart() const;
    // Mode d'emploi : renvoie la ville de départ du trajet
    //

    char* getVilleArrivee() const;
    // Mode d'emploi : renvoie la ville d'arrivée du trajet
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

    Trajet ( const char* depart, const char* arrivee );
    // Mode d'emploi : initialise la ville de départ et d'arrivée grâce aux paramètres données
    //

    virtual ~Trajet ( );
    // Mode d'emploi : libère la mémoire utilisée par villeDepart et villeArrivee
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    char* villeDepart; // ville de départ du trajet
    char* villeArrivee; // ville d'arrivée du trajet
};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // TRAJET_H
