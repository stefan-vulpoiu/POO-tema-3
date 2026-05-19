#include "CasaSmart.h"
#include "Interfete.h"
#include "Exceptii.h"
#include "Termostat.h"
#include "Televizor.h"

CasaSmart& CasaSmart::getInstanta()
{
    static CasaSmart instanta;
    return instanta;
}

CasaSmart& CasaSmart::operator+=(DispozitivSmart* d)
{
    dispozitive.push_back(d);
    return *this;
}

void CasaSmart::afiseazaToate() const
{
    std::cout << "\n--- STATUS CASA SMART ---\n";
    if (dispozitive.empty())
        std::cout << "(Niciun dispozitiv instalat)\n";
    for (auto d : dispozitive)
        std::cout << *d << "\n";
}

void CasaSmart::declanseazaEveniment(const std::string& eveniment)
{
    std::cout << "\n-> Declansare eveniment global: " << eveniment << "...\n";
    for (auto d : dispozitive)
    {
        d->update(eveniment);
    }
}

void CasaSmart::regleazaDispozitiv(const std::string& nume, int valoare)
{
    for (auto d : dispozitive)
    {
        if (d->getNume() == nume)
        {
            //Televizorul
            Televizor* tv = dynamic_cast<Televizor*>(d);
            if (tv)
            {
                tv->regleazaNivel(valoare);
                std::cout << "-> Volum TV setat cu succes!\n";
                return;
            }

            //Termostatul (setTemperatura)
            Termostat* t = dynamic_cast<Termostat*>(d);
            if (t)
            {
                t->setTemperatura((float)valoare);
                std::cout << "-> Temperatura termostatului aplicata cu succes!\n";
                return;
            }

            //orice altceva care e IReglabil (Bec, AerConditionat, Frigider)
            IReglabil* r = dynamic_cast<IReglabil*>(d);
            if (r)
            {
                r->regleazaNivel(valoare);
                std::cout << "-> Setare (intensitate/temperatura) aplicata cu succes!\n";
                return;
            }

            //daca se ajunge aici, e un dispozitiv care nu suporta reglaje
            throw SmartHomeException("Acest dispozitiv nu poate fi reglat manual!");
        }
    }
    //daca a terminat for-ul si nu a dat return, inseamna ca nu a gasit numele
    throw DispozitivInexistentException(nume);
}

void CasaSmart::stergeDispozitiv(const std::string& nume)
{
    for (auto it = dispozitive.begin(); it != dispozitive.end(); ++it)
    {
        if ((*it)->getNume() == nume)
        {
            delete *it;
            dispozitive.erase(it);
            std::cout << "-> Dispozitiv sters cu succes\n";
            return;
        }
    }
    throw DispozitivInexistentException(nume);
}

void CasaSmart::schimbaCanalTV(const std::string& nume, int canal)
{
    for (auto d : dispozitive)
    {
        if (d->getNume() == nume)
        {
            //verificam daca dispozitivul este un Televizor
            Televizor* tv = dynamic_cast<Televizor*>(d);
            if (tv) {
                tv->schimbaCanal(canal); //apelam functia din Televizor.cpp
                std::cout << "-> [TV] Canalul a fost schimbat la " << canal << "\n";
                return;
            }
            throw SmartHomeException("Acest dispozitiv nu este un Televizor");
        }
    }
    throw DispozitivInexistentException(nume);
}

CasaSmart::~CasaSmart()
{
    for (auto d : dispozitive)
        delete d;
}