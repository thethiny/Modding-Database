#include<iostream>
#include<fstream>
using namespace std;

int main(int argv, const char* argc[])
{
    ifstream fin, finlog, fincon;
    ofstream fout;
    string base, diff;
    long long ctr = 0, pos, len;
    unsigned char type, c;

    if (argv > 1)
    {
        base = argc[1];
    }
    if (argv > 2)
    {
        diff = argc[2];
    }

    if (argv == 1)
    {
        cout<<"Enter Base File Name: ";
        cin>>base;
        cout<<"Enter Modified File Name: ";
        cin>>diff;
    }
    else if (argv == 2)
    {
        cout<<"Enter Modified File Name: ";
        cin>>diff;
    }

    fin.open(base.c_str(), ios::binary);
    if (!fin.good())
    {
        cerr<<"Cannot open Base File "<<base<<".";
        return 1;
    }

    finlog.open((diff+".difflog").c_str(), ios::binary);
    fincon.open((diff+".diff").c_str(), ios::binary);
    if (!finlog.good())
    {
        cerr<<"Cannot open Modified File "<<diff<<".";
        return 2;
    }

    fout.open(diff.c_str(), ios::binary);
    fin>>noskipws;
    finlog>>noskipws;
    fincon>>noskipws;
    cout<<"Patching...";
    while(finlog>>c)
    {
        pos = 0;
        pos |= c;
        pos <<= 8;
        finlog>>c;
        pos |= c;
        pos <<= 8;
        finlog>>c;
        pos |= c;
        pos <<= 8;
        finlog>>c;
        pos |= c;

        finlog>>c;
        len = 0;
        len |= c;
        len <<= 8;
        finlog>>c;
        len |= c;
        len <<= 8;
        finlog>>c;
        len |= c;
        len <<= 8;
        finlog>>c;
        len |= c;

        finlog>>type;

        /*cout<<hex<<"@ "<<pos<<" for "<<len<<" do ";
        switch(type)
        {
            case 0: cout<<"Replace"; break;
            case 1: cout<<"Delete"; break;
            case 2: cout<<"Add"; break;
        }
        cout<<endl<<"\t";*/

        while(ctr < pos)
        {
            fin>>c;
            fout<<c;
            ctr++;
        }

        if (type == 0)
        {
            for (int i = 0; i < len; i++)
            {
                fin>>c;
                fincon>>c;
                fout<<c;
                ctr++;
            }
        }
        else if (type == 1)
        {
            for (int i = 0; i < len; i++)
            {
                fin>>c;
                ctr++;
            }
        }
        else if (type == 2)
        {
            for (int i = 0; i < len; i++)
            {
                fincon>>c;
                fout<<c;
                ctr++;
            }
        }


        //cout<<"Done!\n";

    }

    while(fin>>c)
        fout<<c;

    cout<<"Done!"<<endl;
    cout<<"Seek output in "<<diff;




}
