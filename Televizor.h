#pragma once
#include "DispozitivSmart.h"
#include "Interfete.h"
#include "Parametru.h"

class Televizor : public DispozitivSmart, public IReglabil
{
private:
    Parametru<int> volum;
    Parametru<int> canal;
public:
    Televizor(std::string n);

    //implementam IReglabil pentru a controla volumul (0-100)
    void regleazaNivel(int procent) override;
    
    //metoda specifica pentru televizor
    void schimbaCanal(int c);

    //implementare IObserver
    void update(const std::string& eveniment) override;

    DispozitivSmart* clone() const override
    {
        return new Televizor(*this);
    }

protected:
    void do_afisare(std::ostream& out) const override;
};