Eseu proiect:

Proiectul Smart Home are ca scop modelarea unui sistem inteligent de gestionare a locuintei. Aplicatia serveste pentru implementarea, testarea si demonstrarea principiilor fundamentale ale POO, fiind dezvoltată din tema 2. In plus față de tema 2 au fost integrate șabloane (templates), respectând principiile SOLID și implementând trei Design Pattern-uri: Singleton, Factory Method și Observer.



Clasa CasaSmart reprezinta creierul acestui sistem si gestioneaza un vector de pointeri la clasa de bază. Aceasta a fost transformata într-un Singleton, ascunzând constructorul, pentru ca în memorie sa existe un singur "sistem central", accesibil prin metoda getInstanta(). Tot aici este implementata logica principală pentru modul Observer: metoda declanseazaEveniment("SEARA") parcurge vectorul și dă comanda d->update("SEARA") mai departe, moment in care becul isi regleaza automat intensitatea, scazand-o la 20%, termostatul seteaza temperatura la 22 de grade C, televizorul se opreste, aerul conditionat se opreste, iar frigiderul creste temperatura de la 3 grade C la 5 grade C. În mod similar, pentru modul DIMINEATA, becul se stinge, fiind deja lumina naturala, termostatul seteaza temperatura din casa la 19 grade C, televizorul porneste, se muta pe canalul 5 si seteaza un volum de 15, aerul conditionat porneste si isi regleaza temperatura la 22 grade C, iar frigiderul trece la o racire mai puternica, de 3 grade C.

În clasa DispozitivFactory am aplicat Design Pattern-ul Factory Method. În loc să scriem new BecRgb() prin tot meniul aplicației, am creat această clasă care realizează crearea. Meniul doar o apelează dându-i un număr corespunzator tipului de dispozitiv (1 = Bec, 2 = Termostat, 3 = Televizor, 4 = Frigider, 5 = Aer Conditionat) și un nume, iar fabrica îi returnează pointerul deja creat. Respectă principiul Open-Closed: dacă mai adăugăm un sistem de alarmă în proiect, modificăm doar în DispozitivFactory.

Clasa DispozitivSmart este clasa de bază pe care o mostenesc celelalte dispozitive din casă. Ea conține lucrurile comune: un nume, o stare (pornit/oprit), un contor static (numarTotal) care retine numarul de dispozitive și un destructor virtual care are rolul de a curăța corect memoria din clasele derivate la final. Tot aici este implementat idiomul NVI (Non-Virtual Interface) pentru afișarea detaliilor pe ecran. În plus, clasa moștenește interfața IObserver, deci toți copiii ei vor fi „Observatori”.

Clasele derivate sunt: BecRgb, Termostat, Televizor, Frigider, AerConditionat. Acestea sunt dispozitivele propriu-zise din casă. Fiecare moștenește DispozitivSmart. În interior folosesc clasa șablon Parametru pentru caracteristicile lor specifice (televizorul are canal și volum de tip int, termostatul, frigiderul și aerul conditionat au temperatură de tip float, iar becul are intensitate de tip int). Fiecare își implementează propria metodă update().

Meniu este clasa care se ocupă cu citirile de la tastatură si afisarile pe ecran, Contine un while si un switch cu toate optiunile posibile aplicate pe dispozitivele casei smart:

1 -> Adaugă un dispozitiv;

2 -> Afișează toate dispozitivele;

3 -> Declanșează modul SEARA;

4 -> Declanșează modul DIMINEATA;

5 -> Numara tipul de dispozitive;

6 -> Setează optiunile unui dispozitiv (temperatura, volum);

7 -> Elimină un dispozitiv;

8 -> Schimbă canalul la televizor;

0 -> Închide programul.

Tot aici sunt punctate și erorile prin blocurile try-catch. Dacă utilizatorul face o greșeală, sistemul prinde SmartHomeException, afișează un mesaj clar de eroare și îl lasă să încerce din nou, fără să se închidă rularea programului.


Clasa Parametru este clasa șablon, care reține valoarea curentă si limitele superioara si inferioara. Dacă este introdusă o valoare peste limită prin setValoare(), va arunca eroare. Astfel este respectat și principiul S: Single responsibility principle.

Fișierul Utilitare.h conține funcția șablon numaraDispozitiveDupaTip<T>. Ea folosește dynamic_cast ca să verifice numarul exact de elemente de tipul <T>.

În fișierul Exceptii.h sunt creat propriile erori posibile ale programului pentru ca acesta sa nu dea crash. Avem o clasă de bază SmartHomeException care moștenește std::exception din C++. Din ea derivă ValoareInvalidaException (care afiseaza un mesaj de eroare corespunzator daca valoarea introdusa la tastatura este in afara limitelor permise) și DispozitivInexistentException (care afiseaza un mesaj de eroare corespunzator daca se introduce un nume gresit la tastatura atunci cand vrem sa stergem un dispozitiv).

În fișierul Interfete.h sunt definite funcțiile virtuale pure. IReglabil obligă dispozitivele (cum ar fi becul sau televizorul) să aibă o funcție regleazaNivel() ca să poată fi modificate de la 0 la 100. IObserver este piesa principală din Design Pattern-ul Observer, obligând clasele să aibă o metodă update() ca să știe cum să asculte și să reacționeze când Casa le trimite un semnal (ex: modul SEARA sau DIMINEATA).


Proiectul respectă, de asemenea, principiile SOLID:

S (Single Responsibility Principle): Clasa CasaSmart se ocupă de gestionarea dispozitivelor, iar interacțiunea cu utilizatorul (afișările și citirea de la tastatură) a fost mutată complet în clasa Meniu. De asemenea, logica de validare a valorilor a fost mutată în clasa șablon Parametru<T>. Fiecare clasă face acum un singur lucru.

O (Open-Closed Principle): Codul este deschis pentru extensii, dar închis pentru modificări. Dacă vrem să adăugăm un dispozitiv nou, nu trebuie să modificăm logica din CasaSmart. Doar creăm clasa nouă și o adăugăm în DispozitivFactory.

L (Liskov Substitution Principle): Orice obiect derivat trebuie să poată înlocui clasa de bază fără să producă erori. Vectorul de pointeri DispozitivSmart* respectă acest lucru. Se pot apela funcții generale pe orice pointer din listă, iar dispozitivele se vor comporta în mod corect.

I (Interface Segregation Principle): Am creat interfețe mici și specifice în locul unei interfațe cu multe funcții. De exemplu, Termostatul nu moștenește IReglabil (pentru că se reglează în grade, nu în procente 0-100). Fiecare dispozitiv implementează doar condițiile de care are nevoie.

D (Dependency Inversion Principle): CasaSmart nu depinde de clasele dispozitivelor specifice (BecRgb, Frigider, etc.), ci comunică cu ele doar prin abstracții. Casa nu are nevoie să cunoască funcționarea internă a fiecărui dispozitiv; ea trimite comenzile generale bazându-se exclusiv pe interfața IObserver.



În cadrul proiectului sunt implementate și trei Design Pattern-uri:

SINGLETON: CasaSmart a devenit un Singleton: constructorul este private și copierea clasei este blocată. Singura modalitate de a interacționa cu sistemul este prin metoda statică getInstanta(), care garantează că tot programul folosește mereu o singură casă inteligentă.

FACTORY METHOD: Pentru a nu aglomera clasa Meniu cu detalii despre crearea obiectelor (folosind instrucțiuni new), a fost creată clasa DispozitivFactory. Dacă utilizatorul vrea să adauge un bec, Meniu nu creează becul direct, ci prin intermediul fabricii.

OBSERVER: Prin interfața IObserver pe care o moștenesc toate dispozitivele, CasaSmart dă doar o comandă generală (de exemplu: "SEARA"). Fiecare dispozitiv primește comanda și se modifică singur.

Pentru a preveni memory leaks, destructorul clasei de bază este virtual (virtual ~DispozitivSmart()). Astfel, la închiderea programului, managerul CasaSmart golește automat tot vectorul, eliberând corect memoria pentru fiecare dispozitiv în parte.


Bibliografie:

Resursele de pe Teams



https://refactoring.guru/design-patterns/cpp



https://www.geeksforgeeks.org/system-design/modern-c-design-patterns-tutorial/



https://www.geeksforgeeks.org/system-design/solid-principle-in-programming-understand-with-real-life-examples/



https://medium.com/@oleksandra_shershen/solid-principles-implementation-and-examples-in-c-99f0d7e3e868



https://codesignal.com/learn/courses/applying-clean-code-principles-in-cpp/lessons/applying-solid-principles-in-cpp



https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md


https://github.com/andrachiritoiu/University-Work/tree/main/Anul%201/Semestrul%202/Programare%20Orientata%20pe%20Obiecte/Proiecte


https://github.com/DimaOanaTeodora/Uni-Work-2019-2022/tree/main/AN%201%20SEM%202/Programare%20orientata%20pe%20obiecte


https://github.com/DavidPatranjel/Proiect-POO


https://github.com/AlexVulpoiu/OOP-Homework_3


https://github.com/dariabroscoteanu/OOP/blob/main/Projects/Project%203.cpp