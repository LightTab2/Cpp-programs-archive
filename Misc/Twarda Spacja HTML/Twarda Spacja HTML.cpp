//Progam will add a non-breaking space before every 1-character word in given html file 
#include <iostream>
#include <fstream>
#include <algorithm>
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

    //Try to open file
    char temp;
    ifstream html(path + ".html");
    ofstream output("output.html", ios::out | ios::trunc);
    while (!html)
    {
        //Couldn't load the file named "[path]"
        //Do you want to retry (y,t,p), or load another file (n,w)?
        if (!nolog) cout << "Nie udalo sie wczytac pliku o nazwie \"" << path << "\"\n"
            "Pononowic probe (y,t,p), czy wczytac inny plik (n,w)?\n";
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
    while (html && buffer.find("<body>") == string::npos) 
    {
        getline(html,buffer);
        output << buffer << '\n';
    }
    if (temp == 't' || temp == 'y')
    {
        while (html)
        {
            getline(html,buffer);
            string::size_type pos[2] = {0,0};
            pos[0] = buffer.find('<');
            pos[1] = buffer.find(' ');
            while (pos[1] != string::npos)
            {
                //If '<' is closer than ' '
                if (pos[1] > pos[0])
                {
                    //Search of next ' ' position, after nearest '>', relative to saved '<' position
                    pos[1] = buffer.find(' ', buffer.find('>',pos[0]+1u));
                    //And for next '<' position
                    pos[0] = buffer.find('<', pos[0]+1);
                }
                else
                {
                    //Let's find next space
                    //If it has 2 character distance to pos[1], then it means pos[1]+1 is a single
                    //character
                    string::size_type temp = buffer.find(' ', pos[1]+1);
                    if (temp == (pos[1]+2))
                    {
                        buffer.erase(temp, 1);
                        buffer.insert(temp, "&nbsp;");
                        temp += 5;
                    }
                    else if ((temp == string::npos && (pos[1] + 2 == buffer.length())))
                        buffer.insert(buffer.length()-1,"&nbsp;");
                    pos[1] = temp;
                }
            }
            output << buffer << '\n';
        }
    }
    else if (temp == 'n')
    {
        while (html)
        {
            getline(html,buffer);
            string::size_type pos[2] = {0,0};
            pos[0] = buffer.find('<');
            pos[1] = buffer.find("&nbsp;");
            while (pos[1] != string::npos)
            {
                //If '<' is closer than '&nbsp;'
                if (pos[1] > pos[0])
                {
                    //Search of next '&nbsp;' position, after nearest '>', relative to saved '<' position
                    pos[1] = buffer.find("&nbsp;", max(pos[0]+1u,buffer.find('>',pos[0]+1u)));
                    //And for next '<' position
                    pos[0] = buffer.find('<', pos[0]+1);
                }
                else
                {
                    buffer.erase(pos[1], 6);
                    buffer.insert(pos[1], " ");
                    pos[1] = buffer.find("&nbsp;", pos[1]+1);
                }
            }
            output << buffer << '\n';
        }
    }
    return 0;
}
