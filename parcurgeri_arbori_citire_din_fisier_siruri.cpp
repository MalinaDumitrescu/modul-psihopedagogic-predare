#include <iostream>
#include <fstream>

using namespace std;

// Definim structura unui nod din arbore
struct Nod {

    // Valoarea memorata in nod
    int info;

    // Pointer catre fiul stang
    Nod* stg;

    // Pointer catre fiul drept
    Nod* dr;
};

// Functie care creeaza un nod nou in memorie
Nod* creareNod(int valoare) {

    // Alocam dinamic memorie pentru un nod
    Nod* p = new Nod;

    // Punem valoarea primita in campul info
    p->info = valoare;

    // Initial nodul nu are fiu stang
    p->stg = nullptr;

    // Initial nodul nu are fiu drept
    p->dr = nullptr;

    // Returnam adresa nodului creat
    return p;
}

// Functie de parcurgere in preordine: Radacina - Stanga - Dreapta
void preordine(Nod* rad) {

    // Daca nodul nu exista, ne oprim
    if (rad == nullptr) return;

    // Afisam valoarea nodului curent
    cout << rad->info << " ";

    // Parcurgem recursiv subarborele stang
    preordine(rad->stg);

    // Parcurgem recursiv subarborele drept
    preordine(rad->dr);
}

// Functie de parcurgere in inordine: Stanga - Radacina - Dreapta
void inordine(Nod* rad) {

    // Daca nodul nu exista, ne oprim
    if (rad == nullptr) return;

    // Parcurgem recursiv subarborele stang
    inordine(rad->stg);

    // Afisam valoarea nodului curent
    cout << rad->info << " ";

    // Parcurgem recursiv subarborele drept
    inordine(rad->dr);
}

// Functie de parcurgere in postordine: Stanga - Dreapta - Radacina
void postordine(Nod* rad) {

    // Daca nodul nu exista, ne oprim
    if (rad == nullptr) return;

    // Parcurgem recursiv subarborele stang
    postordine(rad->stg);

    // Parcurgem recursiv subarborele drept
    postordine(rad->dr);

    // Afisam valoarea nodului curent
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

    // Intoarcem 1 + maximul dintre cele doua inaltimi
    return 1 + max(hStg, hDr);
}

// Functie care calculeaza numarul de frunze
int numarFrunze(Nod* rad) {

    // Daca arborele este vid, nu are frunze
    if (rad == nullptr) return 0;

    // Daca nodul nu are nici fiu stang, nici fiu drept, este frunza
    if (rad->stg == nullptr && rad->dr == nullptr)
        return 1;

    // Numarul total de frunze este suma frunzelor din stanga si dreapta
    return numarFrunze(rad->stg) + numarFrunze(rad->dr);
}

// Functie care calculeaza suma tuturor valorilor din arbore
int suma(Nod* rad) {

    // Daca arborele este vid, suma este 0
    if (rad == nullptr) return 0;

    // Suma = nod curent + suma din stanga + suma din dreapta
    return rad->info + suma(rad->stg) + suma(rad->dr);
}

// Functie care sterge tot arborele din memorie
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

// Functia principala
int main() {

    // Deschidem fisierul de intrare
    ifstream fin("arbore.txt");

    // Verificam daca fisierul s-a deschis corect
    if (!fin) {

        // Afisam mesaj de eroare daca fisierul nu exista
        cout << "Fisierul nu a fost gasit!";

        // Incheiem programul
        return 0;
    }

    // n = numarul de noduri, rad = indicele radacinii
    int n, rad;

    // Citim numarul de noduri si radacina din fisier
    fin >> n >> rad;

    // Vector pentru fiii stangi
    int stg[101], dr[101];

    // Citim vectorul stg din fisier
    for (int i = 1; i <= n; i++)
        fin >> stg[i];

    // Citim vectorul dr din fisier
    for (int i = 1; i <= n; i++)
        fin >> dr[i];

    // Vector de pointeri catre nodurile create
    Nod* noduri[101];

    // Cream toate nodurile arborelui
    for (int i = 1; i <= n; i++)
        noduri[i] = creareNod(i);

    // Legam nodurile intre ele dupa vectorii stg si dr
    for (int i = 1; i <= n; i++) {

        // Daca exista fiu stang, il conectam
        if (stg[i] != 0)
            noduri[i]->stg = noduri[stg[i]];

        // Daca exista fiu drept, il conectam
        if (dr[i] != 0)
            noduri[i]->dr = noduri[dr[i]];
    }

    // Stabilim adresa radacinii arborelui
    Nod* radacina = noduri[rad];

    // Afisam parcurgerea in preordine
    cout << "Preordine: ";
    preordine(radacina);
    cout << "\n";

    // Afisam parcurgerea in inordine
    cout << "Inordine: ";
    inordine(radacina);
    cout << "\n";

    // Afisam parcurgerea in postordine
    cout << "Postordine: ";
    postordine(radacina);
    cout << "\n";

    // Afisam inaltimea arborelui
    cout << "Inaltime: " << inaltime(radacina) << "\n";

    // Afisam numarul de frunze
    cout << "Frunze: " << numarFrunze(radacina) << "\n";

    // Afisam suma valorilor din arbore
    cout << "Suma: " << suma(radacina) << "\n";

    // Eliberam memoria ocupata de arbore
    stergeArbore(radacina);

    // Programul se termina corect
    return 0;
}