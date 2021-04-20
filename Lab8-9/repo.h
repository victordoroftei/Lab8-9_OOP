#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "domain.h"
#include "utils.h"
#include "RepoAbstract.h"

using std::swap;
using std::find_if;
using std::copy_if;
using std::end;
using std::distance;

/// <summary>
/// Repository-ul de Oferte.
/// </summary>
class Repo : public RepoAbstract
{

private:

	vector<Oferta> continut;

public:

	/*
		Parametri de intrare / iesire:
			-

		Preconditii:
			-

		Postconditii:
			- se va crea un repository vid

		Constructorul pentru obiectele de tip Repo.
	*/
	Repo();

	/*
		Parametri de intrare:
			- repo: repo-ul cu care trebuie comparat repo-ul curent

		Parametri de iesire:
			-

		Preconditii:
			- other: un obiect de tipul Repo

		Postconditii:
			-

		Supraincarcarea operatorului ==
		Functia returneaza true daca obiectul curent este egal cu obiectul other,
		sau false in caz contrar.
	*/
	bool operator ==(const Repo& other) const;

	/*
		Parametri de intrare / iesire:
			-
		
		Preconditii / postconditii:
			-

		Functie getter pentru continutul repository-ului.
	*/
	vector<Oferta> getContinut() override;

	/*
		Parametri de intrare:
			- of: obiect de tipul Oferta, ce trebuie adaugat in continutul repository-ului

		Parametri de iesire:
			- 

		Preconditii:
			- of: obiect de tipul Oferta

		Postconditii:
			- this->continut = this->continut + of

		Functia adauga Oferta transmisa ca parametru in continutul repository-ului.
	*/
	void repoAdaugareOferta(const Oferta& of) override;

	/*	
		Parametri de intrare:
			- of: obiect de tipul Oferta; trebuie sa se verifice daca exista sau nu in continutul repository-ului

		Parametri de iesire:
			-
		
		Preconditii / postconditii:
			-

		Functia verifica daca oferta of exista in continutul repository-ului
		si returneaza true daca da, sau false in caz contrar.
	*/
	bool repoExistentaOferta(const Oferta& of) const override;

	/*
		Parametri de intrare:
			- of: obiect de tipul Oferta, ce trebuie sters din continutul repository-ului.

		Parametri de iesire:
			-

		Preconditii:
			- of: obiect de tipul Oferta ce apartine continutului repository-ului.

		Postconditii:
			- this->continut = this->continut - of
	*/
	void repoStergereOferta(const Oferta& of) override;

	/*
		Parametri de intrare:
			- ofOld: obiect de tipul Oferta, ce trebuie modificat
			- denumire: string, noua denumire a obiectului ce trebuie modificat
			- destinatie: string, noua destinatie a obiectului ce trebuie modificat
			- tip: string, noul tip al obiectului ce trebuie modificat
			- pret: integer, noul pret al obiectului ce trebuie modificat

		Parametri de iesire:
			-

		Preconditii:
			- ofOld: obiect de tipul Oferta
			- denumire, destinatie, tip: string-uri nevide
			- pret: integer pozitiv nenul

		Functia modifica datele ofertei ofOld cu cele noi, date ca parametri.
	*/
	void repoModificareOferta(const Oferta& ofOld, const string& denumire, const string& destinatie, const string& tip, const int pret) override;

	/*
		Parametri de intrare:
			- of: Oferta a carui index trebuie returnat

		Parametri de iesire:
			-

		Preconditii:
			-

		Postconditii:
			-

		Functia returneaza -1 daca Oferta transmisa ca parametru nu exista in repository, sau indexul sau in caz contrar.
	*/
	int getIndexFromOferta(const Oferta& of) const override;

	/*
		Parametri de intrare:
			- substr: string-ul ce reprezinta subsirul dupa care se va realiza filtrarea

		Parametri de iesire:
			-

		Preconditii:
			- substr: string

		Postconditii:
			-

		Functia returneaza un vector de Oferte ce contine toate Ofertele care au in destinatie subsirul dat ca parametru.
	*/
	vector<Oferta> repoFiltrareDupaDestinatie(const string& substr) const override;

	/*
		Parametri de intrare:
			- pret: pretul dupa care se va realiza filtrarea

		Parametri de iesire:
			- 

		Preconditii:
			- pret: integer

		Postconditii:
			-

		Functia returneaza un vector de Oferte ce contine toate Ofertele care au pretul mai mic sau egal cu cel dat ca parametru.
	*/
	vector<Oferta> repoFiltrareDupaPret(const int pret) const override;

	/*
		Parametri de intrare:
			- cresc: ordinea sortarii (crescator = true / descrescator = false)
			- camp: campul dupa care se va face sortarea

		Parametri de iesire:
			-

		Preconditii:
			- cresc: boolean
			- camp: string (denumire / destinatie / tip + pret)

		Functia sorteaza repository-ul in functie de ordinea si campul dat.
	*/
	void repoSortareGenerica(const bool cresc, const string camp) override;

	/*
		Parametri de intrare:
			- cresc: ordinea sortarii

		Parametri de iesire:
			-

		Preconditii:
			-

		Postconditii:
			-

		Functia sorteaza repository-ul dupa doua criterii (tip si pret).
	*/
	void repoSortareMultipla(const bool cresc) override;
};