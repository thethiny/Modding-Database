#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

int main()
{
    ifstream fin("html_out.txt");
    ofstream fout("html_arabic.txt");
    fin>>noskipws;
    string s;

    while(getline(fin, s))
    {
        if (s.substr(0, 4) == "/ar/")
            fout<<s<<endl;;
    }
}
