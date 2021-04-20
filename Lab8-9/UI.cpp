#include "UI.h"

void Console::afisareRepo()
{
	int k = 1;
	vector<Oferta> continut = this->repo.getContinut();

	if (continut.size() == 0)
	{
		cout << "Lista de oferte este vida!\n";

		return;
	}

	cout << "Lista de oferte este:\n";

	for (auto& i: continut)
	{
		cout << k << ": Denumire: " << i.getDenumire() << ", Destinatie: " << i.getDestinatie();
		cout << ", Tip: " << i.getTip() << ", Pret: " << i.getPret() << '\n';
		
		k++;
	}
}

void Console::afisareWishlist()
{
	int k = 1;
	vector<Oferta> continut = this->wl.getContinut();

	if (continut.size() == 0)
	{
		cout << "Wishlist-ul este vid!\n";

		return;
	}

	cout << "Wishlist-ul are urmatoarele " << this->wl.getDimensiune() << " Oferte:\n";

	for (auto& i : continut)
	{
		cout << k << ": Denumire: " << i.getDenumire() << ", Destinatie: " << i.getDestinatie();
		cout << ", Tip: " << i.getTip() << ", Pret: " << i.getPret() << '\n';

		k++;
	}
}

void Console::afisareOfertaDupaIndex(const int index)
{
	const vector<Oferta>& v = this->repo.getContinut();

	cout << index + 1 << ": Denumire: " << v.at(index).getDenumire() << ", Destinatie: " << v.at(index).getDestinatie();
	cout << ", Tip: " << v.at(index).getTip() << ", Pret: " << v.at(index).getPret() << '\n';
}

void Console::afisareVectorOferte(const vector<Oferta>& vec)
{
	if (vec.size() == 0)
	{
		cout << "\nNu exista nicio Oferta cu filtrul dorit!\n";
		return;
	}

	int k = 0;
	cout << '\n';

	for (auto& i: vec)
	{
		cout << k + 1 << ": Denumire: " << i.getDenumire() << ", Destinatie: " << i.getDestinatie();
		cout << ", Tip: " << i.getTip() << ", Pret: " << i.getPret() << '\n';

		k++;
	}
}

void Console::meniuWishlist()
{
	if (system("CLS"))
		system("clear");

	int comanda = -1;
	while (true)
	{
		cout << "=============== MENIU WISHLIST ===============";
		cout << "\n1) Adaugare Oferta existenta in Wishlist.";
		cout << "\n2) Golire Wishlist.";
		cout << "\n3) Generare Wishlist.";
		cout << "\n4) Exportare Wishlist intr-un fisier CSV.";

		cout << "\n0) Intoarcere la meniul principal.";

		cout << "\n\nIntroduceti comanda dorita: ";
		cin >> comanda;

		if (comanda == 1)
		{
			string destinatie;

			cout << "\nIntroduceti destinatia Ofertei pe care doriti sa o adaugati in Wishlist: ";
			cin.get();
			getline(cin, destinatie);

			try
			{
				this->srv.srvAdaugareWishlist(destinatie);

				this->afisareWishlist();
			}

			catch (const WishlistError& we)
			{
				cout << "Eroare Wishlist: " << we.getMessage() << '\n';
			}
		}

		else if (comanda == 2)
		{
			try
			{
				this->srv.srvGolireWishlist();

				cout << "\nWishlist-ul este vid acum!\n";
			}

			catch (const WishlistError& we)
			{
				cout << "Eroare Wishlist: " << we.getMessage() << '\n';
			}
		}

		else if (comanda == 3)
		{
			int deGenerat = -1;

			cout << "\nIntroduceti cate elemente doriti sa generati in Wishlist: ";
			cin >> deGenerat;

			try
			{
				this->srv.srvGenerareWishlist(deGenerat);

				this->afisareWishlist();
			}

			catch (const WishlistError& we)
			{
				cout << "Eroare Wishlist: " << we.getMessage() << '\n';
			}
		}

		else if (comanda == 4)
		{
			string numeFisier;

			cout << "\nIntroduceti numele fisierului in care doriti sa exportati Wishlist-ul  (fara extensie, aceasta va fi automat adaugata):\n";
			cin.get();
			getline(cin, numeFisier);

			try
			{
				this->srv.srvExportareWishlist(numeFisier);

				cout << "\nWishlist-ul a fost exportat in fisierul " << numeFisier << ".csv!\n";
			}

			catch (const WishlistError& we)
			{
				cout << "Eroare Wishlist: " << we.getMessage() << '\n';
			}

		}

		else if (comanda == 0)
		{
			if (system("CLS"))
				system("clear");
			
			return;
		}

		else
			cout << "\nComanda invalida!\n";
	}
}

void Console::afisareRaport(const map<string, int>& dict)
{
	cout << "\nRaportul este:\n";

	int i = 1;
	for (const auto& elem : dict)
	{
		cout << i << ") Denumire: " << elem.first << ", " << elem.second << " Oferte.\n";
		i++;
	}
}

void Console::afisareMeniu()
{
	cout << "=============== AGENTIE DE TURISM ===============";
	cout << "\n1)  Adaugare oferta.";
	cout << "\n2)  Modificare oferta.";
	cout << "\n3)  Stergere oferta.";
	cout << "\n4)  Afisare lista de oferte.";
	cout << "\n5)  Cautare oferta.";
	cout << "\n6)  Filtrare oferte dupa destinatie.";
	cout << "\n7)  Filtrare oferte dupa pret.";
	cout << "\n8)  Sortarea listei de oferte.";
	cout << "\n9)  Accesare meniu pentru wishlist.";
	cout << "\n10) Generare raport denumiri.";
	cout << "\n11) Undo ultima actiune.";

	cout << "\n0)  Inchiderea aplicatiei.";
}

void Console::run()
{
	int comanda = -1;
	while (true)
	{
		comanda = -1;

		afisareMeniu();
		cout << "\n\nIntroduceti comanda dorita: ";
		cin >> comanda;


		if (comanda == 1)
		{
			string denumire, destinatie, tip;
			int pret;

			cout << "\nIntroduceti denumirea ofertei pe care doriti sa o adaugati: ";
			cin.get();
			getline(cin, denumire);

			cout << "\nIntroduceti destinatia ofertei pe care doriti sa o adaugati: ";
			getline(cin, destinatie);

			cout << "\nIntroduceti tipul ofertei pe care doriti sa o adaugati: ";
			getline(cin, tip);

			cout << "\nIntroduceti pretul ofertei pe care doriti sa o adaugati: ";
			cin >> pret;

			try
			{
				this->srv.srvAdaugareOferta(denumire, destinatie, tip, pret);

				cout << "Oferta a fost adaugata!\n";

				this->afisareRepo();
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		}

		else if (comanda == 2)
		{
			string destinatieOld, denumire, destinatie, tip;
			int pret = 0;

			cout << "\nIntroduceti destinatia ofertei pe care doriti sa o modificati: ";

			cin.get();
			getline(cin, destinatieOld);

			cout << "\nIntroduceti noua denumire: ";
			getline(cin, denumire);

			cout << "\nIntroduceti noua destinatie: ";
			getline(cin, destinatie);

			cout << "\nIntroduceti noul tip: ";
			getline(cin, tip);

			cout << "\nIntroduceti noul pret: ";
			cin >> pret;

			try
			{
				this->srv.srvModificareOferta(destinatieOld, denumire, destinatie, tip, pret);

				cout << "Oferta a fost modificata!\n";

				this->afisareRepo();
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		}

		else if (comanda == 3)
		{
			string destinatie;

			cout << "\nIntroduceti destinatia ofertei pe care doriti sa o stergeti: ";
			cin.get();
			getline(cin, destinatie);

			try
			{
				this->srv.srvStergereOferta(destinatie);

				cout << "Oferta a fost stearsa!\n";

				this->afisareRepo();
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		}

		else if (comanda == 4)
			this->afisareRepo();

		else if (comanda == 5)
		{
			string destinatie;

			cout << "\nIntroduceti destinatia ofertei pe care doriti sa o cautati: ";

			cin.get();
			getline(cin, destinatie);

			try
			{
				const int index = this->srv.srvCautareOferta(destinatie);

				cout << "Aceasta oferta exista!\n";
				this->afisareOfertaDupaIndex(index);
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}

		}

		else if (comanda == 6)
		{
			string substr;
			cout << "\nIntroduceti substring-ul dupa care doriti sa faceti filtrarea: ";

			cin.get();
			getline(cin, substr);

			this->afisareVectorOferte(this->srv.srvFiltrareDupaDestinatie(substr));
		}

		else if (comanda == 7)
		{
			int pret;
			cout << "\nIntroduceti pretul dupa care doriti sa faceti filtrarea: ";

			cin >> pret;

			this->afisareVectorOferte(this->srv.srvFiltrareDupaPret(pret));
		}

		else if (comanda == 8)
		{
			try
			{
				cout << "Introduceti campul dupa care doriti sa faceti sortarea (denumire / destinatie / tip + pret): ";
				string camp;

				cin.get();
				getline(cin, camp);

				cout << "Introduceti ordinea in care sa se faca sortarea (cresc / descresc): ";
				string cresc;

				getline(cin, cresc);

				this->srv.srvSortareGenerica(cresc, camp);
				this->afisareRepo();
			}

			catch (const DomainError& de)
			{
				cout << "Eroare Domain: " << de.getMessage() << '\n';
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		}

		else if (comanda == 9)
		{
			this->meniuWishlist();
		}

		else if (comanda == 10)
		{
			try
			{
				this->afisareRaport(this->srv.srvRaport());
			}

			catch (const RepoError& re)
			{
				cout << "Eroare Repo: " << re.getMessage() << '\n';
			}
		}

		else if (comanda == 11)
		{
			try
			{
				this->srv.srvUndo();

				this->afisareRepo();
			}

			catch (const UndoError& ue)
			{
				cout << "Eroare Undo: " << ue.getMessage() << '\n';
			}
		}

		else if (comanda == 0)
		{
			cout << "\nAplicatia se va inchide...\n";
			return;
		}

		else
			cout << "\nComanda invalida!\n";
	}
}