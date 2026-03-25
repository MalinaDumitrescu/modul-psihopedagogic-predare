#include <iostream>
#include <fstream>
#include <climits>   // pentru INT_MIN si INT_MAX
using namespace std;

/*
    CERINTE

    Un arbore binar de cautare este un arbore binar care are in plus
    urmatoarele proprietati:
    - cheile stocate in noduri apartin unei multimi peste care exista
      o relatie de ordine
    - cheia dintr-un nod oarecare este mai mare decat cheile tuturor
      nodurilor din subarborele stang si mai mica decat cheile tuturor
      nodurilor din subarborele drept

    1. Se da un vector cu n intregi.
       a) Scrieti o functie care sa creeze un arbore binar de cautare
          cu valorile din vector.
       b) Scrieti o functie care determina valoarea maxima.
       c) Scrieti o functie care determina valoarea minima.
       d) Afisati arborele in preordine, inordine si postordine.

    2. Se da un arbore binar ce stocheaza intregi.
       Scrieti o functie care verifica daca arborele este arbore
       binar de cautare.

    3. Se da un arbore binar de cautare ce stocheaza intregi.
       Scrieti o functie care verifica daca o valoare data se afla
       in arbore (cautare).
*/

// deschidem fisierul de intrare
ifstream fin("date.in");

// val[i]     = valoarea din nodul i
// stanga[i]  = indexul copilului stang al nodului i
// dreapta[i] = indexul copilului drept al nodului i
int val[100], stanga[100], dreapta[100];

// n   = numarul total de noduri create pana acum
// rad = radacina arborelui
int n = 0;
int rad = 0;

/*
    1.a) FUNCTIA DE INSERARE / CREARE A ARBORELUI BINAR DE CAUTARE

    Rol:
    - adauga o valoare x in arborele binar de cautare

    Parametri:
    - nod este transmis prin referinta, ca sa putem modifica direct
      copilul stang/drept sau chiar radacina
    - x este valoarea pe care vrem sa o inseram

    Idee:
    1. Daca nod == 0, inseamna ca aici nu exista nod.
       Deci cream un nod nou.
    2. Daca x este mai mic decat valoarea curenta, mergem in stanga.
    3. Daca x este mai mare decat valoarea curenta, mergem in dreapta.
    4. Daca x este egal, nu il mai inseram, ca sa evitam duplicatele.
*/
void inserare(int &nod, int x)
{
    // daca pozitia curenta este libera, cream nod nou
    if (nod == 0)
    {
        n++;                  // crestem numarul total de noduri
        val[n] = x;           // salvam valoarea in noul nod
        stanga[n] = 0;        // initial nodul nu are copil stang
        dreapta[n] = 0;       // initial nodul nu are copil drept
        nod = n;              // legam aceasta pozitie de noul nod
    }
    else if (x < val[nod])
    {
        // daca x este mai mic, trebuie sa il inseram in subarborele stang
        inserare(stanga[nod], x);
    }
    else if (x > val[nod])
    {
        // daca x este mai mare, trebuie sa il inseram in subarborele drept
        inserare(dreapta[nod], x);
    }
    else
    {
        // daca x este egal cu val[nod], nu facem nimic
        // in acest exemplu nu permitem duplicate
    }
}

/*
    1.d) PARCURGEREA SRD = inordine

    Ordinea este:
    1. Subarbore stang
    2. Radacina
    3. Subarbore drept

    Proprietate importanta:
    - daca arborele este binar de cautare, aceasta parcurgere afiseaza
      valorile in ordine crescatoare
*/
void SRD(int nod)
{
    // daca nodul exista
    if (nod != 0)
    {
        SRD(stanga[nod]);        // mergem in stanga
        cout << val[nod] << " "; // afisam radacina
        SRD(dreapta[nod]);       // mergem in dreapta
    }
}

/*
    1.d) PARCURGEREA RSD = preordine

    Ordinea este:
    1. Radacina
    2. Subarbore stang
    3. Subarbore drept
*/
void RSD(int nod)
{
    if (nod != 0)
    {
        cout << val[nod] << " "; // afisam radacina prima
        RSD(stanga[nod]);        // apoi stanga
        RSD(dreapta[nod]);       // apoi dreapta
    }
}

/*
    1.d) PARCURGEREA SDR = postordine

    Ordinea este:
    1. Subarbore stang
    2. Subarbore drept
    3. Radacina
*/
void SDR(int nod)
{
    if (nod != 0)
    {
        SDR(stanga[nod]);        // mai intai stanga
        SDR(dreapta[nod]);       // apoi dreapta
        cout << val[nod] << " "; // la final radacina
    }
}

/*
    1.c) FUNCTIA PENTRU MINIM

    Intr-un arbore binar de cautare:
    - cea mai mica valoare este in nodul cel mai din stanga

    Idee:
    - din radacina, mergem continuu pe legaturile din stanga
      pana nu mai exista copil stang
*/
int minim(int nod)
{
    // daca arborele este gol
    if (nod == 0)
        return -1;

    // mergem cat de mult se poate in stanga
    while (stanga[nod] != 0)
        nod = stanga[nod];

    // valoarea nodului obtinut este minima
    return val[nod];
}

/*
    1.b) FUNCTIA PENTRU MAXIM

    Intr-un arbore binar de cautare:
    - cea mai mare valoare este in nodul cel mai din dreapta

    Idee:
    - din radacina, mergem continuu pe legaturile din dreapta
      pana nu mai exista copil drept
*/
int maxim(int nod)
{
    // daca arborele este gol
    if (nod == 0)
        return -1;

    // mergem cat de mult se poate in dreapta
    while (dreapta[nod] != 0)
        nod = dreapta[nod];

    // valoarea nodului obtinut este maxima
    return val[nod];
}

/*
    2) FUNCTIA DE VERIFICARE DACA ARBORELE ESTE ABC

    Atentie:
    Nu este suficient sa verificam doar:
    - nodul stang < radacina
    - nodul drept > radacina

    Trebuie verificata regula pentru TOT subarborele.

    De aceea folosim 2 limite:
    - limitaMin = cea mai mica valoare permisa
    - limitaMax = cea mai mare valoare permisa

    Exemplu:
    daca un nod este in subarborele drept al lui 10,
    atunci el trebuie sa fie > 10, chiar daca este copil al altui nod.
*/
bool esteABC(int nod, int limitaMin, int limitaMax)
{
    // arborele gol este considerat corect
    if (nod == 0)
        return true;

    // verificam daca valoarea nodului respecta intervalul permis
    if (val[nod] <= limitaMin || val[nod] >= limitaMax)
        return false;

    // verificam recursiv:
    // - in stanga, toate valorile trebuie sa fie intre limitaMin si val[nod]
    // - in dreapta, toate valorile trebuie sa fie intre val[nod] si limitaMax
    return esteABC(stanga[nod], limitaMin, val[nod]) &&
           esteABC(dreapta[nod], val[nod], limitaMax);
}

/*
    3) FUNCTIA DE CAUTARE

    Idee:
    - daca x este egal cu valoarea din nod, l-am gasit
    - daca x este mai mic, cautam in stanga
    - daca x este mai mare, cautam in dreapta
    - daca ajungem la 0, inseamna ca nu exista
*/
bool cauta(int nod, int x)
{
    // daca nu exista nod, valoarea nu a fost gasita
    if (nod == 0)
        return false;

    // daca am gasit valoarea
    if (val[nod] == x)
        return true;

    // alegem directia potrivita
    if (x < val[nod])
        return cauta(stanga[nod], x);
    else
        return cauta(dreapta[nod], x);
}

int main()
{
    int x;

    /*
        REZOLVARE 1.a

        Citim toate valorile din fisier si construim arborele.

        Exemplu:
        daca in date.in avem:
        5 3 8 2

        arborele va deveni:
              5
             / \
            3   8
           /
          2
    */
    while (fin >> x)
        inserare(rad, x);

    /*
        REZOLVARE 1.d

        Afisam cele 3 parcurgeri cerute:
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
        REZOLVARE 1.c SI 1.b

        Afisam valoarea minima si valoarea maxima
    */
    cout << "Valoarea minima este: " << minim(rad) << "\n";
    cout << "Valoarea maxima este: " << maxim(rad) << "\n";

    /*
        REZOLVARE 2

        Verificam daca arborele obtinut este arbore binar de cautare
    */
    if (esteABC(rad, INT_MIN, INT_MAX))
        cout << "Arborele este binar de cautare.\n";
    else
        cout << "Arborele NU este binar de cautare.\n";

    /*
        REZOLVARE 3

        Citim o valoare de la tastatura si verificam daca exista
        in arbore
    */
    int k;
    cout << "Introdu valoarea cautata: ";
    cin >> k;

    if (cauta(rad, k))
        cout << "Valoarea exista in arbore.\n";
    else
        cout << "Valoarea NU exista in arbore.\n";

    return 0;
}