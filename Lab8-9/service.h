#pragma once

#include <fstream>
#include <map>

#include "RepoAbstract.h"
#include "validator.h"
#include "undo.h"

using std::ofstream;
using std::map;
using std::make_unique;
using std::unique_ptr;

class Wishlist;
class Service;

/// <summary>
/// Serivce-ul (controller-ul) aplicatiei
/// </summary>
class Service
{

private:

	RepoAbstract& repo;
	Validator& validator;
	Wishlist& wishlist;
	vector<unique_ptr<ActiuneUndo>> undoList;

public:

	/*
		Parametri de intrare:
			- r: repository-ul ce trebuie asignat service-ului
			- v: validatorul ce trebuie asignat service-ului

		Parametri de iesire:
			-

		Preconditii:
			- r: obiect de tipul Repo
			- v: obiect de tipul Validator

		Postconditii:
			- this->repo = r
			- this->validator = v

		Constructorul clasei Service.
	*/
	Service(RepoAbstract& r, Validator& v, Wishlist& w) : repo{ r }, validator{ v }, wishlist{ w } {};

	/*
		Parametri de intrare:
			- denumire: string ce reprezinta denumirea Ofertei ce trebuie adaugata
			- destinatie: string ce reprezinta destinatia Ofertei ce trebuie adaugata
			- tip: string ce reprezinta tipul Ofertei ce trebuie adaugata
			- pret: integer ce reprezinta pretul Ofertei ce trebuie adaugata

		Parametri de iesire:
			-

		Preconditii:
			- denumire, destinatie, tip: string-uri
			- pret: integer

		Postconditii:
			- daca datele sunt valide, se creeaza si adauga in repository o Oferta cu datele transmise ca parametri

		Functia valideaza datele noii oferte, si daca totul este in regula, creeaza o Oferta cu aceste date
		si o trimite repository-ului pentru a fi adaugata.
	*/
	void srvAdaugareOferta(const string& denumire, const string& destinatie, const string& tip, const int pret);

	/*
		Parametri de intrare:
			- destinatieOld: string ce reprezinta destinatia Ofertei ce ar trebui sa fie modificata
			- denumire: string ce reprezinta noua denumire a Ofertei ce trebuie modificata
			- destinatie: string ce reprezinta noua destinatie a Ofertei ce trebuie modificata
			- tip: string ce reprezinta noul tip al Ofertei ce trebuie modificata
			- pret: integer ce reprezinta noul pret al Ofertei ce trebuie modificata

		Parametri de iesire:
			-

		Preconditii:
			- destinatieOld, denumire, destinatie, tip: string-uri
			- pret: integer

		Postconditii:
			- daca toate datele sunt valide, se modifica in repository Oferta cu destinatia destinatieOld

		Functia valideaza existenta Ofertei cu destinatia destinatieOld. Daca exista, se valideaza noile date,
		si daca totul este in regula, se modifica in repository Oferta.
	*/
	void srvModificareOferta(const string& destinatieOld, const string& denumire, const string& destinatie, const string& tip, const int pret);

	/*
		Parametri de intrare:
			- destinatie: string-ul dupa care trebuie stersa Oferta

		Parametri de iesire:
			-

		Preconditii:
			- destinatie: string

		Postconditi:
			- daca Oferta cu destinatia transmisa ca parametru exista, va fi stearsa din repository

		Functia sterge Oferta cu destinatia transmisa ca parametru, daca aceasta exista in repository.
	*/
	void srvStergereOferta(const string& destinatie);

	/*
		Parametri de intrare:
			- destinatie: string ce reprezinta destinatia Ofertei ce trebuie cautate

		Parametri de iesire:
			-

		Preconditii:
			- destinatie: string

		Postconditii:
			-

		Functia cauta in repository Oferta cu destinatia data si arunca eroare daca nu exista,
		sau ii returneaza indexul daca exista.
	*/
	const int srvCautareOferta(const string& destinatie);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru Repository-ul Service-ului.
	*/
	vector<Oferta> srvGetRepoContinut() const;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru  UndoList-ul Service-ului.
	*/
	vector<ActiuneUndo*> srvGetUndoList() const;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru Wishlist-ul Service-ului.
	*/
	Wishlist srvGetWishlist() const;

	/*
		Parametri de intrare:
			- substr: subsirul dupa care se va realiza filtrarea

		Parametri de iesire:
			-

		Preconditii:
			- substr: string

		Postconditii:
			-

		Functia are rolul de a valida subsirul transmis ca parametru
		si de a apela functii din repository pentru filtrare.
	*/
	const vector<Oferta> srvFiltrareDupaDestinatie(const string& substr);

	/*
		Parametri de intrare:
			- pret: pretul dupa care se va realiza filtrarea

		Parametri de iesire:
			-

		Preconditii:
			- pret: integer

		Postconditii:
			-

		Functia are rolul de a valida pretul transmis ca parametru si de a apela functii din repository pentru filtrare.
	*/
	const vector<Oferta> srvFiltrareDupaPret(const int pret);

	/*
		Parametri de intrare:
			- ord: ordinea sortarii
			- camp: string

		Parametri de iesire:
			-
		Preconditii:
			- ord: string
			- camp: string

		Postconditii:
			-

		Functia are rolul de a valida campul transmis ca parametru
		si de a apela functii din repository ce sorteaza lista de Oferte.
	*/
	void srvSortareGenerica(const string& ord, const string& camp);

	/*
		Parametri de intrare:
			- destinatie: string-ul destinatiei Ofertei ce trebuie adaugata

		Parametri de iesire:
			- 

		Preconditii:
			- destinatie: string

		Postconditii:
			- this->wishlist->continut = this->wishlist->continut + Oferta cu destinatia data ca parametru

		Functia adauga o Oferta ce trebuie sa existe deja in Repository, cu destinatia data, in Wishlist.
	*/
	void srvAdaugareWishlist(const string& destinatie);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			- 

		Functia goleste tot ce se afla in Wishlist.
	*/
	void srvGolireWishlist();

	/*
		Parametri de intrare:
			- deGenerat: numar ce reprezinta cate Oferte trebuie generate in Wishlist

		Parametri de iesire:
			-

		Preconditii:
			- deGenerat: integer

		Postconditii:
			- this->wishlist = Wishlist cu deGenerat Oferte random din Repository

		Functia genereaza deGenerat Oferte random din Repository si le pune in Wishlist.
	*/
	void srvGenerareWishlist(const int deGenerat);

	/*
		Parametri de intrare:
			- numeFisier: numele fisierului in care se va exporta Wishlist-ul

		Parametri de iesire
			-

		Preconditii:
			- numeFisier: string

		Postconditii:
			- numeFisier.csv (daca e valid) va contine Wishlist-ul exportat

		Functia exporta Wishlist-ul in fisierul dat ca parametru, cu extensia ".csv". 
	*/
	void srvExportareWishlist(const string& numeFisier);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia genereaza un raport sub forma unui dictionar ordonat (map), care va contine
		numarul de Oferte pentru fiecare denumire din Repository.
	*/
	map<string, int> srvRaport();

	/*
		Parametri de intrare / iesire:
			-

		Preconditii:
			-

		Postconditii:
			- repository-ul va avea efectuata actiunea de undo

		Functia efectueaza undo-ul, asigurand faptul ca undoList-ul este nevid si aruncand exceptie in caz contrar.
	*/
	void srvUndo();
};

/// <summary>
/// Clasa pentru Wishlist (cosul de cumparaturi).
/// </summary>
class Wishlist
{

private:

	vector <Oferta> continut;
	int dimensiune;

public:
	
	/*
		Constructorul clasei Wishlist.
	*/
	Wishlist();

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			- 

		Functie de getter pentru continutul Wishlist-ului.
	*/
	vector <Oferta> getContinut() const;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			- 

		Functie de getter pentru dimensiunea Wishlist-ului.
	*/
	int getDimensiune() const;

	/*
		Parametri de intrare:
			- of: Oferta ce trebuie adaugata in Wishlist

		Parametri de iesire:
			-

		Preconditii:
			- of: Oferta ce exista deja in Repository

		Postconditii:
			- this->wishlist = this->wishlist + Oferta

		Functia adauga Oferta data in Wishlist.
	*/
	void wlAdaugare(const Oferta& of);

	/*
		Parametri de intrare:
			- 

		Parametri de iesire:
			-

		Preconditii:
			-

		Postconditii:
			- this->wishlist = vid;
	*/
	void wlGolire();

	/*
		Parametri de intrare:
			- deGenerat: numarul de Oferte ce trebuie generat in Wishlist
			- continutRepo: lista de Oferte din Repository

		Parametri de iesire:
			-

		Preconditii:
			- deGenerat: integer pozitiv nenul, mai mic decat continutRepo.size()
			- continutRepo: vector<Oferta>

		Functia genereaza in Wishlist deGenerat Oferte ce exista in Repository.
	*/
	void wlGenerare(const int deGenerat, const vector<Oferta>& continutRepo);
};