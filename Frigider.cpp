#include "Frigider.h"
#include <iostream>

Frigider::Frigider(std::string n, float temp) : DispozitivSmart(n), temperaturaCurenta(temp, 1.0f, 7.0f)
{
    this->porneste(); //frigiderul este pornit by default
}

void Frigider::regleazaNivel(int valoare)
{
    //validarea se face in clasa sablon
    temperaturaCurenta.setValoare((float)valoare);
}

void Frigider::update(const std::string& eveniment)
{
    if (eveniment == "SEARA")
    {
        regleazaNivel(5);
        std::cout << "[Notificare Frigider] " << getNume() << " setat pe recire cu 5C pentru seara\n";
    }
    else
        if (eveniment == "DIMINEATA")
        {
            regleazaNivel(3); //racire mai puternica peste zi
            std::cout << "[Notificare Frigider] " << getNume() << " setat pe racire cu 3C pentru dimineata\n";
        }
}

void Frigider::do_afisare(std::ostream& out) const
{
    DispozitivSmart::do_afisare(out);
    out << " | Temperatura: " << temperaturaCurenta.getValoare() << " grade";
}