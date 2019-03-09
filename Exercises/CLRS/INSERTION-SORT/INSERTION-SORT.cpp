#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;
vector<long long> A;

int main()
{
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
        mt19937_64 PRNG(time(0));
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
													//pamietac o zmianie indeksowania
	for (int j = 1, key = 0; j != A.size(); ++j)	//for j = 2 to A.length
	{
		key = A[j];									//  key = A[j]
		int i = j - 1;								//  i = j - 1
		while (i >= 0 && A[i] < key)				//  while i > 0 ^ A[i] < key
		{
			A[i + 1] = A[i];						//      A[i+1] = A[i]
			i = i - 1;								//      i = i - 1
		}
		A[i + 1] = key;								//  A[i+1] = key
	}		

	cout << "Posortowany ciag nierosnaca:\n";
	for (int j = 0; j != A.size(); ++j)
		cout << A[j] << ' ';
	if (pause) system("pause");
    return 0;
}
