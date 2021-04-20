#include "validator.h"

void Validator::validareDateOferta(const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	if (denumire == "")
		throw DomainError("Denumirea Ofertei este invalida!", 2);

	if (destinatie == "")
		throw DomainError("Destinatia Ofertei este invalida!", 3);


	if (tip == "")
		throw DomainError("Tipul Ofertei este invalid!", 4);

	if (pret <= 0)
		throw DomainError("Pretul Ofertei este invalid!", 5);
}

void Validator::validareCampSortare(const string& camp)
{
	if (camp != "denumire" and camp != "destinatie" and camp != "tip + pret")
		throw RepoError("Campul pentru sortare este invalid!", 8);
}

void Validator::validareOrdineSortare(const string& ordine)
{
	if (ordine != "cresc" and ordine != "descresc")
		throw RepoError("Ordinea pentru sortare este invalida!", 9);
}
