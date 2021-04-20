#pragma once

#include "domain.h"
#include "repo.h"

class ActiuneUndo
{

public:

	/*
		Functia virtuala generala pentru doUndo.
	*/
	virtual void doUndo() = 0;

	/*
		Destructorul clasei ActiuneUndo.

		Din moment ce clasele UndoAdauga, UndoModifica si UndoSterge mostenesc de la ActiuneUndo,
		aceasta functie este destructor si pentru acele clase.
	*/
	virtual ~ActiuneUndo(){};

};

class UndoAdauga : public ActiuneUndo
{
	

public:

	Oferta ofertaAdaugata;
	RepoAbstract& repo;

	/*
		Parametri de intrare:
			- r: Repository-ul pe care se va face actiunea de undo
			- of: Oferta ce trebuie stearsa inapoi

		Parametri de iesire:
			-

		Preconditii:
			- r: Repository
			- of: Oferta

		Postconditii:
			-

		Constructorul clasei UndoAdaugare.
	*/
	UndoAdauga(RepoAbstract& r, const Oferta& of) : repo{ r }, ofertaAdaugata{ of } {};

	/*
		Parametri de intrare / iesire:
			-

		Preconditii:
			-

		Postconditii:
			- repo = repo - ofertaAdaugata

		Functia de efectuare a undo-ului.
	*/
	void doUndo() override
	{
		repo.repoStergereOferta(ofertaAdaugata);
	}

};

class UndoModifica : public ActiuneUndo
{

public:

	Oferta ofertaVeche, ofertaNoua;
	RepoAbstract& repo;

	/*
		Parametri de intrare:
			- r: Repository-ul pe care se va face actiunea de undo
			- of: Oferta ce trebuie modificata inapoi

		Parametri de iesire:
			-

		Preconditii:
			- r: Repository
			- of: Oferta

		Postconditii:
			-

		Constructorul clasei UndoModifica.
	*/
	UndoModifica(RepoAbstract& r, const Oferta& ofV, const Oferta& ofN) : repo{ r }, ofertaVeche{ ofV }, ofertaNoua{ ofN } {};

	/*
		Parametri de intrare / iesire:
			-

		Preconditii:
			-

		Postconditii:
			- repo = repo - ofertaNoua + ofertaVeche

		Functia de efectuare a undo-ului.
	*/
	void doUndo() override
	{
		repo.repoModificareOferta(ofertaNoua, ofertaVeche.getDenumire(), ofertaVeche.getDestinatie(), ofertaVeche.getTip(), ofertaVeche.getPret());
	}

};

class UndoSterge : public ActiuneUndo
{

public:

	Oferta ofertaStearsa;
	RepoAbstract& repo;

	/*
		Parametri de intrare: 
			- r: Repository-ul pe care se va face actiunea de undo
			- of: Oferta ce trebuie adaugata inapoi

		Parametri de iesire:
			- 

		Preconditii:
			- r: Repository
			- of: Oferta

		Postconditii:
			- 

		Constructorul clasei UndoSterge.
	*/
	UndoSterge(RepoAbstract& r, const Oferta& of) : repo{ r }, ofertaStearsa{ of } {};

	/*
		Parametri de intrare / iesire:
			-

		Preconditii:
			-

		Postconditii:
			- repo = repo + ofertaStearsa

		Functia de efectuare a undo-ului.
	*/
	void doUndo() override
	{
		repo.repoAdaugareOferta(ofertaStearsa);
	}

};