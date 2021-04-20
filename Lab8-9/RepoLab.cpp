#include "RepoLab.h"

vector<Oferta> RepoLab::getContinut()
{
	vector<Oferta> vec;
	for (auto& per : this->continut)
		vec.push_back(per.second);

	return vec;
}

bool RepoLab::operator ==(const RepoLab& other) const
{
	bool found = false;

	if (this->continut.size() != other.continut.size())
		return false;

	for (auto& per1 : this->continut)
	{
		found = false;

		for (auto& per2 : other.continut)
			if (per1.first == per2.first and per1.second == per2.second)
				found = true;

		if (!found)
			return false;
	}

	return true;
}

void RepoLab::repoAdaugareOferta(const Oferta& of)
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

	this->continut[of.getDestinatie()] = of;
}

bool RepoLab::repoExistentaOferta(const Oferta& of) const
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

	for (auto& per : this->continut)
	{
		if (per.second == of)
			return true;
	}

	return false;
}

void RepoLab::repoStergereOferta(const Oferta& of)
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

	this->continut.erase(of.getDestinatie());
}

void RepoLab::repoModificareOferta(const Oferta& ofOld, const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

	unordered_map<string, Oferta> nou;
	for (auto& per : this->continut)
	{
		if (!(per.second == ofOld))
			nou[per.first] = per.second;

		else
		{
			per.second.setDenumire(denumire);
			per.second.setDestinatie(destinatie);
			per.second.setTip(tip);
			per.second.setPret(pret);

			nou[destinatie] = per.second;
		}
	}

	this->continut = nou;
}

int RepoLab::getIndexFromOferta(const Oferta& of) const
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

	int index = 0;
	for (auto& p : this->continut)
	{
		if (p.second == of)
			return index;

		index++;
	}

	return -1;
}

vector<Oferta> RepoLab::repoFiltrareDupaDestinatie(const string& substr) const
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

	vector<Oferta> vec;

	for (auto& per : this->continut)
	{
		if (per.first.find(substr) <= per.first.size() - 1)
			vec.push_back(per.second);
	}

	return vec;
}

vector<Oferta> RepoLab::repoFiltrareDupaPret(const int pret) const
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

	vector<Oferta> vec;

	for (auto& per : this->continut)
	{
		if (per.second.getPret() <= pret)
			vec.push_back(per.second);
	}

	return vec;
}

void RepoLab::repoSortareGenerica(const bool cresc, const string camp)
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

	/*unsigned int i = 0, j = 0;
	for (i = 0; i <= this->continut.size() - 2; i++)
		for (j = i + 1; j <= this->continut.size() - 1; j++)
			if (comparatorGeneric(this->continut.at(i), this->continut.at(j), camp, cresc) != 1)
				swap(this->continut.at(i), this->continut.at(j));*/

	vector<Oferta> vec;

	for (auto& per : this->continut)
		vec.push_back(per.second);

	this->continut.clear();

	sort(vec.begin(), vec.end(), [&camp, &cresc](const Oferta& of1, const Oferta& of2)
		{
			return comparatorGeneric(of1, of2, camp, cresc);
		});

	for (auto& of : vec)
		this->continut[of.getDestinatie()] = of;
}

void RepoLab::repoSortareMultipla(const bool cresc)
{
	const double pb = static_cast<double>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
	if (pb < this->prob)
		throw (RepoError("Se pare ca astazi nu aveti noroc!", 777));

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

	vector<Oferta> vec;

	for (auto& per : this->continut)
		vec.push_back(per.second);

	this->continut.clear();

	sort(vec.begin(), vec.end(), [&cresc](const Oferta& of1, const Oferta& of2)
		{
			if (of1.getTip() == of2.getTip())
				return comparatorGeneric(of1, of2, "pret", cresc);

			else
				return comparatorGeneric(of1, of2, "tip", cresc);
		});

	for (auto& of : vec)
		this->continut[of.getDestinatie()] = of;
}