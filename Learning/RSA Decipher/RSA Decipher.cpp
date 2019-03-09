#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
bool isSmaller(const string &str1, const string &str2) //nie jestem autorem tego
{
	int n1 = str1.length(), n2 = str2.length();

	if (n1 < n2)
		return true;
	if (n2 < n1)
		return false;

	for (int i = 0; i<n1; i++)
		if (str1[i] < str2[i])
			return true;
		else if (str1[i] > str2[i])
			return false;

	return false;
}

string findDiff(string str1, string str2) //nie jestem autorem tego
{
	if (isSmaller(str1, str2))
		throw runtime_error('\"' + str1 + "\" jest mniejsze od \"" + str2 + '\"');

	string str = "";

	int n1 = str1.length(), n2 = str2.length();

	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());

	int carry = 0;
	char temp[1]; //yeah I know it's horrible, but this is done ah hoc and I dont care if it's not transparent or ineffective
	for (int i = 0; i<n2; i++)
	{
		temp[0] = str1[i];
		int n1 = stoi(temp, 0, 16);
		temp[0] = str2[i];
		int sub =  n1 - stoi(temp, 0, 16) - carry;
		if (sub < 0)
		{
			sub = sub + 16;
			carry = 1;
		}
		else
			carry = 0;

		if (sub >= 10) str += sub + 'a' - 10;
		else str += sub + '0';
	}
	for (int i = n2; i<n1; i++)
	{
		temp[0] = str1[i];
		int sub = (stoi(temp, 0, 16) - carry);

		if (sub < 0)
		{
			sub = sub + 16;
			carry = 1;
		}
		else
			carry = 0;

		if (sub >= 10) str += sub + 'a' - 10;
		else str += sub + '0';
	}
	unsigned i = 1;
	while (str[str.size() - i] == '0') ++i;
	str = str.substr(0, str.size() - i+1);
	reverse(str.begin(), str.end());
	return str;
}

string findSum(string str1, string str2)
{
	if (str1.length() > str2.length())
		swap(str1, str2);

	string str = "";

	int n1 = str1.length(), n2 = str2.length();

	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());
	char temp[1];
	int carry = 0;
	for (int i = 0; i<n1; i++)
	{
		temp[0] = str1[i];
		int n1 = stoi(temp, 0, 16);
		temp[0] = str2[i];
		int sum = n1 + stoi(temp,0,16) + carry;
		if ((sum % 16) >= 10) str += sum % 16 + 'a' - 10;
		else str += sum % 10 + '0';

		carry = sum / 16;
	}

	for (int i = n1; i<n2; i++)
	{
		temp[0] = str2[i];
		int sum = stoi(temp, 0, 16) + carry;
		if ((sum % 16) >= 10) str += sum % 16 + 'a' - 10;
		else str += sum % 10 + '0';
		carry = sum / 16;
	}

	if ((carry % 16) >= 10) str += carry % 16 + 'a' - 10;
		else if (carry) str += carry % 10 + '0';

	reverse(str.begin(), str.end());
	return str;
}

string multiply(const string &num1, const string &num2) //nie jestem autorem tego
{
	unsigned n1 = num1.size();
	unsigned n2 = num2.size();
	if (!n1 || !n2)
		return "0";

	vector<int> result(n1 + n2, 0);

	int i_n1 = 0;
	int i_n2 = 0;
	char temp[1];
	for (int i = n1 - 1; i >= 0; i--)
	{
		int carry = 0;
		temp[0] = num1[i];
		int n1 = stoi(temp, 0, 16);
		i_n2 = 0;

		for (int j = n2 - 1; j >= 0; j--)
		{
			temp[0] = num2[j];

			int sum = n1 * stoi(temp, 0, 16) + result[i_n1 + i_n2] + carry;

			carry = sum / 16;

			result[i_n1 + i_n2] = sum % 16;

			i_n2++;
		}
		if (carry > 0)
			result[i_n1 + i_n2] += carry;

		i_n1++;
	}

	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0)
		--i;

	if (i == -1)
		return "0";

	string s = "";

	while (i >= 0)
	{
		if (result[i] >= 10) s += result[i--] + 'a' - 10;
		else s += result[i--] + '0';
	}

	return s;
}

string modulo(string num, const string &modulo)	
{
	if (!num.size() || !modulo.size())
		return "0";
	if (isSmaller(num, modulo))
		return num;

	int n1 = num.size(),
		n2 = modulo.size();
	string considered = num.substr(0, n2);
	if (n1 == n2)
	{
		while (isSmaller(modulo, considered))
			considered = findDiff(considered, modulo);
		if (considered == modulo) considered = "0";
	}
	else
	for (int i = n2; i != n1; ++i)
	{
		while (isSmaller(modulo, considered))
			considered = findDiff(considered, modulo);
		if (considered == modulo) considered = "0";
		considered += num[i];
		while (considered[0] == '0')
			considered.erase(0);
	}
	while (isSmaller(modulo, considered))
		considered = findDiff(considered, modulo);
	if (considered == modulo) considered = "0";

	return considered;
}

string modularpower(string num, long long &power, const string &mod)
{
	num = modulo(num, mod);
	string result = "1";
	while (power > 0)
	{
		if (power & 1ll)
			result = modulo(multiply(num, result), mod);

			power = power >> 1;
			num = modulo(multiply(num, num), mod);
	}
	return result;
}

bool nolog = false;
int main(int argc, char *args[])
{
    for (int x = 0; x != argc; ++x)
    {
        if (args[x] == "-nolog") nolog = true;
    }
	beg:auto start = chrono::steady_clock::now();
	try
	{
		string n, message;
		long long e;
		if (!nolog) cout << "Podaj modulus (hex):\n";
		getline(cin, n);
		n.erase(remove_if(n.begin(), n.end(), [](unsigned char c) {return !isalnum(c); }), n.end());
		transform(n.begin(), n.end(), n.begin(), ::tolower);

		if (!nolog) cout << "Podaj wykladnik (dec):\n";
		std::string temp;
		getline(cin, temp);
		e = stoi(temp);

		if (!nolog) cout << "Podaj wiadomosc (hex):\n";
		getline(cin, message);
		start = chrono::steady_clock::now();
		message.erase(remove_if(message.begin(), message.end(), [](unsigned char c) {return !isalnum(c); }), message.end());
		transform(message.begin(), message.end(), message.begin(), ::tolower);

		if (!nolog) cout << "Odszyfrowania wiadomosc (hex) to:\n";
            cout << modularpower(message, e, n) << std::endl;
	}
	catch (runtime_error &err)
	{
		cout << err.what();
	}
	catch (...)
	{
		cout << "Fatal Error";
	}
	if (!nolog) cout << "\nIt took ONLY: " << chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start).count() << endl;
	//system("pause");
	goto beg;
    return 0;
}

