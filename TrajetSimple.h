/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : novembre 2019
    copyright            : (C) 2019 par Killian OECHSLIN et Thomas MIGNOT
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined (TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <trajetSimple>
// Cette classe permet de modéliser un trajet simple, c'est à dire un trajet élémentaire
// partant d'une ville A et allant à une ville B avec 1 seul moyen de transport
//
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    char* getTransport() const;
    // Mode d'emploi : Retourne le moyen de transport du trajet simple
    //

    virtual void AfficherTrajet() const;
    // Mode d'emploi : Affiche le trajet simple correspondant sur la sortie standard : ville de départ, ville d'arrivée, moyen de transport
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple (const char* depart,const char* arrive ,const char * moyenTransport);
    // Mode d'emploi : Construit un trajet simple qui contient une ville de départ, une ville d'arrivée et un moyen de transport
    //

      virtual ~TrajetSimple ( );
    // Mode d'emploi : libère la zone mémoire correspondant aux attributs du trajet simple
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	char* moyenTransport;

};

//-------------------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJETSIMPLE_H
