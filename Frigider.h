#pragma once
#include "DispozitivSmart.h"
#include "Interfete.h"
#include "Parametru.h"

class Frigider : public DispozitivSmart, public IReglabil
{
private:
    Parametru<float> temperaturaCurenta;
public:
    Frigider(std::string n, float temp = 4.0f);

    void regleazaNivel(int valoare) override;

    //implementare IObserver
    void update(const std::string& eveniment) override;

    DispozitivSmart* clone() const override
    {
        return new Frigider(*this);
    }

protected:
    void do_afisare(std::ostream& out) const override;
};