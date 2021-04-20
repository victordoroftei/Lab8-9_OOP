#include <iostream>
#include <crtdbg.h>

#include "test.h"
#include "UI.h"

/*
    6 Agentie de turism
    Creati o aplicatie care permite:
        · gestiunea unei liste de oferte turistice. Oferta: denumire, destinatie, tip, pret
        · adaugare, stergere, modificare si afisare oferte turistice
        · cautare oferta
        · filtrare oferte turistice dupa: destinatie, pret
        · sortare oferte dupa: denumire, destinatie, tip + pret
*/

int main()
{

    {
        runAllTests();
        Validator v;
        Repo r;
        RepoLab r2(0.1);
        Wishlist w;
        Service s1{ r, v, w };
        Service s2{ r2, v, w };
        Console c1{ s1, r, v, w }, c2{ s2, r2, v, w };

        // c1.run();
         c2.run();
    }

    _CrtDumpMemoryLeaks();
    return 0;
}