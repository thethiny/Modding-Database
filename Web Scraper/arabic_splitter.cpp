#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ifstream fin("text.txt");
    ofstream fout("out.txt");
    fin>>noskipws;
    int ctr = 0;
    unsigned char c;
    while (fin>>c)
    {
        //cout<<c;
        if (c <= 0x20 || c > 'z')
        {
            ctr++;
            fout<<c;
        }
        else if (c >= '0' && c <= '9')
            fout<<c;

    }
    cout<<"Found "<<ctr<<" Non-English Characters."<<endl;
}
