#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
//stworzenie folderow

using namespace std;

bool warunek(string filename);
bool nolog = false;
int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
    }
	random_device rd;
	mt19937 gen(rd());

	unsigned index = 0;
	vector<pair<unsigned, pair<long long, long long>>> signedparameter;
	vector<pair<unsigned, pair<unsigned long long, unsigned long long>>> unsignedparameter;
	vector<pair<unsigned, pair<string, vector<char>>>> charparameter;
	if (!nolog) cout << "Podawaj przedzialy i okresl czy sa oznakowane (zawiera ujemne liczby)\n"
		"\"u\" jesli nie jest oznakowany, tylko przy 1. parametrze\n"
		"Jezeli chcesz podac ciag znakow uprzedz to \"[liczbaznakow]c\"\n"
		"\"[liczbaznakow]\" moze byc zastapiona \"p[numerparametru]\"\n"
		"By zakonczyc dzialanie generatora wpisz nazwe programu zaczynajac znakiem \"n\"\n";
	string przedzial;

	while (cin)
	{
		cin >> przedzial;
		if (przedzial[0] == 'u')
		{
			unsignedparameter.emplace_back(index, pair<unsigned long long, unsigned long long>(stoi(przedzial.substr(1)), 0));
			cin >> przedzial;
			unsignedparameter.back().second.second = stoi(przedzial);
		}
		else if (przedzial.find('c') != string::npos)
		{
			charparameter.emplace_back();
			charparameter.back().first = index;
			charparameter.back().second.first = przedzial.substr(0,przedzial.find('c'));
			for (const char & c : przedzial.substr(przedzial.find('c')+1))
				charparameter.back().second.second.push_back(c);
		}
		else if (przedzial[0] == 'n')
		{
			string nazwa;
			transform(przedzial.begin() + 1, przedzial.end(), back_inserter(nazwa), ::toupper);
			if (!nolog) cout << "Podaj liczbe testow do wygenerowania:\n";
			unsigned long long ilosc;
			cin >> ilosc;
			//vector<pair<unsigned long long, long long>> parametry;

			for (int i = 0; i != ilosc; ++i)
			{
				for (;;)
				{
					vector<pair<unsigned long long, unsigned long long>> uparametry;
					auto it1 = unsignedparameter.cbegin();
					auto it2 = signedparameter.cbegin();
					auto it3 = charparameter.cbegin();
					ofstream file("in/" + przedzial.substr(1) + '_' + to_string(i + 1) + ".in");
					for (int j = 0; j != index; ++j)
					{
						if (!unsignedparameter.empty() && it1 != unsignedparameter.cend() && it1->first == j)
						{
							uniform_int_distribution<unsigned long long> rand(it1->second.first, it1->second.second);
							uparametry.emplace_back(j, rand(gen));
							file << uparametry.back().second << '\n';
							++it1;
						}
						else if (!signedparameter.empty() && it2 != signedparameter.cend() && it2->first == j)
						{
							uniform_int_distribution<long long> rand(it2->second.first, it2->second.second);
							long long generated = rand(gen);
							uparametry.emplace_back(j, generated);
							file << generated << '\n';
							++it2;
						}
						else if (!charparameter.empty() && it3 != charparameter.cend())
						{
							unsigned long long limit;
							if (it3->second.first.empty()) limit = 0;
							else if (it3->second.first[0] == 'p')
							{
								for (auto &el : uparametry) //optymalizacja potrzebna af
									if (el.first == (stoi(it3->second.first.substr(1))-1))
										limit = el.second;
							}
							else limit = stoi(it3->second.first);
							stringstream str;
							for (long long i = 0; i != limit; ++i)
							{
								uniform_int_distribution<int> rand(0, it3->second.second.size() - 1);
								str << it3->second.second[rand(gen)] << '\n';
							}
							string temp = str.str();
							temp.erase(remove(temp.begin(), temp.end(), '\n'), temp.end() );
							file << temp << endl;
							++it3;
						}
					}
					string polecenie = nazwa + ".exe < in/" + przedzial.substr(1) + '_' + to_string(i + 1)
						+ ".in > myout/" + przedzial.substr(1) + '_' + to_string(i + 1)
						+".out";
					try
					{
						system(polecenie.c_str());
						if (warunek("myout/" + przedzial.substr(1) + '_' + to_string(i + 1)
							+ ".out")) break;
					}
					catch (...)
					{
						cout << "Krytyczny blad\nNajprawdopodobniej nie mozna wczytac pliku \"myout/" + przedzial.substr(1) + '_' + to_string(i + 1)
							+ ".out\", co mogloby byc wynikiem blednego dzialania lub braku programu \"" + nazwa + ".exe\"\n";
						system("pause");
						break;
					}
				}
			}
			break;
		}
		else
		{
			signedparameter.emplace_back(index, pair<long long, long long>(stoi(przedzial), 0));
			cin >> przedzial;
			signedparameter.back().second.second = stoi(przedzial);
		}
		++index;
	}
	if (przedzial[0] == 'n') if (!nolog) cout << "Sukces" << endl;
	else if (!nolog) cout << "Niepowodzenie" << endl;
	system("pause");
	return 0;
}
enum porownanie
{
	brak,
	wieksze,
	mniejsze,
	rowne,
	rozne
};
bool warunek(string filename)
{
	static bool first = true;
	string buffer;
	ifstream in(filename.c_str());
	if (!in) throw 
		"FFD8FFE000104A46494600010101006000600000FFE101044578696600004D4D002A00000008000A011A00050000000100000086011B0005000000010000008E0"
		"128000300000001000200000131000200000011000000960132000200000014000000A8013E000500000002000000BC013F000500000006000000CC51100001000"
		"0000101000000511100040000000100000EC4511200040000000100000EC4000000000001770A000003E80001770A000003E87061696E742E6E657420342E302E3"
		"2310000323031373A30353A30392032303A34373A35350000007A26000186A000008084000186A00000FA00000186A0000080E8000186A000007530000186A0000"
		"0EA60000186A000003A98000186A000001770000186A0FFDB004300593D434E4338594E484E645E596985DE90857A7A85FFC2CDA1DEFFFFFFFFFFFFFFFFFFFFFFF"
		"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDB0043015E6464857585FF9090FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
		"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC00011080052004403012200021101031101FFC4001F00000105010101010101000"
		"00000000000000102030405060708090A0BFFC400B5100002010303020403050504040000017D01020300041105122131410613516107227114328191A1082342B"
		"1C11552D1F02433627282090A161718191A25262728292A3435363738393A434445464748494A535455565758595A636465666768696A737475767778797A83848"
		"5868788898A92939495969798999AA2A3A4A5A6A7A8A9AAB2B3B4B5B6B7B8B9BAC2C3C4C5C6C7C8C9CAD2D3D4D5D6D7D8D9DAE1E2E3E4E5E6E7E8E9EAF1F2F3F4F"
		"5F6F7F8F9FAFFC4001F0100030101010101010101010000000000000102030405060708090A0BFFC400B5110002010204040304070504040001027700010203110"
		"4052131061241510761711322328108144291A1B1C109233352F0156272D10A162434E125F11718191A262728292A35363738393A434445464748494A535455565"
		"758595A636465666768696A737475767778797A82838485868788898A92939495969798999AA2A3A4A5A6A7A8A9AAB2B3B4B5B6B7B8B9BAC2C3C4C5C6C7C8C9CAD"
		"2D3D4D5D6D7D8D9DAE2E3E4E5E6E7E8E9EAF2F3F4F5F6F7F8F9FAFFDA000C03010002110311003F00B751B4BCE148A266F91957EF62AAC4642D863C7A1A96FB12D"
		"93B166FE234D0CE9D0EE1DE91C9D876E73F4A8E27763823F1C74A94D89365C8DC3AE47E34EAAF11DB21CF00D58AB4EE52770A28A298C28A28A00AECAC548C1CFD2"
		"99F677C6703F3AB7452B02D3629794DDF1FE7F0A3CB61D0FEB57480460D40C36B63F0A97742726203F28C9CFAD4D16767B76A6C401CE40CE6A4A715D4515D428A2"
		"8AA2828A28A0028A28A003A540C77367DEA594FCBF5350B1DA2A24FA1127D03BE47514A6675EC08FD69AADB8918A53529B424EC4B1CCB274E0FA1A7D527183B874"
		"3FA54F04DBB0ADF7BD7D6B44CB4C9A8A28A630A28A0824100E2802091F327B014D009E69CEA14E09CF14808C718AC9EE66C0003A523E700A9E879FA528DB9E08CD"
		"2D210C232AC3D391510E0E7BD4CA7E61EF50B0C123D0D5219790EE40DEA334532DCE621EDC515A1A12514514010124927D4D273E82A5741D4714DD87B1159B4C87"
		"16339F4A5A5D8DEA052ECF56FCA9598B95919E0FE351C98F31B352850779EB8E951CDF7CFB8A761DAC87C121442319E68A627DDA2AD0D6C5CA28A299423FDDA4A2"
		"8A4C028A28A432387EE9FF3D85432F45FF768A2910F6153A514514D023FFFD9";
	static vector<pair<unsigned, pair<porownanie, long long>>> reguly;
	static unsigned long long min;
	if (first)
	{
		if (!nolog) cout << "\nPodawaj reguly dla kolejnych danych wyjsciowych\n"
			"Dostepne porownania to \">\", \"<\", \"=\", \"!=\"\n"
			"Przed kazdym z porownan mozliwe jest wpisanie jakiejs liczby lub litery \"a\"\n"
			"Podana liczba to ilosc zastosowania porownania dla kolejnych danych\n"
			"Litera \"a\" oznacza, ze porownanie zastosowane jest do wszystkich pozostalych danych\n"
			"Program nie wie ile danych istnieje, dlatego uzycie \"a\" jest konieczne\n"
			"Jezeli nie nada sie zadnego porownania, to regula nie zostanie utworzona\n"
			"np. \"121\" sprawi, ze nastepne 121 danych nie bedzie podlegac zadnym warunkom\n"
			"Jezeli nie wszystkie warunki sa spelnione, test generowany jest ponownie\n" 
			"Na razie wartosci bedace ciagiem znakow nie sa obslugiwane\n" 
			"Podaj minimalna liczbe danych wyjsciowych (0 jezeli minimum nie istnieje):" << endl;
		cin >> min;
		for (int i = 0; first;)
		{
			string temp;
			if (!nolog) cout << "Podaj regule jaka ma miec dana wyjsciowa numer " << to_string(i+1) << ":\n";
			cin >> temp;
			temp.erase(remove_if(temp.begin(), temp.end(), [](char&c) {
				return !(c == '!' || c == '=' || c == '>' || c== '<' || isalnum(c));
			}));

			pair<unsigned, pair<porownanie, long long>> regula;
			unsigned pos;
			auto &por = regula.second.first;

			if ((pos = temp.find('=')) != string::npos)
			{
				if (pos != 0 && temp[pos - 1] == '!') por = rozne;
				else por = rowne;
			}
			else if ((pos = temp.find('>')) != string::npos) por = wieksze;
			else if ((pos = temp.find('<')) != string::npos) por = mniejsze;
			else por = brak;

			if (temp[0] == 'a')
				first = false;
			else if (por != brak)
			{
				if (pos)
				{
					unsigned counter = stoi(temp.substr(0, pos));
					regula.first = i += counter;
				}
				else
					regula.first = ++i;
			}
			else regula.first += stoi(temp);
			
			if (por != brak)
				regula.second.second = stoi(temp.substr(pos));
			reguly.push_back(regula);
		}
	}
	auto regula = reguly.cbegin();
	int i = 0;
	for (; in; ++i)
	{
		in >> buffer;
		if (i < regula->first) --regula;
		switch (regula->second.first)
		{
		case wieksze:
			if (!(stoi(buffer) > regula->second.second)) return false;
			break;
		case mniejsze:
			if (!(stoi(buffer) < regula->second.second)) return false;
			break;
		case rowne:
			if (!(stoi(buffer) == regula->second.second)) return false;
			break;
		case rozne:
			if (!(stoi(buffer) != regula->second.second)) return false;
			break;
			default:
				break;
		}
		if (regula+1 != reguly.cend()) ++regula;
	}
	if (i < min) return false;
	return true;
}
