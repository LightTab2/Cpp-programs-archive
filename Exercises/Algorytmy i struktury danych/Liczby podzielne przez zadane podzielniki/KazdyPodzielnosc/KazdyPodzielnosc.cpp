#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Interval
{
    long long min = ~(-1ull >> 1), max = -1ull >> 1;
};
const long long maximum = -1ull >> 1;
bool nolog = false, nopause = false;

int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
        else if (args[x] == "-nopause") nopause = true;
    }
    vector<long long> dzielniki;
	Interval interval;

    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "W przedziale <a;b> liczb calkowitych wyszukaj wszystkie liczby podzielne przez kazda "
        "z liczb z zadanego zbioru P\n\n";

    if (!nolog) cout << "Podaj przedzial liczb <a;b>:\nPodaj a:\n";
	cin >> interval.min;

    if (!nolog) cout << "Podaj b:\n";
    cin >> interval.max;
    while (interval.min < interval.max)
    {
        if (!nolog) cout << "\nPrzedzial nie moze sie konczyc mniejsza liczba niz sie zaczyna, sproboj ponownie:\n";
        cin >> interval.max;
    }

    long long buffer, multip = 1;
    if (!nolog) cout << "Podawaj dzielniki (wpisz dowolny inny niz cyfra znak, by zakonczyc wpisywanie):\n";
    while (cin >> buffer) 
        multip *= buffer;
   
    if (!nolog) cout << "Liczby w przedziale <" << interval.min << ";" << interval.max << ">, podzielne przez "
    "przynajmniej jeden z podanych dzielnikow to:\n";

    for (int x = 1; multip * x <= interval.max; ++x)
        cout << multip * x << " ";
    //Press any key to exit the program
    if (!nopause) system("pause");
    return 0;
}
