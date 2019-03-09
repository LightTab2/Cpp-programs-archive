#define UNICODE 1

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <conio.h>
#include <vector>
using namespace std;

bool nolog = false, nopause = false;
int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
		if (args[x] == "-nopause") nopause = true;
    }
	setlocale(LC_ALL, "");
	wchar_t *path = new wchar_t[MAX_PATH];
	ZeroMemory(path, sizeof(path));
	GetCurrentDirectory(MAX_PATH, path);

	wstring token;
	wchar_t *filename = new wchar_t[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"Programy (*.exe)\0*.exe\0Wszystkie pliki (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = L"Wybierz program";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
	while (!GetOpenFileName(&ofn));

	wstring::size_type pos = 0;
	//Odpalamy SharpInterface, ma on przesłać input w eleganckiej formie
	{
		STARTUPINFO info;
		PROCESS_INFORMATION processInfo;
		ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));
		ZeroMemory(&info, sizeof(STARTUPINFO));

		info.cb = sizeof(STARTUPINFO);
		info.dwFlags |= STARTF_USESTDHANDLES;

		wstring arg = filename, temp = path;
		replace(arg.begin(), arg.end(), ' ', '*');
		arg = L"SharpInterface.exe /o /n" + arg;
		arg += L" /s";
		replace(temp.begin(), temp.end(), ' ', '*');
		arg += temp;
		arg += L"\\temp.txt";
		wcscat_s(path, MAX_PATH + 100, L"\\SharpInterface.exe");

		SECURITY_ATTRIBUTES saAttr;
		saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
		saAttr.bInheritHandle = TRUE;
		saAttr.lpSecurityDescriptor = NULL;

		wchar_t *args = new wchar_t[arg.size()+1];
		wcscpy_s(args, arg.size() + 1, arg.c_str());

		while (!CreateProcess(path, args, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo));

		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
	path[wcslen(path) - strlen("SharpInterface.exe")] = 0;
	wcscat_s(path, MAX_PATH + 100, L"temp.txt");
	wifstream out(path);
	wstring buffer = L"", output = L"";
	if (!nolog) wcout << L"Otrzymany output to:\n";
	while (getline(out, buffer))
	{
		output += buffer;  
		if (!nolog) wcout << buffer << endl;
	}
	vector<unsigned int> wyniki;
	if (!output.empty())
	{
		out.clear();
		out.seekg(0);
		if (!nolog) wcout << L"Podaj znaki, które rozdzielają wyniki (zakończ wpisywanie naciskając Escape, rozdzielaj nową linią):\n";
		wchar_t c = 'a';
		vector<wstring> tokens;
		tokens.emplace_back();
		while (c != 27)
		{
			c = _getch();
			if (c == 13)
			{
				if (!tokens.back().empty())tokens.emplace_back();
				if (!nolog) wcout << endl;
			}
			else if (c == L'\b')
			{
				if (!nolog) wcout << L"\b \b";
				if (!tokens.back().empty()) tokens.back().pop_back();
			}
			else if (c > 31)
			{
				if (!nolog) wcout << c;
				tokens.back().push_back(c);
			}

		}
		if (tokens.back().empty()) tokens.erase(tokens.end() - 1);
		for (const wstring s : tokens)
		{
			pos = -1;
			while ((pos = output.find(s, pos+1)) != wstring::npos)
			{
				if (find(wyniki.cbegin(), wyniki.cend(), pos) == wyniki.cend())
				wyniki.push_back(pos);
			}
		}
		if (!nolog) wcout << endl;
		if (wyniki.empty())
		{
			if (!nolog) wcout << L"Output jest pusty, elementów jest 0\n";
			_wsystem(L"pause");
			return 0;
		}
		if (!nolog) wcout << L"Liczba elementów(licząc puste) na standardowym wyjściu to: ";
			wcout << wyniki.size() + 1 << endl;
		sort(wyniki.begin(), wyniki.end());
		for (auto it = wyniki.begin(); it != wyniki.end()-1;)
			if (*(it++) == *it - 1) wyniki.erase(it--);
		if (!nolog) wcout << L"Liczba elementów(nielicząc pustych) na standardowym wyjściu to: ";
		wcout << wyniki.size() + 1 << endl;
		
	}
	if (!nolog) wcout << L"Sukces!\n";
	if (!nopause) _wsystem(L"pause");
	return 0;
}
