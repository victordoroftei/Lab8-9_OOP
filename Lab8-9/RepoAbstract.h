#pragma once

#include "domain.h"
#include <vector>

using std::vector;

class RepoAbstract
{

public:

	virtual vector<Oferta> getContinut() = 0;

	virtual void repoAdaugareOferta(const Oferta& of) = 0;

	virtual bool repoExistentaOferta(const Oferta& of) const = 0;

	virtual void repoStergereOferta(const Oferta& of) = 0;

	virtual void repoModificareOferta(const Oferta& ofOld, const string& denumire, const string& destinatie, const string& tip, const int pret) = 0;

	virtual int getIndexFromOferta(const Oferta& of) const = 0;

	virtual vector<Oferta> repoFiltrareDupaDestinatie(const string& substr) const = 0;

	virtual vector<Oferta> repoFiltrareDupaPret(const int pret) const = 0;

	virtual void repoSortareGenerica(const bool cresc, const string camp) = 0;

	virtual void repoSortareMultipla(const bool cresc) = 0;

	virtual ~RepoAbstract() = default;

};
