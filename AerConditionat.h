#pragma once
#include "DispozitivSmart.h"
#include "Interfete.h"
#include "Parametru.h"

class AerConditionat : public DispozitivSmart, public IReglabil
{
private:
    Parametru<float> temperaturaCurenta;
public:
    AerConditionat(std::string n, float temp = 22.0f);

    void regleazaNivel(int valoare) override;

    //implementat IObserver
    void update(const std::string& eveniment) override;

    DispozitivSmart* clone() const override
    {
        return new AerConditionat(*this);
    }

protected:
    void do_afisare(std::ostream& out) const override;
};