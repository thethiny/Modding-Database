#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;

    fin.open("Extract/$StartupCacheDir$/Config/X64-MK10Game.ini",ios::binary);
    fin>>noskipws;
    fout.open("noNull.txt",ios::binary);

    unsigned char x;

    while(fin>>x)
    {
        if (x != 0x00)
        fout<<x;
    }

    return 0;
}
