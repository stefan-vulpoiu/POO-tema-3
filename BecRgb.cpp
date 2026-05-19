#include "BecRgb.h"

BecRgb::BecRgb(std::string n) : DispozitivSmart(n), intensitate(0, 0, 100)
{
    //trimit numele mai departe catre constructorul clasei de baza ca sa il initializeze el,
    //apoi initializez parametrul cu valoarea de start, min si max
}

void BecRgb::regleazaNivel(int procent)
{
    //clasa Parametru arunca ValoareInvalidaException
    intensitate.setValoare(procent);

    if (intensitate.getValoare() > 0)
        porneste();
    else
        opreste();
}

void BecRgb::update(const std::string& eveniment)
{
    //fiecare obiect stie cum sa reactioneze
    if (eveniment == "SEARA")
        regleazaNivel(20);
    else
        if (eveniment == "DIMINEATA")
            opreste();
}

void BecRgb::do_afisare(std::ostream& out) const
{
    //apelam functionalitatea din clasa parinte pentru a afisa "[Nume] Stare"
    DispozitivSmart::do_afisare(out);
    //si apoi completam specific cu informatiile doar pentru Bec
    out << " | Luminozitate: " << intensitate.getValoare() << "%";
}