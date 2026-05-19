#pragma once
#include "DispozitivSmart.h"
#include "Parametru.h"

//termostatul ramane un DispozitivSmart, dar acum implementeaza si IObserver
//(prin mostenirea din clasa de baza)

//termostatul mosteneste toate functionalitatile DispozitivuluiSmart

//spre deosebire de BecRgb, termostatul are o mostenire simpla
//el este un DispozitivSmart, dar nu mosteneste interfata IReglabil
class Termostat : public DispozitivSmart
{
private:
    Parametru<float> temperatura;
public:
    Termostat(std::string n);
    void setTemperatura(float t);

    //metoda obligatorie din interfata IObserver
    void update(const std::string& eveniment) override;

    DispozitivSmart* clone() const override
    {
        return new Termostat(*this);
    }

protected:
    void do_afisare(std::ostream& out) const override;
};

