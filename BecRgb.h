#pragma once
#include "DispozitivSmart.h"
#include "Parametru.h" // Adaugat

//mostenire multipla: BecRgb este un DispozitivSmart si, in acelasi timp,
//implementeaza interfata IReglabil
class BecRgb : public DispozitivSmart, public IReglabil //mosteneste DispozitivSmart; implementeaza IReglabil
{
private:
    Parametru<int> intensitate; //folosim clasa sablon
public:
    BecRgb(std::string n);

    //'override' obliga compilatorul sa verifice daca suprascriem corect o functie virtuala din clasa parinte
    void regleazaNivel(int procent) override;

    void update(const std::string& eveniment) override; // Metoda noua Observer

    DispozitivSmart* clone() const override //constructor de copiere
    {
        return new BecRgb(*this); //foloseste constructorul de copiere default
    }

protected:
    void do_afisare(std::ostream& out) const override;
};