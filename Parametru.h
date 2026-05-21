//Parametru.h (Clasa template)
#pragma once
#include "Exceptii.h"
#include <string>

//S: Single responsibility principle
//am folosit principiul S prin faptul ca aceasta clasa se ocupa acum cu verificarea parametrilor,
//astfel incat sa vedem daca volumul, temperatura, intensitatea, etc se afla in limite

//litera T tine locul oricarui tip de data; in loc de int, float, etc.., avem Parametru<T>
template <typename T>
class Parametru
{
private:
    T valoare;
    T limitaMin;
    T limitaMax;
public:
    Parametru(T val, T min, T max) : valoare(val), limitaMin(min), limitaMax(max) {}

    T getValoare() const { return valoare; }

    void setValoare(T nouaValoare)
    {
        if (nouaValoare < limitaMin || nouaValoare > limitaMax)
        {
            throw ValoareInvalidaException("Valoarea depaseste limitele permise!");
        }
        valoare = nouaValoare;
    }
};