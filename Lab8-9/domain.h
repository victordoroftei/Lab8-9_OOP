#pragma once

#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::string;

/// <summary>
/// Clasa pentru Ofertele de vacanta
/// </summary>
class Oferta
{

private:

	string denumire, destinatie, tip;
	int pret;

public:

	/*
		Parametri de intrare / parametri de iesire:
			-

		Preconditii / postconditii:
			-

		Constructor default.
	*/
	Oferta() ;

	/*
		Parametri de intrare:
			- denumire: string ce va reprezenta denumirea Ofertei
			- destintie: string ce va reprezenta destinatia Ofertei
			- tip: string ce va reprezenta tipul Ofertei
			- pret: integer ce va reprezenta pretul Ofertei

		Parametri de iesire:
			-

		Preconditii:
			- denumire, destinatie, tip: string-uri nevide
			- pret: integer pozitiv nenul

		Postconditii:
			- se creeaza un obiect de tipul Oferta

		Functia are rol de constructor pentru clasa Oferta.
	*/
	Oferta(const string& denumire, const string& destinatie, const string& tip, const int pret) ;

	/*
		Parametri de intrare / parametri de iesire:
			-

		Preconditii / postconditii:
			-

		Constructorul de copiere pentru clasa Oferta.
	*/
	Oferta(const Oferta& other) ;

	/*
		Parametri de intrare:
			- other: oferta cu care trebuie comparata oferta curenta

		Parametri de iesire:
			-

		Preconditii:
			- other: un obiect de tipul Oferta

		Postconditii:
			-

		Supraincarcarea operatorului == 
		Functia returneaza true daca obiectul curent este egal cu obiectul other,
		sau false in caz contrar.
	*/
	bool operator ==(const Oferta& other) const ;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / posconditii:
			-

		Functia getter pentru pretul unui obiect de tipul Oferta.
	*/
	int getPret() const ;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / posconditii:
			-

		Functia getter pentru denumirea unui obiect de tipul Oferta.
	*/
	string getDenumire() const ;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / posconditii:
			-

		Functia getter pentru destinatia unui obiect de tipul Oferta.
	*/
	string getDestinatie() const ;

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / posconditii:
			-

		Functia getter pentru tipul unui obiect de tipul Oferta.
	*/
	string getTip() const ;

	/*
		Parametri de intrare:
			- newDenumire: noua denumire pentru obiect

		Parametri de iesire:
			-

		Preconditii:
			- newDenumire: string nevid

		Postconditii:
			- this->denumire = newDenumire

		Functia actualizeaza denumirea obiectului curent cu cea noua, trimisa ca parametru.
	*/
	void setDenumire(const string& newDenumire) ;

	/*
		Parametri de intrare:
			- newDestinatie: noua destinatie pentru obiect

		Parametri de iesire:
			-

		Preconditii:
			- newDestinatie: string nevid

		Postconditii:
			- this->destinatie = newDestinatie

		Functia actualizeaza destinatia obiectului curent cu cea noua, trimisa ca parametru.
	*/
	void setDestinatie(const string& newDestinatie) ;

	/*
		Parametri de intrare:
			- newTip: noul tip pentru obiect

		Parametri de iesire:
			-

		Preconditii:
			- newTip: string nevid

		Postconditii:
			- this->tip = newTip

		Functia actualizeaza tipul obiectului curent cu cel nou, trimis ca parametru.
	*/
	void setTip(const string& newTip) ;

	/*
		Parametri de intrare:
			- newPret: noul pret pentru obiect

		Parametri de iesire:
			-

		Preconditii:
			- newPret: integer pozitiv nenul

		Postconditii:
			- this->pret = newPret

		Functia actualizeaza pretul obiectului curent cu cel nou, trimis ca parametru.
	*/
	void setPret(const int newPret) ;
};