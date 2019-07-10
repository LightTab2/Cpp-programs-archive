#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <chrono>
using namespace std;
struct Interval
{
    long long min = ~(-1ull >> 1), max = -1ull >> 1;
};
const long long maximum = -1ull >> 1;
bool nolog = false, nopause = false, timer = false;

int main(int argc, char *args[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int x = 0; x != argc; ++x)
    {
        if (!strcmp(args[x], "-nolog")) nolog = true;
        else if (!strcmp(args[x], "-nopause")) nopause = true;
        else if (!strcmp(args[x], "-time")) timer = true;
    }
    vector<long long> dzielniki;
	Interval interval;

    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "W przedziale <a;b> liczb calkowitych wyszukaj wszystkie liczby podzielne przez kazda "
        "z liczb z zadanego zbioru P\n\n";

    if (!nolog) cout << "Podaj przedzial liczb <a;b>:\nPodaj a:" << endl;
	cin >> interval.min;

    if (!nolog) cout << "Podaj b:" << endl;
    cin >> interval.max;
    while (interval.min > interval.max)
    {
        if (!nolog) cout << "\nPrzedzial nie moze sie konczyc mniejsza liczba niz sie zaczyna, sproboj ponownie:" << endl;
        cin >> interval.max;
    }

    long long buffer, multip = 1;
    if (!nolog) cout << "Podawaj dzielniki (wpisz dowolny inny niz cyfra znak, by zakonczyc wpisywanie):" << endl;

    while (cin >> buffer) 
        multip *= buffer;
   
    if (!nolog) cout << "Liczby w przedziale <" << interval.min << ";" << interval.max << ">, podzielne przez "
    "wszystkie z podanych dzielnikow to:" << endl;

    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();

    for (int x = 1; multip * x <= interval.max; ++x)
        cout << multip * x << " ";
    cout << endl;

    if (timer)
    {
        stop = chrono::high_resolution_clock::now();
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
