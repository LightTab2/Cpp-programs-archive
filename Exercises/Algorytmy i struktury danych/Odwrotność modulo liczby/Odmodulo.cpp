#include <iostream>
#include <cmath>
#include <chrono>
#include <cstring>
using namespace std;

bool nolog = false, nopause = false, timer = false;

bool ExtendedEuclidean(long long a, long long b, long long &x)
{
    long long y, u = y = 0, v = 1,
         bcopy = b;
    //If they're negative, make them positive. Cast 'depression-away' spell on 'em
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    if (a < b)
    {
        swap(a, b);
        swap(x, u);
        swap(y, v);
    }
    while (b)
    {
        long long q = a/b;
        a %= b;
        x -= u * q;
        y -= v * q;
        swap(a, b);
        swap(x, u);
        swap(y, v);
    }
    if (x < 0) x += bcopy;
    if (a == 1) return true;
    return false;
}

int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x],"-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    long long a,b;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n" //maybe I should use wcout and polish locale, the longer the text the less readable it is
        "Dla danych liczb naturalnych a i b znajdz taka liczbe naturalna x, aby a * x % b = 1\n"
        "lub stwierdz, iz liczba x nie istnieje.\n\n"
        "Jestem ciekaw, czy nastepujace rozwiazane bedzie prawidlowe z uwzglednieniem liczb ujemnych, dlatego "
        "oryginalne 'liczba naturalna' w tresci zadania moze tutaj byc czytane jako 'liczba calkowita'\n\n"

        "Rozwiazanie (bedzie troche matematyki):\n"
        "ax mod b = 1 jest niemozliwe, jezeli a i b nie sa wzglednie pierwsze, dowod:\n"
        "Jezeli a i b nie sa wzglednie pierwsze, to prawda, ze a = c * y i b = c * z\n"
        "ax = qb + r <=> (c * y)x = q(c * z) + r <=> r = c(xy - qz)\n"
        "Jezeli warunki sa spelnione, to wszystkie liczby z wyjatkiem q sa naturalne, a q jest liczba calkowita, "
        "r to reszta z dzielenia. W takim razie niezaleznie od wyrazenia w nawiasie, jezeli c aka wspolny "
        "dzielnik nie jest rowny 1 reszta z dzielenia takze nigdy nie bedzie rowna 1\n\n"
        "Do nastepnej czesci bedzie potrzebne zrozumienie tozsamosci Bezouta:\n"
        "Dla liczb calkowitych a i b o wspolnym dzielniku d dowolne liczby calkowite x,y spelniaja:\n"
        "ax + by = cd, gdzie c to liczba calkowita;"

        "Dowod:\n"
        "Skoro d jest najwiekszym wspolnym dzielnikiem: a = e * d, b = f * d    e,f naleza do calkowitych\n"
        "(e * d)x + (f * d)y = c*d <=>\n"
        "c = e * x + f * y, c sklada sie z sumy iloczynow liczb naturalnych i calkowitych, zatem tez jest calkowita\n"
        "Dlaczego nie moze byc wieloktrotnoscia mniejszego wspolnym dzielnika?\n"
        "Moze, ale i tak ta wielkrotonosc bedzie rowna c * d. Wikipedia ma naprawde ciekawy dowod, ale chyba prostszy "
        "jest ten, bo to tylko zwykle przeksztalcenia:\n"
        "w to wspolny dzielnik inny (zatem tez i mniejszy) niz d:\n"
        "a = g * w = e * d, b = h * w = f * d\n"
        "(g * w)x + (h * w)y = j * w <=>\n"
        "(e * d)x + (f * d)y = j * w <=>\n"
        "c * d = j * w\n\n"

        "W rozszerzonym alogrytmie Euklidesa dla liczb a,b postepuje sie jak w normalnym algorytmie, tyle ze kazda "
        "liczba jest zapisana w postaci:\n"
        "a = xa + yb, na poczatku x = 1, y = 0\n"
        "b = ua + vb, na poczatku u = 0, v = 1\b"
        "Czyli gdy sprowadzimy nasze a lub b do NWD(a,b) na miejsce x,y lub u,v wskocza takie liczby, ze spelnione "
        "bedzie xa + yb = NWD(a,b) lub ua + vb = NWD(a,b). Jezeli NWD(a,b) = 1, to liczba posiada odwortnosc modulo i "
        "liczymy NWD(a,b), jak w normalnym algorytmie, stosujac takie same operacje na wyrazeniu xa + yb i ua + vb, czyli:\n"
        "Jezeli b>a liczymy q = b/a, w przeciwnym wypadku q=a/b\n"
        "Jezeli b>a:\n"
        "b := b - q * a\n"
        "ua + vb := ua + vb - q(xa + yb) => u := u - qx,   v := v - qy\n"
        "Jezeli a>b:\n"
        "a := a - q * b\n"
        "xa + yb := xa + yb - q(ua + vb) => x := x - qu,   y := y - qv\n\n"
        "Jezeli NWD(a,b) bedzie rowne 1, na koncu zostanie nam liczba x badz u, ktora bedzie szukanym minimalnym "
        "wspolczynnikiem Bezouta liczb a i b. Twierdzenie, ze jest to minimalny wspolczynnik mozna udowodnic poprzez indukcje, nie "
        "bede poszerzal i tak juz obszernego dowodu o ten element, dosc intuicyjne powinno wydawac sie, ze produktem "
        "odejmowanie liczb zapisanych w postaci sumy minimalnych wspolczynnikow Bezouta daje nam liczbe zapisana w postaci "
        "minimalnych wspolczynnikow Bezouta. Dlaczego to jest wazne? Poniewaz wtedy zawsze prawda jest, ze x < a, czyli x nigdy nie "
        "wyjdzie poza zakres typu danych. Dowod ze ax mod b = 1:\n"
        "xa + yb = 1 <=> xa = 1 - yb, stad\n"
        "xa mod b = (1 - yb) mod b = (1 mod b - yb mod b) mod b = (1 - 0) mod b = 1 mod b = 1\n\n"
        "Zalozmy ze naszym szukanym wspolczynnikiem okazalo sie byc x, ktore jest ujemne\n"
        "Komputery licza modulo z ujemnych liczb, ale dla nas latwiej byloby znac dodatnia odwrotnosc modulo\n"
        "Jezeli jest to minimalny wspolczynik Bezouta, to wiemy, ze |x| < b, zatem istnieje takie k < b, ze x = b - k\n"
        "ax mod b = x(b - z) mod b = (xb - xz) mod b = -xz mod b = 1\n"
        "Zobaczmy jak zmieni sie sytuacja po dodaniu b (co zapewnia ze liczba bedzie dodatnia) do wartosci x:\n"
        "ax mod b = x(2b - z) mod b = (2xb - xz) mod b = -xz mod b = 1\n\n";
        
    if (!nolog) cout << "Podaj dwie liczby a i b, a program obliczy odwrotnosc modulo b liczby a, jezeli istnieje\n"
        << "Podaj a:\n";
    cin >> a;
    cout << endl;

    if (!nolog) cout << "Podaj b:\n";
    cin >> b;
    cout << endl;

    long long x = 1;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
    if (ExtendedEuclidean(a,b,x))
    {
        if (!nolog) cout << "Odwrotnoscia modulo " << b << " liczby " << a << " jest:\n";
        cout << x << endl;
    }
    else
    {
        if (!nolog) cout << "Odwrotnoscia modulo " << b << " liczby " << a;
        cout << " NIE ISTNIEJE\n";
    }
    
    if (timer) stop = chrono::high_resolution_clock::now();
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
