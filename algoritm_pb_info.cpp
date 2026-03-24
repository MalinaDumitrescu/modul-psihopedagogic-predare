#include <iostream>
using namespace std;


// Variabila n = numărul de noduri din arbore
// st[i] = indicele fiului stâng al nodului i
// dr[i] = indicele fiului drept al nodului i
int n , st[101], dr[101];


// Funcție care citește datele arborelui de la tastatură
void Citire()
{
    // Citim numărul de noduri
    cin >> n;

    // Citim vectorul fiilor stângi
    for(int i = 1 ; i <= n ; i ++)
        cin >> st[i];

    // Citim vectorul fiilor drepți
    for(int i = 1 ; i <= n ; i ++)
        cin >> dr[i];
}


// Funcție care determină rădăcina arborelui
int Radacina()
{
    // Rădăcina este nodul care NU apare ca fiu în st[] sau dr[]

    // Vector auxiliar: v[i] = 1 dacă nodul i apare ca fiu
    int v[101] = {0};

    // Parcurgem toate nodurile
    for(int i = 1 ; i <= n ; i ++)
    {
        // Dacă există fiu stâng
        if(st[i] != 0)

            // marcăm că nodul st[i] apare ca fiu
            v[st[i]] = 1;

        // Dacă există fiu drept
        if(dr[i] != 0)

            // marcăm că nodul dr[i] apare ca fiu
            v[dr[i]] = 1;
    }

    // Căutăm nodul care NU apare ca fiu (acela este rădăcina)
    for(int i = 1 ; i <= n ; i ++)

        // Dacă nodul nu apare ca fiu
        if(v[i] == 0)

            // atunci acesta este rădăcina
            return i;

    // Dacă nu găsim rădăcina (situație rară), returnăm 0
    return 0;
}


// Funcție de parcurgere în inordine: Stânga - Rădăcină - Dreapta
void Inordine(int x)
{
    // Dacă nodul există
    if(x != 0)
    {
        // Parcurgem subarborele stâng
        Inordine(st[x]);

        // Afișăm nodul curent
        cout << x << " ";

        // Parcurgem subarborele drept
        Inordine(dr[x]);
    }
}


// Funcție de parcurgere în preordine: Rădăcină - Stânga - Dreapta
void Preordine(int x)
{
    // Dacă nodul există
    if(x != 0)
    {
        // Afișăm nodul curent
        cout << x << " ";

        // Parcurgem subarborele stâng
        Preordine(st[x]);

        // Parcurgem subarborele drept
        Preordine(dr[x]);
    }
}


// Funcție de parcurgere în postordine: Stânga - Dreapta - Rădăcină
void Postordine(int x)
{
    // Dacă nodul există
    if(x != 0)
    {
        // Parcurgem subarborele stâng
        Postordine(st[x]);

        // Parcurgem subarborele drept
        Postordine(dr[x]);

        // Afișăm nodul curent
        cout << x << " ";
    }
}


// Funcția principală a programului
int main()
{
    // Citim arborele de la tastatură
    Citire();

    // Determinăm rădăcina arborelui
    int R = Radacina();

    // Afișăm parcurgerea în inordine
    Inordine(R);

    // Trecem la linie nouă
    cout << endl;

    // Afișăm parcurgerea în preordine
    Preordine(R);

    // Trecem la linie nouă
    cout << endl;

    // Afișăm parcurgerea în postordine
    Postordine(R);

    // Trecem la linie nouă
    cout << endl;

    // Programul s-a terminat corect
    return 0;
}