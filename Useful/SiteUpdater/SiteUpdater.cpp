#include <fstream>
#include <string>
#include <sstream>
using namespace std;
const char *FILES[][2]
{
	{"Edytory_Tekstow/Vim.html",                    "../LightTab2.github.io/_includes/tutorials/Edytory_Tekstow/Vim.html"},
	{"WebDev/HTML.html",                            "../LightTab2.github.io/_includes/tutorials/WebDev/HTML.html"},
	{"Internet/Niebezpieczenstwa/Meltdown.html",    "../LightTab2.github.io/_includes/descriptions/Internet/Niebezpieczenstwa/Meltdown.html"},
	{"WebDev/LaTeX.html",                           "../LightTab2.github.io/_includes/tutorials/WebDev/LaTeX.html"},
	{"WebDev/SQL.html",                             "../LightTab2.github.io/_includes/tutorials/WebDev/SQL.html"}
};

/*
Cuts some of the original HTML file's content, so it can be read by blog's jekyll's include just fine
*/
void TransformFile(const char* path, const char* pathout)
{
	wifstream ifile;
	wofstream ofile;
	wstringstream reader;
	wstring buf;

	ifile.open(path);
	ofile.open(pathout);
	if (!ifile || !ofile) return;

	reader << ifile.rdbuf();
	getline(reader, buf);
	while (buf.find(L"<body>") == wstring::npos) getline(reader, buf);
	while (getline(reader, buf))
	{
        if (buf[0] == L' ' || buf[0] == L'/t')
        {
            size_t pos = 0;
            while (buf.find(L' ', pos+1) == pos+1 || buf.find(L'/t', pos+1) == pos+1) ++pos; 
            buf.erase(0, pos);
        }
		if (buf.find(L"</body>") != wstring::npos) break;
		ofile << buf << L'\n';
	}

	ifile.close();
	ofile.close();
}

int main()
{
	for (int x = 0, end = sizeof(FILES) / sizeof(const char*[2]); x != end; ++x)
		TransformFile(FILES[x][0], FILES[x][1]);
	return 0;
}
