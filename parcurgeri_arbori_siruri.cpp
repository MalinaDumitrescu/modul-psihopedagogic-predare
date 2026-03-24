#include <iostream>
using namespace std;

// Vectorul info memoreaza valoarea fiecarui nod
int info[101];

// Vectorul stg memoreaza indicele fiului stang
int stg[101];

// Vectorul dr memoreaza indicele fiului drept
int dr[101];

// Variabila care memoreaza indicele radacinii
int radacina;

// Functie de parcurgere in preordine: Radacina - Stanga - Dreapta
void preordine(int nod) {

    // Daca nodul nu exista, ne oprim
    if (nod == 0) return;

    // Afisam valoarea nodului curent
    cout << info[nod] << " ";

    // Parcurgem subarborele stang
    preordine(stg[nod]);

    // Parcurgem subarborele drept
    preordine(dr[nod]);
}

// Functie de parcurgere in inordine: Stanga - Radacina - Dreapta
void inordine(int nod) {

    // Daca nodul nu exista, ne oprim
    if (nod == 0) return;

    // Parcurgem subarborele stang
    inordine(stg[nod]);

    // Afisam valoarea nodului curent
    cout << info[nod] << " ";

    // Parcurgem subarborele drept
    inordine(dr[nod]);
}

// Functie de parcurgere in postordine: Stanga - Dreapta - Radacina
void postordine(int nod) {

    // Daca nodul nu exista, ne oprim
    if (nod == 0) return;

    // Parcurgem subarborele stang
    postordine(stg[nod]);

    // Parcurgem subarborele drept
    postordine(dr[nod]);

    // Afisam valoarea nodului curent
    cout << info[nod] << " ";
}

// Functie care calculeaza inaltimea arborelui
int inaltime(int nod) {

    // Daca nodul nu exista, intoarcem -1
    if (nod == 0) return -1;

    // Calculam inaltimea subarborelui stang
    int hStg = inaltime(stg[nod]);

    // Calculam inaltimea subarborelui drept
    int hDr = inaltime(dr[nod]);

    // Daca inaltimea din stanga este mai mare, o alegem pe ea
    if (hStg > hDr) return 1 + hStg;

    // Altfel alegem inaltimea din dreapta
    return 1 + hDr;
}

// Functie care calculeaza numarul de frunze
int numarFrunze(int nod) {

    // Daca nodul nu exista, nu avem frunze
    if (nod == 0) return 0;

    // Daca nodul nu are copii, este frunza
    if (stg[nod] == 0 && dr[nod] == 0) return 1;

    // Numarul de frunze este suma frunzelor din stanga si dreapta
    return numarFrunze(stg[nod]) + numarFrunze(dr[nod]);
}

// Functie care calculeaza suma valorilor din arbore
int suma(int nod) {

    // Daca nodul nu exista, suma este 0
    if (nod == 0) return 0;

    // Suma este valoarea nodului curent + suma din stanga + suma din dreapta
    return info[nod] + suma(stg[nod]) + suma(dr[nod]);
}

// Functie care verifica daca un nod este frunza
bool esteFrunza(int nod) {

    // Daca nodul nu exista, nu este frunza
    if (nod == 0) return false;

    // Nodul este frunza daca nu are fii
    return stg[nod] == 0 && dr[nod] == 0;
}

// Functie care afiseaza doar frunzele in postordine
void afiseazaFrunzePostordine(int nod) {

    // Daca nodul nu exista, ne oprim
    if (nod == 0) return;

    // Parcurgem subarborele stang
    afiseazaFrunzePostordine(stg[nod]);

    // Parcurgem subarborele drept
    afiseazaFrunzePostordine(dr[nod]);

    // Daca nodul curent este frunza, il afisam
    if (esteFrunza(nod))
        cout << info[nod] << " ";
}

// Functia principala
int main() {

    // Stabilim radacina arborelui
    radacina = 1;

    // Stabilim valorile nodurilor
    info[1] = 1;
    info[2] = 2;
    info[3] = 3;
    info[4] = 4;
    info[5] = 5;
    info[6] = 6;

    // Stabilim fiii stangi
    stg[1] = 2;
    stg[2] = 4;
    stg[3] = 0;
    stg[4] = 0;
    stg[5] = 0;
    stg[6] = 0;

    // Stabilim fiii drepti
    dr[1] = 3;
    dr[2] = 5;
    dr[3] = 6;
    dr[4] = 0;
    dr[5] = 0;
    dr[6] = 0;

    // Afisam parcurgerea in preordine
    cout << "Preordine: ";
    preordine(radacina);
    cout << '\n';

    // Afisam parcurgerea in inordine
    cout << "Inordine: ";
    inordine(radacina);
    cout << '\n';

    // Afisam parcurgerea in postordine
    cout << "Postordine: ";
    postordine(radacina);
    cout << '\n';

    // Afisam inaltimea arborelui
    cout << "Inaltime: " << inaltime(radacina) << '\n';

    // Afisam numarul de frunze
    cout << "Frunze: " << numarFrunze(radacina) << '\n';

    // Afisam suma valorilor din arbore
    cout << "Suma: " << suma(radacina) << '\n';

    // Afisam doar frunzele in postordine
    cout << "Frunze in postordine: ";
    afiseazaFrunzePostordine(radacina);
    cout << '\n';

    return 0;
}