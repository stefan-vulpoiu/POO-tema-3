#pragma once
#include "DispozitivSmart.h"
#include "BecRgb.h"
#include "Termostat.h"
#include "Televizor.h"
#include "Frigider.h"
#include "AerConditionat.h"
#include <string>

//O: Open-closed principle
//am folosit principiul O prin faptul ca putem adauga un singur case aici pentru o noua clasa derivata,
//fara a fi nevoie sa modificam Meniu.cpp sau CasaSmart.cpp, unde am adauga reguli noi pentru creare

class DispozitivFactory
{
public:
    static DispozitivSmart* creazaDispozitiv(int tip, const std::string& nume)
    {
        switch (tip)
        {
            case 1: return new BecRgb(nume);
            case 2: return new Termostat(nume);
            case 3: return new Televizor(nume);
            case 4: return new Frigider(nume);
            case 5: return new AerConditionat(nume);
            default: return nullptr;
        }
    }
};