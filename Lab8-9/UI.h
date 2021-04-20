#pragma once

#include <iostream>
#include <cstdlib>
#include <map>

#include "RepoAbstract.h"
#include "service.h"
#include "utils.h"

using std::cout;
using std::cin;
using std::map;

class Console
{

private:

	Service& srv;
	RepoAbstract& repo;
	Validator& validator;
	Wishlist& wl;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia afiseaza repository-ul.
	*/
	void afisareRepo();

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia afiseaza wishlist-ul.
	*/
	void afisareWishlist();

	/*
		Parametri de intrare:
			- index: integer ce reprezinta indexul Ofertei ce trebuie afisata

		Parametri de iesire:
			-

		Preconditii / postconditii:
			-

		Functia afiseaza Oferta din repository cu indexul dat.
	*/
	void afisareOfertaDupaIndex(const int index);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia ce afiseaza meniul.
	*/
	void afisareMeniu();

	/*
		Parametri de intrare:
			- vec: vectorul de Oferte ce trebuie afisat

		Parametri de iesire:
			- 

		Preconditii:
			- vec: vector de Oferte

		Postconditii:
			-

		Functia afiseaza vectorul de Oferte.
	*/
	void afisareVectorOferte(const vector<Oferta>& vec);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia ce serveste pe post de meniu pentru operatiuni pe Wishlist
	*/
	void meniuWishlist();

	/*
		Parametri de intrare:
			- dict: map-ul ce trebuie afisat

		Parametri de iesire:
			-

		Preconditii:
			- dict: map<string, int>

		Postconditii:
			-

		Functia afiseaza raportul generat sub forma unui dictionar ordonat.
	*/
	void afisareRaport(const map<string, int>& dict);

public:

	/*
		Constructorul clasei Console.
	*/
	Console(Service& s, RepoAbstract& r, Validator& v, Wishlist& w) : srv{ s }, repo{ r }, validator{ v }, wl{w} {};

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			- 

		Functia ce serveste pe post de consola / meniu.
	*/
	void run();	

};