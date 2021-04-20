#pragma once

#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <gsl/gsl>

#include "domain.h"

using std::string;
using std::vector;

/*
	Parametri de intrare:
		- of1: prima Oferta ce trebuie comparata
		- of2: a doua Oferta ce trebuie comparata
		- camp: campul dupa care se va realiza comparatia
		- cresc: ordinea comparatiei (crescatoare sau descrescatoare)

	Parametri de iesire:
		- 

	Preconditii:
		- of1, of2: obiecte de tipul Oferta
		- camp: string (denumire / desinatie / tip + pret)
		- cresc: boolean (crescator = true, descrescator = false)

	Postconditii:
		- 
	
	Functia are rolul de a compara generic doua obiecte de tipul Oferta, in functie de campul si ordinea data.
*/
bool comparatorGeneric(const Oferta& of1, const Oferta& of2, const string& camp, const bool cresc);

/*
	Parametri de intrare:
		- str1: primul string ce trebuie comparat
		- str2: al doilea string ce trebuie comparat
		- cresc: ordinea compararii

	Parametri de iesire:
		-

	Preconditii:
		- str1, str2: string-uri
		- cresc: boolean

	Postconditii:
		-

	Functia compara doua string-uri in functie de ordinea data.
*/
bool cmpString(const string& str1, const string& str2, const bool cresc);

/*
	Parametri de intrare:
		- num1: primul numar ce trebuie comparat
		- num2: al doilea numar ce trebuie comparat

	Parametri de iesire:
		-

	Preconditii:
		- num1, num2: integeri pozitivi nenuli
		- cresc: boolean

	Postconditii:
		- 

	Functia compara doi integeri in functie de ordinea data.
*/
bool cmpInt(const int num1, const int num2, const bool cresc);

class DomainError
{

private:

	string message;
	int code;

public:

	/*
		Parametri de intrare:
			- message: string-ul ce reprezinta mesajul de eroare
			- code: codul ce reprezinta codul erorii

		Parametri de iesire:
			-

		Preconditii:
			- message: string
			- code: integer pozitiv

		Constructorul clasei DomainError.
	*/
	DomainError(const string& message, int code);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru mesajul de eroare.
	*/
	string getMessage() const;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru codul de eroare.
	*/
	int getCode() const;

};

class RepoError
{

private:

	string message;
	int code;

public:

	/*
		Parametri de intrare:
			- message: string-ul ce reprezinta mesajul de eroare
			- code: codul ce reprezinta codul erorii

		Parametri de iesire:
			-

		Preconditii:
			- message: string
			- code: integer pozitiv

		Constructorul clasei RepoError.
	*/
	RepoError(const string& message, int code);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru mesajul de eroare.
	*/
	string getMessage() const;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru codul de eroare.
	*/
	int getCode() const;

};

class WishlistError
{

private:

	string message;
	int code;

public:

	/*
		Parametri de intrare:
			- message: string-ul ce reprezinta mesajul de eroare
			- code: codul ce reprezinta codul erorii

		Parametri de iesire:
			-

		Preconditii:
			- message: string
			- code: integer pozitiv

		Constructorul clasei WishlistError.
	*/
	WishlistError(const string& message, int code);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru mesajul de eroare.
	*/
	string getMessage() const;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru codul de eroare.
	*/
	int getCode() const;

};

class UndoError
{

private:

	string message;
	int code;

public:

	/*
		Parametri de intrare:
			- message: string-ul ce reprezinta mesajul de eroare
			- code: codul ce reprezinta codul erorii

		Parametri de iesire:
			-

		Preconditii:
			- message: string
			- code: integer pozitiv

		Constructorul clasei UndoError.
	*/
	UndoError(const string& message, int code);

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru mesajul de eroare.
	*/
	string getMessage() const;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia de getter pentru codul de eroare.
	*/
	int getCode() const;

};

/*
	Parametri de intrare:
		- v: vectorul ce trebuie shuffle-uit

	Parametri de iesire:
		- v: vectorul shuffle-uit

	Preconditii:
		- v: vector<Oferta>

	Postconditii:
		- v: vectorul shuffle-uit

	Functia da shuffle vectorului v, transmis ca parametru.
*/
void generateVec(vector<Oferta>& v);