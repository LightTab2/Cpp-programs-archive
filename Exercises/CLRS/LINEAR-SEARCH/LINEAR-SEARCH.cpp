#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
using namespace std;
vector<long long> A;

int main()
{
    mt19937_64 PRNG(time(0));
	unsigned mode = 0;
	bool pause = true;
	cout << "Wybierz tryb:\n"
		"0 - pobierz dane ze standardowego strumienia (zakoncz wypisywanie danych dowolnym znakiem niebedacym cyfra)\n"
		"1 - wygeneruj losowe dane o podanej wielkosci\n";
	cin >> mode;
	if (mode)
	{
        long long a,b;
		cout << "Podaj ilosc liczb:\n";
		cin >> mode;
		A.reserve(mode);
        
        cout << "Podaj zakres danych <a,b>:\na = ";
        cin >> a;
        cout << "b = ";
        cin >> b;
        uniform_int_distribution<long long> dist(a, b);
		for (int i = 0; i != mode; ++i) A.push_back(dist(PRNG));
	}
	else
	{
		pause = false;
		while (cin)
		{
			cin >> mode;
			A.push_back(mode);
		}
	}
    cout << "Podaj szukana wartosc (wpisz %, jezeli ma byc losowa istniejaca w ciagu liczb):\n";
    string input;
    cin >> input;
    long long v = 0;
    if (input == "%" && A.size())
    {
        uniform_int_distribution<unsigned> rand(0, A.size()-1);
        v = A[rand(PRNG)];
    }
    else
        v = stoi(input);
    int i = 0;
													//pamietac o zmianie indeksowania
	for (; i != A.size(); ++i)	                    //for i = 1 to A.length
	{
		if (A[i] == v)                              //  if (A[i] == v)
		    break;                                  //      break
	}		
    if (i == A.size()) i = -1;                      //if (i == A.length ^ A[i] != v) i = NIL

    if (i != -1) cout << "Pierwszy(niekoniecznie ostatni) element o wartosci " << v << " znajduje sie w ciagu liczb na pozycji: " << i+1 << ".\n\n";
    else cout << "W tym ciagu liczb nie ma elementu o wartosci " << v << "\n\n";

	for (int j = 0; j != A.size(); ++j)
        if (j == i) cout << "*" << A[j] << "* ";
        else cout << A[j] << ' ';
    cout << '\n';
	if (pause) system("pause");
    return 0;
}
