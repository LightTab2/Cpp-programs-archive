#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>
#include <cstring>
using namespace std;

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

    long double a1, r;
    int n, dot, dotn = 2;
    if (!nolog) cout << "Tresc zadania, ktore ten program rozwiazuje to:\n"
        "Wygeneruj n-kolejnych wyrazow ciagu arytmetycznego\n"
        "Wyniki zostana wygenerowane z precyzja do 1 miejsca po przecinku\n\n";

    if (!nolog) cout << "Podaj pierwszy wyraz ciagu arytmetycznego:" << endl;
	cin >> a1;
    cout << endl;

    if (!nolog) cout << "Podaj roznice:" << endl;
	cin >> r;
    cout << endl;

    if (!nolog) cout << "Podaj liczbe elementow:" << endl;
    cin >> n;
    cout << endl;
    dot = n;
    if (!nolog) cout << n << " elementow tego ciagu arytmetycznego to:" << endl;
    chrono::time_point<chrono::high_resolution_clock> start, stop;
    if (timer) start = chrono::high_resolution_clock::now();
	cout << fixed << setprecision(1);
    //ok, ponizej jest genialny przyklad jak lubie sobie utrudniac zycie
    //Pisze po angielsku, bo mysle po angielsku
    //idea:
    //ceil number of elements to nearest power of 10 eg. 101 turns into 1000, hold it somewhere eg. [ceiled]
    //multiply the result by r 
    //check if precision holds to 0.1
    //to do that, check if number after dot are equal to 9 or 0, up to [length of ceiled]+2
    //ceil a1, if they're equal to 9
    while (dot >= 10) //storing number of 10's powers + 2 in dotn
    {
        if (dot % 10) dot += 10;
        dot/=10;
        ++dotn;
    }
	long double multiplier = 100.0l;
    if ((dot % 10) != 1) ++dotn; //ceiling, not precise but simple, second option is very complicated and on this
	{
		int x = 1;
        for (; x != dotn; ++x, multiplier *= 10.0l)
        {
            if ((static_cast<long long>(a1*multiplier) % 10) < 4) break;
        }
        if (x == dotn) ++dotn;
	}
    //simple task I won't use it (maybe later for fun I'll do it)
    
    multiplier = 10.0l;
	long long remainder = static_cast<long long>(r * multiplier) % 10ll;
    if (!remainder || remainder == 9)
    {
        --dotn;
		while (dotn && (static_cast<long long>(r * multiplier) % 10ll) == remainder)
		{
			multiplier *= 10.0l;
			--dotn;
		}
        if (!dotn)
        {
            long long rr = !remainder ? floor(r) : ceil(r);
            cout << a1 << ' ';
            for (int x = 0; x != n; ++x) cout << (a1+=rr) << ' ';
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
            if (!nopause) system("pause");
            return 0;
        }
    }
    //slower algorithm
    cout << a1 << ' ';
    for (int x = 1; x != n; ++x) cout << a1 + x * r << ' ';

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
