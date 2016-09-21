#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    int ctr = 1, find, Name, Size;
    string fOpen,fOut;
    unsigned char c, s[2], l[4]; //Char, Short, Long

    cout<<"Enter file to open: ";
    cin>>fOpen;

    ifstream fin(fOpen.c_str(), ios::binary);
    cout<<"IsGood? "<<fin.good()<<endl;
    fin>>noskipws;

    fOut = fOpen+"_out";
    ofstream fout(fOut.c_str(), ios::binary);

    cout<<"Enter the one to delete: ";
    cin>>find;

    while(fin>>c)
    {
        if (ctr == find)
        {
            for (int i = 0; i < 9; i++)
                fin>>c;

            fin>>s[0]>>s[1]; //Name
            Name = s[0] + s[1]*0x100;

            for (int i = 0; i < 4; i++)
                fin>>c;

            fin>>l[0]>>l[1]>>l[2]>>l[3]; //Size
            Size = l[0] + l[1]*0x100 + l[2]*0x100*0x100 + l[3]*0x100*0x100*0x100;



            for (int i = 0; i < 0x18+Name+Size -20; i++)
                fin>>c;

            while(fin >> c)
                fout<<c;

            break;

        } else
        {
            fout<<c;
            for (int i = 0; i < 9; i++)
            {
                fin>>c;
                fout<<c;
            }


            fin>>s[0]>>s[1]; //Name
            fout<<s[0]<<s[1];

            Name = s[0] + s[1]*0x100;

            for (int i = 0; i < 4; i++)
            {
                fin>>c;
                fout<<c;
            }


            fin>>l[0]>>l[1]>>l[2]>>l[3]; //Size
            fout<<l[0]<<l[1]<<l[2]<<l[3];

            Size = l[0] + l[1]*0x100 + l[2]*0x100*0x100 + l[3]*0x100*0x100*0x100;

            for (int i = 0; i < 0x18+Name+Size -20; i++)
            {
                fin>>c;
                fout<<c;
            }

            ctr++;

        }
    }



}
