#pragma once

#include <string>

#include "domain.h"
#include "utils.h"

/// <summary>
/// Validatorul aplicatiei
/// </summary>
class Validator
{

public:

	/*
		Parametri de intrare:
			- denumire: string ce reprezinta denumirea Ofertei ce trebuie validata
			- destinatie: string ce reprezinta destinatia Ofertei ce trebuie validata
			- tip: string ce reprezinta tipul Ofertei ce trebuie validata
			- pret: integer ce reprezinta pretul Ofertei ce trebuie validata

		Parametri de iesire:
			-

		Preconditii:
			- denumire, destinatie, tip: string-uri
			- pret: integer

		Postconditii:
			-

		Functia valideaza datele Ofertei si arunca eroare daca vreuna este invalida.
	*/
	void validareDateOferta(const string& denumire, const string& destinatie, const string& tip, const int pret);

	/*
		Parametri de intrare:
			- camp: campul ce trebuie validat

		Parametri de iesire:
			-
		
		Preconditii:
			- camp: string

		Postconditii:
			-

		Functia valideaza campul dupa care se va face sortarea si arunca eroare daca este invalid.
	*/
	void validareCampSortare(const string& camp);

	/*
		Parametri de intrare:
			- ordine: ordinea ce trebuie validata

		Parametri de iesire:
			-

		Preconditii:
			- camp: string

		Postconditii:
			-

		Functia valideaza ordinea dupa care se va face sortarea si arunca eroare daca este invalida.
	*/
	void validareOrdineSortare(const string& ordine);
};