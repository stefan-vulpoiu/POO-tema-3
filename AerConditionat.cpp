#include "AerConditionat.h"
#include <iostream>

AerConditionat::AerConditionat(std::string n, float temp)
    : DispozitivSmart(n), temperaturaCurenta(temp, 10.0f, 30.0f) {}

void AerConditionat::regleazaNivel(int valoare)
{
    //validarea se face in clasa template
    temperaturaCurenta.setValoare((float)valoare);
    porneste();
}

void AerConditionat::update(const std::string& eveniment)
{
    if (eveniment == "SEARA")
    {
        opreste();
        std::cout << "[Notificare Aer] " << getNume() << " a fost oprit seara\n";
    }
    else
        if (eveniment == "DIMINEATA")
        {
            porneste();
            regleazaNivel(22);
            std::cout << "[Notificare Aer] " << getNume() << " a pornit la 22C dimineata\n";
        }
}

void AerConditionat::do_afisare(std::ostream& out) const
{
    DispozitivSmart::do_afisare(out);
    out << " | Temperatura: " << temperaturaCurenta.getValoare() << " grade";
}