#include "service.h"

void Service::srvAdaugareOferta(const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	try
	{
		this->validator.validareDateOferta(denumire, destinatie, tip, pret);

		Oferta of(denumire, destinatie, tip, pret);

		if (this->repo.repoExistentaOferta(of) == true)
			throw RepoError("Exista deja o Oferta cu aceasta destinatie, deci nu se poate face adaugarea!", 0);

		this->repo.repoAdaugareOferta(of);
		
		this->undoList.push_back(make_unique<UndoAdauga>(this->repo, of));
	}

	catch (...)
	{
		throw;}
}

void Service::srvModificareOferta(const string& destinatieOld, const string& denumire, const string& destinatie, const string& tip, const int pret)
{
	try
	{
		Oferta ofOld("", destinatieOld, "", 0);

		if (this->repo.repoExistentaOferta(ofOld) == false)
			throw RepoError("Nu exista o Oferta cu aceasta destinatie, deci nu se poate face modificarea!", 1);

		else
			ofOld = this->repo.getContinut().at(this->repo.getIndexFromOferta(ofOld));

		this->validator.validareDateOferta(denumire, destinatie, tip, pret);

		this->repo.repoModificareOferta(ofOld, denumire, destinatie, tip, pret);

		this->undoList.push_back(make_unique<UndoModifica>(this->repo, ofOld, Oferta(denumire, destinatie, tip, pret)));
	}

	catch (...)
	{
		throw;}
}

void Service::srvStergereOferta(const string& destinatie)
{

	Oferta of("", destinatie, "", 0);

	if (this->repo.repoExistentaOferta(of) == false)
		throw RepoError("Nu exista o Oferta cu aceasta destinatie, deci nu se poate face stergerea!", 6);

	else
		of = this->repo.getContinut().at(this->repo.getIndexFromOferta(of));

	this->repo.repoStergereOferta(of);

	this->undoList.push_back(make_unique<UndoSterge>(this->repo, of));
}

vector<Oferta> Service::srvGetRepoContinut() const
{
	return this->repo.getContinut();
}

Wishlist Service::srvGetWishlist() const
{
	return this->wishlist;
}

const int Service::srvCautareOferta(const string& destinatie)
{
	Oferta o("", destinatie, "", 0);

	const int index = this->repo.getIndexFromOferta(o);

	if (index == -1)
		throw RepoError("Aceasta Oferta NU exista!", 7);

	else
		return index;}

const vector<Oferta> Service::srvFiltrareDupaDestinatie(const string& substr)
{
	return this->repo.repoFiltrareDupaDestinatie(substr);
}

const vector<Oferta> Service::srvFiltrareDupaPret(const int pret)
{
	return this->repo.repoFiltrareDupaPret(pret);
}

void Service::srvSortareGenerica(const string& ord, const string& camp)
{
	try
	{	
		this->validator.validareCampSortare(camp);
		this->validator.validareOrdineSortare(ord);

		bool cresc = true;
		if (ord == "cresc")
			cresc = true;

		else
			cresc = false;

		if (camp != "tip + pret")
			this->repo.repoSortareGenerica(cresc, camp);

		else
			this->repo.repoSortareMultipla(cresc);
	}

	catch (...)
	{
		throw;}
}

void Service::srvAdaugareWishlist(const string& destinatie)
{
	int index = this->repo.getIndexFromOferta(Oferta("", destinatie, "", 0));

	if (index == -1)
		throw WishlistError("Nu exista o Oferta cu aceasta destinatie in Repo, deci nu se poate adauga in Wishlist!", 10);
	
	else
		this->wishlist.wlAdaugare(this->repo.getContinut().at(index));
}

void Service::srvGolireWishlist()
{
	if (this->wishlist.getDimensiune() == 0)
		throw WishlistError("Nu exista nicio Oferta in Wishlist!", 11);

	else
		this->wishlist.wlGolire();
}

void Service::srvGenerareWishlist(const int deGenerat)
{
	const int sizeRepo = this->repo.getContinut().size();

	if (deGenerat <= 0)
		throw WishlistError("Nu se poate efectua generarea, deoarece numarul dat este invalid!", 12);

	if (sizeRepo == 0)
		throw WishlistError("Repository-ul este gol, deci nu se poate genera un Wishlist!", 13);

	if (sizeRepo < deGenerat)
		throw WishlistError("Numarul dat este mai mare decat numarul de Oferte din repository, deci nu se poate genera un Wishlist!", 14);

	this->wishlist.wlGenerare(deGenerat, this->repo.getContinut());
}

void Service::srvExportareWishlist(const string& numeFisier)
{
	string nume = numeFisier;
	if (nume == "" or nume.find('<') < nume.length() or nume.find('>') < nume.length() or nume.find('\\') < nume.length() or nume.find('|') < nume.length()
		or nume.find(':') < nume.length() or nume.find('"') < nume.length() or nume.find('/') < nume.length() or nume.find('?') < nume.length() or nume.find('*') < nume.length())
		throw WishlistError("Numele de fisier dat este invalid!", 15);

	nume += ".csv";
	ofstream fisier(nume);
	
	vector <Oferta> v = this->wishlist.getContinut();

	for (auto& oferta : v)
	{
		fisier << oferta.getDenumire() << ',' << oferta.getDestinatie() << ',';
		fisier << oferta.getTip() << ',' << oferta.getPret() << '\n';
	}

	fisier.close();
}

Wishlist::Wishlist()
{
	this->continut = {};
	this->dimensiune = 0;
}

vector<Oferta> Wishlist::getContinut() const
{
	return this->continut;
}

int Wishlist::getDimensiune() const
{
	return this->dimensiune;
}

void Wishlist::wlAdaugare(const Oferta& of)
{
	this->continut.push_back(of);
	this->dimensiune++;
}

void Wishlist::wlGolire()
{
	this->continut.clear();
	this->dimensiune = 0;
}

void Wishlist::wlGenerare(const int deGenerat, const vector<Oferta>& continutRepo)
{
	vector<Oferta> cpy = continutRepo;

	generateVec(cpy);
	cpy.resize(deGenerat);

	this->continut = cpy;
	this->dimensiune = cpy.size();
}

map<string, int> Service::srvRaport()
{
	vector<Oferta> vec = this->repo.getContinut();

	if (vec.size() == 0)
		throw RepoError("Repo-ul este gol deci nu se poate genera un raport!", 15);

	map<string, int> dict;

	for (const auto& of : vec)
		dict[of.getDenumire()] = 0;

	for (const auto& of : vec)
		dict[of.getDenumire()]++;

	return dict;
}

void Service::srvUndo()
{
	if (this->undoList.empty())
		throw UndoError("Nu exista nicio actiune in istoric, deci nu se poate efectua Undo!", 16);

	this->undoList.back()->doUndo();

	undoList.pop_back();
}