#include<iostream>
#include<fstream>
using namespace std;

int main(int argv, char *args[])
{
    if (argv < 3)
    {
        cout<<"Usage:\n\tAppendBGAD FileToAppendTo FileToLoad1 FileToLoad2 ...[]";
        return 1;
    }
    string fOpen = args[1], fOpenA;
    unsigned char c;
    ifstream fin(fOpen.c_str(), ios::binary);
    fin>>noskipws;
    ofstream fout((fOpen + "_out").c_str(), ios::binary);

    while (fin>>c)
        fout<<c;

    fin.close();
    for (int i = 2; i < argv; i++)
    {

        fOpenA = args[i];
        fin.open(fOpenA.c_str(), ios::binary);
        if (!fin.good())
        {
            cout<<"Error 404: " + fOpenA + " Not Found!";
            return 404;
        } else cout<<fOpenA + " open successful.\n";

        fin>>noskipws;

        while(fin >> c)
            fout<<c;
        fin.close();
    }

    cout<<"All Operations Done Successfully!";
    fin.close();
    fout.close();


}
