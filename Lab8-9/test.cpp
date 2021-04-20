#include "test.h"

using std::cout;
using std::ifstream;

bool cmp(const Oferta& a, const Oferta& b)
{
	return a.getDestinatie() < b.getDestinatie();
}

void testDomain()
{
	Oferta o("Tur", "Grecia", "Mare", 100);
	Oferta oGol;

	assert(o.getDenumire() == "Tur");
	assert(o.getDestinatie() == "Grecia");
	assert(o.getTip() == "Mare");
	assert(o.getPret() == 100);

	o.setDenumire("Vacanta de vara");
	o.setDestinatie("Turcia");
	o.setTip("Mare cu soare");
	o.setPret(999);

	assert(o.getDenumire() == "Vacanta de vara");
	assert(o.getDestinatie() == "Turcia");
	assert(o.getTip() == "Mare cu soare");
	assert(o.getPret() == 999);

	Oferta o2("Antalya", "Turcia", "Mare cu soare", 999);
	assert(o == o2);
}

void testRepo()
{
	Repo r;
	Oferta o1("Munte", "Austria", "Resort", 305), o2("Mare", "Bahamas", "Xll-inclusive", 700);

	r.repoAdaugareOferta(o1);

	vector<Oferta> vec = r.getContinut();

	assert(vec.at(0) == o1);

	vector<Oferta> v, vec2;
	r.repoAdaugareOferta(Oferta("Mare", "Bahamas", "Xll-inclusive", 700));

	assert(r.getContinut().at(0) == Oferta ("Munte", "Austria", "Resort", 305));
	assert(r.getContinut().at(1) == Oferta("Mare", "Bahamas", "Xll-inclusive", 700));

	Oferta o3("Litoral", "Mamaia", "Hotel", 50), o4("Mare", "Austria", "Camping cu rulota", 120);
	assert(r.repoExistentaOferta(o3) == false);
	assert(r.repoExistentaOferta(o4) == true);

	vec = r.repoFiltrareDupaDestinatie("ama");
	assert(vec.at(0) == o2);

	vec = r.repoFiltrareDupaDestinatie("a");
	assert(vec.at(0) == o1);
	assert(vec.at(1) == o2);

	vec = r.repoFiltrareDupaDestinatie("ej");
	assert(vec.size() == 0);

	vec = r.repoFiltrareDupaPret(400);
	assert(vec.at(0) == o1);

	vec = r.repoFiltrareDupaPret(1000);
	assert(vec.at(0) == o1);
	assert(vec.at(1) == o2);

	vec = r.repoFiltrareDupaPret(100);
	assert(vec.size() == 0);

	r.repoModificareOferta(o1, "Mare", "Austria", "Camping cu rulota", 120);
	vec2 = r.getContinut();
	assert(vec2.at(0) == o4);

	vec2 = r.getContinut();
	assert(vec2.at(0) == o4);

	r.repoSortareGenerica(false, "destinatie");
	vec2 = r.getContinut();
	assert(vec2.at(0) == o2);
	assert(vec2.at(1) == o4);

	r.repoAdaugareOferta(Oferta("Munte", "Italia", "Camping cu rulota", 50));
	r.repoSortareMultipla(true);
	vec2 = r.getContinut();
	assert(vec2.at(0) == Oferta("Munte", "Italia", "Camping cu rulota", 50));
	assert(vec2.at(1) == o4);
	assert(vec2.at(2) == o2);

	assert(r.getIndexFromOferta(o4) == 1);

	r.repoStergereOferta(Oferta("Munte", "Italia", "Camping cu rulota", 50));
	r.repoStergereOferta(o2);
	assert(r.getContinut().size() == 1);

	Repo r2;
	r2.repoAdaugareOferta(o2);
	r2.repoAdaugareOferta(Oferta("Camping", "Finlanda", "Cort", 20));
	assert(r2.getContinut().size() == 2);

	assert(!(r == r2));

	Repo r3;
	r3.repoAdaugareOferta(o2);
	r3.repoAdaugareOferta(Oferta("Camping", "Estonia", "Cort", 10));

	assert(!(r2 == r3));

	r3.repoModificareOferta(Oferta("Camping", "Estonia", "Cort", 10), "Camping", "Finlanda", "Cort", 20);

	assert(r2 == r3);
}

void testService()
{
	Repo r, r2;
	Validator v;
	Wishlist w;
	Service s{ r, v, w };

	try
	{
		s.srvGenerareWishlist(1);}

	catch (const WishlistError& we)
	{
		assert(we.getCode() == 13);
	}

	try
	{
		s.srvRaport();}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 15);
	}

	Oferta o("Litoral", "Mamaia", "Hotel", 65);

	s.srvAdaugareOferta("Litoral", "Mamaia", "Hotel", 65);
	r2.repoAdaugareOferta(o);
	vector<Oferta> vv = s.srvGetRepoContinut(), vv2;

	vv2 = r2.getContinut();
	sort(vv.begin(), vv.end(), cmp);
	sort(vv2.begin(), vv2.end(), cmp);
	assert(vv2 == vv);

	vector<Oferta> vec, vec2;

	vec = s.srvFiltrareDupaDestinatie("ama");
	vec2 = r.getContinut();
	assert(vec.at(0) == vec2.at(0));

	vec = s.srvFiltrareDupaPret(100);
	vec2 = r.getContinut();
	assert(vec.at(0) == vec2.at(0));

	try
	{
		s.srvAdaugareOferta("Plaja", "Mamaia", "Motel", 50);}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 0);
	}

	s.srvUndo();
	assert(s.srvGetRepoContinut().size() == 0);

	try
	{
		s.srvUndo();}

	catch (const UndoError& ue)
	{
		assert(ue.getCode() == 16);
	}

	s.srvAdaugareOferta("Litoral", "Mamaia", "Hotel", 65);

	try
	{
		s.srvAdaugareOferta("", "Finlanda", "Hotel", 300);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 2);
	}

	try
	{
		s.srvAdaugareOferta("Munte", "", "Hotel", 300);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 3);
	}

	try
	{
		s.srvAdaugareOferta("Munte", "Finlanda", "", 300);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 4);
	}

	try
	{
		s.srvAdaugareOferta("Munte", "Finlanda", "Hotel", -10);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 5);
	}

	try
	{
		s.srvModificareOferta("Munte", "Finlanda", "Estonia", "Hotel", 300);}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 1);
	}

	try
	{
		s.srvStergereOferta("Finlanda");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 6);
	}

	try
	{
		s.srvCautareOferta("Finlanda");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 7);
	}

	try
	{
		s.srvAdaugareWishlist("Finlanda");}

	catch (const WishlistError& we)
	{
		assert(we.getCode() == 10);
	}

	try
	{
		s.srvGenerareWishlist(-1);}

	catch (const WishlistError& we)
	{
		assert(we.getCode() == 12);
	}

	try
	{
		s.srvGenerareWishlist(100);}

	catch (const WishlistError& we)
	{
		assert(we.getCode() == 14);
	}

	s.srvAdaugareWishlist("Mamaia");
	vector <Oferta> vw1, vw2;
	Wishlist w2;
	vw1.push_back(Oferta("Litoral", "Mamaia", "Hotel", 65));
	w2 = s.srvGetWishlist();
	vw2 = w2.getContinut();

	assert(vw1.at(0) == vw2.at(0));

	s.srvGolireWishlist();
	w2 = s.srvGetWishlist();
	vw2 = w2.getContinut();
	assert(vw2.size() == 0);
	assert(w2.getDimensiune() == 0);

	try
	{
		s.srvGolireWishlist();}

	catch (const WishlistError& we)
	{
		assert(we.getCode() == 11);
	}

	assert(s.srvCautareOferta("Mamaia") == 0);

	s.srvModificareOferta("Mamaia", "Plaja", "Mexic", "All-inclusive", 560);
	r2.repoModificareOferta(o, "Plaja", "Mexic", "All-inclusive", 560);
	vv = s.srvGetRepoContinut();
	assert(vv == r2.getContinut());

	Repo r3;
	s.srvAdaugareOferta("Munte", "Austria", "Pensiune", 300);

	s.srvAdaugareWishlist("Mexic");
	s.srvAdaugareWishlist("Austria");

	s.srvExportareWishlist("test");
	ifstream in("test.csv");

	string s1, s2;
	getline(in, s1);
	getline(in, s2);

	assert(s1 == "Plaja,Mexic,All-inclusive,560");
	assert(s2 == "Munte,Austria,Pensiune,300");

	in.close();

	s.srvSortareGenerica("cresc", "denumire");
	r3.repoAdaugareOferta(Oferta("Plaja", "Mexic", "All-inclusive", 560));
	r3.repoAdaugareOferta(Oferta("Munte", "Austria", "Pensiune", 300));
	r3.repoAdaugareOferta(Oferta("Litoral", "Mamaia", "Zotel", 65));

	s.srvAdaugareOferta("Litoral", "Mamaia", "Zotel", 65);
	vv = s.srvGetRepoContinut();

	vv2 = r3.getContinut();
	sort(vv.begin(), vv.end(), cmp);
	sort(vv2.begin(), vv2.end(), cmp);
	assert(vv2 == vv);
	assert(vv == vv2);

	vv2 = r2.getContinut();
	sort(vv2.begin(), vv2.end(), cmp);
	assert(!(vv == vv2));

	Wishlist w1;
	s.srvGenerareWishlist(2);
	w1 = s.srvGetWishlist();
	assert(w1.getDimensiune() == 2);

	try
	{
		s.srvExportareWishlist("/");}

	catch (const WishlistError& we)
	{
		assert(we.getCode() == 15);
	}

	try
	{
		s.srvExportareWishlist("");}

	catch (const WishlistError& we)
	{
		assert(we.getCode() == 15);
	}


	try
	{
		s.srvSortareGenerica("abc", "destinatie");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 9);
	}

	try
	{
		s.srvSortareGenerica("descresc", "abc");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 8);
	}

	s.srvSortareGenerica("descresc", "tip + pret");

	vv2 = r3.getContinut();
	vv = s.srvGetRepoContinut();
	sort(vv.begin(), vv.end(), cmp);
	sort(vv2.begin(), vv2.end(), cmp);
	assert(vv == vv2);


	Oferta o2("Plaja", "Mexic", "All-inclusive", 560);

	s.srvAdaugareOferta("Plaja", "Mangalia", "Hotel", 100);
	s.srvAdaugareOferta("Munte", "Elvetia", "Resort", 2500);
	s.srvAdaugareOferta("City-break", "Viena", "Apatament central", 300);

	s.srvModificareOferta("Viena", "City-break", "Praga", "Apartament central", 300);
	s.srvUndo();
	assert(s.srvGetRepoContinut().at(5).getDestinatie() == "Viena");

	map<string, int> dict = s.srvRaport();
	vector<string> chei;

	for (const auto& el : dict)
		chei.push_back(el.first);

	assert(dict.size() == 4);
	assert(chei.at(0) == "City-break");
	assert(chei.at(1) == "Litoral");
	assert(chei.at(2) == "Munte");
	assert(chei.at(3) == "Plaja");

	assert(dict.at("City-break") == 1);
	assert(dict.at("Litoral") == 1);
	assert(dict.at("Munte") == 2);
	assert(dict.at("Plaja") == 2);

	s.srvStergereOferta("Mangalia");

	s.srvUndo();
	assert(s.srvGetRepoContinut().size() == 6);
	assert(s.srvGetRepoContinut().at(5) == Oferta("Plaja", "Mangalia", "Hotel", 100));

	s.srvStergereOferta("Mangalia");
	s.srvStergereOferta("Elvetia");
	s.srvStergereOferta("Viena");
	s.srvStergereOferta("Mexic");

	r3.repoStergereOferta(o2);
	vv = s.srvGetRepoContinut();
	vv2 = r3.getContinut();
	sort(vv2.begin(), vv2.end(), cmp);
	sort(vv.begin(), vv.end(), cmp);
	assert(vv == vv2);
}

void testUtils()
{
	assert(cmpString("Ala", "Bala", true) == true);
	assert(cmpString("Bala", "Ala", true) == false);
	assert(cmpString("Ala", "Ala", true) == true);

	assert(cmpString("Ala", "Bala", false) == false);
	assert(cmpString("Bala", "Ala", false) == true);
	assert(cmpString("Ala", "Ala", false) == true);

	assert(cmpInt(10, 100, true) == true);
	assert(cmpInt(100, 10, true) == false);
	assert(cmpInt(10, 10, true) == true);

	assert(cmpInt(10, 100, false) == false);
	assert(cmpInt(100, 10, false) == true);
	assert(cmpInt(10, 10, false) == true);

	Oferta o1("Mare", "Mamaia", "Motel", 60), o2("Munte", "Mecklenburg", "Motel", 660);
	assert(comparatorGeneric(o1, o2, "denumire", true) == true);
	assert(comparatorGeneric(o1, o2, "destinatie", false) == false);
	assert(comparatorGeneric(o1, o2, "tip", true) == true);
	assert(comparatorGeneric(o1, o2, "pret", false) == false);

	DomainError de("Eroare Mare!", 404);
	RepoError re("Eroare Mica...", 501);
	WishlistError we("Eroare Mijlocie.", 403);
	UndoError ue("Eroare COLOSALA!!!", 777);

	assert(de.getCode() == 404);
	assert(re.getCode() == 501);
	assert(we.getCode() == 403);
	assert(ue.getCode() == 777);

	assert(de.getMessage() == "Eroare Mare!");
	assert(re.getMessage() == "Eroare Mica...");
	assert(we.getMessage() == "Eroare Mijlocie.");
	assert(ue.getMessage() == "Eroare COLOSALA!!!");
}

void testValidator()
{
	Validator v;

	try
	{
		v.validareCampSortare("anc");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 8);
	}

	try
	{
		v.validareOrdineSortare("abc");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 9);
	}

	try
	{
		v.validareDateOferta("", "Polonia", "Hotel", 500);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 2);
	}

	try
	{
		v.validareDateOferta("Tara", "", "Hotel", 500);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 3);
	}

	try
	{
		v.validareDateOferta("Tara", "Polonia", "", 500);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 4);
	}

	try
	{
		v.validareDateOferta("Tara", "Polonia", "Hotel", -500);}

	catch (const DomainError& de)
	{
		assert(de.getCode() == 5);
	}
}

void testWishlist()
{
	Wishlist wl;
	wl.wlAdaugare(Oferta("Mare", "Olanda", "Hotel de lux", 3000));

	vector <Oferta> v, v2;
	v.push_back(Oferta("Mare", "Olanda", "Hotel de lux", 3000));

	v2 = wl.getContinut();
	assert(v2.at(0) == v.at(0));
	assert(wl.getDimensiune() == 1);

	wl.wlGolire();
	v2 = wl.getContinut();
	assert(v2.size() == 0);
	assert(wl.getDimensiune() == 0);
}

void testRepoLab()
{
	RepoLab r(0);
	Oferta o1("Munte", "Austria", "Resort", 305), o2("Mare", "Bahamas", "Xll-inclusive", 700);

	r.repoAdaugareOferta(o1);

	vector<Oferta> vec = r.getContinut();

	assert(vec.at(0) == o1);

	vector<Oferta> v, vec2;
	r.repoAdaugareOferta(Oferta("Mare", "Bahamas", "Xll-inclusive", 700));

	assert(r.getContinut().at(0) == Oferta("Munte", "Austria", "Resort", 305));
	assert(r.getContinut().at(1) == Oferta("Mare", "Bahamas", "Xll-inclusive", 700));

	Oferta o3("Litoral", "Mamaia", "Hotel", 50), o4("Mare", "Austria", "Camping cu rulota", 120);
	assert(r.repoExistentaOferta(o3) == false);
	assert(r.repoExistentaOferta(o4) == true);

	vec = r.repoFiltrareDupaDestinatie("ama");
	assert(vec.at(0) == o2);

	vec = r.repoFiltrareDupaDestinatie("a");
	assert(vec.at(0) == o1);
	assert(vec.at(1) == o2);

	vec = r.repoFiltrareDupaDestinatie("ej");
	assert(vec.size() == 0);

	vec = r.repoFiltrareDupaPret(400);
	assert(vec.at(0) == o1);

	vec = r.repoFiltrareDupaPret(1000);
	assert(vec.at(0) == o1);
	assert(vec.at(1) == o2);

	vec = r.repoFiltrareDupaPret(100);
	assert(vec.size() == 0);

	r.repoModificareOferta(o1, "Mare", "Austria", "Camping cu rulota", 120);
	vec2 = r.getContinut();
	assert(vec2.at(0) == o4);

	vec2 = r.getContinut();
	assert(vec2.at(0) == o4);

	r.repoSortareGenerica(false, "destinatie");
	vec2 = r.getContinut();
	assert(vec2.at(0) == o2);
	assert(vec2.at(1) == o4);

	r.repoAdaugareOferta(Oferta("Munte", "Italia", "Camping cu rulota", 50));
	r.repoSortareMultipla(true);
	vec2 = r.getContinut();
	assert(vec2.at(0) == Oferta("Munte", "Italia", "Camping cu rulota", 50));
	assert(vec2.at(1) == o4);
	assert(vec2.at(2) == o2);

	assert(r.getIndexFromOferta(o4) == 1);

	r.repoStergereOferta(Oferta("Munte", "Italia", "Camping cu rulota", 50));
	r.repoStergereOferta(o2);
	assert(r.getContinut().size() == 1);

	RepoLab r2(0);
	r2.repoAdaugareOferta(o2);
	r2.repoAdaugareOferta(Oferta("Camping", "Finlanda", "Cort", 20));
	assert(r2.getContinut().size() == 2);

	assert(!(r == r2));

	RepoLab r3(0);
	r3.repoAdaugareOferta(o2);
	r3.repoAdaugareOferta(Oferta("Camping", "Estonia", "Cort", 10));

	assert(!(r2 == r3));

	r3.repoModificareOferta(Oferta("Camping", "Estonia", "Cort", 10), "Camping", "Finlanda", "Cort", 20);

	assert(r2 == r3);

	RepoLab r4(1);
	
	try
	{
		r4.repoAdaugareOferta(Oferta("Camping", "Norvegia", "Cort", 10));}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);
	}

	try
	{
		r4.repoStergereOferta(Oferta("Camping", "Norvegia", "Cort", 10));}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);
	}

	try
	{
		r4.repoModificareOferta(Oferta("Camping", "Norvegia", "Cort", 10), "A", "B", "C", 4);}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);
	}

	try
	{
		r4.repoExistentaOferta(Oferta("Camping", "Norvegia", "Cort", 10));}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);
	}

	try
	{
		r4.getIndexFromOferta(Oferta("Camping", "Norvegia", "Cort", 10));}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);
	}

	try
	{
		r4.repoFiltrareDupaPret(100);}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);}

	try
	{
		r4.repoFiltrareDupaDestinatie("abc");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);
	}

	try
	{
		r4.repoSortareGenerica(true, "pret");}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);
	}

	try
	{
		r4.repoSortareMultipla(false);}

	catch (const RepoError& re)
	{
		assert(re.getCode() == 777);
	}

	assert(r3.getIndexFromOferta(Oferta("Plaja calda", "Grecia", "Apartament", 300)) == -1);
}

void runAllTests()
{
	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Functia ce ruleaza toate testele.
	*/

	testDomain();
	testRepo();
	testRepoLab();
	testValidator();
	testService();
	testWishlist();
	testUtils();
}