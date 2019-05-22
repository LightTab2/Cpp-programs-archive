#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

int main()
{
	while (true)
	{
		string compile;
		cin >> compile;
		//So it waits for us
		ifstream file("program.txt");
		ofstream out("code.txt");
		std::stringstream buffer;
		int reference = 0, refval[10];
		memset(refval,0, sizeof(refval));
		
		buffer << file.rdbuf();
		while (buffer)	
		{
			string code, value, buf;
			buffer >> code;
			if (code == "@")
			{
                buf += '@';
			}
			transform(code.begin(), code.end(), code.begin(), [](unsigned char c) {return tolower(c); });
			if (code.find('=') != string::npos)
				value = stoi(code.substr(code.find('=')));
			else buffer >> value >> value;

			for (int ref = -reference; ref; )
				if (ref < 0) { buf += '<'; ++ref; }
				else { buf += '>'; --ref; }
			if (code.substr(0, 6) == "amount")
			{
				reference = 0;
				buf += '\'';
			}
			else if (code.substr(0, 6) == "source")
			{
				reference = 0;
				buf += '}';
			}
			else if (code.substr(0, 6) == "target")
			{
				reference = 0;
				buf += ')';
			}
			/*else if (code.substr(0, 3) == "reg")
			{
				buf = "";
				string val;
				int memory = stoi(code.substr(3));
				for (int ref = memory - reference; ref; )
					if (ref < 0) { out << '<'; ++ref; }
					else { out << '>'; --ref; }
				reference = memory;
				buffer >> val >> val;
				for (int addsub = stoi(val) - refval[memory]; addsub; )
					if (addsub < 0) { out << '-'; ++addsub; }
					else { out << '+'; --addsub; }
				refval[memory] = stoi(val);
			}*/
			
			else
			{
				map
			}
			out << buf;
		}
		file.close();
		out.close();
	}
}
