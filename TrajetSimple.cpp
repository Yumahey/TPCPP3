//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

char* TrajetSimple::getTransport() const
{
	return this->moyenTransport;
}

void TrajetSimple::AfficherTrajet () const
{
	cout << " de " << this->villeDepart << " à " << this->villeArrivee << " en " << this->moyenTransport;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

TrajetSimple::TrajetSimple (const char* depart,const char* arrive,const char* moyenTransport)
 : Trajet(depart, arrive)
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
	this->moyenTransport = new char [strlen(moyenTransport) + 1];
	strcpy(this->moyenTransport, moyenTransport);

} //----- Fin de TrajetSimple

TrajetSimple::~TrajetSimple ( )
{
	#ifdef MAP
	    cout << "Appel au destructeur de <TrajetSimple>" << endl;
	#endif
	delete[] this->moyenTransport ;
} //----- Fin de ~TrajetSimple


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
