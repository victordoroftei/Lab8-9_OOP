#include "repo.h"

Repo::Repo()
{
	this->continut = {};
}

vector<Oferta> Repo::getContinut()
{
	return this->continut;
}

bool Repo::operator ==(const Repo& other) const
{
	bool found = false;

	if (this->continut.size() != other.continut.size())
		return false;
			
	for (auto& i : this->continut)
	{
		found = false;

		for (auto& j : other.continut)
			if (i == j)
				found = true;

		if (!found)
			return false;
	}

	return true;
}

void Repo::repoAdaugareOferta(const Oferta& of)
{
	this->continut.push_back(of);
}

bool Repo::repoExistentaOferta(const Oferta& of) const
{
	for (auto& i : this->continut)
	{
		if (i == of)
			return true;
	}

	return false;
}

void Repo::repoStergereOferta(const Oferta& of)
{
	for (auto i = this->continut.begin(); i != this->continut.end(); i++)
		if (*i == of)
		{
			this->continut.erase(i);
			return;
		}
}

void Repo::repoModificareOferta(const Oferta& ofOld, const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	for (auto& i : this->continut)
	{
		if (i == ofOld)
		{
			i.setDenumire(denumire);
			i.setDestinatie(destinatie);
			i.setTip(tip);
			i.setPret(pret);
			return;}}
}

int Repo::getIndexFromOferta(const Oferta& of) const
{
	auto rezultat = find_if(this->continut.begin(), this->continut.end(), [&of](const Oferta& o) -> bool
		{
			return of == o;
		});

	if (rezultat == end(this->continut))
		return -1;

	else
		return distance(this->continut.begin(), rezultat);}	// Distanta de la inceputul continutului la iteratorul rezultat este indexul elementului cautat.

vector<Oferta> Repo::repoFiltrareDupaDestinatie(const string& substr) const
{

	vector<Oferta> vec(this->continut.size());

	auto it = copy_if(this->continut.begin(), this->continut.end(), vec.begin(), [&substr](const Oferta& i) -> bool
		{
			if (i.getDestinatie().find(substr) <= i.getDestinatie().size() - 1)
				return true;

			return false;
		});

	vec.resize(distance(vec.begin(), it));
	// Functia resize redimensioneaza vectorul vec din dimensiunea initiala 
	// (adica cea a lui this->continut) in dimensiunea noua (adica numarul de elemente copiate din this->continut).

	return vec;
}

vector<Oferta> Repo::repoFiltrareDupaPret(const int pret) const
{
	vector<Oferta> vec(this->continut.size());

	auto it = copy_if(this->continut.begin(), this->continut.end(), vec.begin(), [&pret](const Oferta& i) -> bool
		{
			if (i.getPret() <= pret)
				return true;

			return false;
		});

	vec.resize(distance(vec.begin(), it));
	// Functia resize redimensioneaza vectorul vec din dimensiunea initiala 
	// (adica cea a lui this->continut) in dimensiunea noua (adica numarul de elemente copiate din this->continut).

	return vec;
}

void Repo::repoSortareGenerica(const bool cresc, const string camp)
{
	/*unsigned int i = 0, j = 0;
	for (i = 0; i <= this->continut.size() - 2; i++)
		for (j = i + 1; j <= this->continut.size() - 1; j++)
			if (comparatorGeneric(this->continut.at(i), this->continut.at(j), camp, cresc) != 1)
				swap(this->continut.at(i), this->continut.at(j));*/

	sort(this->continut.begin(), this->continut.end(), [&camp, &cresc](const Oferta& of1, const Oferta& of2) 
		{
			return comparatorGeneric(of1, of2, camp, cresc);
		});

}

void Repo::repoSortareMultipla(const bool cresc)
{
	/*unsigned int i = 0, j = 0;
	for (i = 0; i <= this->continut.size() - 2; i++)
		for (j = i + 1; j <= this->continut.size() - 1; j++)
		{
			if (comparatorGeneric(this->continut.at(i), this->continut.at(j), "tip", cresc) == -1)
				swap(this->continut.at(i), this->continut.at(j));

			else if (comparatorGeneric(this->continut.at(i), this->continut.at(j), "tip", cresc) == 0)
				if (comparatorGeneric(this->continut.at(i), this->continut.at(j), "pret", cresc) != 1)
					swap(this->continut.at(i), this->continut.at(j));
		}*/

	sort(this->continut.begin(), this->continut.end(), [&cresc](const Oferta& of1, const Oferta& of2)
		{
			if (of1.getTip() == of2.getTip())
				return comparatorGeneric(of1, of2, "pret", cresc);

			else
				return comparatorGeneric(of1, of2, "tip", cresc);
		});
}