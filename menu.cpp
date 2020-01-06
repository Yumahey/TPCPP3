int main()
{
	Catalogue catalogue;
	int choixMenu=0; // stocke le choix de l'utilisateur
	//int valeurRetour=0; // permet de vérifier que l'utilisateur a bien rentré un chiffre valide
	int nbTrajetRentre = 0; // permet de connaître le nombre de trajets simples saisis en une seule fois
	char villeDepart[100]; // stocke la ville de départ rentrée par l'utilisateur
	char villeArrivee[100]; // stocke la ville d'arrivée rentrée par l'utilisateur
	char moyenTransport[100]; // stocke le moyen de transport rentré par l'utilisateur
	char confirmationSuiteTrajet[50]; // permet d'enchaîner plusieurs trajets simples dans le cas de la saisie d'un trajet composé
	Trajet** trajetRentres=new Trajet*[1]; // stocke les trajets saisis (par défaut le tableau est de taille 1)

	//Variables pour les fichiers d'entrés et sorties
	ifstream testIn;//fichier de lecture
	ofstream testOut;//fichier de sauvegarde
	char nomFile[50];
  	char typeTraj;
	char ville1[30];//ville depart selection
	char ville2[30];// ville d'arrivee selection
	int indiceD;
	int indiceF;

	while(1)
	{
		choixMenu=0;
		cout<<"Choix disponibles : "<<endl;
		cout<<"\t(1) Afficher le catalogue"<<endl;
		cout<<"\t(2) Ajouter un trajet au catalogue"<<endl;
		cout<<"\t(3) Rechercher un parcours (Recherche simple)"<<endl;
		cout<<"\t(4) Rechercher un parcours (Recherche complexe)"<<endl;
		cout<< "\t(5) Lecture selective " << endl;
		cout<< "\t(6) Sauvegarde selective " << endl;
   		cout<<"\t(7) Quitter le programme"<<endl;

		//gestion éventuelle des mauvaises saisies
		do
		{


      		cin>>choixMenu;
			cin.ignore(); // enlève le "Entrer" du buffer de lecture


			if( choixMenu <=0 || choixMenu>=8) // entier non valide
			{
				cout<<"Veuillez entrer un nombre valide et strictement positif et strictement inférieur à 6"<<endl;
          		choixMenu=7;
			}
		}
		while(choixMenu <=0 || choixMenu >=8);

		switch(choixMenu)
		{
			case 1:
      			//affichage catalogue
				catalogue.AfficherCatalogue();
				cout<<endl;
				break;

			case 2:
      			//ajout trajet au catalogue
				nbTrajetRentre=0;
				cout<<"Entrez la ville de départ"<<endl;
        		cin.getline(villeDepart,30,'\n');

				cout<<"Entrez la ville de arrivée"<<endl;

        		cin.getline(villeArrivee,30,'\n');
				cout<<"Entrez le moyen de transport"<<endl;

        		cin.getline(moyenTransport,30,'\n');


				++nbTrajetRentre;
				// on copie le trajet dans le tableau
				trajetRentres[nbTrajetRentre-1]=new TrajetSimple(villeDepart,villeArrivee,moyenTransport);

				cout<<"Le trajet a-t-il une suite ?\n\toui\n\tnon"<<endl;

       			cin.getline(confirmationSuiteTrajet,30,'\n');

				while(strcmp(confirmationSuiteTrajet,"oui")==0) // le trajet a une suite
				{
					// si le trajet a une suite, on prend directement comme point de départ la ville d'arrivée du trajet précédent
					strcpy(villeDepart,villeArrivee);
					// on ne demande donc que la ville d'arrivée du prochain trajet
					cout<<"Entrez la ville d'arrivée"<<endl;

          			cin.getline(villeArrivee,30,'\n');
					cout<<"Entrez le moyen de transport"<<endl;

          			cin.getline(moyenTransport,30,'\n');

					++nbTrajetRentre;
					// on agrandit le tableau de trajet
					Trajet** tableauCopie = new Trajet*[nbTrajetRentre];
					for(int i=0;i<nbTrajetRentre-1;i++)
					{
						tableauCopie[i]=trajetRentres[i];
					}
					delete[] trajetRentres;
					trajetRentres = tableauCopie;
					trajetRentres[nbTrajetRentre-1]= new TrajetSimple(villeDepart,villeArrivee,moyenTransport);


					cout<<"Le trajet a-t-il une suite ?\n\toui\n\tnon"<<endl;

          			cin.getline(confirmationSuiteTrajet,30,'\n');
				}

				if(nbTrajetRentre==1) //trajet simple
				{
					catalogue.Ajouter(trajetRentres[0]);
				}
				else //trajet composé
				{
					Trajet* ptr_tc = new TrajetCompose(trajetRentres,nbTrajetRentre);
					catalogue.Ajouter(ptr_tc);
				}

				// réinitialisation pour la prochaine saisie
				delete[] trajetRentres;
				trajetRentres = new Trajet*[1];

				break;

			case 3:
        		//recherche simple
				cout<<endl<<"Recherche simple de parcours : \n\n";
				cout<<"Entrez la ville de départ : ";

       			cin.getline(villeDepart,30,'\n');

				cout<<"Entrez la ville d'arrivée : ";

        		cin.getline(villeArrivee,30,'\n');
				cout<<endl;
				catalogue.RechercheSimple(villeDepart,villeArrivee);
				cout<<endl;
        		break;

			case 4:
      			//recherche complexe
				cout<<"Recherche complexe de parcours : "<<endl;
				cout<<"Entrez la ville de départ : ";

        		cin.getline(villeDepart,30,'\n');
				cout<<endl<<"Entrez la ville d'arrivée : ";

        		cin.getline(villeArrivee,30,'\n');
				cout<<endl;
				catalogue.RechercheAvancee(villeDepart,villeArrivee);
				cout<<endl;
        		break;

			case 5:
				// lecture selelective
				selectionFichier('L', nomFile, typeTraj, ville1, ville2, indiceD, indiceF);
				testIn.open(nomFile);
				catalogue.Lire(testIn, typeTraj, ville1, ville2, indiceD, indiceF);
				break;

			case 6:
				//sauvegarde selective
				// print taille catalogue
        		selectionFichier('S', nomFile, typeTraj, ville1, ville2, indiceD, indiceF);
				testOut.open(nomFile, ios::app);
				catalogue.SelectionTrajet(testOut, typeTraj, ville1, ville2, indiceD, indiceF);
				break;

      		case 7:
          		// fin du programme, on libère la zone mémoire utilisée
        		delete[] trajetRentres;

        		return 0;
        		break;


		}

	}

	return 0;
}
