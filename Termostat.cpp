#include "Termostat.h"
#include <iostream>


//in constructor initializam clasa sablon cu: valoarea start (20.0), minim (10.0) si maxim (35.0)
Termostat::Termostat(std::string n) : DispozitivSmart(n), temperatura(20.0f, 10.0f, 35.0f)
{
    //trimit numele n si initializez temperatura cu o valoare de start 20
}

void Termostat::setTemperatura(float t)
{
    //clasa sablon Parametru se ocupa de validare
    //daca 't' este gresit, functia va arunca ValoareInvalidaException
    temperatura.setValoare(t);
    porneste();
}

void Termostat::update(const std::string& eveniment)
{
    //Observer
    if (eveniment == "SEARA")
    {
        setTemperatura(22.0f); //seteaza temperatura pentru seara
        std::cout << "[Notificare Termostat] " << getNume() << " a setat temperatura automat la 22.0C\n";
    }
    else if (eveniment == "DIMINEATA")
    {
        setTemperatura(19.0f); //temperatura pentru dimineata
        std::cout << "[Notificare Termostat] " << getNume() << " a setat temperatura automat la 19.0C\n";
    }
}

void Termostat::do_afisare(std::ostream& out) const
{
    DispozitivSmart::do_afisare(out);
    out << " | Temp: " << temperatura.getValoare() << "C";
}