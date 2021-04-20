#include "domain.h"

Oferta::Oferta()
{
	this->denumire = "";
	this->destinatie = "";
	this->tip = "";
	this->pret = 0;
}

Oferta::Oferta(const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	this->denumire = denumire;
	this->destinatie = destinatie;
	this->tip = tip;
	this->pret = pret;
}

Oferta::Oferta(const Oferta& other)
{
	this->denumire = other.denumire;
	this->destinatie = other.destinatie;
	this->tip = other.tip;
	this->pret = other.pret;
}

bool Oferta::operator ==(const Oferta& other) const
{
	return other.destinatie == this->destinatie;
}

int Oferta::getPret() const 
{
	return this->pret;
}

string Oferta::getDenumire() const 
{
	return this->denumire;
}

string Oferta::getDestinatie() const 
{
	return this->destinatie;
}

string Oferta::getTip() const 
{
	return this->tip;
}

void Oferta::setDenumire(const string& newDenumire) 
{
	this->denumire = newDenumire;
}

void Oferta::setDestinatie(const string& newDestinatie) 
{
	this->destinatie = newDestinatie;
}

void Oferta::setTip(const string& newTip) 
{
	this->tip = newTip;
}

void Oferta::setPret(const int newPret) 
{
	this->pret = newPret;
}