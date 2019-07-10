#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
using namespace std;

enum Algorytm
{
    Euklidesa,
    Euklidesa_zoptymalizowany,
    Euklidesa_zoptymalizowany_bitshift
};

bool nolog = false, nopause = false, timer = false;
int main(int argc, char *args[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x],"-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    Algorytm algorithm;
    unsigned long long a, b;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Dla danych dwoch liczb naturalnych \'a\' i \'b\' znajdz najwieksza liczbe naturalna \'c\', ktora dzieli bez reszty liczbe \'a\' "
        "i liczbe \'b\'\n\n"
        "Program posiada 3 algorytmy, rozwiazujace problem:\n"
        "1.\n Skoro a/c jest liczba naturalna i b/c jest liczba naturalna to\n a/c - b/c = (1/c)(a-b), a przeciez (1/c)*abs(a-b) "
        "jest liczba naturalna\n Wykorzystujemy ten fakt i odejmujemy liczby, a wieksza z liczb zastepujemy roznica\n "
        "Gdy a = b, wtedy a/b = 1 i b/a = 1, czyli a = b = c\n\n"

        "2.\n Jezeli a = d * b + r, to bedziemy mogli odjac liczbe b od a d razy i zostanie nam r\n "
        "zatem a mod b = r, w ten sposob mozna usprawnic algorytm\n\n"

        "3.\n Procesory szybciej wykonuja operacje przesunieca bitowego niz dzielenia (implentacja modulo i dzielenia to zazwyczaj ta sama operacja, tylko ze z inna zwracana wartoscia), dlatego szybciej jest wykonac dzielenie przez dwa "
        "(przesuniecie bitowe o jeden w lewo)\n "
        "Operacja NWD(a,b) w zaleznosci od parzystosci (p - parzyste np - nieparzyste) wyglada tak:\n "
        "NWD(p,p) - wspolny dzielnik wynosi 2, dzielimy obie liczby przez dwa i zliczamy liczbe takich dzielen\n "
        "NWD(p, np) lub NWD(np, p) - 2 nie jest wspolnym dzielnikiem wiec p = p/2 ruszy algorytm, a nie wplynie bezposrednio na wartosc c\n "
        "NWD(np, np), zastepujemy jedna z liczb abs(a-b)/2, az do zrownania\n "
        "c = n^[liczba_zliczen] * a\n\n"
        "P.S.: Algorytmy dziala tak samo dla liczb ujemnych, dlatego praktyczne uzycie tego algorytmu jako funkcji, uzywaloby "
        "wartosci bezwzglednych parametrow, a NWD zawsze byloby liczba dodatnia\n\n";
    cout << "Wybierz algortym:" << endl;
    {
        unsigned int alg = static_cast<Algorytm>(4);
        bool display = false;
        while (alg > 3){
            if (display) cout << "Podano nieprawidlowa liczbe. Sprobuj ponownie:" << endl;
            cin >> alg;
            algorithm = static_cast<Algorytm>(alg-1);
            display = true;
        }
    }

    if (!nolog) cout << "Podaj liczbe naturalna a:" << endl;
	cin >> a;
    cout << endl;

    if (!nolog) cout << "Podaj liczbe naturalna b:" << endl;
	cin >> b;
    cout << endl;

    //First writing to cout explains how respective algoritms work
    if (!nolog) cout << "Najwiekszy wspolny dzielnik liczby " << a << " i " << b << " wynosi: ";
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    switch (algorithm){
case Euklidesa:
    if (timer) start = chrono::high_resolution_clock::now();
    while (a != b) {
        if (a > b) a-=b;
        else b-=a;
    }
    if (timer) stop = chrono::high_resolution_clock::now();
        break;
case Euklidesa_zoptymalizowany:
    if (timer) start = chrono::high_resolution_clock::now();
        while (b){
           a %= b;
           swap(a, b);
        }
    if (timer) stop = chrono::high_resolution_clock::now();
        break;
default:
    if (timer) start = chrono::high_resolution_clock::now();
    int k = 0;
    if (!a) break;
    else if (!b) {
        swap(a, b);
        break;
    }
    for (; !((a | b) & 1); ++k)
    {
        a >>= 1;
        b >>= 1;
    }
    while (!(a & 1)) a >>= 1;
    while (!(b & 1)) b >>= 1;
    if (a < b) swap(a, b);
    while (b)
    {
        a -= b;
        a >>= 1;
        if (!a) { a = b; break;}
        while (!(a & 1)) a >>= 1;
        if (a < b) swap(a, b);
    }
    a <<= k;
    if (timer) stop = chrono::high_resolution_clock::now();
        break;
    }
    cout << a << endl;
    if (timer)
    {
        if (!nolog) cout << "Wykonanie algorytmu trwalo: ";
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << fixed << duration.count();
        if (!nolog) cout << " mikrosekund";
        cout << endl;
    }
    //Press any key to exit the program
    if (!nopause) system("pause");
    return 0;
}
