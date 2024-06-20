#include <iostream>

using namespace std;

//Zadanie 2 z roku 2015
//Dzialanie programu: gra w kolko i krzyzyk pomiedzy czlowiekiem a komputerem
//gdzie komputer wybiera sam miejsce ustawienia znaku w zaleznosci od gry czlowieka.
//Komputer nie moze przegrac gry, moze ja tylko wugrac lub zremisowac.


// Funkcja rysuje plansz� gry w k�ko i krzy�yk
// Plansza przechowywana jest w tablicy t[] w elementach o nast�puj�cych indeksach:
// t[1] t[2] t[3]
// t[4] t[5] t[6]
// t[7] t[8] t[9]
void plansza(char t[])
{
    for (int i = 1; i <= 9; i++)
    {
        cout << " " << t[i] << " ";
        if (i % 3)       cout << "|";               // Po elementach 1,2,4,5,7,8 rysujemy |
        else if (i != 9) cout << "\n---+---+---\n"; // Po elementach 3 i 6 poprzeczka
        else            cout << endl;              // Po elemencie 9 koniec wiersza  
    }
}

// Funkcja zwraca true, je�li nast�pi�a
// wygrana danego zawodnika
bool wygrana(char t[], char g, bool cisza)
{
    bool test;
    int i;

    test = false; // Zmienna przyjmuje true, je�li zawodnik ma trzy figury w wierszu, kolumnie lub na przek�tnych

    for (i = 1; i <= 7; i += 3) 
    {
        test |= ((t[i] == g) && (t[i + 1] == g) && (t[i + 2] == g));   // Sprawdzamy wiersze
    }

    for (i = 1; i <= 3; i++)
    {
        test |= ((t[i] == g) && (t[i + 3] == g) && (t[i + 6] == g));  // Sprawdzamy kolumny 
    }

    test |= ((t[1] == g) && (t[5] == g) && (t[9] == g)); // Sprawdzamy przek�tn� 1-5-9

    test |= ((t[3] == g) && (t[5] == g) && (t[7] == g)); // Sprawdzamy przek�tn� 3-5-7

    if (test)
    {
        if (!cisza)
        {
            plansza(t);
            cout << "\nGRACZ " << g << " WYGRYWA!!!\n\n";
        }
        return true;
    }
    return false;
}

// Funkcja zwraca true, je�li na planszy nie ma ju� �adnego wolnego pola na ruch.
bool remis(char t[], bool cisza)
{
    // Je�li napotkamy spacj�, to plansza posiada wolne pola - zwracamy false  

    for (int i = 1; i <= 9; i++) if (t[i] == ' ') return false;

    // Je�li p�tla for zako�czy�a si� normalnie, to na �adnym polu planszy nie by�o
    // spacji. Mamy do czynienia z remisem - zwracamy true

    if (!cisza)
    {
        plansza(t); cout << "\nREMIS !!!\n\n";
    }
    return true;
}

// Algorytm rekurencyjny MINIMAX
// Do algorytmu wchodzimy z plansz�, na kt�rej ustawione jest pole
// bie��cego gracza. Parametr gracz przekazuje literk� gracza, a
// parametr mx przekazuje jego wynik w przypadku wygranej
int minimax(char t[], char gracz)
{
    int m, mmx;

    // Najpierw sprawdzamy, czy bie��cy gracz wygrywa na planszy. Je�li tak, to
    // zwracamy jego maksymalny wynik

    if (wygrana(t, gracz, true)) return (gracz == 'X') ? 1 : -1;

    // Nast�pnie sprawdzamy, czy nie ma remisu. Je�li jest, zwracamy wynik 0

    if (remis(t, true)) return 0;

    // B�dziemy analizowa� mo�liwe posuni�cia przeciwnika. Zmieniamy zatem
    // bie��cego gracza na jego przeciwnika

    gracz = (gracz == 'X') ? 'O' : 'X';

    // Algorytm MINIMAX w kolejnych wywo�aniach rekurencyjnych naprzemiennie analizuje
    // gr� gracza oraz jego przeciwnika. Dla gracza oblicza maksimum wyniku gry, a dla
    // przeciwnika oblicza minimum. Warto�� mmx ustawiamy w zale�no�ci od tego, czyje
    // ruchy analizujemy:
    // X - liczymy max, zatem mmx <- -10
    // O - liczymy min, zatem mmx <-  10

    mmx = (gracz == 'O') ? 10 : -10;

    // Przegl�damy plansz� szukaj�c wolnych p� na ruch gracza. Na wolnym polu ustawiamy
    // literk� gracza i wyznaczamy warto�� tego ruchu rekurencyjnym wywo�aniem
    // algorytmu MINIMAX. Plansz� przywracamy i w zale�no�ci kto gra:
    // X - wyznaczamy maximum
    // O - wyznaczamy minimum

    for (int i = 1; i <= 9; i++)
        if (t[i] == ' ')
        {
            t[i] = gracz;
            m = minimax(t, gracz);
            t[i] = ' ';
            if (((gracz == 'O') && (m < mmx)) || ((gracz == 'X') && (m > mmx))) mmx = m;
        }
    return mmx;
}

// Funkcja wyznacza ruch dla komputera.
int komputer(char t[])
{
    int ruch, i, m, mmx;

    mmx = -10;
    for (i = 1; i <= 9; i++)
        if (t[i] == ' ')
        {
            t[i] = 'X';
            m = minimax(t, 'X');
            t[i] = ' ';
            if (m > mmx)
            {
                mmx = m; ruch = i;
            }
        }
    return ruch;
}

// Funkcja umo�liwia ruch gracza
// Po ruchu nast�puje zamiana gracza
void ruch(char t[], char& gracz)
{
    int r;

    plansza(t);
    if (gracz == 'O')
    {
        cout << "\nCZLOWIEK : wybiera ruch : ";
        cin >> r;
    }
    else
    {
        r = komputer(t);
        cout << "\nKOMPUTER : wybiera ruch : " << r << endl;
    }
    cout << "---------------------------\n\n";
    if ((r >= 1) && (r <= 9) && (t[r] == ' ')) t[r] = gracz;
    gracz = (gracz == 'O') ? 'X' : 'O';
}

int main()
{
    char t[10], gracz, wybor;

    //gra tyle gier dopoki nie powiemy ze koniec
    do
    {
        cout << "Gra w Kolko i Krzyzyk dla gracza i komputera\n"
            "============================================\n\n";
        for (int i = 1; i <= 9; i++) t[i] = ' ';
        gracz = 'O';

        while (!wygrana(t, 'X', false) && !wygrana(t, 'O', false) && !remis(t, false)) ruch(t, gracz);

        cout << "Jeszcze raz ? (T = TAK) : ";
        cin >> wybor;
        cout << "\n\n\n";

    } while ((wybor == 'T') || (wybor == 't'));
}