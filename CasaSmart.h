#pragma once
#include <vector>
#include "DispozitivSmart.h"

class CasaSmart
{
private:
    //compozitie si polimorfism: Vectorul stocheaza pointeri la clasa de baza (*)
    //astfel, in aceeasi colectie putem pune si obiecte de tip BecRgb si de tip Termostat
    //DispozitivSmart* accepta orice obiect derivat
    std::vector<DispozitivSmart*> dispozitive;

    // Singleton: Constructorul privat
    CasaSmart() = default;
public:
    // Singleton: Prevenim copierea si atribuirea
    CasaSmart(const CasaSmart& other) = delete;
    CasaSmart& operator=(const CasaSmart& other) = delete;

    const std::vector<DispozitivSmart*>& getDispozitive() const { return dispozitive; }

    // Singleton: obtinerea instantei
    static CasaSmart& getInstanta();

    CasaSmart& operator+=(DispozitivSmart* d);

    void afiseazaToate() const;
    void regleazaDispozitiv(const std::string& nume, int valoare);
    void stergeDispozitiv(const std::string& nume);
    void schimbaCanalTV(const std::string& nume, int canal);

    //inlocuieste 'activeazaModSeara'
    void declanseazaEveniment(const std::string& eveniment);

    ~CasaSmart(); //destructor
};