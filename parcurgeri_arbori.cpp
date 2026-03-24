#include <iostream>
using namespace std;

// Definim o structura numita Nod
struct Nod {

    // Valoarea memorata in nod
    int info;

    // Pointer catre fiul stang
    Nod* stg;

    // Pointer catre fiul drept
    Nod* dr;
};

// Functie care creeaza dinamic un nod nou si il initializeaza
Nod* creareNod(int valoare) {

    // Alocam dinamic memorie pentru un nod nou
    Nod* p = new Nod;

    // Punem in campul info valoarea primita ca parametru
    p->info = valoare;

    // Initial, fiul stang nu exista
    p->stg = nullptr;

    // Initial, fiul drept nu exista
    p->dr = nullptr;

    // Returnam adresa nodului creat
    return p;
}

// Functie de parcurgere in preordine: Radacina - Stanga - Dreapta
void preordine(Nod* rad) {

    // Daca arborele este vid, ne oprim
    if (rad == nullptr) return;

    // Afisam valoarea din radacina
    cout << rad->info << " ";

    // Parcurgem recursiv subarborele stang
    preordine(rad->stg);

    // Parcurgem recursiv subarborele drept
    preordine(rad->dr);
}

// Functie de parcurgere in inordine: Stanga - Radacina - Dreapta
void inordine(Nod* rad) {

    // Daca arborele este vid, ne oprim
    if (rad == nullptr) return;

    // Parcurgem recursiv subarborele stang
    inordine(rad->stg);

    // Afisam valoarea din radacina
    cout << rad->info << " ";

    // Parcurgem recursiv subarborele drept
    inordine(rad->dr);
}

// Functie de parcurgere in postordine: Stanga - Dreapta - Radacina
void postordine(Nod* rad) {

    // Daca arborele este vid, ne oprim
    if (rad == nullptr) return;

    // Parcurgem recursiv subarborele stang
    postordine(rad->stg);

    // Parcurgem recursiv subarborele drept
    postordine(rad->dr);

    // Afisam valoarea din radacina
    cout << rad->info << " ";
}

// Functie care calculeaza inaltimea arborelui
int inaltime(Nod* rad) {

    // Daca arborele este vid, intoarcem -1
    if (rad == nullptr) return -1;

    // Calculam inaltimea subarborelui stang
    int hStg = inaltime(rad->stg);

    // Calculam inaltimea subarborelui drept
    int hDr = inaltime(rad->dr);

    // Daca inaltimea stanga este mai mare, o folosim pe ea
    if (hStg > hDr) return 1 + hStg;

    // Altfel folosim inaltimea dreapta
    return 1 + hDr;
}

// Functie care calculeaza numarul de frunze
int numarFrunze(Nod* rad) {

    // Daca arborele este vid, nu avem frunze
    if (rad == nullptr) return 0;

    // Daca nodul nu are nici fiu stang, nici fiu drept, este frunza
    if (rad->stg == nullptr && rad->dr == nullptr) return 1;

    // Numarul total de frunze este suma frunzelor din stanga si dreapta
    return numarFrunze(rad->stg) + numarFrunze(rad->dr);
}

// Functie care calculeaza suma valorilor din toate nodurile
int suma(Nod* rad) {

    // Daca arborele este vid, suma este 0
    if (rad == nullptr) return 0;

    // Suma este valoarea nodului curent + suma din stanga + suma din dreapta
    return rad->info + suma(rad->stg) + suma(rad->dr);
}

// Functie care verifica daca un nod este frunza
bool esteFrunza(Nod* rad) {

    // Daca nodul nu exista, nu este frunza
    if (rad == nullptr) return false;

    // Un nod este frunza daca nu are nici fiu stang, nici fiu drept
    return rad->stg == nullptr && rad->dr == nullptr;
}

// Functie care afiseaza doar frunzele, in postordine
void afiseazaFrunzePostordine(Nod* rad) {

    // Daca arborele este vid, ne oprim
    if (rad == nullptr) return;

    // Parcurgem subarborele stang
    afiseazaFrunzePostordine(rad->stg);

    // Parcurgem subarborele drept
    afiseazaFrunzePostordine(rad->dr);

    // Daca nodul curent este frunza, il afisam
    if (esteFrunza(rad))
        cout << rad->info << " ";
}

// Functie care sterge toate nodurile arborelui din memorie
void stergeArbore(Nod* rad) {

    // Daca nodul nu exista, ne oprim
    if (rad == nullptr) return;

    // Stergem mai intai subarborele stang
    stergeArbore(rad->stg);

    // Stergem apoi subarborele drept
    stergeArbore(rad->dr);

    // Stergem nodul curent
    delete rad;
}

// Functia principala a programului
int main() {

    // Cream radacina arborelui cu valoarea 1
    Nod* radacina = creareNod(1);

    // Cream fiul stang al radacinii cu valoarea 2
    radacina->stg = creareNod(2);

    // Cream fiul drept al radacinii cu valoarea 3
    radacina->dr = creareNod(3);

    // Cream fiul stang al nodului 2 cu valoarea 4
    radacina->stg->stg = creareNod(4);

    // Cream fiul drept al nodului 2 cu valoarea 5
    radacina->stg->dr = creareNod(5);

    // Cream fiul drept al nodului 3 cu valoarea 6
    radacina->dr->dr = creareNod(6);

    // Afisam textul pentru preordine
    cout << "Preordine: ";

    // Apelam functia de preordine
    preordine(radacina);

    // Trecem la linie noua
    cout << '\n';

    // Afisam textul pentru inordine
    cout << "Inordine: ";

    // Apelam functia de inordine
    inordine(radacina);

    // Trecem la linie noua
    cout << '\n';

    // Afisam textul pentru postordine
    cout << "Postordine: ";

    // Apelam functia de postordine
    postordine(radacina);

    // Trecem la linie noua
    cout << '\n';

    // Afisam inaltimea arborelui
    cout << "Inaltime: " << inaltime(radacina) << '\n';

    // Afisam numarul de frunze
    cout << "Frunze: " << numarFrunze(radacina) << '\n';

    // Afisam suma valorilor din arbore
    cout << "Suma: " << suma(radacina) << '\n';

    // Afisam textul pentru frunzele afisate in postordine
    cout << "Frunze in postordine: ";

    // Apelam functia care afiseaza doar frunzele
    afiseazaFrunzePostordine(radacina);

    // Trecem la linie noua
    cout << '\n';

    // Eliberam memoria ocupata de arbore
    stergeArbore(radacina);

    // Programul s-a terminat corect
    return 0;
}