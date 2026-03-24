#include <iostream>
#include <fstream>
using namespace std;

struct Nod {
    int info;
    Nod* stg;
    Nod* dr;
};

Nod* creareNod(int valoare) {
    Nod* p = new Nod;
    p->info = valoare;
    p->stg = nullptr;
    p->dr = nullptr;
    return p;
}

void preordine(Nod* rad) {
    if (rad == nullptr) return;
    cout << rad->info << " ";
    preordine(rad->stg);
    preordine(rad->dr);
}

void inordine(Nod* rad) {
    if (rad == nullptr) return;
    inordine(rad->stg);
    cout << rad->info << " ";
    inordine(rad->dr);
}

void postordine(Nod* rad) {
    if (rad == nullptr) return;
    postordine(rad->stg);
    postordine(rad->dr);
    cout << rad->info << " ";
}

int inaltime(Nod* rad) {
    if (rad == nullptr) return -1;
    int hStg = inaltime(rad->stg);
    int hDr = inaltime(rad->dr);
    return 1 + max(hStg, hDr);
}

int numarFrunze(Nod* rad) {
    if (rad == nullptr) return 0;
    if (rad->stg == nullptr && rad->dr == nullptr)
        return 1;
    return numarFrunze(rad->stg) + numarFrunze(rad->dr);
}

int suma(Nod* rad) {
    if (rad == nullptr) return 0;
    return rad->info + suma(rad->stg) + suma(rad->dr);
}

void stergeArbore(Nod* rad) {
    if (rad == nullptr) return;
    stergeArbore(rad->stg);
    stergeArbore(rad->dr);
    delete rad;
}

int main() {

    ifstream fin("arbore.txt");

    if (!fin) {
        cout << "Fisierul nu a fost gasit!";
        return 0;
    }

    int n, rad;
    fin >> n >> rad;

    int stg[101], dr[101];

    for (int i = 1; i <= n; i++)
        fin >> stg[i];

    for (int i = 1; i <= n; i++)
        fin >> dr[i];

    Nod* noduri[101];

    // creare noduri
    for (int i = 1; i <= n; i++)
        noduri[i] = creareNod(i);

    // conectare noduri
    for (int i = 1; i <= n; i++) {

        if (stg[i] != 0)
            noduri[i]->stg = noduri[stg[i]];

        if (dr[i] != 0)
            noduri[i]->dr = noduri[dr[i]];
    }

    Nod* radacina = noduri[rad];

    cout << "Preordine: ";
    preordine(radacina);
    cout << "\n";

    cout << "Inordine: ";
    inordine(radacina);
    cout << "\n";

    cout << "Postordine: ";
    postordine(radacina);
    cout << "\n";

    cout << "Inaltime: " << inaltime(radacina) << "\n";
    cout << "Frunze: " << numarFrunze(radacina) << "\n";
    cout << "Suma: " << suma(radacina) << "\n";

    stergeArbore(radacina);

    return 0;
}