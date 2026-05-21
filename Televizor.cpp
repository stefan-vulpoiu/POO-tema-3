#include "Televizor.h"
#include <iostream>

Televizor::Televizor(std::string n) : DispozitivSmart(n), volum(20, 0, 100), canal(1, 1, 999) {}

void Televizor::regleazaNivel(int procent)
{
    //validarea se face in clasa template
    volum.setValoare(procent);

    if (volum.getValoare() > 0)
        porneste();
    else
        opreste();
}

void Televizor::schimbaCanal(int c)
{
    //validarea se face in clasa template
    canal.setValoare(c);
    porneste();
}

void Televizor::update(const std::string& eveniment)
{
    if (eveniment == "SEARA")
    {
        opreste(); //seara oprim televizorul
        std::cout << "[Notificare Televizor] " << getNume() << " a fost oprit automat seara\n";
    }
    else
        if (eveniment == "DIMINEATA")
        {
            porneste();
            schimbaCanal(5); //deschidem la stirile de dimineata
            regleazaNivel(15); //volum mic
            std::cout << "[Notificare Televizor] " << getNume() << " a fost pornit dimineata (Canal 5, Volum 15)\n";
        }
}

void Televizor::do_afisare(std::ostream& out) const
{
    DispozitivSmart::do_afisare(out);
    out << " | Volum: " << volum.getValoare() << " | Canal: " << canal.getValoare();
}