#include <iostream>
#include <fstream>
using namespace std;

/*
    CERINTE

    Se da fisierul date.in care contine valorile unui arbore binar de cautare.

    a) Construiti arborele binar de cautare folosind valorile din fisier.
    b) Afisati arborele in:
       - preordine
       - inordine
       - postordine
    c) Determinati numarul de noduri din arbore.
    d) Determinati numarul de frunze din arbore.
    e) Calculati suma valorilor din arbore.
    f) Determinati inaltimea arborelui.
    g) Afisati toate nodurile frunza.
    h) Determinati cate noduri au exact un singur fiu.
    i) Determinati cate noduri au exact doi fii.
    j) Cititi o valoare de la tastatura si determinati:
       - daca valoarea exista in arbore
       - pe ce nivel se afla

    Observatie:
    - consideram radacina la nivelul 0
*/

// deschidem fisierul de intrare
ifstream fin("date.in");

// val[i]     = valoarea nodului i
// stanga[i]  = fiul stang al nodului i
// dreapta[i] = fiul drept al nodului i
int val[100], stanga[100], dreapta[100];

// n = numarul total de noduri
// rad = radacina arborelui
int n = 0;
int rad = 0;

/*
    a) FUNCTIA DE INSERARE

    Rol:
    - adauga o valoare x in arborele binar de cautare

    Idee:
    - daca locul este liber, cream nod nou
    - daca x < valoarea curenta, mergem in stanga
    - daca x > valoarea curenta, mergem in dreapta
    - daca x == valoarea curenta, nu mai inseram
*/
void inserare(int &nod, int x)
{
    if (nod == 0)
    {
        n++;
        val[n] = x;
        stanga[n] = 0;
        dreapta[n] = 0;
        nod = n;
    }
    else if (x < val[nod])
    {
        inserare(stanga[nod], x);
    }
    else if (x > val[nod])
    {
        inserare(dreapta[nod], x);
    }
    else
    {
        // nu inseram duplicate
    }
}

/*
    b) PARCURGERE RSD = preordine

    Ordine:
    - Radacina
    - Stanga
    - Dreapta
*/
void RSD(int nod)
{
    if (nod != 0)
    {
        cout << val[nod] << " ";
        RSD(stanga[nod]);
        RSD(dreapta[nod]);
    }
}

/*
    b) PARCURGERE SRD = inordine

    Ordine:
    - Stanga
    - Radacina
    - Dreapta

    La un arbore binar de cautare, afiseaza valorile in ordine crescatoare.
*/
void SRD(int nod)
{
    if (nod != 0)
    {
        SRD(stanga[nod]);
        cout << val[nod] << " ";
        SRD(dreapta[nod]);
    }
}

/*
    b) PARCURGERE SDR = postordine

    Ordine:
    - Stanga
    - Dreapta
    - Radacina
*/
void SDR(int nod)
{
    if (nod != 0)
    {
        SDR(stanga[nod]);
        SDR(dreapta[nod]);
        cout << val[nod] << " ";
    }
}

/*
    c) NUMARUL DE NODURI

    Daca nodul nu exista, intoarcem 0.
    Altfel:
    - 1 pentru nodul curent
    - plus numarul de noduri din stanga
    - plus numarul de noduri din dreapta
*/
int numarNoduri(int nod)
{
    if (nod == 0)
        return 0;

    return 1 + numarNoduri(stanga[nod]) + numarNoduri(dreapta[nod]);
}

/*
    d) NUMARUL DE FRUNZE

    O frunza este un nod care nu are nici fiu stang, nici fiu drept.
*/
int numarFrunze(int nod)
{
    if (nod == 0)
        return 0;

    if (stanga[nod] == 0 && dreapta[nod] == 0)
        return 1;

    return numarFrunze(stanga[nod]) + numarFrunze(dreapta[nod]);
}

/*
    e) SUMA VALORILOR DIN ARBORE

    Daca nodul nu exista, suma este 0.
    Altfel:
    - valoarea nodului curent
    - plus suma din stanga
    - plus suma din dreapta
*/
int sumaNoduri(int nod)
{
    if (nod == 0)
        return 0;

    return val[nod] + sumaNoduri(stanga[nod]) + sumaNoduri(dreapta[nod]);
}

/*
    f) INALTIMEA ARBORELUI

    Definitie folosita:
    - arborele gol are inaltimea 0
    - un arbore nevid are:
      1 + maximul dintre inaltimea subarborelui stang si drept
*/
int inaltime(int nod)
{
    if (nod == 0)
        return 0;

    int hs = inaltime(stanga[nod]);
    int hd = inaltime(dreapta[nod]);

    if (hs > hd)
        return 1 + hs;
    else
        return 1 + hd;
}

/*
    g) AFISAREA FRUNZELOR

    Daca nodul este frunza, il afisam.
    Altfel, continuam recursiv in stanga si in dreapta.
*/
void afisareFrunze(int nod)
{
    if (nod != 0)
    {
        if (stanga[nod] == 0 && dreapta[nod] == 0)
        {
            cout << val[nod] << " ";
        }
        else
        {
            afisareFrunze(stanga[nod]);
            afisareFrunze(dreapta[nod]);
        }
    }
}

/*
    h) NUMARUL DE NODURI CU EXACT UN SINGUR FIU

    Un nod are exact un singur fiu daca:
    - are fiu stang si nu are fiu drept
      sau
    - nu are fiu stang si are fiu drept
*/
int noduriUnFiu(int nod)
{
    if (nod == 0)
        return 0;

    int cnt = 0;

    if ((stanga[nod] == 0 && dreapta[nod] != 0) ||
        (stanga[nod] != 0 && dreapta[nod] == 0))
    {
        cnt = 1;
    }

    return cnt + noduriUnFiu(stanga[nod]) + noduriUnFiu(dreapta[nod]);
}

/*
    i) NUMARUL DE NODURI CU EXACT DOI FII

    Un nod are doi fii daca:
    - are si fiu stang
    - are si fiu drept
*/
int noduriDoiFii(int nod)
{
    if (nod == 0)
        return 0;

    int cnt = 0;

    if (stanga[nod] != 0 && dreapta[nod] != 0)
    {
        cnt = 1;
    }

    return cnt + noduriDoiFii(stanga[nod]) + noduriDoiFii(dreapta[nod]);
}

/*
    j) FUNCTIA DE CAUTARE

    Returneaza true daca valoarea x exista in arbore,
    altfel false.

    Pentru ca este arbore binar de cautare:
    - daca x < val[nod], cautam doar in stanga
    - daca x > val[nod], cautam doar in dreapta
*/
bool cauta(int nod, int x)
{
    if (nod == 0)
        return false;

    if (val[nod] == x)
        return true;

    if (x < val[nod])
        return cauta(stanga[nod], x);
    else
        return cauta(dreapta[nod], x);
}

/*
    j) NIVELUL UNEI VALORI IN ARBORE

    Parametri:
    - nod = nodul curent
    - x = valoarea cautata
    - niv = nivelul curent

    Intoarce:
    - nivelul pe care se afla valoarea
    - -1 daca valoarea nu exista

    Observatie:
    - consideram radacina la nivelul 0
*/
int nivel(int nod, int x, int niv)
{
    if (nod == 0)
        return -1;

    if (val[nod] == x)
        return niv;

    if (x < val[nod])
        return nivel(stanga[nod], x, niv + 1);
    else
        return nivel(dreapta[nod], x, niv + 1);
}

int main()
{
    int x;

    /*
        REZOLVARE a)

        Citim valorile din fisier si construim arborele binar de cautare.
    */
    while (fin >> x)
        inserare(rad, x);

    /*
        REZOLVARE b)

        Afisam cele 3 parcurgeri:
        - preordine
        - inordine
        - postordine
    */
    cout << "Parcurgere RSD (preordine): ";
    RSD(rad);
    cout << "\n";

    cout << "Parcurgere SRD (inordine): ";
    SRD(rad);
    cout << "\n";

    cout << "Parcurgere SDR (postordine): ";
    SDR(rad);
    cout << "\n";

    /*
        REZOLVARE c)

        Afisam numarul total de noduri.
    */
    cout << "Numarul de noduri este: " << numarNoduri(rad) << "\n";

    /*
        REZOLVARE d)

        Afisam numarul de frunze.
    */
    cout << "Numarul de frunze este: " << numarFrunze(rad) << "\n";

    /*
        REZOLVARE e)

        Afisam suma valorilor din arbore.
    */
    cout << "Suma valorilor din arbore este: " << sumaNoduri(rad) << "\n";

    /*
        REZOLVARE f)

        Afisam inaltimea arborelui.
    */
    cout << "Inaltimea arborelui este: " << inaltime(rad) << "\n";

    /*
        REZOLVARE g)

        Afisam toate nodurile frunza.
    */
    cout << "Frunzele arborelui sunt: ";
    afisareFrunze(rad);
    cout << "\n";

    /*
        REZOLVARE h)

        Afisam numarul nodurilor cu exact un singur fiu.
    */
    cout << "Numarul nodurilor cu un singur fiu este: " << noduriUnFiu(rad) << "\n";

    /*
        REZOLVARE i)

        Afisam numarul nodurilor cu exact doi fii.
    */
    cout << "Numarul nodurilor cu doi fii este: " << noduriDoiFii(rad) << "\n";

    /*
        REZOLVARE j)

        Citim o valoare de la tastatura si verificam:
        - daca exista
        - pe ce nivel se afla
    */
    int k;
    cout << "Introdu valoarea cautata: ";
    cin >> k;

    if (cauta(rad, k))
        cout << "Valoarea exista in arbore.\n";
    else
        cout << "Valoarea NU exista in arbore.\n";

    int niv = nivel(rad, k, 0);

    if (niv == -1)
        cout << "Valoarea nu are nivel deoarece nu exista in arbore.\n";
    else
        cout << "Valoarea se afla pe nivelul " << niv << ".\n";

    return 0;
}



/*  date.in  :
 *
7 4 10 2 6 8 12

Arborele va fi:

        7
      /   \
     4     10
    / \    / \
   2   6  8  12
Rezultate așteptate:
RSD: 7 4 2 6 10 8 12
SRD: 2 4 6 7 8 10 12
SDR: 2 6 4 8 12 10 7
număr noduri: 7
număr frunze: 4
sumă: 49
înălțime: 3
frunze: 2 6 8 12
noduri cu un fiu: 0
noduri cu doi fii: 3
Încă 3 fișiere bune pentru comparație
Varianta 1
1 2 3 4 5 6 7
Varianta 2
7 6 5 4 3 2 1
Varianta 3
15 9 20 4 12 17 25 2 6 11 14 */