#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

string to_upper(string &str)
{
	string ret;
	transform(str.begin(), str.end(), back_inserter(ret), ::toupper);
	return ret;
};

bool nolog = false;
int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
    }
	ifstream out, mout;
	ofstream err("err.txt");

	string output, myoutput;
	string nazwa_programu;

	if (!nolog) cout << "Podaj nazwe programu:\n";
	cin >> nazwa_programu;

	auto removecheck = [](unsigned char c) {return !isalnum(c); };
	unsigned iter = 1;

	for (;;)
	{
		string open_path = "out/"; open_path += nazwa_programu; 
			open_path += to_string(iter); open_path += ".out";
		out.open(open_path);
		if (!out)
		{
			err << "Koniec" << endl;
			break;
		}

		open_path = "myout/"; open_path += nazwa_programu;
		open_path += to_string(iter); open_path += ".out";
		string polecenie = to_upper(nazwa_programu) + ".exe < in/" + nazwa_programu + to_string(iter)
			+ ".in > myout/" + nazwa_programu + to_string(iter) + ".out";
		system(polecenie.c_str());
			
		mout.open(open_path);
		if (!mout)
		{
			err << "Nie udalo sie uruchomic programu \"" + to_upper(nazwa_programu) + ".exe\"" << endl;
			break;
		}

		output.assign(istreambuf_iterator<char>(out), istreambuf_iterator<char>());	
		myoutput.assign(istreambuf_iterator<char>(mout), istreambuf_iterator<char>());

		output.erase(remove_if(output.begin(), output.end(), removecheck), output.end());
		myoutput.erase(remove_if(myoutput.begin(), myoutput.end(), removecheck), myoutput.end());
		if (output != myoutput) err << "Wyniki nie zgadzaja sie w\n\"" + nazwa_programu 
			+ to_string(iter) + "\"" << endl;

		out.close(); 
		mout.close();
		++iter;
	}
	return 0;
}

