#pragma once
#include <string>

//o interfata este o clasa care declara functii (nu poti crea obiecte, ci doar o poti mosteni)
//interfata pentru dispozitivele care au un nivel reglabil (0-100)
class IReglabil
{
public:
    virtual void regleazaNivel(int procent) = 0; //functie virtuala; clasele derivate tb sa suprascrie
    virtual ~IReglabil() = default; //destructor
};

//interfata pentru design pattern-ul Observer
//fiecare dispozitiv se seteaza singur;ex: la modul SEARA, nu mai setez manual fiecare temperatura/volum/..
class IObserver
{
public:
    virtual void update(const std::string& eveniment) = 0;
    virtual ~IObserver() = default;
};