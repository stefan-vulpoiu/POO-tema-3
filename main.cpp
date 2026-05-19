#include "Meniu.h"

int main()
{
    Meniu aplicatie;
    aplicatie.ruleaza();
    return 0;
}
/*
Ghid de testare la rulare:

- 1 (Adauga): creeaza si introduce un nou dispozitiv in casa inteligenta
    * Tip: 1-5 (1=Bec, 2=Termostat, 3=Televizor, 4=Frigider, 5=Aer Conditionat)
    * Nume: ex. LuminaHol -> Adauga noul dispozitiv direct in vectorul polimorfic

- 2 (Afiseaza): afiseaza starea tuturor dispozitivelor

- 3 (Seara) / 4 (Dimineata): declanseaza evenimente globale in casa
    * Seara: CasaSmart notifica observatorii (IObserver). Becurile scad la 20%, termostatul trece pe 22C,
             TV-ul si Aerul Conditionat se opresc, iar frigiderul e setat la 5C
    * Dimineata: Becurile se opresc, termostatul trece pe 19C, TV-ul porneste pe canalul 5 (volum 15),
                 Aerul Conditionat porneste la 22C, iar frigiderul raceste la 3C
                 Toate deciziile sunt luate local de fiecare obiect

- 5 (Numara dispozitive): numara cate dispozitive de un anumit tip exista
    * TipCautat: 1-5 (1=Bec, 2=Termostat, 3=Televizor, 4=Frigider, 5=Aer Conditionat)

- 6 (Seteaza): modifica manual un dispozitiv:
    * Nume: LuminaSufragerie | Valoare: 0-100 (exemplu: 80 -> Becul se aprinde la 80%)
    * Nume: TermostatCentral | Valoare: 10-35 (exemplu: 100 -> Prinde exceptia custom a clasei sablon
                                        (100 > 35 grade) si afiseaza eroarea fara sa dea crash)
    * Nume: TV_Living | Valoare: 0-100 (seteaza volumul televizorului)

- 7 (Sterge): elimina definitiv un dispozitiv:
    * Nume: LuminaSufragerie | Sterge dispozitivul din vector si elibereaza memoria
    * Nume: TermostatCentral | Sterge dispozitivul din vector si elibereaza memoria
    * Nume: Invalid | (exemplu: Canapea -> Prinde exceptia custom de dispozitiv
                                inexistent si afiseaza eroarea fara sa dea crash)

- 8 (Canal TV): schimba canalul exclusiv pentru un televizor:
    * Nume: TV_Living | Valoare: 1-999
    * Nume: TermostatCentral | Valoare: 5 -> Prinde exceptia "Acest dispozitiv nu este un Televizor"

- 0 (Iesire): inchide programul curat (apeleaza destructorul virtual pentru a preveni memory leaks,
              eliberand toata memoria gestionata de instanta unica / Design Pattern-ul Singleton)
*/