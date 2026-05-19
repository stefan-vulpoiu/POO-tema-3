#include "Meniu.h"
#include "CasaSmart.h"
#include "DispozitivFactory.h"
#include "Utilitare.h"
#include "BecRgb.h"
#include <iostream>
#include <string>

void Meniu::ruleaza()
{
    //luam instanta unica de CasaSmart (Singleton)
    CasaSmart& casa = CasaSmart::getInstanta();
    int optiune;

    //initializam casa cu cateva dispozitive la pornire
    casa += DispozitivFactory::creazaDispozitiv(1, "LuminaSufragerie");
    casa += DispozitivFactory::creazaDispozitiv(2, "TermostatCentral");
    casa += DispozitivFactory::creazaDispozitiv(3, "TV_Living");
    casa += DispozitivFactory::creazaDispozitiv(4, "Frigider_Bucatarie");

    do {
        std::cout << "\n--- MENIU CASA SMART ---\n";
        std::cout << "1. Adauga un dispozitiv\n";
        std::cout << "2. Afiseaza toate dispozitivele\n";
        std::cout << "3. Declanseaza mod SEARA\n";
        std::cout << "4. Declanseaza mod DIMINEATA\n";
        std::cout << "5. Cate becuri RGB avem? (Test functie Template)\n";
        std::cout << "6. Seteaza manual un dispozitiv\n";
        std::cout << "7. Elimina un dispozitiv\n";
        std::cout << "8. Schimba canalul la Televizor\n";
        std::cout << "0. Iesire\n";
        std::cout << "Alege: ";
        std::cin >> optiune;

        switch (optiune)
        {
            case 1:
            {
                int tip;
                std::string nume;
                std::cout << "Ce dispozitiv adaugi? (1=Bec, 2=Termostat, 3=Televizor, 4=Frigider, 5=Aer Conditionat): ";
                std::cin >> tip;
                std::cout << "Numele noului dispozitiv: ";
                std::cin >> nume;

                DispozitivSmart* nou = DispozitivFactory::creazaDispozitiv(tip, nume);
                if (nou) {
                    casa += nou;
                    std::cout << "-> Dispozitiv creat si adaugat!\n";
                } else {
                    std::cout << "-> Tip invalid!\n";
                }
                break;
            }
            case 2:
                casa.afiseazaToate();
                break;
            case 3:
                casa.declanseazaEveniment("SEARA");
                break;
            case 4:
                casa.declanseazaEveniment("DIMINEATA");
                break;
            case 5:
            {
                int nrBecuri = numaraDispozitiveDupaTip<BecRgb>(casa.getDispozitive());
                std::cout << "Avem " << nrBecuri << " bec(uri) RGB in casa\n";
                break;
            }
            case 6:
            {
                std::string nume;
                int valoare;
                std::cout << "Numele dispozitivului pe care vrei sa il modifici: ";
                std::cin >> nume;
                std::cout << "Valoarea noua: ";
                std::cin >> valoare;

                //folosim blocul try-catch pentru a prinde exceptiile aruncate
                //de clasa noastra sablon Parametru<T> (ex: valoare prea mare)
                try
                {
                    casa.regleazaDispozitiv(nume, valoare);
                }
                catch (const SmartHomeException& e) {
                    //daca am introdus 200 grade la frigider, programul nu va da crash,
                    //ci va afisa eroarea
                    std::cout << "Eroare: " << e.what() << "\n";
                }
                break;
            }
            case 7:
            {
                std::string nume;
                std::cout << "Numele dispozitivului pe care vrei sa il stergi: ";
                std::cin >> nume;

                try {
                    casa.stergeDispozitiv(nume);
                }
                catch (const SmartHomeException& e) {
                    //DispozitivInexistentException daca numele nu e bun
                    std::cout << "Eroare: " << e.what() << "\n";
                }
                break;
            }
            case 8:
            {
                std::string nume;
                int canal;
                std::cout << "Numele televizorului: ";
                std::cin >> nume;
                std::cout << "Numarul canalului nou (1-999): ";
                std::cin >> canal;

                try
                {
                    casa.schimbaCanalTV(nume, canal);
                }
                catch (const SmartHomeException& e)
                {
                    std::cout << "Eroare: " << e.what() << "\n";
                }
                break;
            }
            case 0:
                std::cout << "Exit\n";
                break;
            default:
                std::cout << "Optiune invalida!\n";
        }
    } while (optiune != 0);
}