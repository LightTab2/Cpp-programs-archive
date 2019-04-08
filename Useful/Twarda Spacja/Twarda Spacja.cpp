//Progam will add a non-breaking space before every 1-character word in given html file 
//Sphagetti code warning - never look, if you don't have to
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

bool nolog = false;
int main(int argc, char *args[])
{
	for (int x = 0; x != argc; ++x)
	{
		if (args[x] == "-nolog") nolog = true;
	}
	//Input the name of the file that is going to be converted
	string path;
	if (!nolog) cout << "Podaj nazwe pliku:\n";
	cin >> path;

	//Try to open the file
	char temp;
	ifstream html(path);
	ofstream output("output.html", ios::out | ios::trunc);
	while (!html)
	{
		//Couldn't load the file named "[path]"
		//Do you want to retry (y,t,p), or load another file (n,w)?
		if (!nolog) cout << "Nie udalo sie wczytac pliku o nazwie \"" << path << "\"\n"
			"Pononowic probe (p,t,y), czy wczytac inny plik (n,w)?\n";
		cin >> temp;

		switch (temp)
		{
		case 'y':
		case 't':
		case 'p':
			html.open(path);
			break;
		case 'n':
		case 'w':
			if (!nolog) cout << "Podaj nazwe pliku:\n";
			cin >> path;
			html.open(path);
			break;
		default:
			return -1;
		}
	}
	//Add non-breaking spaces (t, y) or delete all non-breaking spaces (n)?
	if (!nolog) cout << "Czy wstawiac twarda spacje (t, y), czy usunac wszystkie twarde spacje (n)?\n";
	cin >> temp;
	string buffer = "";
	if (path.find(".html") != string::npos)
		while (html && buffer.find("<body>") == string::npos)
		{
			getline(html, buffer);
			output << buffer << '\n';
		}
	if (temp == 't' || temp == 'y')
	{
		while (html)
		{
			static bool newline = false;
		newlineread: getline(html, buffer);
			string::size_type pos[3] = { 0u, 0u, 0u };
			pos[0] = buffer.find('<');
			pos[1] = buffer.find(' ');
			pos[2] = buffer.find('>', pos[0] + 1u);
			while (pos[1] != string::npos)
			{
				//find another <tag> if crossed one
				if (pos[0] != string::npos && pos[1] > pos[0])
				{
					if (pos[1] = buffer.find(' ', pos[2] + 1u) == string::npos)
					{
						if (!newline) newline = true;
						else output << '\n';
						output << buffer;
						goto newlineread;
					}
					pos[0] = buffer.find('<', pos[0] + 1u);
					pos[2] = buffer.find('>', pos[0] + 1u);
					if (pos[0] != string::npos && pos[2] == string::npos)
					{
						while (true)
						{
							if (!html) return 0;
							if (!newline) newline = true;
							else output << '\n';
							output << buffer;
							getline(html, buffer);
							if (buffer.find('>') != string::npos)
							{
								pos[0] = buffer.find('<', buffer.find('>') + 1u);
								pos[1] = buffer.find(' ', buffer.find('>') + 1u);
								pos[2] = buffer.find('>', pos[0] + 1u);
								break;
							}
						}
						continue;
					}
				}
				string::size_type temp = buffer.find(' ', pos[1] + 1u);
				if (temp == (pos[1] + 2u) && temp < pos[0])
				{
					buffer.erase(temp, 1u);
					buffer.insert(temp, "&nbsp;");
					//add 5 because size of buffer changed
					temp += 5u;
					if (pos[0] != string::npos) pos[0] += 5u;
				}
				else if ((temp == string::npos && (pos[1] + 2u == buffer.length())))
					buffer.insert(buffer.length() - 1u, "&nbsp;");

				pos[1] = temp;
			}
			if (!newline) newline = true;
			else output << '\n';
			output << buffer;
		}
	}
	else if (temp == 'n')
	{
		while (html)
		{
			getline(html, buffer);
			string::size_type pos[2] = { buffer.find("&nbsp;"), buffer.rfind(' ', buffer.find("&nbsp;")) };
			while (pos[0] != string::npos)
			{
				if (pos[0] - pos[1] < 3u)
				{
					buffer.erase(pos[0], 6);
					buffer.insert(pos[0], " ");
					pos[0] -= 5u;
				}
				pos[0] = buffer.find("&nbsp;", pos[0] + 1u);
				pos[1] = buffer.rfind(" ", pos[0]);
			}
			static bool newline = false;
			if (!newline) newline = true;
			else output << '\n';
			output << buffer;
		}
	}
	return 0;
}
